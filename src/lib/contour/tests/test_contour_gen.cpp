#include <gtest/gtest.h>

#include "lib/grid/grid.hpp"
#include "grid/grid_ops.hpp"
#include "contour/contour.hpp"


class TestGrid : public GeoGrid<double> {
public:
  explicit TestGrid(const std::vector<std::vector<double>>& data) : GeoGrid<double>(data[0].size(), data.size(), GeoTransform(), GeoProjection()) {
    for (size_t i = 0; i < data.size(); i++) {
      for (size_t j = 0; j < data[0].size(); j++) {
        (*this)[{i, j}] = data[i][j];
      }
    }
  }
};

TEST(ContourGen, ContourGen) {
  //std::vector<std::vector<double>> data = {
    //{0.5, 0.5, 0.5, 0.5, 0.5},
    //{0.5, 1.5, 1.5, 1.5, 0.5},
    //{0.5, 1.5, 1.5, 1.5, 0.5},
    //{0.5, 1.5, 1.5, 1.5, 0.5},
    //{0.5, 1.5, 1.5, 1.5, 0.5},
    //{0.5, 0.5, 0.5, 0.5, 0.5}
  //};
  std::vector<std::vector<double>> data = {
    {0.5, 0.5, 0.5},
    {0.5, 1.5, 0.5},
    {0.5, 0.5, 0.5}
  };
  TestGrid grid(data);

  GridGraph is_contour = GridGraph<char>(grid);
  for(size_t i = 0; i < grid.height(); i++) {
    for(size_t j = 0; j < grid.width(); j++) {
      Coordinate2D<size_t> coord = {j, i};
      for (Direction2D dir : {Direction2D::DOWN, Direction2D::RIGHT}) {
        LineCoord2D<size_t> line_coord = {coord, dir};
        std::cout << line_coord << std::endl;
        if (is_contour.in_bounds(line_coord)) {
          std::cout << "In bounds" << std::endl;
          is_contour[line_coord] = crosses_contour(grid[coord], grid[coord + dir], 1);
          std::cout << (int)is_contour[line_coord] << std::endl;
        }
      }
    }
  }

  std::cout << is_contour << std::endl;


  Contour contour = Contour::FromGridGraph(LineCoord2D<size_t>(1, 0, Direction2D::DOWN), grid, is_contour, 1);

  std::cout << contour << std::endl;
}
