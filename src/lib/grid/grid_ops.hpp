#pragma once

#include "grid.hpp"
#include "utilities/timer.hpp"
#include <numeric>

enum class DownsampleMethod {
  MEAN,
  MEDIAN
};

template <typename T>
GeoGrid<T> downsample(const GeoGrid<T>& grid, size_t factor, DownsampleMethod method=DownsampleMethod::MEDIAN) {
  TimeFunction timer("downsampling");
  GeoTransform transform = grid.transform();
  transform.set_dx(transform.dx() * factor);
  transform.set_dy(transform.dy() * factor);
  GeoGrid<T> result(grid.width() / factor, grid.height() / factor, std::move(transform), GeoProjection(grid.projection()));
  for (size_t i = 0; i < result.height(); i++) {
    for (size_t j = 0; j < result.width(); j++) {
      std::vector<T> values;
      for (size_t k = 0; k < factor; k++) {
        for (size_t l = 0; l < factor; l++) {
          values.push_back(grid[{i*factor + k, j*factor + l}]);
        }
      }
      if (method == DownsampleMethod::MEAN) {
        result[{i, j}] = std::accumulate(values.begin(), values.end(), 0.0) / values.size();
      } else if (method == DownsampleMethod::MEDIAN) {
        std::sort(values.begin(), values.end());
        result[{i, j}] = values[values.size() / 2];
      }
    }
  }
  return result;
}

template <typename T>
GeoGrid<T> remove_outliers(const GeoGrid<T>& grid, double z_threshold=0.5) {
  TimeFunction timer("remove outliers");
  GeoGrid<T> result(grid.width(), grid.height(), GeoTransform(grid.transform()), GeoProjection(grid.projection()));
  for (size_t i = 1; i < grid.height()-1; i++) {
    for (size_t j = 1; j < grid.width()-1; j++) {
      T z = grid[{i, j}];
      double max_neighbour = std::max({grid[{i-1, j}], grid[{i, j-1}], grid[{i+1, j}], grid[{i, j+1}]});
      double min_neighbour = std::min({grid[{i-1, j}], grid[{i, j-1}], grid[{i+1, j}], grid[{i, j+1}]});
      if (min_neighbour - z > z_threshold || z - max_neighbour > z_threshold) {
        result[{i, j}] = (max_neighbour + min_neighbour) / 2;
      } else {
        result[{i, j}] = z;
      }
    }
  }
  return result;
}
