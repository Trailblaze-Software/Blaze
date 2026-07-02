#pragma once

#include <cmath>
#include <cstdint>
#include <deque>
#include <limits>
#include <map>
#include <numeric>
#include <optional>

#include "grid.hpp"
#include "utilities/coordinate.hpp"
#include "utilities/progress_tracker.hpp"

enum class DownsampleMethod { MEAN, MEDIAN };

// Flood-fill from the grid edge through cells with no LiDAR points. Cells reachable
// this way are "exterior"; the complement is the LiDAR coverage mask used to
// exclude extrapolated DEM/vegetation/contour data outside the surveyed area.
template <typename IsEmptyFn>
GeoGrid<bool> compute_lidar_coverage_mask(size_t width, size_t height,
                                          const GeoTransform& transform,
                                          const GeoProjection& projection, IsEmptyFn&& is_empty,
                                          ProgressTracker&& progress_tracker) {
  START_TRACKER("computing LiDAR coverage mask");
  GeoGrid<bool> exterior(width, height, GeoTransform(transform), GeoProjection(projection));
  std::vector<uint8_t> visited(width * height, 0);
  std::deque<std::pair<size_t, size_t>> queue;

  const auto try_seed = [&](size_t col, size_t row) {
    const size_t idx = row * width + col;
    if (visited[idx] || !is_empty(col, row)) {
      return;
    }
    visited[idx] = 1;
    exterior[{col, row}] = true;
    queue.emplace_back(col, row);
  };

  if (width > 0 && height > 0) {
    for (size_t col = 0; col < width; col++) {
      try_seed(col, 0);
      try_seed(col, height - 1);
    }
    for (size_t row = 1; row + 1 < height; row++) {
      try_seed(0, row);
      try_seed(width - 1, row);
    }

    while (!queue.empty()) {
      const auto [col, row] = queue.front();
      queue.pop_front();
      for (Direction2D dir :
           {Direction2D::UP, Direction2D::DOWN, Direction2D::LEFT, Direction2D::RIGHT}) {
        const long long ncol = static_cast<long long>(col) + dir.dx();
        const long long nrow = static_cast<long long>(row) + dir.dy();
        if (ncol < 0 || nrow < 0 || static_cast<size_t>(ncol) >= width ||
            static_cast<size_t>(nrow) >= height) {
          continue;
        }
        const size_t ucol = static_cast<size_t>(ncol);
        const size_t urow = static_cast<size_t>(nrow);
        const size_t idx = urow * width + ucol;
        if (visited[idx] || !is_empty(ucol, urow)) {
          continue;
        }
        visited[idx] = 1;
        exterior[{ucol, urow}] = true;
        queue.emplace_back(ucol, urow);
      }
    }
  }

  GeoGrid<bool> coverage(width, height, GeoTransform(transform), GeoProjection(projection));
#pragma omp parallel for
  for (size_t row = 0; row < height; row++) {
    for (size_t col = 0; col < width; col++) {
      coverage[{col, row}] = !exterior[{col, row}];
    }
  }
  progress_tracker.set_proportion(1.0);
  return coverage;
}

inline Extent2D coverage_extent(const GeoGrid<bool>& coverage) {
  Extent2D ext;
  bool any = false;
  for (size_t row = 0; row < coverage.height(); row++) {
    for (size_t col = 0; col < coverage.width(); col++) {
      if (!coverage[{col, row}]) {
        continue;
      }
      any = true;
      const auto c0 = coverage.transform().pixel_to_projection(
          {static_cast<double>(col), static_cast<double>(row)});
      const auto c1 = coverage.transform().pixel_to_projection(
          {static_cast<double>(col + 1), static_cast<double>(row + 1)});
      ext.grow(Extent2D{std::min(c0.x(), c1.x()), std::max(c0.x(), c1.x()),
                        std::min(c0.y(), c1.y()), std::max(c0.y(), c1.y())});
    }
  }
  if (!any) {
    const auto c0 = coverage.transform().pixel_to_projection({0.0, 0.0});
    const auto c1 = coverage.transform().pixel_to_projection(
        {static_cast<double>(coverage.width()), static_cast<double>(coverage.height())});
    return {std::min(c0.x(), c1.x()), std::max(c0.x(), c1.x()), std::min(c0.y(), c1.y()),
            std::max(c0.y(), c1.y())};
  }
  return ext;
}

// After downsampling a floating-point grid, mark coarse cells NaN when any source
// sub-cell was nodata.
template <typename T>
  requires std::is_floating_point_v<T>
void enforce_downsample_nodata(GeoGrid<T>& coarse, const GeoGrid<T>& fine, size_t factor) {
  if (factor <= 1) {
    return;
  }
#pragma omp parallel for
  for (size_t row = 0; row < coarse.height(); row++) {
    for (size_t col = 0; col < coarse.width(); col++) {
      bool has_nodata = false;
      for (size_t k = 0; k < factor && row * factor + k < fine.height() && !has_nodata; k++) {
        for (size_t l = 0; l < factor && col * factor + l < fine.width(); l++) {
          if (!std::isfinite(fine[{col * factor + l, row * factor + k}])) {
            has_nodata = true;
            break;
          }
        }
      }
      if (has_nodata) {
        coarse[{col, row}] = std::numeric_limits<T>::quiet_NaN();
      }
    }
  }
}

template <typename T>
  requires std::is_floating_point_v<T>
void apply_coverage_mask(GeoGrid<T>& grid, const GeoGrid<bool>& coverage) {
  AssertEQ(grid.width(), coverage.width());
  AssertEQ(grid.height(), coverage.height());
#pragma omp parallel for
  for (size_t row = 0; row < grid.height(); row++) {
    for (size_t col = 0; col < grid.width(); col++) {
      if (!coverage[{col, row}]) {
        grid[{col, row}] = std::numeric_limits<T>::quiet_NaN();
      }
    }
  }
}

#define SQ(x) ((x) * (x))

template <typename T>
GeoGrid<T> downsample(const GeoGrid<T>& grid, size_t factor, ProgressTracker&& progress_tracker,
                      DownsampleMethod method = DownsampleMethod::MEDIAN) {
  START_TRACKER("downsampling grid");
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

inline bool sample_coverage_at_pixel(const GeoGrid<bool>& coverage,
                                     const GeoTransform& dest_transform, size_t col, size_t row) {
  const auto pt = dest_transform.pixel_to_projection(
      {static_cast<double>(col) + 0.5, static_cast<double>(row) + 0.5});
  const auto cov_px = coverage.transform().projection_to_pixel(pt);
  if (cov_px.x() < 0.0 || cov_px.y() < 0.0 || cov_px.x() >= static_cast<double>(coverage.width()) ||
      cov_px.y() >= static_cast<double>(coverage.height())) {
    return false;
  }
  return coverage[{static_cast<size_t>(cov_px.x()), static_cast<size_t>(cov_px.y())}];
}

// Sample `coverage` at every pixel of `dest` and set each cell to `data_value`
// (where coverage is true) or `nodata_value` (where false / out of bounds).
template <typename T>
void fill_grid_from_coverage(GeoGrid<T>& dest, const GeoGrid<bool>& coverage, const T& data_value,
                             const T& nodata_value) {
#pragma omp parallel for
  for (size_t row = 0; row < dest.height(); row++) {
    for (size_t col = 0; col < dest.width(); col++) {
      dest[{col, row}] = sample_coverage_at_pixel(coverage, dest.transform(), col, row)
                             ? data_value
                             : nodata_value;
    }
  }
}

// Clear pixels outside the LiDAR coverage mask, leaving covered pixels unchanged.
template <typename T>
void mask_outside_coverage(GeoGrid<T>& dest, const GeoGrid<bool>& coverage, const T& nodata_value) {
#pragma omp parallel for
  for (size_t row = 0; row < dest.height(); row++) {
    for (size_t col = 0; col < dest.width(); col++) {
      if (!sample_coverage_at_pixel(coverage, dest.transform(), col, row)) {
        dest[{col, row}] = nodata_value;
      }
    }
  }
}

template <typename T>
void remove_outliers(GeoGrid<T>& grid, ProgressTracker&& progress_tracker, double z_threshold = 1,
                     bool z_only = false) {
  START_TRACKER("removing outliers");
  bool no_outliers = false;
  int iter_count = 0;
  while (!no_outliers) {
    iter_count++;
    no_outliers = true;
    int num_outliers = 0;
#pragma omp parallel for reduction(+ : num_outliers)
    for (size_t i = 0; i < grid.height(); i++) {
      for (size_t j = 0; j < grid.width(); j++) {
        if (!std::isfinite(grid[{j, i}])) {
          continue;
        }
        if (i == 0 || j == 0 || i == grid.height() - 1 || j == grid.width() - 1) {
          continue;
        }
        T z = grid[{j, i}];
        double max_neighbour = std::max({0.5 * (grid[{j - 1, i}] + grid[{j + 1, i}]),
                                         0.5 * (grid[{j, i - 1}] + grid[{j, i + 1}])});
        double min_neighbour = std::min({0.5 * (grid[{j - 1, i}] + grid[{j + 1, i}]),
                                         0.5 * (grid[{j, i - 1}] + grid[{j, i + 1}])});
        if (!std::isfinite(max_neighbour) || !std::isfinite(min_neighbour) ||
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

// Check if a value is a real ground elevation (not a hole awaiting interpolation).
// Interior holes use max() as sentinel; exterior nodata uses NaN (non-finite).
inline static bool has_value(double value) {
  constexpr double MAX_VAL = std::numeric_limits<double>::max();
  return std::isfinite(value) && value < MAX_VAL && value > -MAX_VAL;
}

template <typename T>
void interpolate_holes(GeoGrid<T>& grid, ProgressTracker&& progress_tracker) {
  START_TRACKER("interpolating holes");
#pragma omp parallel for
  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      // Exterior nodata is NaN; interior holes awaiting fill use max() (still finite).
      if (!std::isfinite(grid[{j, i}])) {
        continue;
      }
      if (has_value(grid[{j, i}])) {
        continue;
      }
      std::map<Direction2D, std::optional<std::pair<size_t, T>>> neighbours;
      for (Direction2D dir :
           {Direction2D::UP, Direction2D::DOWN, Direction2D::LEFT, Direction2D::RIGHT}) {
        neighbours[dir] = std::nullopt;
        for (size_t k = 1; grid.in_bounds({j + dir.dx() * k, i + dir.dy() * k}); k++) {
          if (has_value(grid[{j + dir.dx() * k, i + dir.dy() * k}])) {
            neighbours[dir] = std::pair<size_t, T>(k, grid[{j + dir.dx() * k, i + dir.dy() * k}]);
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

template <typename T>
GeoGrid<std::optional<std::byte>> bool_grid(const GeoGrid<T>& grid, T threshold,
                                            ProgressTracker&& progress_tracker) {
  START_TRACKER("building boolean grid");
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
