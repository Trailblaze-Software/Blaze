#pragma once

#include <pdal/util/Bounds.hpp>

#include "config_input/config_input.hpp"
#include "contour.hpp"
#include "utilities/timer.hpp"

template <typename T>
GridGraph<std::set<double>> identify_contours(const GeoGrid<T> &grid, T contour_interval) {
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
              grid[line_coord.start()], grid[line_coord.end()], contour_interval);
        }
      }
    }
  }
  return contour_heights;
}

inline std::vector<Contour> join_contours(const std::vector<Contour> &contours,
                                          double max_dist = 10) {
  std::vector<Contour> joined_contours;
  for (const Contour &c : contours) {
    bool joined = false;
    for (size_t i = 0; i < joined_contours.size(); i++) {
      Contour &joined_c = joined_contours[i];
      if ((joined_c.points().front() - c.points().front()).magnitude_sqd() < max_dist * max_dist) {
        std::reverse(joined_c.points().begin(), joined_c.points().end());
        std::copy(c.points().begin(), c.points().end(), std::back_inserter(joined_c.points()));
        joined = true;
        break;
      } else if ((joined_c.points().back() - c.points().front()).magnitude_sqd() <
                 max_dist * max_dist) {
        std::copy(c.points().begin(), c.points().end(), std::back_inserter(joined_c.points()));
        joined = true;
        break;
      } else if ((joined_c.points().front() - c.points().back()).magnitude_sqd() <
                 max_dist * max_dist) {
        std::reverse(joined_c.points().begin(), joined_c.points().end());
        std::copy(c.points().rbegin(), c.points().rend(), std::back_inserter(joined_c.points()));
        joined = true;
        break;
      } else if ((joined_c.points().back() - c.points().back()).magnitude_sqd() <
                 max_dist * max_dist) {
        std::copy(c.points().rbegin(), c.points().rend(), std::back_inserter(joined_c.points()));
        joined = true;
        break;
      }
    }
    if (!joined) {
      joined_contours.emplace_back(c);
    }
  }
  return joined_contours;
}

inline std::vector<Contour> trim_contours(const std::vector<Contour> &contours,
                                          const pdal::BOX2D &bounds) {
  std::vector<Contour> trimmed_contours;
  for (const Contour &c : contours) {
    Contour trimmed_contour(c.height(), std::vector<Coordinate2D<double>>{});
    for (const Coordinate2D<double> &point : c.points()) {
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
std::vector<Contour> generate_contours(const GeoGrid<T> &grid,
                                       const ContourConfigs &contour_config) {
  TimeFunction timer("generating contours");
  GridGraph is_contour = identify_contours(grid, contour_config.min_interval.in(au::meters));
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
  std::cout << "Generated " << contours.size() << " contours" << std::endl;
  return contours;
}

inline GeoGrid<std::optional<std::byte>> generate_naive_contours(const GeoGrid<double> &ground) {
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
      bool is_countour = crosses_contour(z, z_north, contour_interval) ||
                         crosses_contour(z, z_south, contour_interval) ||
                         crosses_contour(z, z_west, contour_interval) ||
                         crosses_contour(z, z_east, contour_interval);
      naive_countours[{i, j}] = is_countour ? std::optional<std::byte>{std::byte{0}} : std::nullopt;
    }
  }
  return naive_countours;
}
