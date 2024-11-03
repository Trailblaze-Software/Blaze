#pragma once

#include <algorithm>
#include <cstddef>
#include <cstring>
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
#include <memory>

#include "utilities/coordinate.hpp"

namespace pdal {
class BOX2D;
}

class GDALDataset;
class RGBColor;

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

  GeoTransform(GDALDataset &dataset);

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
 protected:
  using T = std::conditional_t<std::is_same_v<U, bool>, BlazeBool, U>;

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
  int m_data_type;
  std::vector<std::byte> m_data;

 public:
  FlexGrid(size_t width, size_t height, int n_bytes, int data_type = {});

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
  int data_type() const;
};

template <typename GridT>
class MultiBand {
  std::vector<GridT> m_grids;

 public:
  template <typename... Args>
  MultiBand(int n_bands, Args... args) {
    m_grids.reserve(n_bands);
    for (int i = 0; i < n_bands; i++) {
      m_grids.emplace_back(std::forward<Args>(args)...);
    }
  }

  MultiBand(size_t width, size_t height) {
    (void)width;
    (void)height;
    Fail("This shouldn't be required :(");
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

  double width_m() const { return GridT::width() * dx(); }
  double height_m() const { return GridT::height() * dx(); }

  template <typename U>
  static Geo FromPoints(const Geo &grid) {
    return Geo(grid.width() - 1, grid.height() - 1,
               GeoTransform(grid.transform().x() + grid.transform().dx() / 2,
                            grid.transform().y() + grid.transform().dy() / 2, grid.transform().dx(),
                            grid.transform().dy()),
               grid.projection());
  }

  static Geo<Grid<RGBColor>> FromGeoImg(const GeoImgGrid &grid);

  Geo slice(const pdal::BOX2D &extent);
  std::unique_ptr<pdal::BOX2D> extent() const;

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

template <typename T>
T interpolate_value(const GeoGrid<T> &grid, const Coordinate2D<double> &projection_coord);
