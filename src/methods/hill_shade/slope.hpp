#pragma once

#include <cmath>
#include <limits>
#include <numbers>

#include "grid/grid.hpp"
#include "utilities/progress_tracker.hpp"

#define SQ(x) ((x) * (x))

template <typename T>
GeoGrid<double> slope(const GeoGrid<T>& grid, ProgressTracker&& progress_tracker) {
  START_TRACKER("computing slope");
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
      result[{j, i}] = atan(sqrt(dz_dx * dz_dx + dz_dy * dz_dy));
    }
  }
  return result;
}
