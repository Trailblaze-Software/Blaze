

# File contour.hpp

[**File List**](files.md) **>** [**contour**](dir_168d7404e8aa1148a0abea8bd7ba0546.md) **>** [**contour.hpp**](contour_8hpp.md)

[Go to the documentation of this file](contour_8hpp.md)


```C++
#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <limits>
#include <optional>
#include <string>
#include <utility>

#include "config_input/config_input.hpp"
#include "grid/grid.hpp"
#include "grid/grid_ops.hpp"
#include "utilities/coordinate.hpp"

template <typename T>
T round_down(T val, T interval) {
  return interval * std::floor(val / interval);
}

template <typename T>
inline bool crosses_contour(std::pair<T, T> hs, T contour_interval) {
  // True if the pair of heights crosses the contour interval. Includes the maximum height being a
  // multiple of the interval but not the minimum height to ensure that crosses_interval({a,b}, i)
  // and crosses_interval({b, c}) do not double count where a<b<c.
  T max = std::max(hs.first, hs.second);
  T min = std::min(hs.first, hs.second);
  return round_down(max, contour_interval) > min;
}

template <typename T>
inline std::set<T> get_contour_heights(std::pair<T, T> hs, T contour_interval) {
  std::set<T> heights;
  T max = std::max(hs.first, hs.second);
  T min = std::min(hs.first, hs.second);
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
  std::string m_layer_name;
  bool m_is_loop = false;

 public:
  Contour(double height, std::vector<Coordinate2D<double>>&& points, std::string layer_name = "")
      : m_height(height), m_points(std::move(points)), m_layer_name(std::move(layer_name)) {
    if (m_points.size() > 1) {
      const auto& front = m_points.front();
      const auto& back = m_points.back();
      m_is_loop = (front - back).magnitude_sqd() < 1e-10;
    }
  }

  static Contour from_polyline(const Polyline& polyline);
  Polyline to_polyline(const ContourConfigs& configs) const;

  double height() const { return m_height; }
  const std::string& layer_name() const { return m_layer_name; }
  const std::vector<Coordinate2D<double>>& points() const { return m_points; }
  std::vector<Coordinate2D<double>>& points() { return m_points; }

  template <typename T>
  static Contour FromGridGraph(const LineCoord2D<size_t>& starting_point, double height,
                               const GeoGrid<T>& grid, GridGraph<std::set<double>>& contour_heights,
                               SaddlePolicy saddle_policy = SaddlePolicy::ByHeight) {
    // Helper: bilinear centre of the marching-squares cell the crossing enters.
    auto bilinear_centre = [&](const LineCoord2DCrossing<size_t>& crossing) -> double {
      const auto& s = crossing.start();
      long long j, i;
      if (crossing.dir() == Direction2D::RIGHT) {
        // RIGHT edge (horizontal): crossing_dir == DOWN → enter cell below (s).
        // crossing_dir == UP   → enter cell above (s.y - 1).
        j = static_cast<long long>(s.x());
        i = crossing.crossing_dir() == Direction2D::DOWN ? static_cast<long long>(s.y())
                                                         : static_cast<long long>(s.y()) - 1;
      } else {
        // DOWN edge (vertical): crossing_dir == RIGHT → enter cell to the right (s).
        // crossing_dir == LEFT  → enter cell to the left (s.x - 1).
        j = crossing.crossing_dir() == Direction2D::RIGHT ? static_cast<long long>(s.x())
                                                          : static_cast<long long>(s.x()) - 1;
        i = static_cast<long long>(s.y());
      }
      if (j < 0 || i < 0 || j + 1 >= static_cast<long long>(grid.width()) ||
          i + 1 >= static_cast<long long>(grid.height())) {
        // Cell corners are not all addressable; treat as below threshold (separate).
        return height;
      }
      const size_t uj = static_cast<size_t>(j);
      const size_t ui = static_cast<size_t>(i);
      return 0.25 * (static_cast<double>(grid[{uj, ui}]) + static_cast<double>(grid[{uj + 1, ui}]) +
                     static_cast<double>(grid[{uj, ui + 1}]) +
                     static_cast<double>(grid[{uj + 1, ui + 1}]));
    };

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
            grid[current_point.start()], grid[current_point.end()], static_cast<T>(height)));
        end = true;

        // Collect all candidate next-edges that carry this contour height.
        std::vector<LineCoord2DCrossing<size_t>> candidates;
        for (LineCoord2DCrossing<size_t> next_point : current_point.next_points()) {
          if (contour_heights.in_bounds(next_point) &&
              contour_heights[next_point].contains(height)) {
            candidates.push_back(next_point);
          }
        }

        if (!candidates.empty()) {
          if (candidates.size() == 1) {
            current_point = candidates[0];
          } else {
            // Saddle cell: which candidate "separates" (traces around one
            // above-threshold corner) vs "merges" (connects both above corners)
            // depends on which corner of the entry edge is above threshold.
            // Check the grid value at the start cell of the current edge.
            const T entry_val = grid[current_point.start()];
            const bool separate_is_first = (entry_val > static_cast<T>(height));

            const double centre = bilinear_centre(current_point);
            if (saddle_policy == SaddlePolicy::AlwaysInside) {
              current_point = separate_is_first ? candidates[1] : candidates[0];
            } else if (saddle_policy == SaddlePolicy::AlwaysOutside) {
              current_point = separate_is_first ? candidates[0] : candidates[1];
            } else {
              // ByHeight: centre > height → merge, else separate.
              if (centre > height) {
                current_point = separate_is_first ? candidates[1] : candidates[0];
              } else {
                current_point = separate_is_first ? candidates[0] : candidates[1];
              }
            }
          }
          end = false;
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

  // Snap the back endpoint onto the front to close a near-loop. No-op if the
  // contour has fewer than two points.
  void close_loop() {
    if (m_points.size() < 2) return;
    m_points.back() = m_points.front();
    m_is_loop = true;
  }

  friend std::ostream& operator<<(std::ostream& os, const Contour& contour) {
    os << "Contour at height " << contour.height() << " with " << contour.points().size()
       << " points";
    return os;
  }

  bool is_loop() const { return m_is_loop; }

  // Orient contour so that higher grid values are on the left when following the
  // line. For elevation contours this means uphill is on the left; for density
  // grids the above-threshold side is on the left. CCW outer rings then have
  // positive signed area; CW hole rings have negative signed area.
  template <typename T>
  void orient_consistent(const GeoGrid<T>& value_grid) {
    if (m_points.size() < 2) return;

    auto try_sample = [&](const Coordinate2D<double>& point) -> std::optional<double> {
      Coordinate2D<double> pixel = value_grid.transform().projection_to_pixel(point);
      if (pixel.x() < 0.0 || pixel.y() < 0.0 ||
          pixel.x() >= static_cast<double>(value_grid.width()) ||
          pixel.y() >= static_cast<double>(value_grid.height())) {
        return std::nullopt;
      }
      double val = interpolate_value(value_grid, point);
      if (!std::isfinite(val) || val >= 1e6) {
        return std::nullopt;
      }
      return val;
    };

    auto orient_from_offset = [&](double offset_distance) -> bool {
      size_t num_samples = std::min(static_cast<size_t>(20), m_points.size() - 1);
      size_t step = (m_points.size() - 1) / num_samples;
      if (step == 0) step = 1;

      int samples = 0;
      double higher_on_left_score = 0.0;

      for (size_t i = 0; i < m_points.size() - 1; i += step) {
        const auto& p1 = m_points[i];
        const auto& p2 = m_points[i + 1];

        Coordinate2D<double> dir = p2 - p1;
        double dir_length = dir.magnitude();
        if (dir_length < 1e-10) continue;

        dir = Coordinate2D<double>(dir.x() / dir_length, dir.y() / dir_length);
        Coordinate2D<double> left_perp(-dir.y(), dir.x());
        Coordinate2D<double> mid_point((p1.x() + p2.x()) / 2.0, (p1.y() + p2.y()) / 2.0);

        Coordinate2D<double> left_point =
            mid_point +
            Coordinate2D<double>(left_perp.x() * offset_distance, left_perp.y() * offset_distance);
        Coordinate2D<double> right_point =
            mid_point -
            Coordinate2D<double>(left_perp.x() * offset_distance, left_perp.y() * offset_distance);

        std::optional<double> left_val = try_sample(left_point);
        std::optional<double> right_val = try_sample(right_point);
        if (!left_val || !right_val) {
          continue;
        }

        higher_on_left_score += *left_val - *right_val;
        samples++;
      }

      if (samples > 0 && higher_on_left_score < 0.0) {
        std::reverse(m_points.begin(), m_points.end());
      }
      return samples > 0;
    };

    const double dx = value_grid.transform().dx();
    // Half a cell — 10% of dx lands in the same cell on coarse grids and ties on
    // smoothed threshold plateaus, leaving orientation arbitrary.
    if (!orient_from_offset(dx * 0.5)) {
      // Near padded borders many 0.5-cell offsets fall outside the grid; retry closer in.
      orient_from_offset(dx * 0.25);
    }
  }
};
```


