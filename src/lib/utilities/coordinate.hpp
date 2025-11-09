#pragma once

#include <array>
#include <cmath>
#include <iostream>
#include <ostream>
#include <type_traits>
#include <vector>

#include "assert/assert.hpp"

class Direction2D {
 public:
  enum Dir { UP, DOWN, LEFT, RIGHT, UR, UL, DR, DL };

 private:
  Dir m_dir;

 public:
  Direction2D(Dir dir) : m_dir(dir) {}
  operator Dir() const { return m_dir; }

  std::array<Direction2D, 2> orthogonal_dirs() const {
    if (m_dir == DOWN || m_dir == UP) return {{LEFT, RIGHT}};
    return {{UP, DOWN}};
  }
  bool orthogonal_to(Direction2D other) const {
    return ((m_dir == UP || m_dir == DOWN) && (other.m_dir == LEFT || other.m_dir == RIGHT)) ||
           ((m_dir == LEFT || m_dir == RIGHT) && (other.m_dir == UP || other.m_dir == DOWN));
  }

  int dx() const {
    switch (m_dir) {
      case UP:
      case DOWN:
        return 0;
      case LEFT:
      case UL:
      case DL:
        return -1;
      case RIGHT:
      case UR:
      case DR:
        return 1;
    }
    unreachable();
  }

  int dy() const {
    switch (m_dir) {
      case UP:
      case UR:
      case UL:
        return -1;
      case DOWN:
      case DR:
      case DL:
        return 1;
      case LEFT:
      case RIGHT:
        return 0;
    }
    unreachable();
  }

  Direction2D opposite() const {
    switch (m_dir) {
      case UP:
        return Direction2D(DOWN);
      case DOWN:
        return Direction2D(UP);
      case LEFT:
        return Direction2D(RIGHT);
      case RIGHT:
        return Direction2D(LEFT);
      case UR:
        return Direction2D(DL);
      case UL:
        return Direction2D(DR);
      case DR:
        return Direction2D(UL);
      case DL:
        return Direction2D(UR);
    }
    unreachable();
  }

  friend std::ostream &operator<<(std::ostream &os, const Direction2D &dir) {
    switch (dir.m_dir) {
      case UP:
        os << "UP";
        break;
      case DOWN:
        os << "DOWN";
        break;
      case LEFT:
        os << "LEFT";
        break;
      case RIGHT:
        os << "RIGHT";
        break;
      case UR:
        os << "UR";
        break;
      case UL:
        os << "UL";
        break;
      case DR:
        os << "DR";
        break;
      case DL:
        os << "DL";
        break;
    }
    return os;
  }
};

const std::array<Direction2D, 4> ORTHOGONAL_DIRECTIONS = {
    Direction2D(Direction2D::UP), Direction2D(Direction2D::DOWN), Direction2D(Direction2D::LEFT),
    Direction2D(Direction2D::RIGHT)};

const std::array<Direction2D, 8> ALL_DIRECTIONS = {
    Direction2D(Direction2D::UP),    Direction2D(Direction2D::DOWN), Direction2D(Direction2D::LEFT),
    Direction2D(Direction2D::RIGHT), Direction2D(Direction2D::UR),   Direction2D(Direction2D::UL),
    Direction2D(Direction2D::DR),    Direction2D(Direction2D::DL)};

template <typename T>
class Coordinate2D {
  static_assert(std::is_arithmetic<T>::value, "Coordinate2D only supports arithmetic types");

  std::array<T, 2> m_data;

 public:
  Coordinate2D(T x, T y) : m_data{{x, y}} {}

  Coordinate2D() = default;

  const T &x() const { return m_data[0]; }
  const T &y() const { return m_data[1]; }
  T &x() { return m_data[0]; }
  T &y() { return m_data[1]; }

  template <typename U>
  operator Coordinate2D<U>() const {
    return Coordinate2D<U>(x(), y());
  }

  Coordinate2D<double> offset_to_center() const {
    return Coordinate2D<double>(x() + 0.5, y() + 0.5);
  }

  Coordinate2D<double> round_NW(double grid_size) const {
    return Coordinate2D<double>(x() - fmod(x(), grid_size), y() + grid_size - fmod(y(), grid_size));
  }

  Coordinate2D<size_t> round() const { return Coordinate2D<size_t>(x() + 0.5, y() + 0.5); }

  friend std::ostream &operator<<(std::ostream &os, const Coordinate2D &coord) {
    os << "Coordinate2D(" << coord.x() << ", " << coord.y() << ")";
    return os;
  }

  Coordinate2D operator+(Direction2D dir) const {
    switch (dir) {
      case Direction2D::UP:
        return Coordinate2D(x(), y() - 1);
      case Direction2D::DOWN:
        return Coordinate2D(x(), y() + 1);
      case Direction2D::LEFT:
        return Coordinate2D(x() - 1, y());
      case Direction2D::RIGHT:
        return Coordinate2D(x() + 1, y());
      case Direction2D::UR:
        return Coordinate2D(x() + 1, y() - 1);
      case Direction2D::UL:
        return Coordinate2D(x() - 1, y() - 1);
      case Direction2D::DR:
        return Coordinate2D(x() + 1, y() + 1);
      case Direction2D::DL:
        return Coordinate2D(x() - 1, y() + 1);
    }
    unreachable();
  }

  Coordinate2D operator+(Coordinate2D o) const { return Coordinate2D(x() + o.x(), y() + o.y()); }
  Coordinate2D operator-(Coordinate2D o) const { return Coordinate2D(x() - o.x(), y() - o.y()); }
  bool operator==(const Coordinate2D &o) const { return x() == o.x() && y() == o.y(); }

  T magnitude_sqd() const { return x() * x() + y() * y(); }
  T magnitude() const { return std::sqrt(magnitude_sqd()); }
};

template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
std::array<Coordinate2D<T>, 4> orthogonal_neighbors(const Coordinate2D<T> &coord) {
  return {Coordinate2D<T>(coord.x() - 1, coord.y()), Coordinate2D<T>(coord.x() + 1, coord.y()),
          Coordinate2D<T>(coord.x(), coord.y() - 1), Coordinate2D<T>(coord.x(), coord.y() + 1)};
}

template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
class LineCoord2D : public Coordinate2D<T> {
  Direction2D m_dir;

 public:
  LineCoord2D(T x, T y, Direction2D dir) : Coordinate2D<T>(x, y), m_dir(dir) {}
  LineCoord2D(const Coordinate2D<T> &coord, Direction2D dir) : Coordinate2D<T>(coord), m_dir(dir) {}
  Coordinate2D<T> start() const { return *this; }
  Coordinate2D<T> end() const { return *this + m_dir; }

  Direction2D dir() const { return m_dir; }

  friend std::ostream &operator<<(std::ostream &os, const LineCoord2D &line_coord) {
    os << "LineCoord2D(" << line_coord.start() << ", " << line_coord.dir() << ")";
    return os;
  }
};

template <typename T>
class Coordinate3D : public Coordinate2D<T> {
  double m_z;

 public:
  Coordinate3D(T x, T y, T z) : Coordinate2D<T>(x, y), m_z(z) {}

  Coordinate3D() = default;

  const T z() const { return m_z; }
  T &z() { return m_z; }
};

template <typename T>
class LineCoord2DCrossing : public LineCoord2D<T> {
  Direction2D m_crossing_dir;

 public:
  LineCoord2DCrossing(T x, T y, Direction2D dir, Direction2D crossing_dir)
      : LineCoord2D<T>(x, y, dir), m_crossing_dir(crossing_dir) {}
  LineCoord2DCrossing(const LineCoord2D<T> &line_coord, Direction2D crossing_dir)
      : LineCoord2D<T>(line_coord), m_crossing_dir(crossing_dir) {}

  Direction2D crossing_dir() const { return m_crossing_dir; }

  LineCoord2DCrossing flip() const {
    return LineCoord2DCrossing({LineCoord2D<T>::end(), LineCoord2D<T>::dir().opposite()},
                               m_crossing_dir);
  }

  std::vector<LineCoord2DCrossing> next_points() const {
    std::vector<LineCoord2DCrossing> result;

    std::vector<Direction2D> dirs;
    if (LineCoord2D<T>::dir().orthogonal_to(crossing_dir())) {
      dirs.emplace_back(crossing_dir());
    } else {
      for (Direction2D dir :
           {Direction2D::UP, Direction2D::DOWN, Direction2D::LEFT, Direction2D::RIGHT}) {
        if (dir.orthogonal_to(LineCoord2D<T>::dir())) {
          dirs.emplace_back(dir);
        }
      }
    }

    for (Direction2D dir : dirs) {
      Assert(dir.orthogonal_to(LineCoord2D<T>::dir()),
             "Crossing direction is not orthogonal to direction");
      result.emplace_back(LineCoord2DCrossing<T>({LineCoord2D<T>::start() + dir, dir.opposite()},
                                                 LineCoord2D<T>::dir().opposite()));
      result.emplace_back(LineCoord2DCrossing<T>({LineCoord2D<T>::end() + dir, dir.opposite()},
                                                 LineCoord2D<T>::dir()));
      result.emplace_back(
          LineCoord2DCrossing<T>({LineCoord2D<T>::start() + dir, LineCoord2D<T>::dir()}, dir));
    }

    for (size_t i = 0; i < result.size(); i++) {
      if (result[i].dir() == Direction2D::UP || result[i].dir() == Direction2D::LEFT) {
        result[i] = result[i].flip();
      }
    }

    return result;
  }

  friend std::ostream &operator<<(std::ostream &os, const LineCoord2DCrossing &line_coord) {
    os << "LineCoord2DCrossing(" << line_coord.start() << ", " << line_coord.dir() << ", "
       << line_coord.crossing_dir() << ")";
    return os;
  }
};

struct Extent2D {
  double minx = std::numeric_limits<double>::infinity();
  double maxx = -std::numeric_limits<double>::infinity();
  double miny = std::numeric_limits<double>::infinity();
  double maxy = -std::numeric_limits<double>::infinity();

  bool contains(double x, double y) const {
    return minx <= x && x <= maxx && miny <= y && y <= maxy;
  }

  void grow(const Extent2D &other) {
    minx = std::min(minx, other.minx);
    maxx = std::max(maxx, other.maxx);
    miny = std::min(miny, other.miny);
    maxy = std::max(maxy, other.maxy);
  }

  friend std::ostream &operator<<(std::ostream &os, const Extent2D &extent) {
    return os << "[(" << extent.minx << ", " << extent.maxx << "), (" << extent.miny << ", "
              << extent.maxy << ")]";
  }
};

struct Extent3D : Extent2D {
  double minz = std::numeric_limits<double>::infinity();
  double maxz = -std::numeric_limits<double>::infinity();

  Extent3D() = default;
  Extent3D(const Extent2D &extent, double minz, double maxz)
      : Extent2D(extent), minz(minz), maxz(maxz) {}
  Extent3D(double minx, double maxx, double miny, double maxy, double minz, double maxz)
      : Extent2D{minx, maxx, miny, maxy}, minz(minz), maxz(maxz) {}

  void grow(double x, double y, double z) {
    minx = std::min(x, minx);
    maxx = std::max(x, maxx);
    miny = std::min(y, miny);
    maxy = std::max(y, maxy);
    minz = std::min(z, minz);
    maxz = std::max(z, maxz);
  }

  void grow(double border) {
    minx -= border;
    maxx += border;
    miny -= border;
    maxy += border;
    minz -= border;
    maxz += border;
  }

  bool intersects(const Extent3D &other) const {
    return !(other.minx > maxx || other.maxx < minx || other.miny > maxy || other.maxy < miny ||
             other.minz > maxz || other.maxz < minz);
  }

  Coordinate3D<double> center() const {
    return Coordinate3D<double>((minx + maxx) / 2, (miny + maxy) / 2, (minz + maxz) / 2);
  }

  double max_extent() const { return std::max(std::max(maxx - minx, maxy - miny), maxz - minz); }

  void grow(const Extent3D &other) {
    Extent2D::grow(other);
    minz = std::min(minz, other.minz);
    maxz = std::max(maxz, other.maxz);
  }

  Extent3D operator-(const Coordinate3D<double> &offset) const {
    return {minx - offset.x(), maxx - offset.x(), miny - offset.y(),
            maxy - offset.y(), minz - offset.z(), maxz - offset.z()};
  }

  Extent3D intersection(const Extent3D &other) const {
    return {std::max(minx, other.minx), std::min(maxx, other.maxx), std::max(miny, other.miny),
            std::min(maxy, other.maxy), std::max(minz, other.minz), std::min(maxz, other.maxz)};
  }

  bool operator!=(const Extent3D &other) const {
    return minx != other.minx || maxx != other.maxx || miny != other.miny || maxy != other.maxy ||
           minz != other.minz || maxz != other.maxz;
  }

  friend std::ostream &operator<<(std::ostream &os, const Extent3D &extent) {
    return os << "[(" << extent.minx << ", " << extent.maxx << "), (" << extent.miny << ", "
              << extent.maxy << "), (" << extent.minz << ", " << extent.maxz << ")]";
  }
};
