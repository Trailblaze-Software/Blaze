#pragma once

#include <array>
#include <iostream>
#include <ostream>
#include <type_traits>
#include <vector>

class Direction2D {
 public:
  enum Dir { UP, DOWN, LEFT, RIGHT };

 private:
  Dir m_dir;

 public:
  Direction2D(Dir dir) : m_dir(dir) {}
  operator Dir() const { return m_dir; }

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
        return -1;
      case RIGHT:
        return 1;
    }
  }

  int dy() const {
    switch (m_dir) {
      case UP:
        return -1;
      case DOWN:
        return 1;
      case LEFT:
      case RIGHT:
        return 0;
    }
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
    }
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
    }
    return os;
  }
};

template <typename T>
class Coordinate2D {
  static_assert(std::is_arithmetic<T>::value, "Coordinate2D only supports arithmetic types");

  std::array<T, 2> m_data;

 public:
  Coordinate2D(T x, T y) : m_data{x, y} {}

  T x() const { return m_data[0]; }
  T y() const { return m_data[1]; }

  template <typename U>
  operator Coordinate2D<U>() const {
    return Coordinate2D<U>(x(), y());
  }

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
    }
  }
};

template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
std::array<Coordinate2D<T>, 4> orthogonal_neighbours(const Coordinate2D<T> &coord) {
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

  T z() const { return m_z; }
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
