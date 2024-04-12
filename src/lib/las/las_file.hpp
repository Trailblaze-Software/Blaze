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

#include "au/units/meters.hh"
#include "grid/grid.hpp"
#include "las_point.hpp"
#include "utilities/timer.hpp"

inline void print_metadata(const pdal::MetadataNode &node, const std::string &prefix = "") {
  std::cout << prefix << node.name() << ": " << node.value() << std::endl;
  for (const std::string &name : node.childNames()) {
    print_metadata(node.findChild(name), prefix + "  ");
  }
}

class LASFile {
  std::vector<LASPoint> m_points;
  pdal::BOX3D m_bounds;
  GeoProjection m_projection;

 public:
  explicit LASFile(const std::string &filename) {
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
    m_projection = GeoProjection(las_header.srs().getWKT());

    std::cout << "Read " << point_view->size() << " points" << std::endl;
    //std::cout << "Spatial reference: " << pdal::SpatialReference(las_header.srs().getWKT())
              //<< std::endl;
//
    //std::cout << "Fields: " << std::endl;
    //for (pdal::Dimension::Id dim : dims) {
      //std::cout << "- " << pdal::Dimension::name(dim) << ": " << pdal::Dimension::description(dim)
                //<< " (" << point_view->dimType(dim) << ")" << std::endl;
    //}

    std::cout << "Reading metadata took " << timer << std::endl;

    Timer point_timer;
    for (pdal::PointId idx = 0; idx < point_view->size(); idx++) {
      m_points.emplace_back(LASPoint(point_view->point(idx)));
    }
    std::cout << "Reading points took " << point_timer << std::endl;
  }

  std::size_t n_points() const { return m_points.size(); }
  const LASPoint &operator[](std::size_t i) const { return m_points[i]; }

  Coordinate2D<double> top_left() const { return {m_bounds.minx, m_bounds.maxy}; }
  au::QuantityD<au::Meters> width() const { return au::meters(m_bounds.maxx - m_bounds.minx); }
  au::QuantityD<au::Meters> height() const { return au::meters(m_bounds.maxy - m_bounds.miny); }
  const GeoProjection &projection() const { return m_projection; }

  LASPoint &operator[](std::size_t i) { return m_points[i]; }
  void push_back(const LASPoint &point) { m_points.push_back(point); }

  void write(const std::string &filename) const {
    pdal::Options options;
    options.add("filename", filename);
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

  auto begin() { return m_points.begin(); }
  auto end() { return m_points.end(); }
};
