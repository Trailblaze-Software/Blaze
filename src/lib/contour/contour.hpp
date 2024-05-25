#pragma once

#include <cmath>

#include "config_input/config_input.hpp"
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

class Polyline;

class Contour {
  double m_height;
  bool m_is_loop;
  std::vector<Coordinate2D<double>> m_points;

 public:
  Contour(double height, std::vector<Coordinate2D<double>> &&points)
      : m_height(height), m_points(std::move(points)) {
    if (m_points.size() > 1) {
      m_is_loop = (m_points[0] - m_points.back()).magnitude_sqd() < 1e-10;
    }
  }

  static Contour from_polyline(const Polyline &polyline);

  Polyline to_polyline(const ContourConfigs &configs) const;

  double height() const { return m_height; }
  const std::vector<Coordinate2D<double>> &points() const { return m_points; }
  std::vector<Coordinate2D<double>> &points() { return m_points; }

  static Contour FromGridGraph(const LineCoord2D<size_t> &starting_point,
                               const GeoGrid<double> &grid, GridGraph<char> &is_contour,
                               const ContourConfigs &configs) {
    double contour_interval = configs.min_interval.in(au::Meters{});
    std::pair<double, double> heights = grid.get_values(starting_point);
    double max_height = std::max(heights.first, heights.second);
    double contour_height = max_height - fmod(max_height, contour_interval);

    std::vector<Coordinate2D<double>> contour_points;
    int pass = 0;
    for (Direction2D dir : starting_point.dir().orthogonal_dirs()) {
      std::vector<Coordinate2D<double>> this_contour_points;
      LineCoord2DCrossing<size_t> current_point(starting_point, dir);
      bool end = false;
      bool first_iter = true;
      while (!end) {
        if (!first_iter || pass > 0) is_contour[current_point] = false;
        first_iter = false;
        this_contour_points.emplace_back(interpolate_coordinates(
            grid.transform().pixel_to_projection(current_point.start().offset_to_center()),
            grid.transform().pixel_to_projection(current_point.end().offset_to_center()),
            grid[current_point.start()], grid[current_point.end()], contour_height));
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
      if (pass == 0) {
        std::reverse_copy(this_contour_points.begin(), this_contour_points.end(),
                          std::back_inserter(contour_points));
        contour_points.pop_back();
        pass += 1;
      } else {
        std::copy(this_contour_points.begin(), this_contour_points.end(),
                  std::back_inserter(contour_points));
      }
    }
    return Contour(contour_height, std::move(contour_points));
  }

  void push_back(const Coordinate2D<double> &point) {
    m_points.push_back(point);
    if (m_points.size() > 1) {
      m_is_loop = (m_points[0] - m_points.back()).magnitude_sqd() < 1e-10;
    }
  }

  friend std::ostream &operator<<(std::ostream &os, const Contour &contour) {
    os << "Contour at height " << contour.height() << " with " << contour.points().size()
       << " points";
    return os;
  }
};
