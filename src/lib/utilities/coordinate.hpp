#pragma once

#include <array>
#include <cstddef>
#include <ostream>

template<typename T>
class Coordinate2D {
  static_assert(std::is_arithmetic<T>::value, "Coordinate2D only supports arithmetic types");

  std::array<T, 2> m_data;

public:
  Coordinate2D(T x, T y) : m_data{x, y} {}

  T x() const { return m_data[0]; }
  T y() const { return m_data[1]; }

  template<typename U>
  operator Coordinate2D<U>() const { return Coordinate2D<U>(x(), y()); }

  friend std::ostream& operator<<(std::ostream& os, const Coordinate2D& coord) {
    os << "Coordinate2D(" << coord.x() << ", " << coord.y() << ")";
    return os;
  }
};

template <typename T>
class Coordinate3D : public Coordinate2D<T>{
  double m_z;

public:
  Coordinate3D(T x, T y, T z) : Coordinate2D<T>(x, y), m_z(z) {}

  T z() const { return m_z; }
};
