#pragma once

#include <cstddef>
#include <optional>

#include "config_input/config_input.hpp"
#include "grid/grid.hpp"
#include "las/las_point.hpp"
#include "tif/tif.hpp"
#include "utilities/coordinate.hpp"
#include "utilities/timer.hpp"

class PointHeightClass {
 public:
  enum PointHeightClassEnum { Ground, Low, Medium, High };

 private:
  PointHeightClassEnum m_class;

 public:
  PointHeightClass(PointHeightClassEnum c) : m_class(c) {}
  operator PointHeightClassEnum() const { return m_class; }
};

template <>
struct std::hash<PointHeightClass> {
  size_t operator()(const PointHeightClass& c) const {
    return (PointHeightClass::PointHeightClassEnum)c;
  }
};

inline std::map<double, PointHeightClass> height_to_class{{0, PointHeightClass::Ground},
                                                          {0.2, PointHeightClass::Low},
                                                          {0.5, PointHeightClass::Medium},
                                                          {2.5, PointHeightClass::High}};

inline std::optional<PointHeightClass> classify_point(double height) {
  if (height < -5) {
    return std::nullopt;
  }
  PointHeightClass prev = PointHeightClass::Ground;
  for (auto it = height_to_class.begin(); it != height_to_class.end(); it++) {
    if (height < it->first) {
      return prev;
    }
    prev = it->second;
  }
  return prev;
}

class ClassCount {
  std::unordered_map<PointHeightClass, size_t> m_counts;

 public:
  ClassCount()
      : m_counts{{PointHeightClass::Ground, 0},
                 {PointHeightClass::Low, 0},
                 {PointHeightClass::Medium, 0},
                 {PointHeightClass::High, 0}} {}

  size_t& operator[](PointHeightClass c) { return m_counts[c]; }
  const size_t& operator[](PointHeightClass c) const { return m_counts.at(c); }

  size_t get_cumulative_count(PointHeightClass c) const {
    size_t count = 0;
    for (auto it = height_to_class.begin(); it != height_to_class.end(); it++) {
      if (it->second <= c) {
        count += m_counts.at(it->second);
      }
    }
    return count;
  }
};

inline GeoGrid<double> get_blocked_proportion(const GeoGrid<std::vector<LASPoint>>& grid,
                                                const GeoGrid<double>& ground, const VegeHeightConfig&
                                                vege_config) {
  TimeFunction timer("counting " + vege_config.name + " blocked proportion");
  GeoGrid<double> blocked_proportion(grid.width(), grid.height(), GeoTransform(grid.transform()),
                                   GeoProjection(grid.projection()));
#pragma omp parallel for
  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      size_t below_count = 0;
      size_t in_count = 0;
      for (const LASPoint& las_point : grid[{j, i}]) {
        double ground_height = ground.interpolate_value(las_point);
        double height = las_point.z() - ground_height;
        if (height > 0 && height < vege_config.max_height.in(au::meters)) {
          if (height < vege_config.min_height.in(au::meters)) {
            below_count++;
          } else {
            in_count++;
          }
        }
      }
      blocked_proportion[{j, i}] = (double)in_count / (in_count + below_count);
    }
  }
  return blocked_proportion;
}

inline GeoGrid<ClassCount> count_height_classes(const GeoGrid<std::vector<LASPoint>>& grid,
                                                const GeoGrid<double>& height_grid) {
  TimeFunction timer("Counting height classes");
  GeoGrid<ClassCount> class_counts(grid.width(), grid.height(), GeoTransform(grid.transform()),
                                   GeoProjection(grid.projection()));
  GeoGrid<std::optional<std::byte>> neg_heights(grid.width(), grid.height(),
                                                GeoTransform(grid.transform()),
                                                GeoProjection(grid.projection()));

#pragma omp parallel for
  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      neg_heights[{j, i}] = std::nullopt;
      for (const LASPoint& las_point : grid[{j, i}]) {
        double ground_height = height_grid.interpolate_value(las_point);
        double height = las_point.z() - ground_height;
        std::optional<PointHeightClass> c = classify_point(height);
        if (c.has_value()) {
          class_counts[{j, i}][c.value()]++;
        } else {
          neg_heights[{j, i}] = std::byte(0);
          // std::cout << "Warning: point at " << j << ", " << i << " has height " << height
          //<< " which is not classified (ground: " << ground_height << ")" << "\n";
          // Coordinate2D<double> pixel_coord =
          // height_grid.transform().projection_to_pixel(las_point); std::cout << pixel_coord << " "
          // << height_grid[pixel_coord] << std::endl; size_t x =
          // static_cast<size_t>(pixel_coord.x() - 0.5); size_t y =
          // static_cast<size_t>(pixel_coord.y() - 0.5); double x_frac = pixel_coord.x() - 0.5 - x;
          // double y_frac = pixel_coord.y() - 0.5 - y;
          // double top_left = height_grid[{x, y}];
          // double top_right = height_grid[{x + 1, y}];
          // double bottom_left = height_grid[{x, y + 1}];
          // double bottom_right = height_grid[{x + 1, y + 1}];
          // std::cout << x_frac << " " << y_frac << " " << top_left << " " <<top_right << " " <<
          // bottom_left << " " << bottom_right << std::endl;
        }
      }
    }
  }
  write_to_tif(neg_heights, "neg_heights.tif");
  return class_counts;
}

inline GeoGrid<double> proportion_blocked(const GeoGrid<ClassCount>& class_counts,
                                          PointHeightClass c) {
  TimeFunction timer("Calculating proportion blocked at " + std::to_string(c));
  GeoGrid<double> proportion_blocked(class_counts.width(), class_counts.height(),
                                     GeoTransform(class_counts.transform()),
                                     GeoProjection(class_counts.projection()));

#pragma omp parallel for
  for (size_t i = 0; i < class_counts.height(); i++) {
    for (size_t j = 0; j < class_counts.width(); j++) {
      size_t total = class_counts[{j, i}].get_cumulative_count(c);
      if (total == 0) {
        proportion_blocked[{j, i}] = 0;
        continue;
      }
      proportion_blocked[{j, i}] =
          (double)class_counts[{j, i}][c] / class_counts[{j, i}].get_cumulative_count(c);
    }
  }
  return proportion_blocked;
}

inline GeoGrid<double> canopy_proportion(const GeoGrid<ClassCount>& class_counts) {
  return proportion_blocked(class_counts, PointHeightClass::High);
}

inline GeoGrid<double> threshold(const GeoGrid<double>& grid, double threshold) {
  TimeFunction timer("Thresholding");
  GeoGrid<double> thresholded(grid.width(), grid.height(), GeoTransform(grid.transform()),
                              GeoProjection(grid.projection()));
#pragma omp parallel for
  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      thresholded[{j, i}] = grid[{j, i}] > threshold ? 1 : 0;
    }
  }
  return thresholded;
}

inline GeoGrid<double> low_pass(const GeoGrid<double>& grid, int delta = 8) {
  TimeFunction timer("Low pass filter");
  GeoGrid<double> low_pass(grid.width(), grid.height(), GeoTransform(grid.transform()),
                           GeoProjection(grid.projection()));
#pragma omp parallel for
  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      double sum = 0;
      double weight_sum = 0;
      for (int x = -delta; x <= delta; x++) {
        for (int y = -delta; y <= delta; y++) {
          if (y + (int)i >= 0 && i + y < grid.height() && x + (int)j >= 0 &&
              (unsigned int)j + x < grid.width()) {
            if (sqrt(x * x + y * y) <= delta) {
              double weight = 1 - (sqrt(x * x + y * y) / delta);
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

inline GeoGrid<double> vege_proportion(const GeoGrid<ClassCount>& class_counts) {
  return proportion_blocked(class_counts, PointHeightClass::Medium);
}
