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

inline std::vector<Contour> join_contours(std::vector<Contour> contours, double max_dist) {
  const double max_dist_sqd = max_dist * max_dist;
  // Orientation-preserving endpoint pairings only (no reversing polylines):
  //   {back_a, front_b} → append b to a; {front_a, back_b} → prepend b onto a.
  struct JoinOrientation {
    bool use_front_a;
    bool use_front_b;
  };
  static constexpr JoinOrientation legal_joins[] = {{false, true}, {true, false}};

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
        for (JoinOrientation join : legal_joins) {
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
