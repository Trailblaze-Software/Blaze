#pragma once

#include <algorithm>
#include <cmath>

#include "config_input/config_input.hpp"
#include "grid/grid.hpp"
#include "grid/grid_ops.hpp"
#include "utilities/coordinate.hpp"

template <typename T>
T round_down(T val, T interval) {
  if (val < 0) {
    return val - fmod(val, interval) - interval;
  } else {
    return val - fmod(val, interval);
  }
}

template <typename T>
inline bool crosses_contour(T h1, T h2, T contour_interval) {
  T max = std::max(h1, h2);
  T min = std::min(h1, h2);
  return round_down(max, contour_interval) > min;
}

template <typename T>
inline std::set<T> get_contour_heights(T h1, T h2, T contour_interval) {
  std::set<T> heights;
  T max = std::max(h1, h2);
  T min = std::min(h1, h2);
  for (T h = round_down(max, contour_interval); h > min; h -= contour_interval) {
    heights.insert(h);
  }
  return heights;
}

template <typename T, typename U>
Coordinate2D<T> interpolate_coordinates(const Coordinate2D<T>& a, const Coordinate2D<T>& b,
                                        const U& a_val, const U& b_val, const U& target) {
  double a_weight;
  if (a_val == b_val) {
    a_weight = 0.5;
  } else {
    a_weight = (double)(b_val - target) / (b_val - a_val);
  }
  double b_weight = 1 - a_weight;
  return Coordinate2D<T>(a.x() * a_weight + b.x() * b_weight, a.y() * a_weight + b.y() * b_weight);
}

class Polyline;

class Contour {
  double m_height;
  std::vector<Coordinate2D<double>> m_points;
  bool m_is_loop = false;

 public:
  Contour(double height, std::vector<Coordinate2D<double>>&& points)
      : m_height(height), m_points(std::move(points)) {
    if (m_points.size() > 1) {
      const auto& front = m_points.front();
      const auto& back = m_points.back();
      m_is_loop = (front - back).magnitude_sqd() < 1e-10;
    }
  }

  static Contour from_polyline(const Polyline& polyline);
  Polyline to_polyline(const ContourConfigs& configs) const;

  double height() const { return m_height; }
  const std::vector<Coordinate2D<double>>& points() const { return m_points; }
  std::vector<Coordinate2D<double>>& points() { return m_points; }

  static Contour FromGridGraph(const LineCoord2D<size_t>& starting_point, double height,
                               const GeoGrid<double>& grid,
                               GridGraph<std::set<double>>& contour_heights) {
    std::vector<Coordinate2D<double>> contour_points;
    int pass = 0;
    for (Direction2D dir : starting_point.dir().orthogonal_dirs()) {
      std::vector<Coordinate2D<double>> this_contour_points;
      LineCoord2DCrossing<size_t> current_point(starting_point, dir);
      bool end = false;
      bool first_iter = true;
      while (!end) {
        if (!first_iter || pass > 0) {
          auto it = contour_heights[current_point].find(height);
          if (it == contour_heights[current_point].end()) {
            AssertEQ(first_iter, true);
            AssertEQ(pass, 1);
            break;
          }
          contour_heights[current_point].erase(it);
        }
        first_iter = false;
        this_contour_points.emplace_back(interpolate_coordinates(
            grid.transform().pixel_to_projection(current_point.start().offset_to_center()),
            grid.transform().pixel_to_projection(current_point.end().offset_to_center()),
            grid[current_point.start()], grid[current_point.end()], height));
        end = true;
        for (LineCoord2DCrossing<size_t> next_point : current_point.next_points()) {
          if (contour_heights.in_bounds(next_point) &&
              contour_heights[next_point].contains(height)) {
            current_point = next_point;
            end = false;
            break;
          }
        }
      }
      if (pass == 0) {
        std::reverse_copy(this_contour_points.begin(), this_contour_points.end(),
                          std::back_inserter(contour_points));
        pass += 1;
      } else {
        if (this_contour_points.size() > 0) contour_points.pop_back();
        std::copy(this_contour_points.begin(), this_contour_points.end(),
                  std::back_inserter(contour_points));
      }
    }
    return Contour(height, std::move(contour_points));
  }

  void push_back(const Coordinate2D<double>& point) {
    m_points.push_back(point);
    if (m_points.size() > 1) {
      m_is_loop = (m_points.front() - m_points.back()).magnitude_sqd() < 1e-10;
    }
  }

  friend std::ostream& operator<<(std::ostream& os, const Contour& contour) {
    os << "Contour at height " << contour.height() << " with " << contour.points().size()
       << " points";
    return os;
  }

  bool is_loop() const { return m_is_loop; }

  // Orient contour so that left side (when following the line) is uphill
  void orient_consistent(const GeoGrid<double>& elevation_grid) {
    if (m_points.size() < 2) return;

    // Sample several points along the contour to determine orientation
    // Use a reasonable number of samples (not all points for performance)
    size_t num_samples = std::min(static_cast<size_t>(20), m_points.size() - 1);
    size_t step = (m_points.size() - 1) / num_samples;
    if (step == 0) step = 1;

    int left_higher_count = 0;
    int right_higher_count = 0;
    double offset_distance = elevation_grid.transform().dx() * 0.1;  // 10% of grid resolution

    for (size_t i = 0; i < m_points.size() - 1; i += step) {
      const auto& p1 = m_points[i];
      const auto& p2 = m_points[i + 1];

      // Calculate direction vector
      Coordinate2D<double> dir = p2 - p1;
      double dir_length = dir.magnitude();
      if (dir_length < 1e-10) continue;

      // Normalize direction
      dir = Coordinate2D<double>(dir.x() / dir_length, dir.y() / dir_length);

      // Calculate perpendicular vector pointing left (90 degrees counterclockwise)
      // For a vector (dx, dy), the left perpendicular is (-dy, dx)
      Coordinate2D<double> left_perp(-dir.y(), dir.x());

      // Sample point at the middle of the segment
      Coordinate2D<double> mid_point((p1.x() + p2.x()) / 2.0, (p1.y() + p2.y()) / 2.0);

      // Points to the left and right
      Coordinate2D<double> left_point =
          mid_point +
          Coordinate2D<double>(left_perp.x() * offset_distance, left_perp.y() * offset_distance);
      Coordinate2D<double> right_point =
          mid_point -
          Coordinate2D<double>(left_perp.x() * offset_distance, left_perp.y() * offset_distance);

      // Sample elevations (with bounds checking)
      // Check if points are within grid bounds before interpolating
      // interpolate_value requires points to be at least 0.5 pixels from edges for bilinear
      // interpolation
      Coordinate2D<double> left_pixel = elevation_grid.transform().projection_to_pixel(left_point);
      Coordinate2D<double> right_pixel =
          elevation_grid.transform().projection_to_pixel(right_point);

      if (left_pixel.x() >= 0.5 && left_pixel.y() >= 0.5 &&
          left_pixel.x() < elevation_grid.width() - 0.5 &&
          left_pixel.y() < elevation_grid.height() - 0.5 && right_pixel.x() >= 0.5 &&
          right_pixel.y() >= 0.5 && right_pixel.x() < elevation_grid.width() - 0.5 &&
          right_pixel.y() < elevation_grid.height() - 0.5) {
        double left_elev = interpolate_value(elevation_grid, left_point);
        double right_elev = interpolate_value(elevation_grid, right_point);

        if (std::isfinite(left_elev) && std::isfinite(right_elev) && left_elev < 1e6 &&
            right_elev < 1e6) {  // Check for valid elevation values
          if (left_elev > right_elev) {
            left_higher_count++;
          } else if (right_elev > left_elev) {
            right_higher_count++;
          }
        }
      }
    }

    // If more segments have right side higher, reverse the contour
    if (right_higher_count > left_higher_count) {
      std::reverse(m_points.begin(), m_points.end());
    }
  }
};
