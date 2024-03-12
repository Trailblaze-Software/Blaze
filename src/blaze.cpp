#include <iostream>
#include <pdal/io/BufferReader.hpp>
#include <pdal/io/LasHeader.hpp>
#include <pdal/io/LasReader.hpp>
#include <pdal/pdal.hpp>

#include "contour/contour.hpp"
#include "contour/contour_gen.hpp"
#include "dxf/dxf.hpp"
#include "grid/grid_ops.hpp"
#include "las/las_file.hpp"
#include "lib/grid/grid.hpp"
#include "lib/vegetation/vegetation.hpp"
#include "methods/hill_shade/hill_shade.hpp"
#include "tif/tif.hpp"
#include "isom/symbols.hpp"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: blaze <las_file>" << std::endl;
    return 1;
  }

  LASFile las_file = LASFile(argv[1]);

  double bin_resolution = 0.5;
  GeoGrid<std::vector<LASPoint>> binned_points(
      std::ceil(las_file.width() / bin_resolution), std::ceil(las_file.height() / bin_resolution),
      GeoTransform(las_file.top_left(), bin_resolution), GeoProjection(las_file.projection()));

  {
    TimeFunction timer("binning");
    for (const LASPoint &las_point : las_file) {
      binned_points[binned_points.transform().projection_to_pixel(las_point)].emplace_back(
          las_point);
    }
  }

  double resolution = bin_resolution;
  GeoGrid<double> grid(
      std::ceil(las_file.width() / resolution), std::ceil(las_file.height() / resolution),
      GeoTransform(las_file.top_left(), resolution), GeoProjection(las_file.projection()));

  GeoGrid<std::optional<std::byte>> buildings =
      GeoGrid<std::optional<std::byte>>(grid.width(), grid.height(), GeoTransform(grid.transform()),
                                        GeoProjection(grid.projection()));

  {
    TimeFunction timer("min finding");
#pragma omp parallel for
    for (size_t i = 0; i < binned_points.height(); i++) {
      for (size_t j = 0; j < binned_points.width(); j++) {
        bool is_building = false;
        double min = std::numeric_limits<unsigned int>::max();
        for (const LASPoint &las_point : binned_points[{i, j}]) {
          min = std::min(min, las_point.z());
          if (las_point.classification() == LASClassification::Building) {
            is_building = true;
          }
        }
        grid[{i, j}] = min;
        buildings[{i, j}] = is_building ? std::optional<std::byte>{std::byte{0}} : std::nullopt;
      }
    }
  }

  grid = remove_outliers(grid, 0.2);
  grid = interpolate_holes(grid);

  write_to_tif(grid, "grid.tif");
  write_to_tif(buildings, "buildings.tif");

  GeoGrid<double> smooth_grid = remove_outliers(downsample(grid, 3));
  write_to_tif(smooth_grid, "smooth_grid.tif");

  write_to_dxf(generate_contours(smooth_grid, 2.5), "contours.dxf");
  // crt name must match dxf name... I can't work out string variables yet lol
  write_to_crt("contours.crt");

  GeoGrid<ClassCount> class_counts = count_height_classes(binned_points, smooth_grid);
  GeoGrid<double> canopy = canopy_proportion(class_counts);
  write_to_tif(canopy, "canopy_proportion.tif");
  GeoGrid<double> canopy_thresh = threshold(canopy, 0.1);
  write_to_tif(canopy_thresh, "canopy_thresh.tif");



  GeoGrid<double> low_pass_canopy = low_pass(canopy);
  write_to_tif(low_pass_canopy, "low_pass_canopy.tif");
  write_to_tif(bool_grid(low_pass_canopy, 20.), "bool_low_pass_canopy.tif");
  write_to_tif(vege_proportion(class_counts), "vege_proportion.tif");
  write_to_tif(low_pass(canopy_thresh), "low_pass_canopy_thresh.tif");
  GeoGrid<double> vegetation = vege_proportion(class_counts);
  GeoGrid<double> low_pass_vege = low_pass(vege_proportion(class_counts));
  write_to_tif(low_pass_vege, "low_pass_vege.tif");
  write_to_tif_with_thresh(low_pass_vege, "vege_proportion_thresh.tif", 0.01);

  GeoGrid<std::optional<std::byte>> naive_countours =
      GeoGrid<std::optional<std::byte>>(grid.width(), grid.height(), GeoTransform(grid.transform()),
                                        GeoProjection(grid.projection()));

  double contour_interval = 2.5;
  for (size_t i = 1; i < grid.height() - 1; i++) {
    for (size_t j = 1; j < grid.width() - 1; j++) {
      double z = grid[{i, j}];
      double z_north = grid[{i - 1, j}];
      double z_south = grid[{i + 1, j}];
      double z_west = grid[{i, j - 1}];
      double z_east = grid[{i, j + 1}];
      bool is_countour = crosses_contour(z, z_north, contour_interval) ||
                         crosses_contour(z, z_south, contour_interval) ||
                         crosses_contour(z, z_west, contour_interval) ||
                         crosses_contour(z, z_east, contour_interval);
      naive_countours[{i, j}] = is_countour ? std::optional<std::byte>{std::byte{0}} : std::nullopt;
    }
  }

  write_to_tif(naive_countours, "naive_countours.tif");
  write_to_image_tif(hill_shade(smooth_grid), "hill_shade_multi.tif");

   GeoGrid<CMYKColor> canopy_color(
      canopy.width(), canopy.height(), GeoTransform(canopy.transform()), GeoProjection(canopy.projection()));
  for (size_t i = 0; i < canopy.height(); i++) {
    for (size_t j = 0; j < canopy.width(); j++) {
      canopy_color[{j, i}] = canopy_thresh[{j, i}] > 0.1 ? ISOMSymbol(ISOMSymbol::Forest).color() : ISOMSymbol(ISOMSymbol::RoughOpenLand).color();
      if (vegetation[{j, i}] > 0.05) {
        canopy_color[{j, i}] = ISOMSymbol(ISOMSymbol::VegetationSlow).color();
      }
      if (vegetation[{j, i}] > 0.3) {
        canopy_color[{j, i}] = ISOMSymbol(ISOMSymbol::VegetationWalk).color();
      }
      if (vegetation[{j, i}] > 0.6) {
        canopy_color[{j, i}] = ISOMSymbol(ISOMSymbol::VegetationFight).color();
      }
      if (naive_countours[{j, i}].has_value()) {
        canopy_color[{j, i}] = ISOMSymbol(ISOMSymbol::Contour).color();
      }
      if (buildings[{j, i}].has_value()) {
        canopy_color[{j, i}] = ISOMSymbol(ISOMSymbol::Building).color();
      }
    }
  }
  write_to_tif(canopy_color, "canopy_color.tif"); write_to_image_tif(slope(smooth_grid), "slope.tif");
}
