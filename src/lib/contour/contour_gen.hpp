#pragma once

#include "contour.hpp"

template <typename T>
GridGraph<char> identify_contours(const GeoGrid<T>& grid, double contour_interval) {
  GridGraph is_contour = GridGraph<char>(grid); 
  for(size_t i = 0; i < grid.height(); i++) {
    for(size_t j = 0; j < grid.width(); j++) {
      Coordinate2D<size_t> coord = {j, i};
      for (Direction2D dir : {Direction2D::DOWN, Direction2D::RIGHT}) {
        LineCoord2D<size_t> line_coord = {coord, dir};
        if (is_contour.in_bounds(line_coord)) {
          is_contour[line_coord] = crosses_contour(grid[line_coord.start()], grid[line_coord.end()], contour_interval);
        }
      }
    }
  }
  return is_contour;
}

template <typename T>
std::vector<Contour> generate_contours(const GeoGrid<T>& grid, double contour_interval) {
  GridGraph is_contour = identify_contours(grid, contour_interval);
  std::vector<Contour> contours;
  for (size_t i = 0; i < is_contour.height(); i++) {
    for (size_t j = 0; j < is_contour.width(); j++) {
      Coordinate2D<size_t> coord = {j, i};
      for (Direction2D dir : {Direction2D::DOWN, Direction2D::RIGHT}) {
        LineCoord2D<size_t> line_coord = {coord, dir};
        if (is_contour.in_bounds(line_coord) && is_contour[line_coord]) {
          contours.emplace_back(Contour::FromGridGraph(line_coord, grid, is_contour, contour_interval));
        }
      }
    }
  }
  return contours;
}
