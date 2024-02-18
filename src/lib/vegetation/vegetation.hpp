#pragma once

#include <cstddef>
#include <map>

class PointHeightClass {
 public:
  enum PointHeightClassEnum { Ground, Low, Medium, High };

 private:
  PointHeightClassEnum m_class;

 public:
  PointHeightClass(PointHeightClassEnum c) : m_class(c) {}
  operator PointHeightClassEnum() const { return m_class; }
};

std::map<double, PointHeightClass> height_to_class{{0, PointHeightClass::Ground},
                                                   {0.2, PointHeightClass::Low},
                                                   {0.5, PointHeightClass::Medium},
                                                   {2.5, PointHeightClass::High}};

typedef std::map<PointHeightClass, size_t> ClassCount;

GeoGrid<ClassCount> count_height_classes(const GeoGrid<std::vector<LASPoint>>& grid,
                                         const GeoGrid<double>& height_grid) {
  GeoGrid<ClassCount> class_counts(grid.width(), grid.height(), GeoTransform(grid.transform()),
                                   GeoProjection(grid.projection()));
  (void)height_grid;

  return class_counts;
}
