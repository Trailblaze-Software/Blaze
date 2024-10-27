#pragma once

#include <algorithm>
#include <any>
#include <cstddef>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <optional>
#include <pdal/util/Bounds.hpp>
#include <string>
#include <type_traits>
#include <vector>

#include "assert/assert.hpp"
#ifdef _MSC_VER
#pragma warning(push, 0)
#endif
#include "au/quantity.hh"
#include "au/units/meters.hh"
#ifdef _MSC_VER
#pragma warning(pop)
#endif
#include "gdal.h"
#include "gdal_priv.h"
#include "isom/colors.hpp"
#include "utilities/coordinate.hpp"
#include "utilities/filesystem.hpp"

class GeoTransform {
  double geoTranform[6];

 public:
  GeoTransform(double upper_left_x, double upper_left_y, double dx = 1.0, double dy = -1.0) {
    geoTranform[0] = upper_left_x;  // center of top left pixel is 0.5, 0.5
    geoTranform[1] = dx;            // w->e pixel resolution
    geoTranform[2] = 0;             // Row rotation
    geoTranform[3] = upper_left_y;
    geoTranform[4] = 0;   // Column rotation
    geoTranform[5] = dy;  // n->s pixel resolution (so negative is up)
  }

  explicit GeoTransform(const Coordinate2D<double> &upper_left, double resolution)
      : GeoTransform(upper_left.x(), upper_left.y(), resolution, -resolution) {}

  GeoTransform() : GeoTransform(0, 0, 1, -1) {};

  GeoTransform(GDALDataset &dataset) { dataset.GetGeoTransform(geoTranform); }

  const double *get_raw() const { return geoTranform; }

  GeoTransform with_new_resolution(au::QuantityD<au::Meters> new_resolution) const {
    return GeoTransform(x(), y(), new_resolution.in(au::meters), -new_resolution.in(au::meters));
  }

  Coordinate2D<double> pixel_to_projection(const Coordinate2D<double> &coord) const {
    double new_x = x() + coord.x() * dx() + coord.y() * rot_x();
    double new_y = y() + coord.y() * dy() + coord.x() * rot_y();
    return {new_x, new_y};
  }

  Coordinate2D<double> projection_to_pixel(const Coordinate2D<double> &coord) const {
    double new_x = (rot_x() * coord.y() - coord.x() * dy() - y() * rot_x() + x() * dy()) /
                   (rot_x() * rot_y() - dy() * dx());
    double new_y = (rot_y() * coord.x() - coord.y() * dx() - x() * rot_y() + y() * dx()) /
                   (rot_x() * rot_y() - dy() * dx());
    return {new_x, new_y};
  }

  friend std::ostream &operator<<(std::ostream &os, const GeoTransform &transform) {
    os << "GeoTransform(x: " << transform.x() << ", y: " << transform.y()
       << ", dx: " << transform.dx() << ", dy: " << transform.dy()
       << ", rot_x: " << transform.rot_x() << ", rot_y: " << transform.rot_y() << ")";
    return os;
  }

  double x() const { return geoTranform[0]; }
  double dx() const { return geoTranform[1]; }
  double rot_x() const { return geoTranform[2]; }
  double y() const { return geoTranform[3]; }
  double rot_y() const { return geoTranform[4]; }
  double dy() const { return geoTranform[5]; }

  au::QuantityD<au::Meters> dx_m() const { return au::meters(dx()); }
  au::QuantityD<au::Meters> dy_m() const { return au::meters(dy()); }

  void set_dx(double dx) { geoTranform[1] = dx; }
  void set_dy(double dy) { geoTranform[5] = dy; }
};

class GeoProjection {
  std::string m_projection;

 public:
  explicit GeoProjection(const std::string &projection) : m_projection(projection) {}

  GeoProjection() = default;

  const std::string &to_string() const { return m_projection; }
};

class GridData {
 protected:
  size_t m_width;
  size_t m_height;

 public:
  GridData(size_t width, size_t height) : m_width(width), m_height(height) {}

  size_t width() const { return m_width; }
  size_t height() const { return m_height; }

  bool in_bounds(const Coordinate2D<size_t> &coord) const {
    return coord.x() < m_width && coord.y() < m_height;
  }
};

struct BlazeBool {
  bool value;
  BlazeBool(bool value) : value(value) {}
  BlazeBool() : value(false) {}
  BlazeBool &operator=(bool new_value) {
    this->value = new_value;
    return *this;
  }
  operator bool() const { return value; }
};

class FlexGrid;

template <typename U>
class Grid : public GridData {
  using T = std::conditional_t<std::is_same_v<U, bool>, BlazeBool, U>;

 protected:
  std::vector<T> m_data;
  int m_repeats;

 public:
  Grid(size_t width, size_t height, int repeats = 1)
      : GridData(width, height), m_data(width * height * repeats), m_repeats(repeats) {}

  T &operator[](Coordinate2D<size_t> coord) {
    return m_data.at(coord.y() * width() * m_repeats + coord.x() * m_repeats);
  }
  const T &operator[](Coordinate2D<size_t> coord) const {
    return m_data.at(coord.y() * width() * m_repeats + coord.x() * m_repeats);
  }

  std::pair<T, T> get_values(const LineCoord2D<size_t> &coord) const {
    return {(*this)[coord.start()], (*this)[coord.end()]};
  }

  void fill(const T &value) { std::fill(m_data.begin(), m_data.end(), value); }

  void copy_from(const Grid &other) {
    AssertEQ(width(), other.width());
    AssertEQ(height(), other.height());
    AssertEQ(m_data.size(), other.m_data.size());
    m_data = other.m_data;
  }

  T max_value() const { return *std::max_element(m_data.begin(), m_data.end()); }
  T min_value() const { return *std::min_element(m_data.begin(), m_data.end()); }

  typedef T value_type;

  void fill_from(const Grid &other, const Coordinate2D<size_t> &top_left = {0, 0}) {
#pragma omp parallel for
    for (size_t i = 0; i < other.height(); i++) {
      for (size_t j = 0; j < other.width(); j++) {
        if (this->in_bounds(top_left + Coordinate2D<size_t>{j, i}))
          (*this)[top_left + Coordinate2D<size_t>{j, i}] = other[{j, i}];
      }
    }
  }

  void fill_from(const FlexGrid &other, const Coordinate2D<long long> &top_left = {0, 0});

  friend std::ostream &operator<<(std::ostream &os, const Grid &grid) {
    os << "Grid<" << typeid(T).name() << ">(" << grid.width() << ", " << grid.height() << ")"
       << std::endl;
    for (size_t i = 0; i < grid.height(); i++) {
      for (size_t j = 0; j < grid.width(); j++) {
        if constexpr (std::is_same_v<T, char>) {
          os << (grid[{j, i}] ? "X" : "_");
        } else {
          os << grid[{j, i}];
        }
      }
      os << std::endl;
    }
    return os;
  }
};

class FlexGrid : public GridData {
 protected:
  unsigned int m_data_size;
  std::optional<GDALDataType> m_data_type;
  std::vector<std::byte> m_data;

 public:
  FlexGrid(size_t width, size_t height, int n_bytes, std::optional<GDALDataType> data_type = {})
      : GridData(width, height),
        m_data_size(n_bytes),
        m_data_type(data_type),
        m_data(width * height * n_bytes) {}

  std::byte *operator[](Coordinate2D<size_t> coord) {
    return m_data.data() + coord.y() * width() * m_data_size + coord.x() * m_data_size;
  }
  const std::byte *operator[](Coordinate2D<size_t> coord) const {
    return m_data.data() + coord.y() * width() * m_data_size + coord.x() * m_data_size;
  }

  template <typename T>
  T get(const Coordinate2D<long long> &coord) const {
    return *reinterpret_cast<const T *>(m_data.data() + coord.y() * width() * m_data_size +
                                        coord.x() * m_data_size);
  }

  void fill_from(const FlexGrid &other, const Coordinate2D<long long> &top_left = {0, 0}) {
#pragma omp parallel for
    for (size_t i = 0; i < other.height(); i++) {
      Coordinate2D<long long> start(std::max(top_left.x(), 0ll), (top_left.y() + i));
      size_t diff = start.x() - top_left.x();
      long long num_elements = std::min((long long)other.width(), (long long)width() - start.x());
      if (this->in_bounds(start) && num_elements > 0) {
        std::memcpy((*this)[start], other[{diff, i}], num_elements * m_data_size);
      }
    }
  }

  std::byte *data() { return m_data.data(); }
  const std::byte *data() const { return m_data.data(); }
  unsigned int n_bytes() const { return m_data_size; }
  GDALDataType data_type() const { return m_data_type.value(); }
};

template <typename GridT>
class MultiBand {
  std::vector<GridT> m_grids;

 public:
  template <typename... Args>
  MultiBand(int n_bands, Args... args) {
    m_grids.reserve(n_bands);
    for (int i = 0; i < n_bands; i++) {
      m_grids.emplace_back(args...);
    }
  }

  size_t size() const { return m_grids.size(); }
  size_t width() const { return m_grids[0].width(); }
  size_t height() const { return m_grids[0].height(); }
  bool in_bounds(const Coordinate2D<size_t> &coord) const { return m_grids[0].in_bounds(coord); }

  void fill_from(const MultiBand &other, const Coordinate2D<size_t> &top_left = {0, 0}) {
    AssertEQ(size(), other.size());
    for (size_t i = 0; i < size(); i++) {
      m_grids[i].fill_from(other[i], top_left);
    }
  }

  GridT &operator[](size_t i) { return m_grids[i]; }
  const GridT &operator[](size_t i) const { return m_grids[i]; }
};

class GeoGridData {
 protected:
  GeoTransform m_transform;
  GeoProjection m_projection;

 public:
  GeoGridData(GeoTransform &&transform, GeoProjection &&projection)
      : m_transform(transform), m_projection(projection) {}

  const GeoTransform &transform() const { return m_transform; }
  const GeoProjection &projection() const { return m_projection; }

  double dx() const { return m_transform.dx(); }
  double dy() const { return m_transform.dy(); }
};

template <typename Test, template <typename...> class Ref>
struct is_specialization : std::false_type {};

template <template <typename...> class Ref, typename... Args>
struct is_specialization<Ref<Args...>, Ref> : std::true_type {};

template <class Type, template <typename...> class Template>
inline constexpr bool is_specialization_v = is_specialization<Type, Template>::value;

class GeoImgGrid;

template <typename GridT>
class Geo : public GridT, public GeoGridData {
 public:
  Geo(size_t width, size_t height, GeoTransform &&transform, GeoProjection &&projection)
      : GridT(width, height), GeoGridData(std::move(transform), std::move(projection)) {}

  template <typename... Args>
  Geo(GeoTransform &&transform, GeoProjection &&projection, Args... args)
      : GridT(args...), GeoGridData(std::move(transform), std::move(projection)) {}

  Geo slice(const pdal::BOX2D &extent) {
    Coordinate2D<size_t> top_left = transform().projection_to_pixel({extent.minx, extent.maxy});
    Coordinate2D<size_t> bottom_right = transform().projection_to_pixel({extent.maxx, extent.miny});
    size_t new_width = bottom_right.x() - top_left.x();
    size_t new_height = bottom_right.y() - top_left.y();
    Geo result(new_width, new_height,
               GeoTransform(extent.minx, extent.maxy, transform().dx(), transform().dy()),
               GeoProjection(projection()));
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
    } else {
      static_assert(is_specialization_v<GridT, Grid>);
    }
    return result;
  }

  template <typename U>
  static Geo FromPoints(const Geo &grid) {
    return Geo(grid.width() - 1, grid.height() - 1,
               GeoTransform(grid.transform().x() + grid.transform().dx() / 2,
                            grid.transform().y() + grid.transform().dy() / 2, grid.transform().dx(),
                            grid.transform().dy()),
               grid.projection());
  }

  static Geo<Grid<RGBColor>> FromGeoImg(const GeoImgGrid &grid);

  auto interpolate_value(const Coordinate2D<double> &projection_coord) const {
    Coordinate2D<double> pixel_coord = transform().projection_to_pixel(projection_coord);
    if (pixel_coord.x() < 0 || pixel_coord.y() < 0 || pixel_coord.x() >= GridT::width() ||
        pixel_coord.y() >= GridT::height()) {
      std::cout << "Interpolation out of bounds" << std::endl;
      std::cout << "Projection coord: " << projection_coord << std::endl;
      std::cout << "Pixel coord: " << pixel_coord << std::endl;
      std::cout << "Grid size: " << GridT::width() << ", " << GridT::height() << std::endl;
      Fail("Interpolation out of bounds");
    }
    if (pixel_coord.x() <= 0.5 || pixel_coord.y() <= 0.5 ||
        pixel_coord.x() >= GridT::width() - 0.5 || pixel_coord.y() >= GridT::height() - 0.5) {
      return (*this)[{static_cast<size_t>(pixel_coord.x()), static_cast<size_t>(pixel_coord.y())}];
    }
    size_t x = static_cast<size_t>(pixel_coord.x() - 0.5);
    size_t y = static_cast<size_t>(pixel_coord.y() - 0.5);
    if (x >= GridT::width() || y >= GridT::height()) {
      Fail("Interpolation out of bounds");
    }
    double x_frac = pixel_coord.x() - 0.5 - x;
    double y_frac = pixel_coord.y() - 0.5 - y;
    auto top_left = (*this)[{x, y}];
    auto top_right = (*this)[{x + 1, y}];
    auto bottom_left = (*this)[{x, y + 1}];
    auto bottom_right = (*this)[{x + 1, y + 1}];
    AssertGE(x_frac, 0);
    AssertLE(x_frac, 1);
    AssertGE(y_frac, 0);
    AssertLE(y_frac, 1);
    return top_left * (1 - x_frac) * (1 - y_frac) + top_right * x_frac * (1 - y_frac) +
           bottom_left * (1 - x_frac) * y_frac + bottom_right * x_frac * y_frac;
  }

  pdal::BOX2D extent() const {
    Coordinate2D<double> top_left = transform().pixel_to_projection({0, 0});
    Coordinate2D<double> bottom_right =
        transform().pixel_to_projection({(double)GridT::width(), (double)GridT::height()});
    double min_x = std::min(top_left.x(), bottom_right.x());
    double max_x = std::max(top_left.x(), bottom_right.x());
    double min_y = std::min(top_left.y(), bottom_right.y());
    double max_y = std::max(top_left.y(), bottom_right.y());
    return pdal::BOX2D(min_x, min_y, max_x, max_y);
  }

  template <typename U>
  void fill_from(const Geo<U> &other) {
    Coordinate2D<size_t> top_left =
        transform().projection_to_pixel(other.transform().pixel_to_projection({0, 0})).round();
    GridT::fill_from(other, top_left);
  }

  template <typename U>
  void fill_from(const U &other) {
    GridT::fill_from(other);
  }
};

template <typename T>
using GeoGrid = Geo<Grid<T>>;

typedef Geo<FlexGrid> GeoFlexGrid;

template <typename T>
class GridGraph {
  Grid<T> m_horizontal;
  Grid<T> m_vertical;

 public:
  template <typename U>
  explicit GridGraph(const Grid<U> &grid)
      : m_horizontal(grid.width() - 1, grid.height()),
        m_vertical(grid.width(), grid.height() - 1) {}

  Grid<T> &horizontal() { return m_horizontal; }
  Grid<T> &vertical() { return m_vertical; }
  const Grid<T> &horizontal() const { return m_horizontal; }
  const Grid<T> &vertical() const { return m_vertical; }

  size_t width() const { return m_vertical.width(); }
  size_t height() const { return m_horizontal.height(); }

  const T &operator[](const LineCoord2D<size_t> &coord) const {
    if (coord.dir() == Direction2D::DOWN) {
      return m_vertical[Coordinate2D<size_t>(coord.x(), coord.y())];
    } else if (coord.dir() == Direction2D::RIGHT) {
      return m_horizontal[Coordinate2D<size_t>(coord.x(), coord.y())];
    }
    Fail("Invalid direction");
  }
  T &operator[](const LineCoord2D<size_t> &coord) {
    return const_cast<T &>(static_cast<const GridGraph *>(this)->operator[](coord));
  }

  template <typename U>
  bool in_bounds(const LineCoord2D<U> &coord) const {
    if (coord.x() < 0 || coord.y() < 0) {
      return false;
    }
    if (coord.dir() == Direction2D::DOWN) {
      return coord.x() < width() && coord.y() < std::numeric_limits<U>::max() &&
             coord.y() + 1 < height();
    } else if (coord.dir() == Direction2D::RIGHT) {
      return coord.x() < std::numeric_limits<U>::max() && coord.x() + 1 < width() &&
             coord.y() < height();
    }
    Fail("Invalid direction");
  }

  friend std::ostream &operator<<(std::ostream &os, const GridGraph &graph) {
    os << "GridGraph(" << graph.width() << ", " << graph.height() << ")" << std::endl;
    os << "Horizontal:" << std::endl;
    os << graph.horizontal() << std::endl;
    os << "Vertical:" << std::endl;
    os << graph.vertical() << std::endl;
    return os;
  }
};
