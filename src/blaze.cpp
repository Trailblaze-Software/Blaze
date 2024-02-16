#include <pdal/pdal.hpp>
#include <iostream>
#include <pdal/io/LasReader.hpp>
#include <pdal/io/LasHeader.hpp>
#include <pdal/io/BufferReader.hpp>

#include "las/las_file.hpp"
#include  "lib/utilities/grid.hpp"
#include "tif/tif.hpp"

bool crosses_contour(double h1, double h2, double contour_interval) {
  return h1 - fmod(h1, contour_interval) > h2 || h2 - fmod(h2, contour_interval) > h1;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: blaze <las_file>" << std::endl;
    return 1;
  }

  LASFile las_file = LASFile(argv[1]);

  double bin_resolution = 0.4;
  GeoGrid<std::vector<LASPoint>> binned_points = GeoGrid<std::vector<LASPoint>>(std::ceil(las_file.width() / bin_resolution), std::ceil(las_file.height() / bin_resolution), GeoTransform(las_file.top_left(), bin_resolution), GeoProjection(las_file.projection()));

  for (const LASPoint& las_point : las_file) {
    Assert(std::abs(binned_points.transform().pixel_to_projection(binned_points.transform().projection_to_pixel(las_point)).x() - las_point.x()) < 1.1, "Pixel to projection to pixel");
    binned_points[binned_points.transform().projection_to_pixel(las_point)].emplace_back(las_point);
  }

  double resolution = 0.4;
  GeoGrid<double> grid = GeoGrid<double>(std::ceil(las_file.width() / resolution), std::ceil(las_file.height() / resolution), GeoTransform(las_file.top_left(), resolution), GeoProjection(las_file.projection()));

  for (size_t i = 0; i < binned_points.height(); i++) {
    for (size_t j = 0; j < binned_points.width(); j++) {
        double min = std::numeric_limits<unsigned int>::max();
        for (const LASPoint& las_point : binned_points[{i, j}]) {
          min = std::min(min, las_point.z());
        }
        grid[{i, j}] = min;
      }
    }

  write_to_tif(grid, "grid.tif");

  GeoGrid<std::byte> naive_countours = GeoGrid<std::byte>(grid.width(), grid.height(), GeoTransform(grid.transform()), GeoProjection(grid.projection()));

  double contour_interval = 2.5;
  for (size_t i = 1; i < grid.height() - 1; i++) {
    for (size_t j = 1; j < grid.width() - 1; j++) {
      double z = grid[{i, j}];
      double z_north = grid[{i - 1, j}];
      double z_south = grid[{i + 1, j}];
      double z_west = grid[{i, j - 1}];
      double z_east = grid[{i, j + 1}];
      bool is_countour = crosses_contour(z, z_north, contour_interval) || crosses_contour(z, z_south, contour_interval) || crosses_contour(z, z_west, contour_interval) || crosses_contour(z, z_east, contour_interval);
      naive_countours[{i, j}] = is_countour ? std::byte(0) : std::byte(255);
    }
  }
  write_to_tif(naive_countours, "naive_countours.tif");
}
