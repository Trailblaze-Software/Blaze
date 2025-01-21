#include "grid.hpp"

#include "gdal_priv.h"
#include "img_grid.hpp"
#include "isom/colors.hpp"
#include "las/las_point.hpp"
#include "utilities/timer.hpp"

GeoTransform::GeoTransform(GDALDataset &dataset) { dataset.GetGeoTransform(geoTransform); }

template <typename GridT>
GeoGrid<RGBColor> Geo<GridT>::FromGeoImg(const GeoImgGrid &grid) {
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

template <typename GridT>
Geo<GridT> same_type_different_size(const Geo<GridT> &grid, size_t new_width, size_t new_height,
                                    const Coordinate2D<double> &new_top_left) {
  if constexpr (is_specialization_v<GridT, Grid>) {
    return Geo<GridT>(GeoTransform(new_top_left.x(), new_top_left.y(), grid.transform().dx(),
                                   grid.transform().dy()),
                      GeoProjection(grid.projection()), new_width, new_height);
  } else if constexpr (is_specialization_v<GridT, MultiBand>) {
    return Geo<GridT>(GeoTransform(new_top_left.x(), new_top_left.y(), grid.transform().dx(),
                                   grid.transform().dy()),
                      GeoProjection(grid.projection()), grid.size(), new_width, new_height,
                      grid[0].n_bytes(), grid[0].data_type());
  } else {
    static_assert(is_specialization_v<GridT, Grid>);
  }
}

template <typename GridT>
Geo<GridT> Geo<GridT>::slice(const Extent2D &extent) {
  Coordinate2D<size_t> top_left = transform().projection_to_pixel({extent.minx, extent.maxy});
  Coordinate2D<size_t> bottom_right = transform().projection_to_pixel({extent.maxx, extent.miny});
  size_t new_width = bottom_right.x() - top_left.x();
  size_t new_height = bottom_right.y() - top_left.y();

  Coordinate2D<double> new_top_left = transform().pixel_to_projection(top_left);
  Geo result = same_type_different_size(*this, new_width, new_height, new_top_left);
  if constexpr (is_specialization_v<GridT, Grid>) {
#pragma omp parallel for
    for (size_t i = 0; i < new_height; i++) {
      for (size_t j = 0; j < new_width; j++) {
        result[{j, i}] = (*this)[{j + top_left.x(), i + top_left.y()}];
      }
    }
  } else if constexpr (std::is_same_v<GridT, FlexGrid>) {
#pragma omp parallel for
    for (size_t i = 0; i < new_height; i++) {
      for (size_t j = 0; j < new_width; j++) {
        for (int k = 0; k < FlexGrid::m_data_size; k++) {
          result[{j, i}][k] = (*this)[{j + top_left.x(), i + top_left.y()}][k];
        }
      }
    }
  } else if constexpr (std::is_same_v<GridT, MultiBand<FlexGrid>>) {
    for (size_t band = 0; band < result.size(); band++) {
#pragma omp parallel for
      for (size_t i = 0; i < new_height; i++) {
        for (size_t j = 0; j < new_width; j++) {
          for (unsigned int k = 0; k < (*this)[band].n_bytes(); k++) {
            result[band][{j, i}][k] = (*this)[band][{j + top_left.x(), i + top_left.y()}][k];
          }
        }
      }
    }
  } else {
    static_assert(is_specialization_v<GridT, Grid>);
  }
  return result;
}

template <typename GridT>
std::unique_ptr<Extent2D> Geo<GridT>::extent() const {
  Coordinate2D<double> top_left = transform().pixel_to_projection({0, 0});
  Coordinate2D<double> bottom_right =
      transform().pixel_to_projection({(double)GridT::width(), (double)GridT::height()});
  double min_x = std::min(top_left.x(), bottom_right.x());
  double max_x = std::max(top_left.x(), bottom_right.x());
  double min_y = std::min(top_left.y(), bottom_right.y());
  double max_y = std::max(top_left.y(), bottom_right.y());
  return std::make_unique<Extent2D>(min_x, max_x, min_y, max_y);
}

template class Geo<Grid<double>>;
template class Geo<Grid<RGBColor>>;
template class Geo<Grid<CMYKColor>>;
template class Geo<Grid<std::optional<double>>>;
template class Geo<Grid<std::optional<std::byte>>>;
template class Geo<Grid<std::byte>>;
template class Geo<Grid<std::optional<LASPoint>>>;

template class Geo<MultiBand<FlexGrid>>;

template <typename T>
T interpolate_value(const GeoGrid<T> &grid, const Coordinate2D<double> &projection_coord) {
  Coordinate2D<double> pixel_coord = grid.transform().projection_to_pixel(projection_coord);
  if (pixel_coord.x() < 0 || pixel_coord.y() < 0 || pixel_coord.x() >= grid.width() ||
      pixel_coord.y() >= grid.height()) {
    std::cout << "Interpolation out of bounds" << std::endl;
    std::cout << "Projection coord: " << projection_coord << std::endl;
    std::cout << "Pixel coord: " << pixel_coord << std::endl;
    std::cout << "Grid size: " << grid.width() << ", " << grid.height() << std::endl;
    Fail("Interpolation out of bounds");
  }
  if (pixel_coord.x() <= 0.5 || pixel_coord.y() <= 0.5 || pixel_coord.x() >= grid.width() - 0.5 ||
      pixel_coord.y() >= grid.height() - 0.5) {
    return grid[{static_cast<size_t>(pixel_coord.x()), static_cast<size_t>(pixel_coord.y())}];
  }
  size_t x = static_cast<size_t>(pixel_coord.x() - 0.5);
  size_t y = static_cast<size_t>(pixel_coord.y() - 0.5);
  if (x >= grid.width() || y >= grid.height()) {
    Fail("Interpolation out of bounds");
  }
  double x_frac = pixel_coord.x() - 0.5 - x;
  double y_frac = pixel_coord.y() - 0.5 - y;
  auto top_left = grid[{x, y}];
  auto top_right = grid[{x + 1, y}];
  auto bottom_left = grid[{x, y + 1}];
  auto bottom_right = grid[{x + 1, y + 1}];
  AssertGE(x_frac, 0);
  AssertLE(x_frac, 1);
  AssertGE(y_frac, 0);
  AssertLE(y_frac, 1);
  return top_left * (1 - x_frac) * (1 - y_frac) + top_right * x_frac * (1 - y_frac) +
         bottom_left * (1 - x_frac) * y_frac + bottom_right * x_frac * y_frac;
}

template double interpolate_value(const GeoGrid<double> &grid,
                                  const Coordinate2D<double> &projection_coord);
FlexGrid::FlexGrid(size_t width, size_t height, int n_bytes, int data_type)
    : GridData(width, height),
      m_data_size(n_bytes),
      m_data_type(std::move(data_type)),
      m_data(width * height * n_bytes) {}
int FlexGrid::data_type() const { return m_data_type; }
