#pragma once

#include <cstddef>
#include <map>
#include <optional>

#include "grid/grid.hpp"
#include "las/las_point.hpp"
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

inline std::map<double, PointHeightClass> height_to_class{{0, PointHeightClass::Ground},
                                                          {0.2, PointHeightClass::Low},
                                                          {0.5, PointHeightClass::Medium},
                                                          {2.5, PointHeightClass::High}};

inline std::optional<PointHeightClass> classify_point(double height) {
  if (height < -1) {
    //std::cout << "Warning: negative height" << std::endl;
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
  std::map<PointHeightClass, size_t> m_counts;

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

GeoGrid<ClassCount> count_height_classes(const GeoGrid<std::vector<LASPoint>>& grid,
                                         const GeoGrid<double>& height_grid) {
  TimeFunction timer("Counting height classes");
  GeoGrid<ClassCount> class_counts(height_grid.width(), height_grid.height(),
                                   GeoTransform(height_grid.transform()),
                                   GeoProjection(height_grid.projection()));

#pragma omp parallel for
  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      for (const LASPoint& las_point : grid[{j, i}]) {
        double ground_height = height_grid.interpolate_value(las_point);
        double height = las_point.z() - ground_height;
        std::optional<PointHeightClass> c = classify_point(height);
        if (c.has_value()) {
          class_counts[{j, i}][c.value()]++;
        }
      }
    }
  }
  return class_counts;
}

GeoGrid<double> proportion_blocked(const GeoGrid<ClassCount>& class_counts, PointHeightClass c) {
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

GeoGrid<double> canopy_proportion(const GeoGrid<ClassCount>& class_counts) {
  return proportion_blocked(class_counts, PointHeightClass::High);
}

GeoGrid<double> threshold(const GeoGrid<double>& grid, double threshold) {
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

GeoGrid<double> low_pass(const GeoGrid<double>& grid, int delta = 10) {
  TimeFunction timer("Low pass filter");
  GeoGrid<double> low_pass(grid.width(), grid.height(), GeoTransform(grid.transform()),
                           GeoProjection(grid.projection()));
#pragma omp parallel for
  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      double sum = 0;
      for (int x = -delta; x <= delta; x++) {
        for (int y = -delta; y <= delta; y++) {
          if (y + (int)i >= 0 && i + y < grid.height() && x + (int)j >= 0 &&
              (unsigned int)j + x < grid.width()) {
            if (sqrt(x * x + y * y) <= delta)
              sum += grid[{j + x, i + y}] * (1 - sqrt(x * x + y * y) / delta);
          }
        }
      }
      low_pass[{j, i}] = sum;
    }
  }
  return low_pass;
}

GeoGrid<double> vege_proportion(const GeoGrid<ClassCount>& class_counts) {
  return proportion_blocked(class_counts, PointHeightClass::Medium);
}
