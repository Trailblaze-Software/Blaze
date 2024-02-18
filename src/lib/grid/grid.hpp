#pragma once

#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>

#include "assert/assert.hpp"
#include "utilities/coordinate.hpp"

class GeoTransform {
  double geoTranform[6];

 public:
  GeoTransform(double upper_left_x, double upper_left_y, double dx = 1.0, double dy = -1.0) {
    geoTranform[0] = upper_left_x;  // center of top left pixel is 0.5, 0.5
    geoTranform[1] = dx;            // w->e pixel resolution
    geoTranform[2] = 0;             // Row rotation
    geoTranform[3] = upper_left_y;
    geoTranform[4] = 0;   // Column rotation
    geoTranform[5] = dy;  // n->s pixel resolution (so negative is up)
  }

  explicit GeoTransform(const Coordinate2D<double> &upper_left, double resolution)
      : GeoTransform(upper_left.x(), upper_left.y(), resolution, -resolution) {}

  GeoTransform() : GeoTransform(0, 0, 1, -1){};

  const double *get_raw() const { return geoTranform; }

  Coordinate2D<double> pixel_to_projection(const Coordinate2D<double> &coord) const {
    double new_x = x() + coord.x() * dx() + coord.y() * rot_x();
    double new_y = y() + coord.y() * dy() + coord.x() * rot_y();
    return {new_x, new_y};
  }

  Coordinate2D<double> projection_to_pixel(const Coordinate2D<double> &coord) const {
    double new_x = (rot_x() * coord.y() - coord.x() * dy() - y() * rot_x() + x() * dy()) /
                   (rot_x() * rot_y() - dy() * dx());
    double new_y = (rot_y() * coord.x() - coord.y() * dx() - x() * rot_y() + y() * dx()) /
                   (rot_x() * rot_y() - dy() * dx());
    return {new_x, new_y};
  }

  friend std::ostream &operator<<(std::ostream &os, const GeoTransform &transform) {
    os << "GeoTransform(x: " << transform.x() << ", y: " << transform.y()
       << ", dx: " << transform.dx() << ", dy: " << transform.dy()
       << ", rot_x: " << transform.rot_x() << ", rot_y: " << transform.rot_y() << ")";
    return os;
  }

  double x() const { return geoTranform[0]; }
  double dx() const { return geoTranform[1]; }
  double rot_x() const { return geoTranform[2]; }
  double y() const { return geoTranform[3]; }
  double rot_y() const { return geoTranform[4]; }
  double dy() const { return geoTranform[5]; }

  void set_dx(double dx) { geoTranform[1] = dx; }
  void set_dy(double dy) { geoTranform[5] = dy; }
};

class GeoProjection {
  std::string m_projection;

 public:
  explicit GeoProjection(const std::string &projection) : m_projection(projection) {}

  GeoProjection() = default;

  const std::string &to_string() const { return m_projection; }
};

template <typename T>
class Grid {
  size_t m_width;
  size_t m_height;
  std::vector<T> m_data;

 public:
  Grid(size_t width, size_t height) : m_width(width), m_height(height), m_data(width * height) {}
  T &operator[](Coordinate2D<size_t> coord) { return m_data[coord.y() * m_width + coord.x()]; }
  const T &operator[](Coordinate2D<size_t> coord) const {
    return m_data[coord.y() * m_width + coord.x()];
  }

  size_t width() const { return m_width; }
  size_t height() const { return m_height; }

  T max_value() const { return *std::max_element(m_data.begin(), m_data.end()); }
  T min_value() const { return *std::min_element(m_data.begin(), m_data.end()); }

  friend std::ostream &operator<<(std::ostream &os, const Grid &grid) {
    os << "Grid<" << typeid(T).name() << ">(" << grid.width() << ", " << grid.height() << ")"
       << std::endl;
    for (size_t i = 0; i < grid.height(); i++) {
      for (size_t j = 0; j < grid.width(); j++) {
        if constexpr (std::is_same_v<T, char>) {
          os << (grid[{j, i}] ? "X" : "_");
        } else {
          os << grid[{j, i}];
        }
      }
      os << std::endl;
    }
    return os;
  }
};

template <typename T>
class GeoGrid : public Grid<T> {
  using Grid<T>::Grid;
  GeoTransform m_transform;
  GeoProjection m_projection;

 public:
  GeoGrid(size_t width, size_t height, GeoTransform &&transform, GeoProjection &&projection)
      : Grid<T>(width, height), m_transform(transform), m_projection(projection) {}

  const GeoTransform &transform() const { return m_transform; }
  const GeoProjection &projection() const { return m_projection; }

  double dx() const { return m_transform.dx(); }
  double dy() const { return m_transform.dy(); }

  std::pair<T, T> get_values(const LineCoord2D<size_t> &coord) const {
    return {(*this)[coord.start()], (*this)[coord.end()]};
  }

  template <typename U>
  GeoGrid<T> FromPoints(const GeoGrid<U> &grid) {
    return GeoGrid<T>(grid.width() - 1, grid.height() - 1,
                      GeoTransform(grid.transform().x() + grid.transform().dx() / 2,
                                   grid.transform().y() + grid.transform().dy() / 2,
                                   grid.transform().dx(), grid.transform().dy()),
                      grid.projection());
  }

  T interpolate_value(const Coordinate2D<double> &projection_coord) const {
    Coordinate2D<double> pixel_coord = transform().projection_to_pixel(projection_coord);
    if (pixel_coord.x() < 0 || pixel_coord.y() < 0 || pixel_coord.x() >= Grid<T>::width() ||
        pixel_coord.y() >= Grid<T>::height()) {
      Fail("Interpolation out of bounds");
    }
    if (pixel_coord.x() <= 0.5 || pixel_coord.y() <= 0.5 ||
        pixel_coord.x() >= Grid<T>::width() - 0.5 || pixel_coord.y() >= Grid<T>::height() - 0.5) {
      return (*this)[{static_cast<size_t>(pixel_coord.x()), static_cast<size_t>(pixel_coord.y())}];
    }
    size_t x = static_cast<size_t>(pixel_coord.x() - 0.5);
    size_t y = static_cast<size_t>(pixel_coord.y() - 0.5);
    if (x >= Grid<T>::width() || y >= Grid<T>::height()) {
      Fail("Interpolation out of bounds");
    }
    double x_frac = pixel_coord.x() - x;
    double y_frac = pixel_coord.y() - y;
    T top_left = (*this)[{x, y}];
    T top_right = (*this)[{x + 1, y}];
    T bottom_left = (*this)[{x, y + 1}];
    T bottom_right = (*this)[{x + 1, y + 1}];
    return top_left * (1 - x_frac) * (1 - y_frac) + top_right * x_frac * (1 - y_frac) +
           bottom_left * (1 - x_frac) * y_frac + bottom_right * x_frac * y_frac;
  }
};

template <typename T>
class GridGraph {
  Grid<T> m_horizontal;
  Grid<T> m_vertical;

 public:
  template <typename U>
  explicit GridGraph(const Grid<U> &grid)
      : m_horizontal(grid.width() - 1, grid.height()),
        m_vertical(grid.width(), grid.height() - 1) {}

  Grid<T> &horizontal() { return m_horizontal; }
  Grid<T> &vertical() { return m_vertical; }
  const Grid<T> &horizontal() const { return m_horizontal; }
  const Grid<T> &vertical() const { return m_vertical; }

  size_t width() const { return m_vertical.width(); }
  size_t height() const { return m_horizontal.height(); }

  const T &operator[](const LineCoord2D<size_t> &coord) const {
    if (coord.dir() == Direction2D::DOWN) {
      return m_vertical[Coordinate2D<size_t>(coord.x(), coord.y())];
    } else if (coord.dir() == Direction2D::RIGHT) {
      return m_horizontal[Coordinate2D<size_t>(coord.x(), coord.y())];
    }
    Fail("Invalid direction");
  }
  T &operator[](const LineCoord2D<size_t> &coord) {
    return const_cast<T &>(static_cast<const GridGraph *>(this)->operator[](coord));
  }

  template <typename U>
  bool in_bounds(const LineCoord2D<U> &coord) const {
    if (coord.x() < 0 || coord.y() < 0) {
      return false;
    }
    if (coord.dir() == Direction2D::DOWN) {
      return coord.x() < width() && coord.y() + 1 < height();
    } else if (coord.dir() == Direction2D::RIGHT) {
      return coord.x() + 1 < width() && coord.y() < height();
    }
    Fail("Invalid direction");
  }

  friend std::ostream &operator<<(std::ostream &os, const GridGraph &graph) {
    os << "GridGraph(" << graph.width() << ", " << graph.height() << ")" << std::endl;
    os << "Horizontal:" << std::endl;
    os << graph.horizontal() << std::endl;
    os << "Vertical:" << std::endl;
    os << graph.vertical() << std::endl;
    return os;
  }
};
