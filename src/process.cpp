#include "process.hpp"

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
#include "printing/to_string.hpp"
#include "tif/tif.hpp"
#include "utilities/progress_tracker.hpp"

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

GeoGrid<double> adjust_ground_to_slope(const GeoGrid<double>& grid, double original_resolution) {
  GeoGrid<double> result(grid.width(), grid.height(), GeoTransform(grid.transform()),
                         GeoProjection(grid.projection()));

  result.copy_from(grid);
  for (size_t i = 1; i < grid.height() - 1; i++) {
    for (size_t j = 1; j < grid.width() - 1; j++) {
      double dz_dy = (grid[{j + 1, i}] - grid[{j - 1, i}]) / (2 * grid.dx());
      double dz_dx = (grid[{j, i + 1}] - grid[{j, i - 1}]) / (2 * grid.dy());
      result[{j, i}] =
          grid[{j, i}] + 0.5 * (std::abs(dz_dx) + std::abs(dz_dy)) * original_resolution;
    }
  }
  return result;
}

void process_las_file(const fs::path& las_filename, const Config& config,
                      ProgressTracker progress_tracker) {
  TimeFunction outer_timer("processing LAS file " + las_filename.string(), &progress_tracker);
  fs::path output_dir = config.output_path() / las_filename.stem();
  fs::create_directories(output_dir);

  LASFile las_file = LASFile::with_border(las_filename, config.border_width,
                                          progress_tracker.subtracker(0.0, 0.4));

  double bin_resolution = config.grid.bin_resolution;
  GeoGrid<std::vector<LASPoint>> binned_points(
      round_up(las_file.width() / bin_resolution + config.grid.downsample_factor),
      round_up(las_file.height() / bin_resolution + config.grid.downsample_factor),
      GeoTransform(las_file.top_left().round_NW(bin_resolution * config.grid.downsample_factor),
                   bin_resolution),
      GeoProjection(las_file.projection()));

  {
    TimeFunction timer("binning points", &progress_tracker);
    for (const LASPoint& las_point : las_file) {
      binned_points[binned_points.transform().projection_to_pixel(las_point)].emplace_back(
          las_point);
    }
  }
  progress_tracker.set_proportion(0.5);

  GeoGrid<std::optional<LASPoint>> ground_points(binned_points.width(), binned_points.height(),
                                                 GeoTransform(binned_points.transform()),
                                                 GeoProjection(las_file.projection()));

  GeoGrid<std::optional<std::byte>> buildings = GeoGrid<std::optional<std::byte>>(
      ground_points.width(), ground_points.height(), GeoTransform(ground_points.transform()),
      GeoProjection(ground_points.projection()));

  GeoGrid<RGBColor> ground_intensity_img(ground_points.width(), ground_points.height(),
                                         GeoTransform(ground_points.transform()),
                                         GeoProjection(las_file.projection()));

  GeoGrid<std::optional<std::byte>> water = GeoGrid<std::optional<std::byte>>(
      ground_points.width(), ground_points.height(), GeoTransform(ground_points.transform()),
      GeoProjection(ground_points.projection()));

  {
    bool only_classified_ground = true;
    LASFile ground_points_las =
        LASFile(*ground_points.extent(), GeoProjection(ground_points.projection()));
    TimeFunction timer("min finding", &progress_tracker);
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
            u_char intensity = std::clamp(
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
    if (OUT_LAS)
      ground_points_las.write(output_dir / "ground_points_mins.las",
                              progress_tracker.subtracker(0.59, 0.6));
  }
  progress_tracker.set_proportion(0.6);

  GeoGrid<double> ground = get_pixel_heights(ground_points);

  write_to_tif(ground_intensity_img.slice(las_file.export_bounds()),
               output_dir / "ground_intensity.tif", progress_tracker.subtracker(0.62, 0.63));

  ground = remove_outliers(ground, progress_tracker.subtracker(0.63, 0.64),
                           config.ground.outlier_removal_height_diff);
  ground = interpolate_holes(ground, progress_tracker.subtracker(0.64, 0.65));

  write_to_tif(ground.slice(las_file.export_bounds()), output_dir / "ground.tif",
               progress_tracker.subtracker(0.65, 0.66));
  write_to_tif(buildings.slice(las_file.export_bounds()), output_dir / "buildings.tif",
               progress_tracker.subtracker(0.66, 0.67));
  write_to_tif(water.slice(las_file.export_bounds()), output_dir / "water.tif",
               progress_tracker.subtracker(0.67, 0.68));

  if (OUT_LAS)
    LASFile(ground).write(output_dir / "ground.las", progress_tracker.subtracker(0.68, 0.69));

  std::unique_ptr<GeoGrid<double>> downsampled_ground = std::make_unique<GeoGrid<double>>(
      downsample(ground, config.grid.downsample_factor, progress_tracker.subtracker(0.69, 0.7)));
  GeoGrid<double> smooth_ground =
      remove_outliers(*downsampled_ground, progress_tracker.subtracker(0.7, 0.71),
                      config.ground.outlier_removal_height_diff * config.grid.downsample_factor);
  if (OUT_LAS)
    LASFile(*downsampled_ground).write(output_dir / "smooth_ground_no_outlier_removal.las");
  downsampled_ground.reset();

  write_to_tif(smooth_ground.slice(las_file.export_bounds()), output_dir / "smooth_ground.tif",
               progress_tracker.subtracker(0.72, 0.73));

  if (OUT_LAS)
    LASFile(smooth_ground)
        .write(output_dir.parent_path() / "smooth_ground.las",
               progress_tracker.subtracker(0.73, 0.74));

  {
    GeoGrid<double> slope_grid = slope(smooth_ground);
    write_to_image_tif(slope_grid.slice(las_file.export_bounds()), output_dir / "slope.tif",
                       progress_tracker.subtracker(0.74, 0.75));
  }

  smooth_ground = adjust_ground_to_slope(smooth_ground, ground.dx());
  if (OUT_LAS) LASFile(smooth_ground).write(output_dir / "smooth_ground.las");

  const std::vector<Contour> contours =
      generate_contours(smooth_ground, config.contours, progress_tracker.subtracker(0.75, 0.76));

  std::vector<Stream> stream_path =
      stream_paths(smooth_ground, config.water, progress_tracker.subtracker(0.76, 0.77));

  std::vector<Coordinate2D<size_t>> sinks = identify_sinks(smooth_ground);
  GeoGrid<double> filled = fill_depressions(smooth_ground, sinks);
  write_to_tif(filled.slice(las_file.export_bounds()), output_dir / "filled_dem.tif");

  double contour_points_resolution = 20;
  GeoGrid<std::vector<std::shared_ptr<ContourPoint>>> contour_points(
      round_up(smooth_ground.width_m() / contour_points_resolution) + 1,
      round_up(smooth_ground.height_m() / contour_points_resolution) + 1,
      GeoTransform(smooth_ground.transform().pixel_to_projection({0, 0}),
                   contour_points_resolution),
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

  progress_tracker.set_proportion(0.78);

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

  constexpr double INCHES_PER_METER = 39.3701;
  double render_pixel_resolution = config.render.scale / config.render.dpi / INCHES_PER_METER;
  GeoImgGrid final_img(
      round_up(ground.width() * ground.transform().dx() / render_pixel_resolution),
      round_up(ground.height() * ground.transform().dy() / render_pixel_resolution),
      GeoTransform(vege_color.transform().with_new_resolution(render_pixel_resolution)),
      GeoProjection(vege_color.projection()));

  {
    TimeFunction timer("drawing vege", &progress_tracker);
    final_img.draw(GeoImgGrid(vege_color));
  }

  progress_tracker.set_proportion(0.8);
  {
    TimeFunction timer("drawing stuff", &progress_tracker);
    final_img.draw(GeoImgGrid(water_color));
  }

  {
    TimeFunction timer("drawing contours", &progress_tracker);
    for (const Contour& contour : contours) {
      if (config.contours.layer_name_from_height(contour.height()) == "Contour") continue;
      const ContourConfig& contour_config = config.contours.pick_from_height(contour.height());
      RGBColor color = to_rgb(contour_config.color);
      final_img.draw(contour, color, contour_config.width / 1000 * config.render.scale);
    }
  }

  {
    TimeFunction timer("drawing paths", &progress_tracker);
    for (const Stream& stream : stream_path) {
      const WaterConfig& water_config = config.water.config_from_catchment(stream.catchment);
      final_img.draw(stream.coords, water_config.color,
                     water_config.width / 1000 * config.render.scale);
    }
  }

  {
    TimeFunction timer("drawing stuff", &progress_tracker);
    final_img.draw(GeoImgGrid(building_color));
  }

  final_img.save_to(output_dir / "final_img.tif", las_file.export_bounds());

  progress_tracker.set_proportion(0.9);

  for (const Contour& contour : contours) {
    if (config.contours.layer_name_from_height(contour.height()) != "Contour") continue;
    const ContourConfig& contour_config = config.contours.pick_from_height(contour.height());
    RGBColor color = to_rgb(contour_config.color);
    final_img.draw(contour, color, contour_config.width / 1000 * config.render.scale);
  }

  {
    TimeFunction timer("drawing paths", &progress_tracker);
    for (const Stream& stream : stream_path) {
      const WaterConfig& water_config = config.water.config_from_catchment(stream.catchment);
      final_img.draw(stream.coords, water_config.color,
                     water_config.width / 1000 * config.render.scale);
    }
  }

  final_img.draw(GeoImgGrid(building_color));

  for (const std::shared_ptr<ContourPoint>& point : all_contour_points) {
    if (point->slope() > 0.8) {
      final_img.draw_point(*point, RGBColor(0, 0, 0), 1.5);
    }
  }

  final_img.save_to(output_dir / "final_img_extra_contours.tif", las_file.export_bounds());
}
