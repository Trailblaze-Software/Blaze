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

  write_to_dxf(generate_contours(smooth_ground, config.contours), output_dir / "contours.dxf");
  // crt name must match dxf name
  write_to_crt(output_dir / "contours.crt");

  // VEGE
  

  GeoGrid<ClassCount> class_counts = count_height_classes(binned_points, smooth_ground);
  GeoGrid<double> canopy = canopy_proportion(class_counts);
  write_to_tif(canopy, output_dir / "canopy_proportion.tif");
  GeoGrid<double> canopy_thresh = threshold(canopy, 0.1);
  write_to_tif(canopy_thresh, output_dir / "canopy_thresh.tif");

  GeoGrid<double> low_pass_canopy = low_pass(canopy);
  write_to_tif(low_pass_canopy, output_dir / "low_pass_canopy.tif");
  write_to_tif(bool_grid(low_pass_canopy, 20.), output_dir / "bool_low_pass_canopy.tif");
  write_to_tif(vege_proportion(class_counts), output_dir / "vege_proportion.tif");
  write_to_tif(low_pass(canopy_thresh), output_dir / "low_pass_canopy_thresh.tif");
  GeoGrid<double> vegetation = vege_proportion(class_counts);
  GeoGrid<double> low_pass_vege = low_pass(vege_proportion(class_counts));
  write_to_tif(low_pass_vege, output_dir / "low_pass_vege.tif");
  write_to_tif_with_thresh(low_pass_vege, output_dir / "vege_proportion_thresh.tif", 0.01);

  GeoGrid<std::optional<std::byte>> naive_countours =
      GeoGrid<std::optional<std::byte>>(ground.width(), ground.height(), GeoTransform(ground.transform()),
                                        GeoProjection(ground.projection()));

  //double contour_interval = 2.5;
  //for (size_t i = 1; i < grid.height() - 1; i++) {
    //for (size_t j = 1; j < grid.width() - 1; j++) {
      //double z = grid[{i, j}];
      //double z_north = grid[{i - 1, j}];
      //double z_south = grid[{i + 1, j}];
      //double z_west = grid[{i, j - 1}];
      //double z_east = grid[{i, j + 1}];
      //bool is_countour = crosses_contour(z, z_north, contour_interval) ||
                         //crosses_contour(z, z_south, contour_interval) ||
                         //crosses_contour(z, z_west, contour_interval) ||
                         //crosses_contour(z, z_east, contour_interval);
      //naive_countours[{i, j}] = is_countour ? std::optional<std::byte>{std::byte{0}} : std::nullopt;
    //}
  //}
//
  //write_to_tif(naive_countours, output_dir / "naive_countours.tif");
  write_to_image_tif(hill_shade(smooth_ground), output_dir / "hill_shade_multi.tif");

  GeoGrid<CMYKColor> canopy_color(canopy.width(), canopy.height(), GeoTransform(canopy.transform()),
                                  GeoProjection(canopy.projection()));
  GeoGrid<RGBColor> building_color(canopy.width(), canopy.height(), GeoTransform(canopy.transform()),
                                  GeoProjection(canopy.projection()));
  for (size_t i = 0; i < canopy.height(); i++) {
    for (size_t j = 0; j < canopy.width(); j++) {
      //canopy_color[{j, i}] = canopy_thresh[{j, i}] > 0.1
                                 //? ISOMSymbol(ISOMSymbol::Forest).color()
                                 //: ISOMSymbol(ISOMSymbol::RoughOpenLand).color();
      //if (vegetation[{j, i}] > 0.15) {
        //canopy_color[{j, i}] = ISOMSymbol(ISOMSymbol::VegetationSlow).color();
      //}
      //if (vegetation[{j, i}] > 0.3) {
        //canopy_color[{j, i}] = ISOMSymbol(ISOMSymbol::VegetationWalk).color();
      //}
      //if (vegetation[{j, i}] > 0.6) {
        //canopy_color[{j, i}] = ISOMSymbol(ISOMSymbol::VegetationFight).color();
      //}
      //if (naive_countours[{j, i}].has_value()) {
        //canopy_color[{j, i}] = ISOMSymbol(ISOMSymbol::Contour).color();
      //}
      //if (buildings[{j, i}].has_value()) {
        //building_color[{j, i}] = ISOMSymbol(ISOMSymbol::Building).color().toRGB();
      //}
    }
  }
  write_to_tif(canopy_color, output_dir / "canopy_color.tif");
  write_to_image_tif(slope(smooth_ground), output_dir / "slope.tif");

  GeoImgGrid canopy_img(canopy_color);
  canopy_img.save_to(output_dir / "canopy_img.tif");


  au::QuantityD<au::Meters> render_pixel_resolution = config.render.scale / config.render.dpi;
  GeoImgGrid final_img(round_up(ground.width() * ground.transform().dx_m() / render_pixel_resolution), round_up(ground.height() * ground.transform().dy_m() / render_pixel_resolution),
      GeoTransform(canopy.transform().with_new_resolution(render_pixel_resolution)),
                       GeoProjection(canopy.projection()));
  final_img.draw(canopy_img);

  for (const Contour &contour : generate_contours(smooth_ground, config.contours)) {
    const ContourConfig &contour_config = config.contours.pick_from_height(contour.height());
    final_img.draw(contour, to_rgb(contour_config.color), contour_config.width *
        config.render.scale);
  }
  //final_img.draw(GeoImgGrid(building_color));
  final_img.save_to(output_dir / "final_img.tif");
}
