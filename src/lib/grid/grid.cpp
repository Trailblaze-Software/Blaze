#include "grid.hpp"

#include "img_grid.hpp"
#include "isom/colors.hpp"
#include "utilities/timer.hpp"

template <>
GeoGrid<RGBColor> GeoGrid<RGBColor>::FromGeoImg(const GeoImgGrid &grid) {
  TimeFunction timer("FromGeoImg");
  GeoGrid<RGBColor> new_grid(grid.width(), grid.height(), GeoTransform(grid.transform()),
                             GeoProjection(grid.projection()));
#pragma omp parallel for
  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      new_grid[{j, i}] = grid.get_rgb_color(i, j);
    }
  }
  return new_grid;
}

template <typename T>
void Grid<T>::fill_from(const FlexGrid &other, const Coordinate2D<long long> &top_left) {
  AssertEQ(other.n_bytes(), sizeof(T));
  for (size_t i = 0; i < height(); i++) {
    for (size_t j = 0; j < width(); j++) {
      (*this)[{j, i}] = other.get<T>(top_left + Coordinate2D<long long>(j, i));
    }
  }
}

template class Grid<double>;
