#include "grid.hpp"

#include "img_grid.hpp"
#include "isom/colors.hpp"
#include "utilities/timer.hpp"

template <>
GeoGrid<RGBColor> GeoGrid<RGBColor>::FromGeoImg(const GeoImgGrid &grid) {
  GeoGrid<RGBColor> new_grid(grid.width(), grid.height(), GeoTransform(grid.transform()),
                             GeoProjection(grid.projection()));
  TimeFunction timer("FromGeoImg");
#pragma omp parallel for
  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      new_grid[{j, i}] = grid.get_rgb_color(i, j);
    }
  }
  return new_grid;
}
