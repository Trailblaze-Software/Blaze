#pragma once

#include <cmath>

#include "grid/grid.hpp"
#include "utilities/coordinate.hpp"

template <typename T>
inline bool crosses_contour(T h1, T h2, T contour_interval) {
  T max = std::max(h1, h2);
  T min = std::min(h1, h2);
  return max - fmod(max, contour_interval) > min;
}

template <typename T, typename U>
Coordinate2D<T> interpolate_coordinates(const Coordinate2D<T> &a, const Coordinate2D<T> &b,
                                        const U &a_val, const U &b_val, const U &target) {
  double a_weight = (double)(b_val - target) / (b_val - a_val);
  double b_weight = 1 - a_weight;
  return Coordinate2D<T>(a.x() * a_weight + b.x() * b_weight, a.y() * a_weight + b.y() * b_weight);
}

class Contour {
  double m_height;
  std::vector<Coordinate2D<double>> m_points;

 public:
  Contour(double height, std::vector<Coordinate2D<double>> &&points)
      : m_height(height), m_points(points) {}

  double height() const { return m_height; }
  const std::vector<Coordinate2D<double>> &points() const { return m_points; }

  static Contour FromGridGraph(const LineCoord2D<size_t> &starting_point,
                               const GeoGrid<double> &grid, GridGraph<char> &is_contour,
                               double contour_interval) {
    std::vector<Coordinate2D<double>> contour_points;
    std::pair<double, double> heights = grid.get_values(starting_point);
    double max_height = std::max(heights.first, heights.second);
    double contour_height = max_height - fmod(max_height, contour_interval);

    LineCoord2DCrossing<size_t> current_point(starting_point, starting_point.dir());
    bool end = false;
    bool first_iter = true;
    while (!end) {
      if (!first_iter)
        is_contour[current_point] = false;
      first_iter = false;
      contour_points.emplace_back(interpolate_coordinates(
          grid.transform().pixel_to_projection(current_point.start()),
          grid.transform().pixel_to_projection(current_point.end()), grid[current_point.start()],
          grid[current_point.end()], contour_height));
      end = true;
      for (LineCoord2DCrossing<size_t> next_point : current_point.next_points()) {
        if (is_contour.in_bounds(next_point) && is_contour[next_point]) {
          std::pair<double, double> next_heights = grid.get_values(next_point);
          double next_max_height = std::max(next_heights.first, next_heights.second);
          double next_min_height = std::min(next_heights.first, next_heights.second);
          if (next_max_height >= contour_height && contour_height >= next_min_height) {
            current_point = next_point;
            end = false;
            break;
          }
        }
      }
    }
    return Contour(contour_height, std::move(contour_points));
  }

  friend std::ostream &operator<<(std::ostream &os, const Contour &contour) {
    os << "Contour at height " << contour.height() << " with " << contour.points().size()
       << " points";
    return os;
  }
};
