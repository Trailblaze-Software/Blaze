#include <filesystem>
#include <iostream>
#include <pdal/io/BufferReader.hpp>
#include <pdal/io/LasHeader.hpp>
#include <pdal/io/LasReader.hpp>
#include <pdal/pdal.hpp>
#include <opencv2/opencv.hpp>

#include "au/units/meters.hh"
#include "config_input/config_input.hpp"
#include "contour/contour_gen.hpp"
#include "dxf/dxf.hpp"
#include "grid/grid_ops.hpp"
#include "grid/img_grid.hpp"
#include "las/las_file.hpp"
#include "lib/grid/grid.hpp"
#include "lib/vegetation/vegetation.hpp"
#include "methods/hill_shade/hill_shade.hpp"
#include "tif/tif.hpp"

size_t round_up(double x) { return std::ceil(1e-8 + std::abs(x)); }

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: blaze <las_file>" << std::endl;
    return 1;
  }

  Config config = Config::FromFile("config.json");
  std::cout << config << std::endl;

  fs::path output_dir = "out";
  LASFile las_file = LASFile(argv[1]);
  output_dir = output_dir / argv[1];

  au::QuantityD<au::Meters> bin_resolution = config.grid.bin_resolution;
  GeoGrid<std::vector<LASPoint>> binned_points(
      round_up(las_file.width() / bin_resolution), round_up(las_file.height() / bin_resolution),
      GeoTransform(las_file.top_left(), bin_resolution.in(au::meters)),
      GeoProjection(las_file.projection()));

  {
    TimeFunction timer("binning points");
    for (const LASPoint &las_point : las_file) {
      binned_points[binned_points.transform().projection_to_pixel(las_point)].emplace_back(
          las_point);
    }
  }

  au::QuantityD<au::Meters> resolution = bin_resolution;
  GeoGrid<double> ground(round_up(las_file.width() / resolution),
                       round_up(las_file.height() / resolution),
                       GeoTransform(las_file.top_left(), resolution.in(au::meters)),
                       GeoProjection(las_file.projection()));

  GeoGrid<std::optional<std::byte>> buildings =
      GeoGrid<std::optional<std::byte>>(ground.width(), ground.height(), GeoTransform(ground.transform()),
                                        GeoProjection(ground.projection()));

  {
    TimeFunction timer("min finding");
#pragma omp parallel for
    for (size_t i = 0; i < binned_points.height(); i++) {
      for (size_t j = 0; j < binned_points.width(); j++) {
        bool is_building = false;
        double min = std::numeric_limits<unsigned int>::max();
        for (const LASPoint &las_point : binned_points[{j, i}]) {
          min = std::min(min, las_point.z());
          if (las_point.classification() == LASClassification::Building) {
            is_building = true;
          }
        }
        ground[{j, i}] = min;
        buildings[{j, i}] = is_building ? std::optional<std::byte>{std::byte{0}} : std::nullopt;
      }
    }
  }

  fs::create_directories(output_dir);

  ground = remove_outliers(ground, config.ground.outlier_removal_height_diff.in(au::meters));
  ground = interpolate_holes(ground);

  write_to_tif(ground, output_dir / "ground.tif");
  write_to_tif(buildings, output_dir / "buildings.tif");

  GeoGrid<double> smooth_ground = remove_outliers(downsample(ground, config.grid.downsample_factor));
  write_to_tif(smooth_ground, output_dir / "smooth_ground.tif");

  const std::vector<Contour> contours = generate_contours(smooth_ground, config.contours);
  write_to_dxf(contours, output_dir / "contours.dxf");
  // crt name must match dxf name
  write_to_crt(output_dir / "contours.crt");

  // VEGE
  std::map<std::string, GeoGrid<double>> vege_maps;
  for (const VegeHeightConfig& vege_config : config.vege.height_configs) {
    GeoGrid<std::optional<double>> blocked_proportion = get_blocked_proportion(binned_points, smooth_ground, vege_config);
    fs::create_directories(output_dir / "raw_vege");
    write_to_tif(blocked_proportion, output_dir / "raw_vege" / (vege_config.name + ".tif"));
    GeoGrid<double> smooth_blocked_proportion = low_pass(blocked_proportion, 3);
    vege_maps.emplace(vege_config.name, std::move(smooth_blocked_proportion));
  }

  write_to_image_tif(hill_shade(smooth_ground), output_dir / "hill_shade_multi.tif");

  GeoGrid<CMYKColor> vege_color(binned_points.width(), binned_points.height(), GeoTransform(binned_points.transform()),
                                  GeoProjection(binned_points.projection()));

  GeoGrid<RGBColor> building_color(buildings.width(), buildings.height(), GeoTransform(buildings.transform()),
                                  GeoProjection(buildings.projection()));


  for (size_t i = 0; i < vege_color.height(); i++) {
    for (size_t j = 0; j < vege_color.width(); j++) {
      vege_color[{j, i}] = to_cmyk(config.vege.background_color);
      if (buildings[{j, i}])
        building_color[{j, i}] = to_rgb(config.buildings.color);
    }
  }
  for (const VegeHeightConfig& vege_config : config.vege.height_configs) {
    for (size_t i = 0; i < vege_maps.at(vege_config.name).height(); i++) {
      for (size_t j = 0; j < vege_maps.at(vege_config.name).width(); j++) {
        std::optional<ColorVariant> color = vege_config.pick_from_blocked_proportion(vege_maps.at(vege_config.name)[{j, i}]);
        if (color) {
          vege_color[{j, i}] = to_cmyk(color.value());
        }
      }
    }
  }
  write_to_tif(vege_color, output_dir / "vege_color.tif");
  write_to_image_tif(slope(smooth_ground), output_dir / "slope.tif");

  au::QuantityD<au::Meters> render_pixel_resolution = config.render.scale / config.render.dpi;
  GeoImgGrid final_img(round_up(ground.width() * ground.transform().dx_m() / render_pixel_resolution), round_up(ground.height() * ground.transform().dy_m() / render_pixel_resolution),
      GeoTransform(vege_color.transform().with_new_resolution(render_pixel_resolution)),
                       GeoProjection(vege_color.projection()));

  final_img.draw(vege_color);

  for (const Contour &contour : contours) {
    const ContourConfig &contour_config = config.contours.pick_from_height(contour.height());
    RGBColor color = to_rgb(contour_config.color);
    final_img.draw(contour, color, contour_config.width *
        config.render.scale);
  }
  final_img.draw(GeoImgGrid(building_color));

  final_img.save_to(output_dir / "final_img.tif");
}
