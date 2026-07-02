#pragma once

#include <cmath>
#include <limits>
#include <numbers>

#include "grid/grid.hpp"
#include "utilities/progress_tracker.hpp"

#define DEG2RAD(x) ((x) * std::numbers::pi / 180)
#define SQ(x) ((x) * (x))

template <typename T>
GeoGrid<double> hill_shade(const GeoGrid<T>& grid, double azimuth, double altitude,
                           const bool multidirectional, ProgressTracker&& progress_tracker) {
  START_TRACKER("computing hill shade");
  GeoGrid<double> result(grid.width(), grid.height(), GeoTransform(grid.transform()),
                         GeoProjection(grid.projection()));
  result.fill(std::numeric_limits<double>::quiet_NaN());
  for (size_t i = 1; i < grid.height() - 1; i++) {
    for (size_t j = 1; j < grid.width() - 1; j++) {
      const double center = grid[{j, i}];
      const double east = grid[{j + 1, i}];
      const double west = grid[{j - 1, i}];
      const double north = grid[{j, i + 1}];
      const double south = grid[{j, i - 1}];
      if (!std::isfinite(center) || !std::isfinite(east) || !std::isfinite(west) ||
          !std::isfinite(north) || !std::isfinite(south)) {
        continue;
      }
      double dz_dx = (east - west) / (2 * grid.dx());
      double dz_dy = (north - south) / (2 * grid.dy());
      double slope_val = atan(sqrt(dz_dx * dz_dx + dz_dy * dz_dy));
      double aspect = atan2(dz_dy, dz_dx);
      double hill_shade_val = 0;
      if (!multidirectional) {
        hill_shade_val = (cos(DEG2RAD(altitude)) * cos(slope_val) +
                          sin(DEG2RAD(altitude)) * sin(slope_val) * cos(DEG2RAD(azimuth) - aspect));
      } else {
        // Multidirectional hillshade https://pubs.usgs.gov/of/1992/of92-422/of92-422.pdf
        for (double az : std::array<double, 4>{
                 {azimuth - 67.5, azimuth - 22.5, azimuth + 22.5, azimuth + 67.5}}) {
          hill_shade_val += SQ(sin(aspect - DEG2RAD(az))) *
                            (cos(DEG2RAD(altitude)) * cos(slope_val) +
                             sin(DEG2RAD(altitude)) * sin(slope_val) * cos(DEG2RAD(az) - aspect));
        }
      }
      result[{j, i}] = hill_shade_val;
    }
  }
  return result;
}
