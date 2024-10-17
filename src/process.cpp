#include "process.hpp"

#include "au/quantity.hh"
#include "au/units/meters.hh"
#include "cliff/cliff.hpp"
#include "contour/contour_gen.hpp"
#include "dxf/dxf.hpp"
#include "grid/grid_ops.hpp"
#include "grid/img_grid.hpp"
#include "isom/colors.hpp"
#include "las/las_file.hpp"
#include "las/las_point.hpp"
#include "lib/grid/grid.hpp"
#include "lib/vegetation/vegetation.hpp"
#include "methods/hill_shade/hill_shade.hpp"
#include "methods/water/water.hpp"
#include "tif/tif.hpp"

constexpr bool OUT_LAS = false;

size_t round_up(double x) { return std::ceil(1e-8 + std::abs(x)); }

enum class GroundMethod { LOWER_BOUND, LOWEST_POINT, INTERPOLATE };

GeoGrid<double> get_pixel_heights(const GeoGrid<std::optional<LASPoint>>& ground_points,
                                  GroundMethod method = GroundMethod::LOWEST_POINT) {
  GeoGrid<double> ground(ground_points.width(), ground_points.height(),
                         GeoTransform(ground_points.transform()),
                         GeoProjection(ground_points.projection()));
#pragma omp parallel for
  for (size_t i = 0; i < ground.height(); i++) {
    for (size_t j = 0; j < ground.width(); j++) {
      if (ground_points[{j, i}]) {
        if (method == GroundMethod::LOWEST_POINT) {
          ground[{j, i}] = ground_points[{j, i}]->z();
        } else {
          Fail("Not implemented");
        }
      } else {
        ground[{j, i}] = std::numeric_limits<double>::max();
      }
    }
  }
  return ground;
}

GeoGrid<double> adjust_ground_to_slope(const GeoGrid<double>& grid,
                                       au::QuantityD<au::Meters> original_resolution) {
  GeoGrid<double> result(grid.width(), grid.height(), GeoTransform(grid.transform()),
                         GeoProjection(grid.projection()));

  result.copy_from(grid);
  for (size_t i = 1; i < grid.height() - 1; i++) {
    for (size_t j = 1; j < grid.width() - 1; j++) {
      double dz_dy = (grid[{j + 1, i}] - grid[{j - 1, i}]) / (2 * grid.dx());
      double dz_dx = (grid[{j, i + 1}] - grid[{j, i - 1}]) / (2 * grid.dy());
      result[{j, i}] = grid[{j, i}] + 0.5 * (std::abs(dz_dx) + std::abs(dz_dy)) *
                                          original_resolution.in(au::meters);
    }
  }
  return result;
}

void process_las_file(const fs::path& las_filename, const Config& config) {
  TimeFunction timer("processing LAS file " + las_filename.string());
  fs::path output_dir = config.output_directory;
  for (std::string s : las_filename) {
    if (s != "/") output_dir /= s;
  }
  fs::create_directories(output_dir);

  LASFile las_file = LASFile::with_border(las_filename, config.border_width.in(au::meters));

  au::QuantityD<au::Meters> bin_resolution = config.grid.bin_resolution;
  GeoGrid<std::vector<LASPoint>> binned_points(
      round_up(las_file.width() / bin_resolution), round_up(las_file.height() / bin_resolution),
      GeoTransform(las_file.top_left(), bin_resolution.in(au::meters)),
      GeoProjection(las_file.projection()));

  {
    TimeFunction timer("binning points");
    for (const LASPoint& las_point : las_file) {
      binned_points[binned_points.transform().projection_to_pixel(las_point)].emplace_back(
          las_point);
    }
  }

  au::QuantityD<au::Meters> resolution = bin_resolution;
  GeoGrid<std::optional<LASPoint>> ground_points(
      round_up(las_file.width() / resolution), round_up(las_file.height() / resolution),
      GeoTransform(las_file.top_left(), resolution.in(au::meters)),
      GeoProjection(las_file.projection()));

  GeoGrid<std::optional<std::byte>> buildings = GeoGrid<std::optional<std::byte>>(
      ground_points.width(), ground_points.height(), GeoTransform(ground_points.transform()),
      GeoProjection(ground_points.projection()));

  GeoGrid<RGBColor> ground_intensity_img(
      round_up(las_file.width() / resolution), round_up(las_file.height() / resolution),
      GeoTransform(las_file.top_left(), resolution.in(au::meters)),
      GeoProjection(las_file.projection()));

  GeoGrid<std::optional<std::byte>> water = GeoGrid<std::optional<std::byte>>(
      ground_points.width(), ground_points.height(), GeoTransform(ground_points.transform()),
      GeoProjection(ground_points.projection()));

  {
    bool only_classified_ground = true;
    LASFile ground_points_las =
        LASFile(ground_points.extent(), GeoProjection(ground_points.projection()));
    TimeFunction timer("min finding");
#pragma omp parallel for
    for (size_t i = 0; i < binned_points.height(); i++) {
      for (size_t j = 0; j < binned_points.width(); j++) {
        bool is_building = false;
        bool is_water = false;
        double min = std::numeric_limits<unsigned int>::max();
        std::optional<LASPoint> min_point = std::nullopt;
        for (const LASPoint& las_point : binned_points[{j, i}]) {
          if (las_point.z() < min && (las_point.classification() == LASClassification::Ground ||
                                      !only_classified_ground)) {
            min = las_point.z();
            min_point = las_point;
            uchar intensity = std::clamp(
                (double)(las_point.intensity() - config.ground.min_ground_intensity) /
                    (config.ground.max_ground_intensity - config.ground.min_ground_intensity) *
                    255.0,
                0.0, 255.0);
            ground_intensity_img[{j, i}] = RGBColor(intensity, intensity, intensity);
          }
          if (las_point.classification() == LASClassification::Building) {
            is_building = true;
          } else if (las_point.classification() == LASClassification::Water) {
            is_water = true;
          }
        }
        ground_points[{j, i}] = min_point;
        if (min_point) {
#pragma omp critical
          ground_points_las.insert(min_point.value());
        }
        buildings[{j, i}] = is_building ? std::optional<std::byte>{std::byte{0}} : std::nullopt;
        water[{j, i}] = is_water ? std::optional<std::byte>{std::byte{0}} : std::nullopt;
      }
    }
    if (OUT_LAS) ground_points_las.write(output_dir / "ground_points_mins.las");
  }

  GeoGrid<double> ground = get_pixel_heights(ground_points);

  write_to_tif(ground_intensity_img.slice(las_file.export_bounds()),
               output_dir / "ground_intensity.tif");

  ground = remove_outliers(ground, config.ground.outlier_removal_height_diff.in(au::meters));
  ground = interpolate_holes(ground);

  write_to_tif(ground.slice(las_file.export_bounds()), output_dir / "ground.tif");
  write_to_tif(buildings.slice(las_file.export_bounds()), output_dir / "buildings.tif");
  write_to_tif(water.slice(las_file.export_bounds()), output_dir / "water.tif");

  if (OUT_LAS) LASFile(ground).write(output_dir / "ground.las");

  GeoGrid<double> smooth_ground = remove_outliers(
      downsample(ground, config.grid.downsample_factor),
      config.ground.outlier_removal_height_diff.in(au::meters)*config.grid.downsample_factor);
  if (OUT_LAS)
    LASFile(downsample(ground, config.grid.downsample_factor))
        .write(output_dir / "smooth_ground_no_outlier_removal.las");
  write_to_tif(smooth_ground.slice(las_file.export_bounds()), output_dir / "smooth_ground.tif");

  if (OUT_LAS) LASFile(smooth_ground).write(output_dir.parent_path() / "smooth_ground.las");

  {
    GeoGrid<double> slope_grid = slope(smooth_ground);
    write_to_image_tif(slope_grid.slice(las_file.export_bounds()), output_dir / "slope.tif");
  }

  smooth_ground = adjust_ground_to_slope(smooth_ground, au::meters(ground.dx()));
  if (OUT_LAS) LASFile(smooth_ground).write(output_dir / "smooth_ground.las");

  const std::vector<Contour> contours = generate_contours(smooth_ground, config.contours);

  std::vector<std::vector<Coordinate2D<double>>> stream_path =
      stream_paths(smooth_ground, config.water);

  au::QuantityD<au::Meters> contour_points_resolution = au::meters(20);
  GeoGrid<std::vector<std::shared_ptr<ContourPoint>>> contour_points(
      round_up(las_file.width() / contour_points_resolution) + 1,
      round_up(las_file.height() / contour_points_resolution) + 1,
      GeoTransform(las_file.top_left(), contour_points_resolution.in(au::meters)),
      GeoProjection(las_file.projection()));

  std::vector<std::shared_ptr<ContourPoint>> all_contour_points;

  for (const Contour& contour : contours) {
    std::shared_ptr<ContourPoint> last_point = nullptr;
    for (size_t i = 0; i < contour.points().size(); i++) {
      const Coordinate2D<double>& point = contour.points().at(i);
      std::shared_ptr<ContourPoint> contour_point =
          std::make_shared<ContourPoint>(point.x(), point.y(), contour.height());
      if (i > 0) {
        contour_point->set_previous(last_point);
        last_point->set_next(contour_point);
      }
      contour_points[contour_points.transform().projection_to_pixel(point)].emplace_back(
          contour_point);
      all_contour_points.emplace_back(contour_point);
      last_point = contour_point;
    }
  }

#pragma omp parallel for
  for (size_t i = 0; i < contour_points.height(); i++) {
    for (size_t j = 0; j < contour_points.width(); j++) {
      std::vector<std::shared_ptr<ContourPoint>>& points = contour_points[{j, i}];
      for (std::shared_ptr<ContourPoint>& point : points) {
        point->find_up_down(contour_points);
      }
    }
  }

  const std::vector<Contour> trimmed_contours = trim_contours(contours, las_file.original_bounds());
  write_to_dxf(contours, output_dir / "contours.dxf", config.contours);

  write_to_dxf(trimmed_contours, output_dir / "trimmed_contours.dxf", config.contours);
  // crt name must match dxf name
  write_to_crt(output_dir / "contours.crt");

  write_to_dxf(stream_path, output_dir / "streams.dxf", "streams");

  // VEGE
  std::map<std::string, GeoGrid<double>> vege_maps;
  for (const VegeHeightConfig& vege_config : config.vege.height_configs) {
    GeoGrid<std::optional<double>> blocked_proportion =
        get_blocked_proportion(binned_points, smooth_ground, vege_config);
    fs::create_directories(output_dir / "raw_vege");
    write_to_tif(blocked_proportion.slice(las_file.export_bounds()),
                 output_dir / "raw_vege" / (vege_config.name + ".tif"));
    GeoGrid<double> smooth_blocked_proportion = low_pass(blocked_proportion, 2);
    vege_maps.emplace(vege_config.name, std::move(smooth_blocked_proportion));
  }

  write_to_image_tif(hill_shade(smooth_ground).slice(las_file.export_bounds()),
                     output_dir / "hill_shade_multi.tif");

  GeoGrid<CMYKColor> vege_color(binned_points.width(), binned_points.height(),
                                GeoTransform(binned_points.transform()),
                                GeoProjection(binned_points.projection()));

  GeoGrid<RGBColor> building_color(buildings.width(), buildings.height(),
                                   GeoTransform(buildings.transform()),
                                   GeoProjection(buildings.projection()));
  GeoGrid<RGBColor> water_color(water.width(), water.height(), GeoTransform(water.transform()),
                                GeoProjection(water.projection()));

#pragma omp parallel for
  for (size_t i = 0; i < vege_color.height(); i++) {
    for (size_t j = 0; j < vege_color.width(); j++) {
      vege_color[{j, i}] = to_cmyk(config.vege.background_color);
      if (buildings[{j, i}]) building_color[{j, i}] = to_rgb(config.buildings.color);
      if (water[{j, i}]) water_color[{j, i}] = to_rgb(CMYKColor(100, 0, 0, 0));
    }
  }
  for (const VegeHeightConfig& vege_config : config.vege.height_configs) {
#pragma omp parallel for
    for (size_t i = 0; i < vege_maps.at(vege_config.name).height(); i++) {
      for (size_t j = 0; j < vege_maps.at(vege_config.name).width(); j++) {
        std::optional<ColorVariant> color =
            vege_config.pick_from_blocked_proportion(vege_maps.at(vege_config.name)[{j, i}]);
        if (color) {
          vege_color[{j, i}] = to_cmyk(color.value());
        }
      }
    }
  }
  write_to_tif(vege_color.slice(las_file.export_bounds()), output_dir / "vege_color.tif");

  au::QuantityD<au::Meters> render_pixel_resolution = config.render.scale / config.render.dpi;
  GeoImgGrid final_img(
      round_up(ground.width() * ground.transform().dx_m() / render_pixel_resolution),
      round_up(ground.height() * ground.transform().dy_m() / render_pixel_resolution),
      GeoTransform(vege_color.transform().with_new_resolution(render_pixel_resolution)),
      GeoProjection(vege_color.projection()));

  {
    TimeFunction timer("drawing vege");
    final_img.draw(vege_color);
  }

  {
    TimeFunction timer("drawing stuff");
    final_img.draw(GeoImgGrid(water_color));
  }

  {
    TimeFunction timer("drawing contours");
    for (const Contour& contour : contours) {
      if (config.contours.layer_name_from_height(contour.height()) == "Contour") continue;
      const ContourConfig& contour_config = config.contours.pick_from_height(contour.height());
      RGBColor color = to_rgb(contour_config.color);
      final_img.draw(contour, color, contour_config.width * config.render.scale);
    }
  }

  {
    TimeFunction timer("drawing paths");
    for (const std::vector<Coordinate2D<double>>& path : stream_path) {
      final_img.draw(path, config.water.configs.at("small").color,
                     config.water.configs.at("small").width * config.render.scale);
    }
  }

  {
    TimeFunction timer("drawing stuff");
    final_img.draw(GeoImgGrid(building_color));
  }

  final_img.save_to(output_dir / "final_img.tif", las_file.export_bounds());

  for (const Contour& contour : contours) {
    if (config.contours.layer_name_from_height(contour.height()) != "Contour") continue;
    const ContourConfig& contour_config = config.contours.pick_from_height(contour.height());
    RGBColor color = to_rgb(contour_config.color);
    final_img.draw(contour, color, contour_config.width * config.render.scale);
  }

  {
    TimeFunction timer("drawing paths");
    for (const std::vector<Coordinate2D<double>>& path : stream_path) {
      final_img.draw(path, config.water.configs.at("small").color,
                     config.water.configs.at("small").width * config.render.scale);
    }
  }

  final_img.draw(GeoImgGrid(building_color));

  for (const std::shared_ptr<ContourPoint>& point : all_contour_points) {
    if (point->slope() > 0.8) {
      final_img.draw_point(*point, RGBColor(0, 0, 0), au::meters(1.5));
    }
  }

  final_img.save_to(output_dir / "final_img_extra_contours.tif", las_file.export_bounds());
}
