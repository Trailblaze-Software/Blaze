#include <cstdint>
#include <iostream>
#include <pdal/Dimension.hpp>
#include <pdal/SpatialReference.hpp>
#include <pdal/io/BufferReader.hpp>
#include <pdal/io/LasHeader.hpp>
#include <pdal/io/LasReader.hpp>
#include <pdal/pdal.hpp>
#include <pdal/util/Bounds.hpp>
#include <string>
#include <vector>

#ifdef _MSC_VER
#pragma warning(push, 0)
#endif
#include "au/units/meters.hh"
#ifdef _MSC_VER
#pragma warning(pop)
#endif
#include "grid/grid.hpp"
#include "las_point.hpp"
#include "utilities/timer.hpp"

enum class BorderType { N, NE, E, SE, S, SW, W, NW };

inline std::ostream &operator<<(std::ostream &os, BorderType border_type) {
  switch (border_type) {
    case BorderType::N:
      return os << "N";
    case BorderType::NE:
      return os << "NE";
    case BorderType::E:
      return os << "E";
    case BorderType::SE:
      return os << "SE";
    case BorderType::S:
      return os << "S";
    case BorderType::SW:
      return os << "SW";
    case BorderType::W:
      return os << "W";
    case BorderType::NW:
      return os << "NW";
  }
  unreachable();
}

inline pdal::BOX2D border_ranges(const pdal::BOX2D &box, BorderType border_type,
                                 double border_width) {
  switch (border_type) {
    case BorderType::N:
      return {box.minx, box.maxy - border_width, box.maxx, box.maxy};
    case BorderType::NE:
      return {box.maxx - border_width, box.maxy - border_width, box.maxx, box.maxy};
    case BorderType::E:
      return {box.maxx - border_width, box.miny, box.maxx, box.maxy};
    case BorderType::SE:
      return {box.maxx - border_width, box.miny, box.maxx, box.miny + border_width};
    case BorderType::S:
      return {box.minx, box.miny, box.maxx, box.miny + border_width};
    case BorderType::SW:
      return {box.minx, box.miny, box.minx + border_width, box.miny + border_width};
    case BorderType::W:
      return {box.minx, box.miny, box.minx + border_width, box.maxy};
    case BorderType::NW:
      return {box.minx, box.maxy - border_width, box.minx + border_width, box.maxy};
  }
  unreachable();
}

inline pdal::BOX2D external_border_ranges(const pdal::BOX2D &box, BorderType border_type,
                                          double border_width) {
  switch (border_type) {
    case BorderType::N:
      return {box.minx, box.maxy, box.maxx, box.maxy + border_width};
    case BorderType::NE:
      return {box.maxx, box.maxy, box.maxx + border_width, box.maxy + border_width};
    case BorderType::E:
      return {box.maxx, box.miny, box.maxx + border_width, box.maxy};
    case BorderType::SE:
      return {box.maxx, box.miny - border_width, box.maxx + border_width, box.miny};
    case BorderType::S:
      return {box.minx, box.miny - border_width, box.maxx, box.miny};
    case BorderType::SW:
      return {box.minx - border_width, box.miny - border_width, box.minx, box.miny};
    case BorderType::W:
      return {box.minx - border_width, box.miny, box.minx, box.maxy};
    case BorderType::NW:
      return {box.minx - border_width, box.maxy, box.minx, box.maxy + border_width};
  }
  unreachable();
}

inline long int round(double x, double resolution = 1.0) {
  return std::round(x / resolution) * resolution;
}

template <typename T>
inline T average(T a, T b) {
  return (a + b) / 2;
}

inline std::string unique_coord_name(const pdal::BOX2D &box) {
  return std::to_string(round(box.minx, 10)) + "_" + std::to_string(round(box.miny, 10)) + "_" +
         std::to_string(round(box.maxx, 10)) + "_" + std::to_string(round(box.maxy, 10));
}

inline void print_metadata(const pdal::MetadataNode &node, const std::string &prefix = "") {
  std::cout << prefix << node.name() << ": " << node.value() << std::endl;
  for (const std::string &name : node.childNames()) {
    print_metadata(node.findChild(name), prefix + "  ");
  }
}

#undef min
#undef max

class LASFile {
  std::vector<LASPoint> m_points;
  std::pair<double, double> m_height_range;
  std::pair<uint16_t, uint16_t> m_intensity_range;
  pdal::BOX3D m_bounds;
  pdal::BOX3D m_original_bounds;
  GeoProjection m_projection;

 public:
  explicit LASFile(const pdal::BOX2D &bounds, GeoProjection &&projection)
      : m_height_range({std::numeric_limits<double>::max(), std::numeric_limits<double>::min()}),
        m_intensity_range(
            {std::numeric_limits<uint16_t>::max(), std::numeric_limits<uint16_t>::min()}),
        m_bounds(bounds),
        m_original_bounds(bounds),
        m_projection(projection){};

  template <typename T>
  explicit LASFile(const GeoGrid<T> &grid)
      : LASFile(grid.extent(), GeoProjection(grid.projection())) {
    for (size_t i = 0; i < grid.height(); i++) {
      for (size_t j = 0; j < grid.width(); j++) {
        Coordinate2D<double> coord =
            grid.transform().pixel_to_projection({(double)j + 0.5, (double)i + 0.5});
        insert(LASPoint(coord.x(), coord.y(), grid[{j, i}], 1000, LASClassification::Ground));
      }
    }
  }

  void insert(const LASPoint &point) {
    m_points.emplace_back(point);
    m_height_range.first = std::min(m_height_range.first, point.z());
    m_height_range.second = std::max(m_height_range.second, point.z());
    m_intensity_range.first = std::min(m_intensity_range.first, point.intensity());
    m_intensity_range.second = std::max(m_intensity_range.second, point.intensity());
    m_bounds.grow(point.x(), point.y(), point.z());
  }

  explicit LASFile(const std::string &filename)
      : m_height_range({std::numeric_limits<double>::max(), std::numeric_limits<double>::min()}),
        m_intensity_range(
            {std::numeric_limits<uint16_t>::max(), std::numeric_limits<uint16_t>::min()}) {
    Timer timer;
    std::cout << "Reading " << filename << " ..." << std::endl;
    pdal::Option las_opt("filename", filename);
    pdal::Options las_opts;
    las_opts.add(las_opt);
    pdal::PointTable table;
    pdal::LasReader las_reader;
    las_reader.setOptions(las_opts);
    las_reader.prepare(table);
    pdal::PointViewSet point_view_set = las_reader.execute(table);
    pdal::PointViewPtr point_view = *point_view_set.begin();
    pdal::Dimension::IdList dims = point_view->dims();
    pdal::LasHeader las_header = las_reader.header();
    m_bounds = las_header.getBounds();
    m_original_bounds = m_bounds;
    m_projection = GeoProjection(las_header.srs().getWKT());

    std::cout << "Read " << point_view->size() << " points" << std::endl;
    // std::cout << "Spatial reference: " << pdal::SpatialReference(las_header.srs().getWKT())
    //<< std::endl;
    //
    // std::cout << "Fields: " << std::endl;
    // for (pdal::Dimension::Id dim : dims) {
    // std::cout << "- " << pdal::Dimension::name(dim) << ": " << pdal::Dimension::description(dim)
    //<< " (" << point_view->dimType(dim) << ")" << std::endl;
    //}

    std::cout << "Reading metadata took " << timer << std::endl;

    Timer point_timer;
    for (pdal::PointId idx = 0; idx < point_view->size(); idx++) {
      insert(LASPoint(point_view->point(idx)));
    }
    std::cout << "Reading points took " << point_timer << std::endl;
  }

  auto begin() { return m_points.begin(); }
  auto end() { return m_points.end(); }

  static LASFile with_border(const fs::path &filename, double border_width) {
    LASFile las_file(filename.string());
    pdal::BOX3D original_bounds = las_file.bounds();
    for (const BorderType border_type :
         {BorderType::N, BorderType::NE, BorderType::E, BorderType::SE, BorderType::S,
          BorderType::SW, BorderType::W, BorderType::NW}) {
      pdal::BOX2D box = external_border_ranges(original_bounds.to2d(), border_type, border_width);
      fs::path border_filename = fs::path("tmp") / (unique_coord_name(box) + ".las");
      if (fs::exists(border_filename)) {
        LASFile border_file(border_filename.string());
        for (const LASPoint &point : border_file) {
          las_file.insert(point);
        }
        las_file.m_bounds.grow(border_file.bounds());
      } else {
        std::cerr << border_type << " border file " << border_filename << " does not exist"
                  << std::endl;
      }
    }
    std::cout << "Combined " << filename << " with borders " << las_file.m_bounds << std::endl;
    return las_file;
  }

  std::size_t n_points() const { return m_points.size(); }
  const LASPoint &operator[](std::size_t i) const { return m_points[i]; }

  Coordinate2D<double> top_left() const { return {m_bounds.minx, m_bounds.maxy}; }
  au::QuantityD<au::Meters> width() const { return au::meters(m_bounds.maxx - m_bounds.minx); }
  au::QuantityD<au::Meters> height() const { return au::meters(m_bounds.maxy - m_bounds.miny); }
  const GeoProjection &projection() const { return m_projection; }

  pdal::BOX2D export_bounds() const {
    return pdal::BOX2D(average(m_bounds.minx, m_original_bounds.minx),
                       average(m_bounds.miny, m_original_bounds.miny),
                       average(m_bounds.maxx, m_original_bounds.maxx),
                       average(m_bounds.maxy, m_original_bounds.maxy));
  }

  pdal::BOX2D original_bounds() const { return m_original_bounds.to2d(); }

  std::pair<double, double> height_range() const { return m_height_range; }
  std::pair<uint16_t, uint16_t> intensity_range() const { return m_intensity_range; }

  LASPoint &operator[](std::size_t i) { return m_points[i]; }
  void push_back(const LASPoint &point) { m_points.push_back(point); }

  void write(const fs::path &filename) const {
    pdal::Options options;
    options.add("filename", filename.string());
    options.add("dataformat_id", 0);

    pdal::PointTable table;
    table.layout()->registerDim(pdal::Dimension::Id::X);
    table.layout()->registerDim(pdal::Dimension::Id::Y);
    table.layout()->registerDim(pdal::Dimension::Id::Z);
    table.layout()->registerDim(pdal::Dimension::Id::Intensity);
    table.layout()->registerDim(pdal::Dimension::Id::Classification);

    pdal::PointViewPtr view(new pdal::PointView(table));
    for (const LASPoint &point : m_points) {
      pdal::PointId idx = view->size();
      point.write_to(view->point(idx));
    }

    pdal::BufferReader reader;
    reader.addView(view);

    pdal::StageFactory factory;
    pdal::Stage *writer = factory.createStage("writers.las");
    writer->setInput(reader);
    writer->setOptions(options);
    writer->prepare(table);
    writer->execute(table);
  }

  const pdal::BOX3D &bounds() const { return m_bounds; }

  void extract_borders(const fs::path &tmp_dir, double border_width) {
    for (const BorderType border_type :
         {BorderType::N, BorderType::NE, BorderType::E, BorderType::SE, BorderType::S,
          BorderType::SW, BorderType::W, BorderType::NW}) {
      pdal::BOX2D box = border_ranges(m_bounds.to2d(), border_type, border_width);
      std::vector<LASPoint> border_points;
      LASFile border_file(box, GeoProjection(m_projection));
      for (const LASPoint &point : m_points) {
        if (box.contains(point.x(), point.y())) {
          border_file.insert(point);
        }
      }
      border_file.write(tmp_dir / (unique_coord_name(border_file.bounds().to2d()) + ".las"));
    }
  }
};

inline void extract_borders(const fs::path &las_filename, double border_width) {
  fs::path tmp_dir = fs::path("tmp");
  fs::create_directories(tmp_dir);

  fs::path done_file = tmp_dir / (las_filename.stem().string() + ".done");

  if (fs::exists(done_file)) {
    std::cout << "Skipping " << las_filename << " because it has already been processed"
              << std::endl;
    return;
  }

  std::cout << "Extracting borders from " << las_filename << " ..." << std::endl;
  LASFile las_file(las_filename.string());
  las_file.extract_borders(tmp_dir, border_width);

  // create done file
  std::ofstream bla(done_file);
}
