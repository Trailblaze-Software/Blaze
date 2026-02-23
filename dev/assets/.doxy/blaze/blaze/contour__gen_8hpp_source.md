

# File contour\_gen.hpp

[**File List**](files.md) **>** [**contour**](dir_168d7404e8aa1148a0abea8bd7ba0546.md) **>** [**contour\_gen.hpp**](contour__gen_8hpp.md)

[Go to the documentation of this file](contour__gen_8hpp.md)


```C++
#pragma once

#include "config_input/config_input.hpp"
#include "contour.hpp"
#include "utilities/timer.hpp"

template <typename T>
GridGraph<std::set<double>> identify_contours(const GeoGrid<T>& grid, T contour_interval) {
  TimeFunction timer("identifying contours");
  GridGraph contour_heights = GridGraph<std::set<double>>(grid);
#pragma omp parallel for
  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      Coordinate2D<size_t> coord = {j, i};
      for (Direction2D dir : {Direction2D::DOWN, Direction2D::RIGHT}) {
        LineCoord2D<size_t> line_coord = {coord, dir};
        if (contour_heights.in_bounds(line_coord)) {
          contour_heights[line_coord] = get_contour_heights(
              {grid[line_coord.start()], grid[line_coord.end()]}, contour_interval);
        }
      }
    }
  }
  return contour_heights;
}

inline std::vector<Contour> join_contours(std::vector<Contour> contours, double max_dist = 15.0) {
  const double max_dist2 = max_dist * max_dist;

  // Only consider the two cases that allow joining without reversal:
  // a.back ↔ b.front (append) and a.front ↔ b.back (prepend)
  struct JoiningOption {
    bool use_front_a;  // true = prepend to a.front, false = append to a.back
    bool use_front_b;  // true = b.front matches, false = b.back matches
  };
  static constexpr JoiningOption cases[] = {
      {false, true},  // a.back   ↔ b.front (append b forward)
      {true, false},  // a.front  ↔ b.back (prepend b forward)
  };

  bool did_any_join = true;
  std::vector<Contour> next_round;

  while (did_any_join) {
    did_any_join = false;
    next_round.clear();

    for (auto& src : contours) {
      const auto& b = src.points();

      double best_d2 = max_dist2;
      int best_idx = -1;
      JoiningOption best_case{};
      for (int i = 0; i < (int)next_round.size(); ++i) {
        const auto& a = next_round[i].points();
        for (JoiningOption c : cases) {
          const auto& pa = (c.use_front_a ? a.front() : a.back());
          const auto& pb = (c.use_front_b ? b.front() : b.back());
          double d2 = (pa - pb).magnitude_sqd();
          if (d2 < best_d2) {
            best_d2 = d2;
            best_idx = i;
            best_case = c;
          }
        }
      }
      if (best_idx >= 0) {
        auto& acc = next_round[best_idx].points();
        // Join without reversing: only two cases are considered
        if (best_case.use_front_a) {
          // a.front ↔ b.back: prepend b forward (skip duplicate join point b.back)
          if (b.size() > 1) {
            acc.insert(acc.begin(), b.begin(), b.end() - 1);
          }
        } else {
          // a.back ↔ b.front: append b forward (skip duplicate join point b.front)
          if (b.size() > 1) {
            acc.insert(acc.end(), b.begin() + 1, b.end());
          }
        }
        did_any_join = true;
      } else {
        next_round.emplace_back(std::move(src));
      }
    }
    contours = std::move(next_round);
  }

  return contours;
}

inline std::vector<Contour> trim_contours(const std::vector<Contour>& contours,
                                          const Extent2D& bounds) {
  std::vector<Contour> trimmed_contours;
  for (const Contour& c : contours) {
    Contour trimmed_contour(c.height(), std::vector<Coordinate2D<double>>{});
    for (const Coordinate2D<double>& point : c.points()) {
      if (bounds.contains(point.x(), point.y())) {
        trimmed_contour.push_back(point);
      } else if (trimmed_contour.points().size() > 0) {
        trimmed_contours.emplace_back(std::move(trimmed_contour));
        trimmed_contour = Contour(c.height(), std::vector<Coordinate2D<double>>{});
      }
    }
    if (trimmed_contour.points().size() > 0) {
      trimmed_contours.emplace_back(std::move(trimmed_contour));
    }
  }
  return trimmed_contours;
}

template <typename T>
std::vector<Contour> generate_contours(const GeoGrid<T>& grid, const ContourConfigs& contour_config,
                                       ProgressTracker progress_tracker) {
  TimeFunction timer("generating contours", &progress_tracker);
  GridGraph is_contour = identify_contours(grid, contour_config.min_interval);
  std::vector<Contour> contours;
  for (size_t i = 0; i < is_contour.height(); i++) {
    for (size_t j = 0; j < is_contour.width(); j++) {
      Coordinate2D<size_t> coord = {j, i};
      for (Direction2D dir : {Direction2D::DOWN, Direction2D::RIGHT}) {
        LineCoord2D<size_t> line_coord = {coord, dir};
        if (is_contour.in_bounds(line_coord)) {
          for (double height : std::set<double>(is_contour[line_coord])) {
            Contour c = Contour::FromGridGraph(line_coord, height, grid, is_contour);
            // TODO use length instead of number of points
            if (c.points().size() > contour_config.pick_from_height(c.height()).min_points) {
              contours.emplace_back(std::move(c));
            }
          }
        }
      }
    }
  }
  progress_tracker.text_update("Generated " + std::to_string(contours.size()) + " contours");
  return contours;
}

inline GeoGrid<std::optional<std::byte>> generate_naive_contours(const GeoGrid<double>& ground) {
  GeoGrid<std::optional<std::byte>> naive_countours = GeoGrid<std::optional<std::byte>>(
      ground.width(), ground.height(), GeoTransform(ground.transform()),
      GeoProjection(ground.projection()));

  double contour_interval = 2.5;
  for (size_t i = 1; i < ground.height() - 1; i++) {
    for (size_t j = 1; j < ground.width() - 1; j++) {
      double z = ground[{i, j}];
      double z_north = ground[{i - 1, j}];
      double z_south = ground[{i + 1, j}];
      double z_west = ground[{i, j - 1}];
      double z_east = ground[{i, j + 1}];
      bool is_countour = crosses_contour({z, z_north}, contour_interval) ||
                         crosses_contour({z, z_south}, contour_interval) ||
                         crosses_contour({z, z_west}, contour_interval) ||
                         crosses_contour({z, z_east}, contour_interval);
      naive_countours[{i, j}] = is_countour ? std::optional<std::byte>{std::byte{0}} : std::nullopt;
    }
  }
  return naive_countours;
}
```


