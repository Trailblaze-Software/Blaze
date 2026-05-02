#pragma once

#include <cstdint>
#include <fstream>
#include <future>
#include <iostream>
#include <limits>
#include <mutex>

#include "ogr_spatialref.h"
#include "spatial_index.hpp"
#ifdef USE_PDAL
#include <pdal/Dimension.hpp>
#include <pdal/SpatialReference.hpp>
#include <pdal/io/BufferReader.hpp>
#include <pdal/io/LasHeader.hpp>
#include <pdal/io/LasReader.hpp>
#include <pdal/pdal.hpp>
#include <pdal/util/Bounds.hpp>
#else
#include "las_reader.hpp"
#include "las_writer.hpp"
#endif
#include <string>
#include <vector>

#include "grid/grid.hpp"
#include "io/crs.hpp"
#include "las_point.hpp"
#include "utilities/filesystem.hpp"
#include "utilities/progress_tracker.hpp"
#include "utilities/resources.hpp"
#include "utilities/timer.hpp"

enum class BorderType { N, NE, E, SE, S, SW, W, NW };

inline std::ostream& operator<<(std::ostream& os, BorderType border_type) {
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

inline Extent2D border_ranges(const Extent2D& box, BorderType border_type, double border_width) {
  switch (border_type) {
    case BorderType::N:
      return {box.minx, box.maxx, box.maxy - border_width, box.maxy};
    case BorderType::NE:
      return {box.maxx - border_width, box.maxx, box.maxy - border_width, box.maxy};
    case BorderType::E:
      return {box.maxx - border_width, box.maxx, box.miny, box.maxy};
    case BorderType::SE:
      return {box.maxx - border_width, box.maxx, box.miny, box.miny + border_width};
    case BorderType::S:
      return {box.minx, box.maxx, box.miny, box.miny + border_width};
    case BorderType::SW:
      return {box.minx, box.minx + border_width, box.miny, box.miny + border_width};
    case BorderType::W:
      return {box.minx, box.minx + border_width, box.miny, box.maxy};
    case BorderType::NW:
      return {box.minx, box.minx + border_width, box.maxy - border_width, box.maxy};
  }
  unreachable();
}

inline Extent2D external_border_ranges(const Extent2D& box, BorderType border_type,
                                       double border_width) {
  switch (border_type) {
    case BorderType::N:
      return {box.minx, box.maxx, box.maxy, box.maxy + border_width};
    case BorderType::NE:
      return {box.maxx, box.maxx + border_width, box.maxy, box.maxy + border_width};
    case BorderType::E:
      return {box.maxx, box.maxx + border_width, box.miny, box.maxy};
    case BorderType::SE:
      return {box.maxx, box.maxx + border_width, box.miny - border_width, box.miny};
    case BorderType::S:
      return {box.minx, box.maxx, box.miny - border_width, box.miny};
    case BorderType::SW:
      return {box.minx - border_width, box.minx, box.miny - border_width, box.miny};
    case BorderType::W:
      return {box.minx - border_width, box.minx, box.miny, box.maxy};
    case BorderType::NW:
      return {box.minx - border_width, box.minx, box.maxy, box.maxy + border_width};
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

inline std::string unique_coord_name(const Extent2D& box) {
  return std::to_string(round(box.minx, 10)) + "_" + std::to_string(round(box.miny, 10)) + "_" +
         std::to_string(round(box.maxx, 10)) + "_" + std::to_string(round(box.maxy, 10));
}

#ifdef USE_PDAL
inline void print_metadata(const pdal::MetadataNode& node, const std::string& prefix = "") {
  std::cout << prefix << node.name() << ": " << node.value() << std::endl;
  for (const std::string& name : node.childNames()) {
    print_metadata(node.findChild(name), prefix + "  ");
  }
}
#endif

#undef min
#undef max

#ifndef USE_PDAL
inline void copy_from(LASPoint& point, const laspp::LASPointFormat0& data) {
  point.x() = data.x;
  point.y() = data.y;
  point.z() = data.z;
  point.intensity() = data.intensity;
  point.classification() = static_cast<LASClassification>(data.classification());
}

inline void copy_from(LASPoint& point, const laspp::LASPointFormat6& data) {
  point.x() = data.x;
  point.y() = data.y;
  point.z() = data.z;
  point.intensity() = data.intensity;
  point.classification() = static_cast<LASClassification>(data.classification);
}

inline void copy_from(laspp::LASPointFormat0& data, const LASPoint& point) {
  data.x = point.x();
  data.y = point.y();
  data.z = point.z();
  data.intensity = point.intensity();
  data.classification_byte.classification =
      static_cast<laspp::LASClassification>(static_cast<uint8_t>(point.classification()));
}

inline std::string convert_geo_keys_to_wkt(const laspp::LASGeoKeys& geo_keys) {
  OGRSpatialReference srs;
  bool projectionSet = false;

  auto keys = geo_keys.get_keys();

  if (keys.find(3072) != keys.end()) {  // Projected CRS
    uint16_t epsg_code = std::get<uint16_t>(keys.at(3072));
    if (srs.importFromEPSG(epsg_code) == OGRERR_NONE) {
      projectionSet = true;
    }
  } else if (keys.find(2048) != keys.end()) {  // Geographic CRS
    uint16_t epsg_code = std::get<uint16_t>(keys.at(2048));
    if (srs.importFromEPSG(epsg_code) == OGRERR_NONE) {
      projectionSet = true;
    }
  }

  if (!projectionSet) {
    std::cerr << geo_keys << std::endl;
    Fail("ERROR: No valid EPSG code found in LASGeoKeys.");
  }

  // Convert to WKT
  char* wkt = nullptr;
  srs.exportToWkt(&wkt);
  std::string wktString = wkt;
  CPLFree(wkt);

  return wktString;
}

inline Extent2D as_extent2d(const laspp::Bound3D& b) {
  return Extent2D(b.min_x(), b.max_x(), b.min_y(), b.max_y());
}

inline Extent3D as_extent3d(const laspp::Bound3D& b) {
  return Extent3D(as_extent2d(b), b.min_z(), b.max_z());
}

// Returns the normalized horizontal WKT for a reader, honouring override_crs
// (a user-supplied shorthand like "EPSG:28355" or a full WKT). Falls back to
// the file's embedded WKT/GeoKeys, then to an empty string if nothing is
// available. Never throws.
inline std::string reader_horizontal_wkt(const laspp::LASReader& reader,
                                         const std::string& override_crs = "") {
  // Use the non-throwing variant so an invalid override_crs degrades to
  // "fall back to the file's embedded CRS" rather than propagating an
  // exception out of a function documented as never throwing.
  const UserCrsParseResult override_parsed = try_user_crs_to_wkt(override_crs);
  if (override_parsed.ok && !override_parsed.wkt.empty()) return override_parsed.wkt;
  if (reader.wkt().has_value()) return normalize_crs_wkt(reader.wkt().value());
  if (reader.geo_keys().has_value()) {
    try {
      return normalize_crs_wkt(convert_geo_keys_to_wkt(reader.geo_keys().value()));
    } catch (const std::exception&) {
    }
  }
  return {};
}

#endif

class LASFile {
 protected:
  std::optional<fs::path> m_filename;
  Extent3D m_bounds;
  Extent3D m_original_bounds;
  GeoProjection m_projection;

 public:
  explicit LASFile(const Extent2D& bounds, GeoProjection&& projection)
      : m_bounds(bounds, std::numeric_limits<double>::max(), std::numeric_limits<double>::min()),
        m_original_bounds(m_bounds),
        m_projection(std::move(projection)) {};

 protected:
#ifndef USE_PDAL
  laspp::QuadtreeSpatialIndex m_spatial_index;

  void from_las_reader(const laspp::LASReader& reader, const std::string& override_crs = "") {
    const laspp::Bound3D& bounds = reader.header().bounds();
    m_bounds = as_extent3d(bounds);
    m_original_bounds = m_bounds;

    // Keep the raw embedded WKT for compound-CRS preservation (vertical datum).
    std::string raw_embedded_wkt;
    if (reader.wkt().has_value()) {
      raw_embedded_wkt = reader.wkt().value();
    } else if (reader.geo_keys().has_value()) {
      try {
        raw_embedded_wkt = convert_geo_keys_to_wkt(reader.geo_keys().value());
      } catch (const std::exception&) {
      }
    }
    const std::string embedded_wkt =
        raw_embedded_wkt.empty() ? std::string{} : normalize_crs_wkt(raw_embedded_wkt);

    const std::string override_wkt = user_crs_to_wkt(override_crs);

    if (!override_wkt.empty()) {
      // "override_crs" wins unconditionally. override_wkt has already been
      // canonicalized to a valid 2D WKT by user_crs_to_wkt(); feeding the raw
      // user string (which can be a shorthand like "EPSG:28355") into
      // make_projection_from_wkt() would leave m_projection holding that
      // shorthand and later crash when GDAL tries to parse it as WKT.
      m_projection = make_projection_from_wkt(override_wkt);
      if (!embedded_wkt.empty() && !wkt_matches(embedded_wkt, override_wkt)) {
        std::cerr << "WARNING: LAS file "
                  << (m_filename.has_value() ? m_filename->string() : std::string("<unknown>"))
                  << " has an embedded CRS that differs from the config 'override_crs'.\n"
                  << "  embedded: " << embedded_wkt << "\n"
                  << "  override: " << override_wkt << "\n"
                  << "  Using the override. Remove 'override_crs' from the config to use the"
                  << " embedded CRS instead." << std::endl;
      }
    } else if (!embedded_wkt.empty()) {
      // Use a GeoProjection that has both the EPSG-normalized horizontal WKT
      // (for 2D outputs like GPKGs and image TIFs) and a compound WKT that
      // preserves any original vertical datum (e.g. AHD) for DEM outputs.
      m_projection = make_projection_from_wkt(raw_embedded_wkt);
    } else {
      Fail("No projection found in LAS file " +
           (m_filename.has_value() ? m_filename->string() : std::string("<unknown>")) +
           ". Either embed a CRS in the file or set the 'override_crs' field in the config"
           " (e.g. \"override_crs\": \"EPSG:28355\").");
    }

    if (reader.has_lastools_spatial_index()) {
      m_spatial_index = reader.lastools_spatial_index();
    }
  }
#endif

 public:
  explicit LASFile(const fs::path& filename, ProgressTracker progress_tracker,
                   [[maybe_unused]] const std::string& override_crs = "")
      : m_filename(filename) {
    Timer timer;
    progress_tracker.text_update(to_string("Reading ", filename, " metadata ..."));
#ifdef USE_PDAL
    (void)override_crs;
#else
    laspp::LASReader reader(filename);
    from_las_reader(reader, override_crs);
    progress_tracker.text_update("Reading metadata took " + to_string(timer));
#endif
  }

  Coordinate2D<double> top_left() const { return {m_bounds.minx, m_bounds.maxy}; }
  double width() const { return m_bounds.maxx - m_bounds.minx; }
  double height() const { return m_bounds.maxy - m_bounds.miny; }
  const GeoProjection& projection() const { return m_projection; }

  Extent2D export_bounds() const {
    return Extent2D(average(m_bounds.minx, m_original_bounds.minx),
                    average(m_bounds.maxx, m_original_bounds.maxx),
                    average(m_bounds.miny, m_original_bounds.miny),
                    average(m_bounds.maxy, m_original_bounds.maxy));
  }

  const Extent3D& bounds() const { return m_bounds; }
  Extent2D original_bounds() const { return m_original_bounds; }

  std::pair<double, double> height_range() const { return {m_bounds.minz, m_bounds.maxz}; }
};

class LASData : public LASFile {
  std::pair<uint16_t, uint16_t> m_intensity_range;
  std::vector<LASPoint> m_points;

 public:
  LASData(const Extent2D& bounds, const GeoProjection& projection)
      : LASFile(bounds, GeoProjection(projection)),
        m_intensity_range(
            {std::numeric_limits<uint16_t>::max(), std::numeric_limits<uint16_t>::min()}) {}

  template <typename T>
  explicit LASData(const GeoGrid<T>& grid)
      : LASData(*grid.extent(), GeoProjection(grid.projection())) {
    for (size_t i = 0; i < grid.height(); i++) {
      for (size_t j = 0; j < grid.width(); j++) {
        Coordinate2D<double> coord =
            grid.transform().pixel_to_projection({(double)j + 0.5, (double)i + 0.5});
        insert(LASPoint(coord.x(), coord.y(), grid[{j, i}], 1000, LASClassification::Ground));
      }
    }
  }

  void insert(const LASPoint& point) {
    m_points.emplace_back(point);
    m_intensity_range.first = std::min(m_intensity_range.first, point.intensity());
    m_intensity_range.second = std::max(m_intensity_range.second, point.intensity());
    m_bounds.grow(point.x(), point.y(), point.z());
  }

#ifndef USE_PDAL
 protected:
  void read_points(laspp::LASReader& reader, ProgressTracker progress_tracker,
                   std::optional<Extent2D> bounds = std::nullopt) {
    Timer point_timer;

    if (bounds.has_value() && reader.has_lastools_spatial_index()) {
      // Create query bounds (note: Bound2D constructor is min_x, min_y, max_x, max_y)
      laspp::Bound2D query_bounds(bounds->minx, bounds->miny, bounds->maxx, bounds->maxy);

      // Get spatial index and find ONLY cells that overlap the query bounds
      const auto& spatial_index = reader.lastools_spatial_index();
      const auto& cells = spatial_index.cells();

      // Collect point intervals ONLY from cells that overlap the query extent
      std::vector<laspp::PointInterval> intervals;
      for (const auto& [cell_index, cell] : cells) {
        // Check if this cell overlaps the query bounds
        laspp::Bound2D cell_bounds = spatial_index.get_cell_bounds(cell_index);

        // Two bounds overlap if: max_x > min_x && max_y > min_y (edge-touching doesn't count)
        bool overlaps = (cell_bounds.max_x() > query_bounds.min_x() &&
                         cell_bounds.min_x() < query_bounds.max_x() &&
                         cell_bounds.max_y() > query_bounds.min_y() &&
                         cell_bounds.min_y() < query_bounds.max_y());

        if (overlaps) {
          // Only add intervals from overlapping cells
          intervals.insert(intervals.end(), cell.intervals.begin(), cell.intervals.end());
        }
      }

      // Get chunk indices for intervals from overlapping cells only
      std::vector<size_t> chunk_indices = reader.get_chunk_indices_from_intervals(intervals);

      progress_tracker.text_update(
          to_string("Reading ", chunk_indices.size(), "/", reader.num_chunks(), " chunks"));

      if (!chunk_indices.empty()) {
        // Calculate total points needed
        size_t total_points = 0;
        if (reader.header().is_laz_compressed()) {
          const auto& points_per_chunk = reader.points_per_chunk();
          for (size_t chunk_idx : chunk_indices) {
            total_points += points_per_chunk[chunk_idx];
          }
        } else {
          total_points = reader.num_points();
        }

        // Read only the chunks that contain points from overlapping cells
        m_points.resize(total_points);
        reader.read_chunks_list(std::span<LASPoint>(m_points), chunk_indices);

        // Filter points that are actually within the bounds
        const auto& transform = reader.header().transform();
        std::vector<LASPoint> filtered_points;
        filtered_points.reserve(m_points.size());

        for (const auto& point : m_points) {
          auto coords = transform.transform_point(point.x(), point.y(), point.z());
          if (query_bounds.contains(coords.x(), coords.y())) {
            filtered_points.push_back(point);
            // Transform coordinates
            filtered_points.back().x() = coords.x();
            filtered_points.back().y() = coords.y();
            filtered_points.back().z() = coords.z();
          }
        }

        m_points = std::move(filtered_points);
      } else {
        // No overlapping cells found, set empty
        m_points.clear();
      }
    } else {
      // No bounds or no spatial index - read all points
      m_points.resize(reader.num_points());
      reader.read_chunks(std::span<LASPoint>(m_points), {0, reader.num_chunks()});

      // Transform coordinates
      const auto& transform = reader.header().transform();
      for (LASPoint& point : m_points) {
        auto coords = transform.transform_point(point.x(), point.y(), point.z());
        point.x() = coords.x();
        point.y() = coords.y();
        point.z() = coords.z();
      }
    }

    progress_tracker.text_update(
        to_string("Reading ", m_points.size(), " points took ", point_timer));

    // Calculate intensity range
    for (const LASPoint& point : m_points) {
      m_intensity_range.first = std::min(m_intensity_range.first, point.intensity());
      m_intensity_range.second = std::max(m_intensity_range.second, point.intensity());
    }

    progress_tracker.text_update(to_string("Calculating extent took ", point_timer));
  }

 public:
#endif

  explicit LASData(const fs::path& filename, ProgressTracker progress_tracker,
                   [[maybe_unused]] bool skip_reading_points = false,
                   [[maybe_unused]] std::optional<Extent2D> bounds = std::nullopt,
                   [[maybe_unused]] const std::string& override_crs = "")
      : LASFile(filename, progress_tracker.subtracker(0, 0.1), override_crs) {
    Timer timer;
    progress_tracker.text_update(to_string("Reading ", filename, " ..."));
    Assert(fs::exists(filename), "File does not exist: " + filename.string());

#ifdef USE_PDAL
    pdal::Option las_opt("filename", filename.string());
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
    const auto& header_bounds = las_header.getBounds();
    m_bounds = Extent3D(
        Extent2D(header_bounds.minx, header_bounds.maxx, header_bounds.miny, header_bounds.maxy),
        header_bounds.minz, header_bounds.maxz);
    m_original_bounds = m_bounds;
    const std::string pdal_raw_wkt = las_header.srs().getWKT();
    const std::string pdal_wkt = normalize_crs_wkt(pdal_raw_wkt);
    const std::string pdal_override_wkt = user_crs_to_wkt(override_crs);
    if (!pdal_override_wkt.empty()) {
      // See matching comment in from_las_reader(): feed the canonicalized
      // WKT, not the raw user string, so shorthands like "EPSG:28355" work.
      m_projection = make_projection_from_wkt(pdal_override_wkt);
      if (!pdal_wkt.empty() && !wkt_matches(pdal_wkt, pdal_override_wkt)) {
        std::cerr << "WARNING: LAS file " << filename.string()
                  << " has an embedded CRS that differs from the config 'override_crs'."
                  << " Using the override." << std::endl;
      }
    } else if (!pdal_wkt.empty()) {
      m_projection = make_projection_from_wkt(pdal_raw_wkt);
    } else {
      Fail("No projection found in LAS file " + filename.string() +
           ". Either embed a CRS in the file or set the 'override_crs' field in the config.");
    }

    progress_tracker.text_update(to_string("Read ", point_view->size(), " points"));
    // std::cout << "Spatial reference: " << pdal::SpatialReference(las_header.srs().getWKT())
    //<< std::endl;
    //
    // std::cout << "Fields: " << std::endl;
    // for (pdal::Dimension::Id dim : dims) {
    // std::cout << "- " << pdal::Dimension::name(dim) << ": " << pdal::Dimension::description(dim)
    //<< " (" << point_view->dimType(dim) << ")" << std::endl;
    //}

    progress_tracker.text_update("Reading metadata took " + to_string(timer));

    Timer point_timer;
    for (pdal::PointId idx = 0; idx < point_view->size(); idx++) {
      insert(LASPoint(point_view->point(idx)));
    }

    progress_tracker.text_update(
        to_string("Reading ", point_view->size(), " points took ", point_timer));
#else
    laspp::LASReader reader(filename);
    from_las_reader(reader, override_crs);
    progress_tracker.text_update("Reading metadata took " + to_string(timer));
    if (skip_reading_points) {
      return;
    }
    read_points(reader, progress_tracker.subtracker(0.1, 1.0), bounds);
#endif
  }

  auto begin() { return m_points.begin(); }
  auto end() { return m_points.end(); }

  std::pair<uint16_t, uint16_t> intensity_range() const { return m_intensity_range; }

  static LASData with_border(const fs::path& filename, double border_width,
                             const std::vector<std::pair<Extent3D, fs::path>>& all_las_file_extents,
                             ProgressTracker progress_tracker,
                             const std::string& override_crs = "") {
    LASData las_file(filename, progress_tracker.subtracker(0.0, 0.6), false, std::nullopt,
                     override_crs);
    Extent3D original_bounds = las_file.bounds();
    Extent3D extended_bounds = original_bounds;
    extended_bounds.grow(border_width);

    std::vector<fs::path> overlapping_filenames;
    for (const auto& [extent, border_filename] : all_las_file_extents) {
      if (extended_bounds.intersects(extent) && extent != original_bounds) {
        overlapping_filenames.push_back(border_filename);
      }
    }
    for (size_t i = 0; i < overlapping_filenames.size(); i++) {
      const fs::path& border_filename = overlapping_filenames[i];
      LASData border_file(
          border_filename.string(),
          progress_tracker.subtracker(0.6 + (double)i / overlapping_filenames.size() * 0.4,
                                      0.6 + (double)(i + 1) / overlapping_filenames.size() * 0.4),
          false, extended_bounds, override_crs);
      for (const LASPoint& point : border_file) {
        if (!extended_bounds.contains(point.x(), point.y())) {
          continue;
        }
        las_file.insert(point);
      }
      Extent3D intersection = extended_bounds.intersection(border_file.bounds());
      las_file.m_bounds.grow(intersection);
    }
    progress_tracker.text_update(
        to_string("Combined ", filename.string(), " with borders ", las_file.bounds()));
    return las_file;
  }

  static LASData with_border(const fs::path& filename, double border_width,
                             ProgressTracker progress_tracker,
                             const std::string& override_crs = "") {
    LASData las_file(filename, progress_tracker.subtracker(0.0, 0.6), false, std::nullopt,
                     override_crs);
    Extent3D original_bounds = las_file.bounds();
    std::vector<fs::path> border_filenames;
    for (const BorderType border_type :
         {BorderType::N, BorderType::NE, BorderType::E, BorderType::SE, BorderType::S,
          BorderType::SW, BorderType::W, BorderType::NW}) {
      Extent2D box = external_border_ranges(original_bounds, border_type, border_width);
      fs::path border_filename = LocalDataRetriever::get_local_data("extracted_borders") /
                                 (unique_coord_name(box) + ".laz");
      if (fs::exists(border_filename)) {
        border_filenames.push_back(border_filename);
      } else {
        std::cerr << border_type << " border file " << border_filename << " does not exist"
                  << std::endl;
      }
    }
    ProgressTracker subtracker = progress_tracker.subtracker(0.6, 1.0);
    for (size_t i = 0; i < border_filenames.size(); i++) {
      const fs::path& border_filename = border_filenames[i];
      LASData border_file(border_filename.string(),
                          subtracker.subtracker((double)i / border_filenames.size(),
                                                (double)(i + 1) / border_filenames.size()));
      for (const LASPoint& point : border_file) {
        las_file.insert(point);
      }
      las_file.m_bounds.grow(border_file.bounds());
    }
    progress_tracker.text_update(
        to_string("Combined ", filename.string(), " with borders ", las_file.m_bounds));
    return las_file;
  }

  std::size_t n_points() const { return m_points.size(); }
  const LASPoint& operator[](std::size_t i) const { return m_points[i]; }

  LASPoint& operator[](std::size_t i) { return m_points[i]; }
  void push_back(const LASPoint& point) { m_points.push_back(point); }

  void write(const fs::path& filename, std::optional<ProgressTracker> progress_tracker = {}) const {
    (void)progress_tracker;
#ifdef USE_PDAL
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
    for (const LASPoint& point : m_points) {
      pdal::PointId idx = view->size();
      point.write_to(view->point(idx));
    }

    pdal::BufferReader reader;
    reader.addView(view);

    pdal::StageFactory factory;
    pdal::Stage* writer = factory.createStage("writers.las");
    writer->setInput(reader);
    writer->setOptions(options);
    writer->prepare(table);
    writer->execute(table);
#else
    std::fstream file(filename, std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
    laspp::LASWriter las_writer(file, 128);
    las_writer.write_wkt(m_projection.to_string());
    std::vector<LASPoint> points_copy = m_points;
    las_writer.header().transform().scale_factors().x() = 0.001;
    las_writer.header().transform().scale_factors().y() = 0.001;
    las_writer.header().transform().scale_factors().z() = 0.001;
    las_writer.header().transform().offsets().x() = m_bounds.minx;
    las_writer.header().transform().offsets().y() = m_bounds.miny;
    las_writer.header().transform().offsets().z() = m_bounds.minz;
    for (LASPoint& point : points_copy) {
      point.x() = (point.x() - m_bounds.minx) / 0.001;
      point.y() = (point.y() - m_bounds.miny) / 0.001;
      point.z() = (point.z() - m_bounds.minz) / 0.001;
    }
    las_writer.write_points(std::span<const LASPoint>(points_copy));
#endif
  }

  void extract_borders(const fs::path& tmp_dir, double border_width,
                       ProgressTracker progress_tracker) const {
    size_t idx = 0;
    for (const BorderType border_type :
         {BorderType::N, BorderType::NE, BorderType::E, BorderType::SE, BorderType::S,
          BorderType::SW, BorderType::W, BorderType::NW}) {
      progress_tracker.set_proportion((double)idx / 8);
      Extent2D box = border_ranges(m_bounds, border_type, border_width);
      LASData border_file(box, GeoProjection(m_projection));
      for (const LASPoint& point : m_points) {
        if (box.contains(point.x(), point.y())) {
          border_file.insert(point);
        }
      }
      if (border_file.n_points() > 0) {
        border_file.write(
            tmp_dir /
                (unique_coord_name(static_cast<const Extent2D&>(border_file.bounds())) + ".laz"),
            progress_tracker.subtracker(((double)idx + 0.5) / 8, (double)(idx + 1) / 8));
      }
      idx++;
    }
  }
};

class AsyncLASData : public LASData {
  std::mutex m_mutex;
  std::promise<void> m_data_promise;
  std::thread m_thread;

 public:
  AsyncLASData(const fs::path& filename, AsyncProgressTracker progress_tracker,
               std::vector<std::function<void()>> callbacks = {})
      : LASData(Extent2D(0, 0, 0, 0), GeoProjection("")) {
    std::promise<void> metadata_promise;
    m_thread =
        std::thread([this, filename, &metadata_promise, progress_tracker, callbacks]() mutable {
#ifndef USE_PDAL
          laspp::LASReader reader(filename);
          this->from_las_reader(reader);
          metadata_promise.set_value();
          std::lock_guard<std::mutex> lock(m_mutex);
          this->read_points(reader, progress_tracker.tracker()->subtracker(0.01, 1.0));
          m_data_promise.set_value();
          for (const auto& callback : callbacks) {
            callback();
          }
#endif
        });
    m_thread.detach();
    metadata_promise.get_future().wait();
  }

  bool data_ready() {
    return m_data_promise.get_future().wait_for(std::chrono::seconds(0)) ==
           std::future_status::ready;
  }
  void wait_for_data() { m_thread.join(); }

  std::mutex& mutex() { return m_mutex; }

  ~AsyncLASData() {
    if (m_thread.joinable()) {
      m_thread.join();
    }
  }
};

inline void extract_borders(const fs::path& las_filename, double border_width,
                            ProgressTracker progress_tracker) {
  fs::path tmp_dir = LocalDataRetriever::get_local_data("extracted_borders");
  fs::create_directories(tmp_dir);

  fs::path done_file = tmp_dir / (las_filename.stem().string() + ".done");

  if (fs::exists(done_file)) {
    progress_tracker.text_update(
        to_string("Skipping ", las_filename, " because it has already been processed"));
    return;
  }

  progress_tracker.text_update(to_string("Extracting borders from ", las_filename, " ..."));
  LASData las_file(las_filename.string(), progress_tracker.subtracker(0.0, 0.6));
  las_file.extract_borders(tmp_dir, border_width, progress_tracker.subtracker(0.6, 1.0));

  // create done file
  std::ofstream bla(done_file);
}
