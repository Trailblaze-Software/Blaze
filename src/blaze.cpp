#include <pdal/pdal.hpp>
#include <iostream>
#include <pdal/io/LasReader.hpp>
#include <pdal/io/LasHeader.hpp>
#include <pdal/io/BufferReader.hpp>

#include "contour/contour.hpp"
#include "dxf/dxf.hpp"
#include "grid/grid_ops.hpp"
#include "las/las_file.hpp"
#include  "lib/grid/grid.hpp"
#include "methods/hill_shade/hill_shade.hpp"
#include "tif/tif.hpp"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: blaze <las_file>" << std::endl;
    return 1;
  }

  write_to_dxf("output.dxf");

  LASFile las_file = LASFile(argv[1]);

  double bin_resolution = 0.4;
  GeoGrid<std::vector<LASPoint>> binned_points = GeoGrid<std::vector<LASPoint>>(std::ceil(las_file.width() / bin_resolution), std::ceil(las_file.height() / bin_resolution), GeoTransform(las_file.top_left(), bin_resolution), GeoProjection(las_file.projection()));

  for (const LASPoint& las_point : las_file) {
    Assert(std::abs(binned_points.transform().pixel_to_projection(binned_points.transform().projection_to_pixel(las_point)).x() - las_point.x()) < 1.1, "Pixel to projection to pixel");
    binned_points[binned_points.transform().projection_to_pixel(las_point)].emplace_back(las_point);
  }

  double resolution = 0.4;
  GeoGrid<double> grid = GeoGrid<double>(std::ceil(las_file.width() / resolution), std::ceil(las_file.height() / resolution), GeoTransform(las_file.top_left(), resolution), GeoProjection(las_file.projection()));

  GeoGrid<std::optional<std::byte>> buildings = GeoGrid<std::optional<std::byte>>(grid.width(), grid.height(), GeoTransform(grid.transform()), GeoProjection(grid.projection()));

  for (size_t i = 0; i < binned_points.height(); i++) {
    for (size_t j = 0; j < binned_points.width(); j++) {
        bool is_building = false;
        double min = std::numeric_limits<unsigned int>::max();
        for (const LASPoint& las_point : binned_points[{i, j}]) {
          min = std::min(min, las_point.z());
          if (las_point.classification() == LASClassification::Building) {
            is_building = true;
          }
        }
        grid[{i, j}] = min;
        buildings[{i, j}] = is_building ? std::optional<std::byte>{std::byte{0}} : std::nullopt;
      }
    }

  grid = remove_outliers(grid, 0.2);

  write_to_tif(grid, "grid.tif");
  write_to_tif(buildings, "buildings.tif");

  GeoGrid<double> smooth_grid = remove_outliers(downsample(grid, 3));
  write_to_tif(smooth_grid, "smooth_grid.tif");

  GridGraph is_contour = GridGraph<char>(smooth_grid); 
  for(size_t i = 0; i < smooth_grid.height(); i++) {
    for(size_t j = 0; j < smooth_grid.width(); j++) {
      Coordinate2D<size_t> coord = {j, i};
      for (Direction2D dir : {Direction2D::DOWN, Direction2D::RIGHT}) {
        LineCoord2D<size_t> line_coord = {coord, dir};
        if (is_contour.in_bounds(line_coord)) {
          is_contour[line_coord] = crosses_contour(smooth_grid[coord], smooth_grid[coord + dir], 2.5);
        }
      }
    }
  }

  std::vector<Contour> contours;
  for(size_t i = 0; i < smooth_grid.height(); i++) {
    for(size_t j = 0; j < smooth_grid.width(); j++) {
      for (Direction2D dir : {Direction2D::DOWN, Direction2D::RIGHT}) {
        LineCoord2D<size_t> line_coord = {i, j, dir};
        if (is_contour.in_bounds(line_coord) && is_contour[line_coord]) {
          contours.emplace_back(Contour::FromGridGraph(line_coord, smooth_grid, is_contour, 2.5));
          std::cout << contours.back() << std::endl;
        }
      }
    }
  }

  write_to_dxf(contours, "contours.dxf");

  exit(0);
  GeoGrid<std::optional<std::byte>> naive_countours = GeoGrid<std::optional<std::byte>>(grid.width(), grid.height(), GeoTransform(grid.transform()), GeoProjection(grid.projection()));

  double contour_interval = 2.5;
  for (size_t i = 1; i < grid.height() - 1; i++) {
    for (size_t j = 1; j < grid.width() - 1; j++) {
      double z = grid[{i, j}];
      double z_north = grid[{i - 1, j}];
      double z_south = grid[{i + 1, j}];
      double z_west = grid[{i, j - 1}];
      double z_east = grid[{i, j + 1}];
      bool is_countour = crosses_contour(z, z_north, contour_interval) || crosses_contour(z, z_south, contour_interval) || crosses_contour(z, z_west, contour_interval) || crosses_contour(z, z_east, contour_interval);
      naive_countours[{i, j}] = is_countour ? std::optional<std::byte>{std::byte{0}} : std::nullopt;
    }
  }

  write_to_tif(naive_countours, "naive_countours.tif");
  write_to_image_tif(hill_shade(smooth_grid), "hill_shade_multi.tif");
  write_to_image_tif(slope(smooth_grid), "slope.tif");
}
