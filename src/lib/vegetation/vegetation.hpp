#pragma once

#include <cstddef>

#include "config_input/config_input.hpp"
#include "grid/grid.hpp"
#include "las/las_point.hpp"
#include "utilities/coordinate.hpp"
#include "utilities/timer.hpp"

inline GeoGrid<std::optional<float>> get_blocked_proportion(
    const GeoGrid<std::vector<LASPoint>>& grid, const GeoGrid<double>& ground,
    const VegeHeightConfig& vege_config) {
  TimeFunction timer("counting " + vege_config.name + " blocked proportion");
  GeoGrid<std::optional<float>> blocked_proportion(grid.width(), grid.height(),
                                                   GeoTransform(grid.transform()),
                                                   GeoProjection(grid.projection()));
#pragma omp parallel for
  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      size_t below_count = 0;
      size_t in_count = 0;
      for (const LASPoint& las_point : grid[{j, i}]) {
        double ground_height = interpolate_value(ground, las_point);
        double height = las_point.z() - ground_height;
        if (height > -1 && height < vege_config.max_height) {
          if (height < vege_config.min_height) {
            below_count++;
          } else {
            in_count++;
          }
        }
      }
      blocked_proportion[{j, i}] =
          (in_count + below_count) > 0
              ? std::make_optional<float>((double)in_count / (in_count + below_count))
              : std::nullopt;
    }
  }
  return blocked_proportion;
}

inline GeoGrid<float> low_pass(const GeoGrid<float>& grid, int delta = 8) {
  TimeFunction timer("Low pass filter");
  GeoGrid<float> low_pass(grid.width(), grid.height(), GeoTransform(grid.transform()),
                          GeoProjection(grid.projection()));
#pragma omp parallel for
  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      float sum = 0;
      float weight_sum = 0;
      for (int x = -delta; x <= delta; x++) {
        for (int y = -delta; y <= delta; y++) {
          if (y + (int)i >= 0 && i + y < grid.height() && x + (int)j >= 0 &&
              (unsigned int)j + x < grid.width()) {
            if (sqrt(x * x + y * y) <= delta) {
              float weight = 1 - (sqrt(x * x + y * y) / delta);
              sum += grid[{j + x, i + y}] * weight;
              weight_sum += weight;
            }
          }
        }
      }
      low_pass[{j, i}] = sum / weight_sum;
    }
  }
  return low_pass;
}

inline GeoGrid<float> low_pass(const GeoGrid<std::optional<float>>& grid, int delta = 8) {
  TimeFunction timer("Low pass filter");
  GeoGrid<float> low_pass(grid.width(), grid.height(), GeoTransform(grid.transform()),
                          GeoProjection(grid.projection()));
#pragma omp parallel for
  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      float sum = 0;
      float weight_sum = 0;
      for (int x = -delta; x <= delta; x++) {
        for (int y = -delta; y <= delta; y++) {
          if (y + (int)i >= 0 && i + y < grid.height() && x + (int)j >= 0 &&
              (unsigned int)j + x < grid.width()) {
            if (sqrt(x * x + y * y) <= delta) {
              float weight = 1 - (sqrt(x * x + y * y) / delta);
              if (grid[{j + x, i + y}].has_value()) {
                sum += *grid[{j + x, i + y}] * weight;
                weight_sum += weight;
              }
            }
          }
        }
      }
      if (weight_sum == 0) {
        low_pass[{j, i}] = 0;
        continue;
      }
      low_pass[{j, i}] = sum / weight_sum;
    }
  }
  return low_pass;
}
