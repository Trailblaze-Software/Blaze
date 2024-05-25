#pragma once

#include "config_input/config_input.hpp"
#include "contour.hpp"

template <typename T>
GridGraph<char> identify_contours(const GeoGrid<T> &grid, T contour_interval) {
  GridGraph is_contour = GridGraph<char>(grid);
  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      Coordinate2D<size_t> coord = {j, i};
      for (Direction2D dir : {Direction2D::DOWN, Direction2D::RIGHT}) {
        LineCoord2D<size_t> line_coord = {coord, dir};
        if (is_contour.in_bounds(line_coord)) {
          is_contour[line_coord] =
              crosses_contour(grid[line_coord.start()], grid[line_coord.end()], contour_interval);
        }
      }
    }
  }
  return is_contour;
}

template <typename T>
std::vector<Contour> generate_contours(const GeoGrid<T> &grid,
                                       const ContourConfigs &contour_config) {
  GridGraph is_contour = identify_contours(grid, contour_config.min_interval.in(au::meters));
  std::vector<Contour> contours;
  for (size_t i = 0; i < is_contour.height(); i++) {
    for (size_t j = 0; j < is_contour.width(); j++) {
      Coordinate2D<size_t> coord = {j, i};
      for (Direction2D dir : {Direction2D::DOWN, Direction2D::RIGHT}) {
        LineCoord2D<size_t> line_coord = {coord, dir};
        if (is_contour.in_bounds(line_coord) && is_contour[line_coord]) {
          Contour c = Contour::FromGridGraph(line_coord, grid, is_contour,
                                             contour_config.min_interval.in(au::meters));
          if (c.points().size() > contour_config.pick_from_height(c.height()).min_points) {
            contours.emplace_back(std::move(c));
          }
        }
      }
    }
  }
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
