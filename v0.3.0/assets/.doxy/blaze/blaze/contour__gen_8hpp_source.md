

# File contour\_gen.hpp

[**File List**](files.md) **>** [**contour**](dir_168d7404e8aa1148a0abea8bd7ba0546.md) **>** [**contour\_gen.hpp**](contour__gen_8hpp.md)

[Go to the documentation of this file](contour__gen_8hpp.md)


```C++
#pragma once

#include <map>
#include <optional>
#include <set>
#include <vector>

#include "config_input/config_input.hpp"
#include "contour.hpp"
#include "geometry/polygon.hpp"
#include "utilities/progress_tracker.hpp"
#include "utilities/timer.hpp"

namespace detail {

template <typename T>
double min_contour_loop_area_m2(const GeoGrid<T>& grid) {
  const double dx = grid.transform().dx();
  const double dy = grid.transform().dy();
  return 0.01 * std::abs(dx * dy);
}

template <typename T>
const GeoGrid<T>& work_grid_for_contours(const GeoGrid<T>& grid, std::optional<T> pad_value,
                                         std::optional<GeoGrid<T>>& padded_out) {
  if (pad_value.has_value()) {
    padded_out.emplace(grid.pad(*pad_value));
    return *padded_out;
  }
  return grid;
}

template <typename T, typename EdgeHeightsFn>
GridGraph<std::set<double>> identify_contour_crossings(const GeoGrid<T>& grid,
                                                       EdgeHeightsFn edge_heights) {
  GridGraph contour_heights = GridGraph<std::set<double>>(grid);
#pragma omp parallel for
  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      Coordinate2D<size_t> coord = {j, i};
      for (Direction2D dir : {Direction2D::DOWN, Direction2D::RIGHT}) {
        LineCoord2D<size_t> line_coord = {coord, dir};
        if (contour_heights.in_bounds(line_coord)) {
          T v1 = grid[line_coord.start()];
          T v2 = grid[line_coord.end()];
          contour_heights[line_coord] = edge_heights(v1, v2);
        }
      }
    }
  }
  return contour_heights;
}

template <typename T, typename AcceptFn, typename EmitFn>
void trace_contours(const GeoGrid<T>& grid, GridGraph<std::set<double>>& contour_heights,
                    AcceptFn accept, EmitFn emit) {
  for (size_t i = 0; i < contour_heights.height(); i++) {
    for (size_t j = 0; j < contour_heights.width(); j++) {
      Coordinate2D<size_t> coord = {j, i};
      for (Direction2D dir : {Direction2D::DOWN, Direction2D::RIGHT}) {
        LineCoord2D<size_t> line_coord = {coord, dir};
        if (!contour_heights.in_bounds(line_coord)) {
          continue;
        }
        for (double height : std::set<double>(contour_heights[line_coord])) {
          Contour c = Contour::FromGridGraph(line_coord, height, grid, contour_heights);
          if (accept(c)) {
            emit(height, std::move(c));
          }
        }
      }
    }
  }
}

}  // namespace detail

template <typename T>
GridGraph<std::set<double>> identify_contours(const GeoGrid<T>& grid, T contour_interval,
                                              ProgressTracker* progress_tracker = nullptr) {
  TimeFunction timer("identifying contours", progress_tracker);
  return detail::identify_contour_crossings(
      grid, [=](T v1, T v2) { return get_contour_heights({v1, v2}, contour_interval); });
}

// Variant of identify_contours that only records contour crossings at the specified
// heights. Useful when you want contours at a few specific values rather than at
// every multiple of an interval (e.g. vegetation density thresholds).
template <typename T>
GridGraph<std::set<double>> identify_contours_at_heights(
    const GeoGrid<T>& grid, const std::set<double>& heights,
    std::optional<T> pad_value = std::nullopt, ProgressTracker* progress_tracker = nullptr) {
  TimeFunction timer("identifying contours at heights", progress_tracker);
  std::optional<GeoGrid<T>> padded;
  const GeoGrid<T>& work_grid = detail::work_grid_for_contours(grid, pad_value, padded);
  return detail::identify_contour_crossings(work_grid, [&](T v1, T v2) {
    std::set<double> crossed;
    T max_val = std::max(v1, v2);
    T min_val = std::min(v1, v2);
    for (double h : heights) {
      // Record a crossing when the height falls strictly above min and at
      // or below max. Matches crosses_contour semantics for a single height
      // (max-inclusive).
      if (min_val < h && h <= max_val) {
        crossed.insert(h);
      }
    }
    return crossed;
  });
}

template <typename T>
GridGraph<std::set<double>> identify_contours_at_heights(
    const GeoGrid<T>& grid, const std::set<double>& heights, T pad_value,
    ProgressTracker* progress_tracker = nullptr) {
  return identify_contours_at_heights(grid, heights, std::optional<T>(pad_value), progress_tracker);
}

template <typename T>
std::map<double, std::vector<Contour>> generate_contours_at_heights(
    const GeoGrid<T>& grid, const std::vector<double>& heights, size_t min_points = 3,
    std::optional<T> pad_value = std::nullopt, ProgressTracker* progress_tracker = nullptr) {
  TimeFunction timer("generating contours at heights", progress_tracker);

  std::optional<GeoGrid<T>> padded;
  const GeoGrid<T>& work_grid = detail::work_grid_for_contours(grid, pad_value, padded);

  std::set<double> height_set(heights.begin(), heights.end());
  GridGraph<std::set<double>> contour_heights =
      identify_contours_at_heights(work_grid, height_set, std::optional<T>(), progress_tracker);

  std::map<double, std::vector<Contour>> contours_by_height;
  detail::trace_contours(
      work_grid, contour_heights, [&](const Contour& c) { return c.points().size() >= min_points; },
      [&](double height, Contour&& c) {
        c.orient_consistent(work_grid);
        if (c.is_loop()) {
          const double min_loop_area = detail::min_contour_loop_area_m2(work_grid);
          if (std::abs(signed_area(c.points())) < min_loop_area) {
            return;
          }
        }
        contours_by_height[height].emplace_back(std::move(c));
      });

  return contours_by_height;
}

template <typename T>
std::map<double, std::vector<Contour>> generate_contours_at_heights(
    const GeoGrid<T>& grid, const std::vector<double>& heights, size_t min_points, T pad_value,
    ProgressTracker* progress_tracker = nullptr) {
  return generate_contours_at_heights(grid, heights, min_points, std::optional<T>(pad_value),
                                      progress_tracker);
}

inline std::vector<Contour> join_contours(std::vector<Contour> contours, double max_dist) {
  const double max_dist_sqd = max_dist * max_dist;
  // Orientation-preserving endpoint pairings only (no reversing polylines):
  //   {back_a, front_b} → append b to a; {front_a, back_b} → prepend b onto a.
  struct JoinOrientation {
    bool use_front_a;
    bool use_front_b;
  };
  static constexpr JoinOrientation LEGAL_JOINS[] = {{false, true}, {true, false}};

  auto append_contour = [](Contour& target, Contour&& source, JoinOrientation join) {
    auto& target_pts = target.points();
    const auto& source_pts = source.points();
    const auto& target_end = join.use_front_a ? target_pts.front() : target_pts.back();
    const auto& source_end = join.use_front_b ? source_pts.front() : source_pts.back();
    const bool shared_endpoint = (target_end - source_end).magnitude_sqd() < 1e-8;
    if (join.use_front_a) {
      std::vector<Coordinate2D<double>> result = source_pts;
      result.insert(
          result.end(),
          (shared_endpoint && target_pts.size() > 1) ? target_pts.begin() + 1 : target_pts.begin(),
          target_pts.end());
      target_pts = std::move(result);
    } else {
      target_pts.insert(
          target_pts.end(),
          (shared_endpoint && source_pts.size() > 1) ? source_pts.begin() + 1 : source_pts.begin(),
          source_pts.end());
    }
  };

  for (bool progressed = true; progressed;) {
    progressed = false;
    const int n = static_cast<int>(contours.size());
    if (n < 2) {
      break;
    }

    std::vector<int> nearest_idx(n, -1);
    std::vector<double> nearest_dist_sqd(n, max_dist_sqd);
    std::vector<JoinOrientation> nearest_join(n);

    for (int i = 0; i < n; ++i) {
      if (contours[i].is_loop()) {
        continue;
      }
      const auto& pts_i = contours[i].points();
      for (int j = 0; j < n; ++j) {
        if (i == j || contours[j].is_loop()) {
          continue;
        }
        const auto& pts_j = contours[j].points();
        for (JoinOrientation join : LEGAL_JOINS) {
          const auto& endpoint_i = join.use_front_a ? pts_i.front() : pts_i.back();
          const auto& endpoint_j = join.use_front_b ? pts_j.front() : pts_j.back();
          const double dist_sqd = (endpoint_i - endpoint_j).magnitude_sqd();
          if (dist_sqd < nearest_dist_sqd[i]) {
            nearest_dist_sqd[i] = dist_sqd;
            nearest_idx[i] = j;
            nearest_join[i] = join;
          }
        }
      }
    }

    std::vector<char> used(n, 0);
    std::vector<Contour> next_round;
    next_round.reserve(static_cast<size_t>(n));

    for (int i = 0; i < n; ++i) {
      if (used[i]) {
        continue;
      }
      const int j = nearest_idx[i];
      if (j >= 0 && !used[j] && nearest_idx[j] == i && nearest_dist_sqd[i] < max_dist_sqd &&
          i < j) {
        Contour& target = contours[i];
        append_contour(target, std::move(contours[j]), nearest_join[i]);
        used[i] = used[j] = 1;
        next_round.emplace_back(std::move(target));
        progressed = true;
      } else {
        next_round.emplace_back(std::move(contours[i]));
      }
    }
    contours = std::move(next_round);
  }

  // Snap nearly-closed loops after all cross-contour joins are done.
  for (Contour& c : contours) {
    if (c.is_loop()) {
      continue;
    }
    auto& pts = c.points();
    if (pts.size() < 2) {
      continue;
    }
    const double gap_sqd = (pts.front() - pts.back()).magnitude_sqd();
    if (gap_sqd < max_dist_sqd) {
      c.close_loop();
    }
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
  GridGraph is_contour = identify_contours(grid, contour_config.min_interval, &progress_tracker);
  std::vector<Contour> contours;
  detail::trace_contours(
      grid, is_contour,
      [&](const Contour& c) {
        return c.points().size() > contour_config.pick_from_height(c.height()).min_points;
      },
      [&](double, Contour&& c) { contours.emplace_back(std::move(c)); });
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


