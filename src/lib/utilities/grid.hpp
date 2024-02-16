#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "coordinate.hpp"
#include "assert/assert.hpp"

class GeoTransform {
  double geoTranform[6];
  public:
    GeoTransform(double upper_left_x, double upper_left_y, double dx = 1.0, double dy = -1.0) {
      geoTranform[0] = upper_left_x; // center of top left pixel is 0.5, 0.5
      geoTranform[1] = dx; // w->e pixel resolution
      geoTranform[2] = 0; // Row rotation
      geoTranform[3] = upper_left_y;
      geoTranform[4] = 0; // Column rotation
      geoTranform[5] = dy; // n->s pixel resolution (so negative is up)
    }

    explicit GeoTransform(const Coordinate2D<double>& upper_left, double resolution) : GeoTransform(upper_left.x(), upper_left.y(), resolution, -resolution) {}

    GeoTransform() = default;

    const double* get_raw() const {
      return geoTranform;
    }

    Coordinate2D<double> pixel_to_projection(const Coordinate2D<double>& coord) const {
      double new_x = x() + coord.x() * dx() + coord.y() * rot_x();
      double new_y = y() + coord.y() * dy() + coord.x() * rot_y();
      return {new_x, new_y};
    }

    Coordinate2D<double> projection_to_pixel(const Coordinate2D<double>& coord) const {
      double new_x = (rot_x() * coord.y() - coord.x() * dy() - y() * rot_x() + x() * dy()) / (rot_x() * rot_y() - dy() * dx());
      double new_y = (rot_y() * coord.x() - coord.y() * dx() - x() * rot_y() + y() * dx()) / (rot_x() * rot_y() - dy() * dx());
      return {new_x, new_y};
    }

    friend std::ostream& operator<<(std::ostream& os, const GeoTransform& transform) {
      os << "GeoTransform(x: " << transform.x() << ", y: " << transform.y() << ", dx: " << transform.dx() << ", dy: " << transform.dy() << ", rot_x: " << transform.rot_x() << ", rot_y: " << transform.rot_y() << ")";
      return os;
    }
  private:

    double x() const {return geoTranform[0];}
    double dx() const {return geoTranform[1];}
    double rot_x() const {return geoTranform[2];}
    double y() const {return geoTranform[3];}
    double rot_y() const {return geoTranform[4];}
    double dy()  const {return geoTranform[5];}
};

class GeoProjection {
  std::string m_projection;

public:
  explicit GeoProjection(const std::string& projection) : m_projection(projection) {}

  GeoProjection() = default;

  const std::string& to_string() const {return m_projection;}
};


template <typename T>
class GeoGrid {
  size_t m_width;
  size_t m_height;
  std::vector<T> m_data;
  GeoTransform m_transform;
  GeoProjection m_projection;

public:
  GeoGrid(size_t width, size_t height, GeoTransform&& transform, GeoProjection&& projection) : m_width(width), m_height(height), m_data(width*height), m_transform(transform), m_projection(projection) {}

  T& operator[](Coordinate2D<size_t> coord) {
    return m_data[coord.y()*m_width + coord.x()];
  }
  const T& operator[](Coordinate2D<size_t> coord) const {
    return m_data[coord.y()*m_width + coord.x()];
  }

  size_t width() const {return m_width;}
  size_t height() const {return m_height;}
  const GeoTransform& transform() const {return m_transform;}
  const GeoProjection& projection() const {return m_projection;}
};
