#pragma once

#include <ogr_spatialref.h>

#include <algorithm>
#include <cmath>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "assert/assert.hpp"
#include "io/crs.hpp"
#include "las/las_file.hpp"
#include "printing/to_string.hpp"
#include "utilities/coordinate.hpp"
#include "utilities/filesystem.hpp"
#include "utilities/progress_tracker.hpp"

// Metadata for a single input LAS/LAZ file used in tiled processing
struct LASFileExtent {
  fs::path path;
  // override_crs value to pass when re-opening this file (empty means use
  // whatever CRS is embedded in the file).
  std::string override_crs;
  // Horizontal-only WKT normalized via make_projection_from_wkt().
  std::string horizontal_wkt;
  Extent3D bounds_native;
  // Axis-aligned bounding box of the file's extent reprojected into the
  // chosen output CRS
  Extent2D bounds_reprojected;
};

// Build a coordinate transformation between two WKT CRSes. Returns nullptr
// when the two CRSes match or either WKT is empty (caller must treat this as
// an identity transform).
inline std::unique_ptr<OGRCoordinateTransformation> make_coord_transform(
    const std::string& src_wkt, const std::string& dst_wkt) {
  if (src_wkt.empty() || dst_wkt.empty()) return {};
  if (src_wkt == dst_wkt || wkt_matches(src_wkt, dst_wkt)) return {};
  OGRSpatialReference src_srs;
  OGRSpatialReference dst_srs;
  if (src_srs.importFromWkt(src_wkt.c_str()) != OGRERR_NONE) {
    Fail("Failed to parse source CRS WKT for reprojection.");
  }
  if (dst_srs.importFromWkt(dst_wkt.c_str()) != OGRERR_NONE) {
    Fail("Failed to parse destination CRS WKT for reprojection.");
  }
  // Force traditional (lon, lat) / (x, y) axis ordering everywhere so the
  // existing LAS x/y semantics continue to hold on either side.
  src_srs.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);
  dst_srs.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);
  std::unique_ptr<OGRCoordinateTransformation> ct(
      OGRCreateCoordinateTransformation(&src_srs, &dst_srs));
  if (!ct) {
    Fail("Could not construct coordinate transformation between CRSes.");
  }
  return ct;
}

// Reproject an axis-aligned Extent2D from src_wkt to dst_wkt
inline Extent2D reproject_extent(const Extent2D& extent, const std::string& src_wkt,
                                 const std::string& dst_wkt) {
  auto ct = make_coord_transform(src_wkt, dst_wkt);
  if (!ct) return extent;

  constexpr int samples_per_edge = 16;
  std::vector<double> xs;
  std::vector<double> ys;
  xs.reserve(samples_per_edge * 4);
  ys.reserve(samples_per_edge * 4);
  const double dx = extent.maxx - extent.minx;
  const double dy = extent.maxy - extent.miny;
  for (int k = 0; k <= samples_per_edge; k++) {
    const double t = static_cast<double>(k) / samples_per_edge;
    xs.push_back(extent.minx + t * dx);
    ys.push_back(extent.miny);
    xs.push_back(extent.minx + t * dx);
    ys.push_back(extent.maxy);
    xs.push_back(extent.minx);
    ys.push_back(extent.miny + t * dy);
    xs.push_back(extent.maxx);
    ys.push_back(extent.miny + t * dy);
  }
  std::vector<int> status(xs.size(), 0);
  const int ok =
      ct->Transform(static_cast<int>(xs.size()), xs.data(), ys.data(), nullptr, status.data());
  if (!ok) {
    Fail("Failed to reproject extent corners between CRSes.");
  }

  Extent2D out;
  for (size_t i = 0; i < xs.size(); i++) {
    if (status[i] && std::isfinite(xs[i]) && std::isfinite(ys[i])) {
      out.grow(Extent2D{xs[i], xs[i], ys[i], ys[i]});
    }
  }
  Assert(std::isfinite(out.minx) && std::isfinite(out.maxx) && std::isfinite(out.miny) &&
             std::isfinite(out.maxy),
         "Reprojected extent has no finite samples.");
  return out;
}

struct TileModeInfo {
  // True when any pair of input files bounds overlap in xy
  bool any_overlap = false;
  // True when input files do not all share the same horizontal CRS
  bool crs_mismatch = false;

  // True when tiled mode must be enabled
  bool required() const { return any_overlap || crs_mismatch; }
};

// Inspect the input files and determine whether tiled processing is required.
// `target_wkt` is the output CRS (usually override_crs or the first file's
// CRS); when empty, the first file's own WKT is used as the reference.
inline TileModeInfo detect_tile_mode_needed(const std::vector<LASFileExtent>& extents) {
  TileModeInfo info;
  if (extents.size() < 2) return info;
  const std::string& ref_wkt = extents.front().horizontal_wkt;
  for (size_t i = 0; i < extents.size(); i++) {
    if (!ref_wkt.empty() && !extents[i].horizontal_wkt.empty() &&
        !wkt_matches(extents[i].horizontal_wkt, ref_wkt)) {
      info.crs_mismatch = true;
    }
    for (size_t j = i + 1; j < extents.size(); j++) {
      if (extents[i].bounds_reprojected.overlaps(extents[j].bounds_reprojected)) {
        info.any_overlap = true;
      }
    }
  }
  return info;
}

// Given extents with bounds_native and horizontal_wkt already populated,
// choose a reference CRS (override_wkt if provided, else the most common
// horizontal_wkt across all extents), reproject every extent's native bounds
// into that CRS to fill bounds_reprojected, then detect overlaps and CRS
// mismatches. Returns the TileModeInfo and sets bounds_reprojected in-place.
inline TileModeInfo analyze_extents(std::vector<LASFileExtent>& extents,
                                    const std::string& override_wkt = "") {
  std::string target_wkt = override_wkt;
  if (target_wkt.empty()) {
    std::unordered_map<std::string, std::size_t> counts;
    for (const LASFileExtent& e : extents) {
      if (!e.horizontal_wkt.empty()) counts[e.horizontal_wkt]++;
    }
    std::size_t best = 0;
    for (const auto& [wkt, n] : counts) {
      if (n > best) {
        best = n;
        target_wkt = wkt;
      }
    }
  }

  for (LASFileExtent& e : extents) {
    if (!target_wkt.empty() && !e.horizontal_wkt.empty() &&
        !wkt_matches(e.horizontal_wkt, target_wkt)) {
      try {
        e.bounds_reprojected = reproject_extent(static_cast<const Extent2D&>(e.bounds_native),
                                                e.horizontal_wkt, target_wkt);
      } catch (const std::exception&) {
        e.bounds_reprojected = static_cast<const Extent2D&>(e.bounds_native);
      }
    } else {
      e.bounds_reprojected = static_cast<const Extent2D&>(e.bounds_native);
    }
  }

  return detect_tile_mode_needed(extents);
}

// Load metadata and reprojected bounds for each input file. `override_crs`
// behaves as in the main pipeline: when non-empty it wins over anything
// embedded in the file. `output_crs_wkt` is the WKT each file's bounds will
// be reprojected into for overlap detection and tile placement. When the
// provided output CRS is empty, the first input file's own CRS is used.
inline std::vector<LASFileExtent> load_input_extents(const std::vector<fs::path>& files,
                                                     const std::string& override_crs,
                                                     std::string& output_crs_wkt,
                                                     ProgressTracker progress) {
  std::vector<LASFileExtent> extents;
  extents.reserve(files.size());

  const std::string override_wkt = user_crs_to_wkt(override_crs);

  for (size_t i = 0; i < files.size(); i++) {
    const fs::path& f = files[i];
    LASFile las(f,
                progress.subtracker(static_cast<double>(i) / files.size(),
                                    static_cast<double>(i + 1) / files.size()),
                override_crs);
    LASFileExtent extent;
    extent.path = f;
    extent.override_crs = override_crs;
    // horizontal_wkt is always the actual WKT (never a shorthand like
    // "EPSG:28355") so that wkt_matches() and OGRSpatialReference parsing
    // work reliably.
    extent.horizontal_wkt = override_wkt.empty() ? las.projection().to_string() : override_wkt;
    extent.bounds_native = las.bounds();
    extents.push_back(std::move(extent));
  }

  if (output_crs_wkt.empty()) {
    if (!override_wkt.empty()) {
      output_crs_wkt = override_wkt;
    } else if (!extents.empty()) {
      output_crs_wkt = extents.front().horizontal_wkt;
    }
  }

  for (LASFileExtent& extent : extents) {
    extent.bounds_reprojected = reproject_extent(static_cast<const Extent2D&>(extent.bounds_native),
                                                 extent.horizontal_wkt, output_crs_wkt);
  }

  return extents;
}

// Compute the union extent in output CRS over all extents.
inline Extent2D union_extent(const std::vector<LASFileExtent>& extents) {
  Extent2D out;
  for (const LASFileExtent& m : extents) {
    out.grow(m.bounds_reprojected);
  }
  return out;
}

// Snap `value` down to a multiple of `step`.
inline double snap_down(double value, double step) { return std::floor(value / step) * step; }

// Snap `value` up to a multiple of `step`.
inline double snap_up(double value, double step) { return std::ceil(value / step) * step; }

struct Tile {
  // Axis-aligned tile extent in the output CRS, not including border.
  Extent2D extent;
  // Output directory name for this tile. When empty, falls back to the
  // SW-corner-based `tile_<sw_x>_<sw_y>` naming.
  std::string name;

  std::string output_name() const {
    if (!name.empty()) return name;
    const long long sw_x = static_cast<long long>(std::llround(extent.minx));
    const long long sw_y = static_cast<long long>(std::llround(extent.miny));
    return "tile_" + std::to_string(sw_x) + "_" + std::to_string(sw_y);
  }
};

// Build one Tile per input file, using the file's reprojected extent as the
// tile extent and the file stem as the output directory name. Used for the
// non-tiled ("one output per input file") mode.
inline std::vector<Tile> tiles_per_file(const std::vector<LASFileExtent>& extents) {
  std::vector<Tile> tiles;
  tiles.reserve(extents.size());
  for (const LASFileExtent& e : extents) {
    tiles.push_back({e.bounds_reprojected, e.path.stem().string()});
  }
  return tiles;
}

// Read points from every overlapping input file into a single LASData whose
// bounds span tile+border in the output CRS. Points from files in a
// different CRS are reprojected on the fly.
inline LASData read_tile_from_inputs(const Extent2D& tile_extent, double border_width,
                                     const std::vector<LASFileExtent>& all_extents,
                                     const std::string& output_crs_wkt, ProgressTracker progress) {
  Extent2D bordered_extent = tile_extent;
  bordered_extent.minx -= border_width;
  bordered_extent.maxx += border_width;
  bordered_extent.miny -= border_width;
  bordered_extent.maxy += border_width;

  std::vector<const LASFileExtent*> overlapping;
  for (const LASFileExtent& extent : all_extents) {
    if (extent.bounds_reprojected.overlaps(bordered_extent)) {
      overlapping.push_back(&extent);
    }
  }

  LASData tile_data(tile_extent, GeoProjection(output_crs_wkt));

  if (overlapping.empty()) {
    return tile_data;
  }

  for (size_t i = 0; i < overlapping.size(); i++) {
    const LASFileExtent& extent = *overlapping[i];
    ProgressTracker sub = progress.subtracker(static_cast<double>(i) / overlapping.size(),
                                              static_cast<double>(i + 1) / overlapping.size());

    // Compute a bounds filter in the source file's own CRS (densified to
    // account for curvature when the CRSes differ).
    const bool same_crs = wkt_matches(extent.horizontal_wkt, output_crs_wkt);
    Extent2D filter_bounds =
        same_crs ? bordered_extent
                 : reproject_extent(bordered_extent, output_crs_wkt, extent.horizontal_wkt);

    LASData src(extent.path, sub.subtracker(0.0, 0.8), /*skip_reading_points=*/false,
                /*bounds=*/filter_bounds,
                /*override_crs=*/extent.override_crs);

    auto ct = make_coord_transform(extent.horizontal_wkt, output_crs_wkt);
    size_t kept = 0;
    for (const LASPoint& src_point : src) {
      double x = src_point.x();
      double y = src_point.y();
      double z = src_point.z();
      if (ct) {
        int status = 0;
        if (!ct->Transform(1, &x, &y, &z, &status) || !status || !std::isfinite(x) ||
            !std::isfinite(y) || !std::isfinite(z)) {
          continue;
        }
      }
      if (!bordered_extent.contains(x, y)) {
        continue;
      }
      LASPoint reprojected(x, y, z, src_point.intensity(), src_point.classification());
      tile_data.insert(reprojected);
      kept++;
    }
    sub.text_update(
        to_string("Tile read ", kept, " points from ", extent.path.filename().string()));
  }
  return tile_data;
}

inline std::vector<Tile> compute_tiles(const Extent2D& overall, double tile_size,
                                       const std::vector<LASFileExtent>& extents = {}) {
  AssertGT(tile_size, 0.0);
  std::vector<Tile> tiles;
  const double minx = snap_down(overall.minx, tile_size);
  const double miny = snap_down(overall.miny, tile_size);
  const double maxx = snap_up(overall.maxx, tile_size);
  const double maxy = snap_up(overall.maxy, tile_size);
  const long long nx =
      std::max<long long>(1, static_cast<long long>(std::llround((maxx - minx) / tile_size)));
  const long long ny =
      std::max<long long>(1, static_cast<long long>(std::llround((maxy - miny) / tile_size)));
  tiles.reserve(static_cast<size_t>(nx * ny));
  for (long long iy = 0; iy < ny; iy++) {
    for (long long ix = 0; ix < nx; ix++) {
      Extent2D tile_extent{minx + ix * tile_size, minx + (ix + 1) * tile_size,
                           miny + iy * tile_size, miny + (iy + 1) * tile_size};
      if (!extents.empty()) {
        const bool any_overlap = std::any_of(
            extents.begin(), extents.end(),
            [&](const LASFileExtent& e) { return e.bounds_reprojected.overlaps(tile_extent); });
        if (!any_overlap) continue;
      }
      tiles.push_back({tile_extent, ""});
    }
  }
  return tiles;
}
