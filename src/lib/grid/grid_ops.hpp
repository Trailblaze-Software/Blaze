#pragma once

#include <cmath>
#include <limits>
#include <map>
#include <numeric>
#include <optional>

#include "grid.hpp"
#include "printing/to_string.hpp"
#include "utilities/coordinate.hpp"
#include "utilities/timer.hpp"

enum class DownsampleMethod { MEAN, MEDIAN };

template <typename T>
GeoGrid<T> downsample(const GeoGrid<T> &grid, size_t factor,
                      DownsampleMethod method = DownsampleMethod::MEDIAN) {
  TimeFunction timer("downsampling");
  GeoTransform transform = grid.transform();
  transform.set_dx(transform.dx() * factor);
  transform.set_dy(transform.dy() * factor);
  GeoGrid<T> result(std::ceil((double)grid.width() / factor),
                    std::ceil((double)grid.height() / factor), std::move(transform),
                    GeoProjection(grid.projection()));
#pragma omp parallel for
  for (size_t i = 0; i < result.height(); i++) {
    for (size_t j = 0; j < result.width(); j++) {
      std::vector<T> values;
      for (size_t k = 0; k < factor && i + k < grid.height(); k++) {
        for (size_t l = 0; l < factor && j + l < grid.width(); l++) {
          if (std::isfinite(grid[{j * factor + l, i * factor + k}]))
            values.push_back(grid[{j * factor + l, i * factor + k}]);
        }
      }
      if (method == DownsampleMethod::MEAN) {
        result[{j, i}] = std::accumulate(values.begin(), values.end(), 0.0) / values.size();
      } else if (method == DownsampleMethod::MEDIAN) {
        std::sort(values.begin(), values.end());
        if (values.size() > 0)
          result[{j, i}] = values[values.size() / 2];
        else
          result[{j, i}] = std::numeric_limits<double>::quiet_NaN();
      }
    }
  }
  return result;
}

template <typename T>
GeoGrid<T> remove_outliers(const GeoGrid<T> &grid, double z_threshold = 0.5) {
  TimeFunction timer("remove outliers");
  GeoGrid<T> result(grid.width(), grid.height(), GeoTransform(grid.transform()),
                    GeoProjection(grid.projection()));
#pragma omp parallel for
  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      if (i == 0 || j == 0 || i == grid.height() - 1 || j == grid.width() - 1) {
        result[{j, i}] = grid[{j, i}];
        continue;
      }
      T z = grid[{i, j}];
      double max_neighbour =
          std::max({grid[{j - 1, i}], grid[{j, i - 1}], grid[{j + 1, i}], grid[{j, i + 1}]});
      double min_neighbour =
          std::min({grid[{j - 1, i}], grid[{j, i - 1}], grid[{j + 1, i}], grid[{j, i + 1}]});
      if (min_neighbour - z > z_threshold || z - max_neighbour > z_threshold) {
        result[{j, i}] = (max_neighbour + min_neighbour) / 2;
      } else {
        result[{j, i}] = z;
      }
    }
  }
  return result;
}

bool has_value(double value) { return std::isfinite(value) && value < 1e6; }

template <typename T>
GeoGrid<T> interpolate_holes(const GeoGrid<T> &grid) {
  TimeFunction timer("interpolate holes");
  GeoGrid<T> result(grid.width(), grid.height(), GeoTransform(grid.transform()),
                    GeoProjection(grid.projection()));
#pragma omp parallel for
  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      if (has_value(grid[{j, i}])) {
        result[{j, i}] = grid[{j, i}];
      } else {
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
        result[{j, i}] = weighted_average / total_weight;
      }
    }
  }
  return result;
}

template <typename T>
GeoGrid<std::optional<std::byte>> bool_grid(const GeoGrid<T> &grid, T threshold) {
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
