

# File grid\_ops.hpp

[**File List**](files.md) **>** [**grid**](dir_b440d1ddeab29faa8ab1c63476ee276f.md) **>** [**grid\_ops.hpp**](grid__ops_8hpp.md)

[Go to the documentation of this file](grid__ops_8hpp.md)


```C++
#pragma once

#include <cmath>
#include <limits>
#include <map>
#include <numeric>
#include <optional>

#include "grid.hpp"
#include "utilities/coordinate.hpp"
#include "utilities/timer.hpp"

enum class DownsampleMethod { MEAN, MEDIAN };

#define SQ(x) ((x) * (x))

template <typename T>
GeoGrid<T> downsample(const GeoGrid<T>& grid, size_t factor, ProgressTracker&& progress_tracker,
                      DownsampleMethod method = DownsampleMethod::MEDIAN) {
  TimeFunction timer("downsampling", &progress_tracker);
  AssertEQ(grid.transform().dx(), -grid.transform().dy());
  GeoGrid<T> result(std::ceil((double)grid.width() / factor),
                    std::ceil((double)grid.height() / factor),
                    grid.transform().with_new_resolution(grid.transform().dx() * factor),
                    GeoProjection(grid.projection()));
#pragma omp parallel for
  for (size_t i = 0; i < result.height(); i++) {
    for (size_t j = 0; j < result.width(); j++) {
      std::vector<T> values;
      for (size_t k = 0; k < factor && i * factor + k < grid.height(); k++) {
        for (size_t l = 0; l < factor && j * factor + l < grid.width(); l++) {
          if (std::isfinite(grid[{j * factor + l, i * factor + k}]))
            values.push_back(grid[{j * factor + l, i * factor + k}]);
        }
      }
      if (method == DownsampleMethod::MEAN) {
        result[{j, i}] = std::accumulate(values.begin(), values.end(), 0.0) / values.size();
      } else if (method == DownsampleMethod::MEDIAN) {
        std::sort(values.begin(), values.end());
        if (values.size() > 0) {
          if (values.size() % 2 == 0) {
            // For even-sized arrays, median is the average of the two middle values
            result[{j, i}] = (values[values.size() / 2 - 1] + values[values.size() / 2]) / 2.0;
          } else {
            // For odd-sized arrays, median is the middle value
            result[{j, i}] = values[values.size() / 2];
          }
        } else {
          result[{j, i}] = std::numeric_limits<double>::quiet_NaN();
        }
      }
    }
  }
  return result;
}

template <typename T>
void remove_outliers(GeoGrid<T>& grid, ProgressTracker progress_tracker, double z_threshold = 1,
                     bool z_only = false) {
  TimeFunction timer("remove outliers", &progress_tracker);
  bool no_outliers = false;
  int iter_count = 0;
  while (!no_outliers) {
    iter_count++;
    no_outliers = true;
    int num_outliers = 0;
#pragma omp parallel for reduction(+ : num_outliers)
    for (size_t i = 0; i < grid.height(); i++) {
      for (size_t j = 0; j < grid.width(); j++) {
        if (i == 0 || j == 0 || i == grid.height() - 1 || j == grid.width() - 1) {
          continue;
        }
        T z = grid[{j, i}];
        double max_neighbour = std::max({0.5 * (grid[{j - 1, i}] + grid[{j + 1, i}]),
                                         0.5 * (grid[{j, i - 1}] + grid[{j, i + 1}])});
        double min_neighbour = std::min({0.5 * (grid[{j - 1, i}] + grid[{j + 1, i}]),
                                         0.5 * (grid[{j, i - 1}] + grid[{j, i + 1}])});
        if (std::isnan(max_neighbour) || std::isnan(min_neighbour) ||
            !std::isfinite(max_neighbour) || !std::isfinite(min_neighbour) ||
            std::abs(max_neighbour) > 1e8 || std::abs(min_neighbour) > 1e8) {
          continue;
        }
        if (min_neighbour - z > z_threshold || z - max_neighbour > z_threshold) {
          if (!z_only) {
            double dist_x =
                (2 * grid.dx() * (grid[{j, i}] - grid[{j + 1, i}]) -
                 (grid[{j + 1, i}] - grid[{j - 1, i}]) * grid.dx()) /
                std::sqrt(SQ(2 * grid.dx()) + SQ((grid[{j + 1, i}] - grid[{j - 1, i}])));
            double dist_y =
                (2 * grid.dy() * (grid[{j, i}] - grid[{j, i + 1}]) -
                 (grid[{j, i + 1}] - grid[{j, i - 1}]) * grid.dy()) /
                std::sqrt(SQ(2 * grid.dy()) + SQ((grid[{j, i + 1}] - grid[{j, i - 1}])));
            if (std::abs(dist_x) < z_threshold || std::abs(dist_y) < z_threshold) {
              continue;
            }
          }
          grid[{j, i}] = (max_neighbour + min_neighbour) / 2;
          no_outliers = false;
          num_outliers++;
        }
      }
    }
    if (iter_count > 10)
      std::cerr << "Removed " << num_outliers << " outliers with threshold " << z_threshold
                << " on iteration " << iter_count << std::endl;
  }
}

// Check if a value is valid (not a hole/missing data)
// Holes are represented as NaN, infinity, or std::numeric_limits<double>::max() or -max()
inline static bool has_value(double value) {
  constexpr double max_val = std::numeric_limits<double>::max();
  return std::isfinite(value) && value < max_val && value > -max_val;
}

template <typename T>
void interpolate_holes(GeoGrid<T>& grid, ProgressTracker progress_tracker) {
  TimeFunction timer("interpolate holes", &progress_tracker);
#pragma omp parallel for
  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      if (!has_value(grid[{j, i}])) {
        std::map<Direction2D, std::optional<std::pair<size_t, T>>> neighbours;
        for (Direction2D dir :
             {Direction2D::UP, Direction2D::DOWN, Direction2D::LEFT, Direction2D::RIGHT}) {
          neighbours[dir] = std::nullopt;
          for (size_t k = 1; grid.in_bounds({j + dir.dy() * k, i + dir.dx() * k}); k++) {
            if (has_value(grid[{j + dir.dy() * k, i + dir.dx() * k}])) {
              neighbours[dir] = std::pair<size_t, T>(k, grid[{j + dir.dy() * k, i + dir.dx() * k}]);
              break;
            }
          }
        }
        T weighted_average = 0;
        double total_weight = 0;
        for (auto [dir, neighbour] : neighbours) {
          if (neighbour.has_value()) {
            weighted_average += neighbour.value().second / neighbour.value().first;
            total_weight += 1.0 / neighbour.value().first;
          }
        }
        if (total_weight == 0) {
          grid[{j, i}] = 0;
        } else {
          grid[{j, i}] = weighted_average / total_weight;
        }
      }
    }
  }
}

template <typename T>
GeoGrid<std::optional<std::byte>> bool_grid(const GeoGrid<T>& grid, T threshold) {
  TimeFunction timer("bool grid");
  GeoGrid<std::optional<std::byte>> result(grid.width(), grid.height(),
                                           GeoTransform(grid.transform()),
                                           GeoProjection(grid.projection()));
#pragma omp parallel for
  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      result[{j, i}] =
          grid[{j, i}] > threshold ? std::optional<std::byte>{std::byte{0}} : std::nullopt;
    }
  }
  return result;
}
```


