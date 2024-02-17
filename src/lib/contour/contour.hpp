#pragma once

#include "assert/assert.hpp"
#include "grid/grid.hpp"
#include "utilities/coordinate.hpp"
#include <cmath>

inline bool crosses_contour(double h1, double h2, double contour_interval) {
  double max = std::max(h1, h2);
  double min = std::min(h1, h2);
  std::cout << max << " " << min << " " << max - fmod(max, contour_interval) << std::endl;
  return max - fmod(max, contour_interval) > min;
}


class Contour {
  double m_height;
  std::vector<Coordinate2D<double>> m_points;

public:
  Contour(double height, std::vector<Coordinate2D<double>>&& points) : m_height(height), m_points(points) {}

  double height() const { return m_height; }
  const std::vector<Coordinate2D<double>>& points() const { return m_points; }

  static Contour FromGridGraph(const LineCoord2D<size_t>& starting_point, const GeoGrid<double>& grid, GridGraph<char>& is_contour, double contour_interval) {
    std::vector<Coordinate2D<double>> contour_points;
    //double height =
    std::pair<double, double> heights = grid.get_values(starting_point);
    double max_height = std::max(heights.first, heights.second);
    double contour_height = max_height - fmod(max_height, contour_interval);

    LineCoord2DCrossing<size_t> current_point(starting_point, starting_point.dir());
    while (true){
      is_contour[current_point] = false;
      contour_points.emplace_back(grid.transform().pixel_to_projection(current_point.start()));
      {
        //std::pair<double, double> heights = grid.get_values(current_point);
        //double max_height = std::max(heights.first, heights.second);
        //double min_height = std::min(heights.first, heights.second);
        //AssertGE(max_height, contour_height);
        //AssertGE(contour_height, min_height);
      }
      bool end = true;
      for (LineCoord2DCrossing<size_t> next_point : current_point.next_points()) {
        if (is_contour.in_bounds(next_point) && is_contour[next_point]) {
          current_point = next_point;
          end = false;
          break;
        }
      } 
      if (end) {
        break;
      }
    }

    return Contour(contour_height, std::move(contour_points));
  }

  friend std::ostream& operator<<(std::ostream& os, const Contour& contour) {
    os << "Contour at height " << contour.height() << " with " << contour.points().size() << " points";
    return os;
  }

};
