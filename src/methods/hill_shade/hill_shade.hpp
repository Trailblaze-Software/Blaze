#pragma once

#include <cmath>
#include <numbers>

#include "grid/grid.hpp"
#include "utilities/timer.hpp"

#define DEG2RAD(x) ((x) * std::numbers::pi / 180)
#define SQ(x) ((x) * (x))

template <typename T>
GeoGrid<double> hill_shade(const GeoGrid<T> &grid, double azimuth = 315, double altitude = 45,
                           bool multidirectional = true) {
  TimeFunction timer("hill shade");
  GeoGrid<double> result(grid.width(), grid.height(), GeoTransform(grid.transform()),
                         GeoProjection(grid.projection()));
  for (size_t i = 1; i < grid.height() - 1; i++) {
    for (size_t j = 1; j < grid.width() - 1; j++) {
      double dz_dy = (grid[{j + 1, i}] - grid[{j - 1, i}]) / (2 * grid.dx());
      double dz_dx = (grid[{j, i + 1}] - grid[{j, i - 1}]) / (2 * grid.dy());
      double slope = atan(sqrt(dz_dx * dz_dx + dz_dy * dz_dy));
      double aspect = atan2(dz_dy, dz_dx);
      double hill_shade_val = 0;
      if (!multidirectional) {
        hill_shade_val = (cos(DEG2RAD(altitude)) * cos(slope) +
                          sin(DEG2RAD(altitude)) * sin(slope) * cos(DEG2RAD(azimuth) - aspect));
      } else {
        // Multidirectional hillshade https://pubs.usgs.gov/of/1992/of92-422/of92-422.pdf
        for (double az : std::array<double, 4>{
                 {azimuth - 67.5, azimuth - 22.5, azimuth + 22.5, azimuth + 67.5}}) {
          hill_shade_val += SQ(sin(aspect - DEG2RAD(az))) *
                            (cos(DEG2RAD(altitude)) * cos(slope) +
                             sin(DEG2RAD(altitude)) * sin(slope) * cos(DEG2RAD(az) - aspect));
        }
      }
      result[{j, i}] = hill_shade_val;
    }
  }
  return result;
}

template <typename T>
GeoGrid<double> slope(const GeoGrid<T> &grid) {
  TimeFunction timer("slope calculation");
  GeoGrid<double> result(grid.width(), grid.height(), GeoTransform(grid.transform()),
                         GeoProjection(grid.projection()));
  for (size_t i = 1; i < grid.height() - 1; i++) {
    for (size_t j = 1; j < grid.width() - 1; j++) {
      double dz_dy = (grid[{j + 1, i}] - grid[{j - 1, i}]) / (2 * grid.dx());
      double dz_dx = (grid[{j, i + 1}] - grid[{j, i - 1}]) / (2 * grid.dy());
      result[{j, i}] = -atan(sqrt(dz_dx * dz_dx + dz_dy * dz_dy));
    }
  }
  return result;
}
