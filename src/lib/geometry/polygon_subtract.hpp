#pragma once

#include <ogrsf_frmts.h>

#include <algorithm>
#include <cmath>
#include <memory>
#include <unordered_map>
#include <vector>

#include "geometry/polygon.hpp"
#include "io/gdal_init.hpp"

namespace detail {

inline void fill_ogr_ring(OGRLinearRing& ring, const std::vector<Coordinate2D<double>>& vertices) {
  for (const auto& vertex : vertices) {
    ring.addPoint(vertex.x(), vertex.y());
  }
  ring.closeRings();
}

inline std::unique_ptr<OGRGeometry> polygon_to_ogr(const PolygonWithHoles& poly) {
  OGRPolygon ogr;
  OGRLinearRing ext;
  fill_ogr_ring(ext, poly.exterior);
  if (ogr.addRing(&ext) != OGRERR_NONE) {
    return nullptr;
  }
  for (const auto& hole : poly.holes) {
    OGRLinearRing int_ring;
    fill_ogr_ring(int_ring, hole);
    if (ogr.addRing(&int_ring) != OGRERR_NONE) {
      return nullptr;
    }
  }
  return std::unique_ptr<OGRGeometry>(ogr.clone());
}

inline std::unique_ptr<OGRGeometry> ring_to_ogr(
    const std::vector<Coordinate2D<double>>& exterior_ring) {
  OGRPolygon ogr;
  OGRLinearRing ext;
  fill_ogr_ring(ext, exterior_ring);
  if (ogr.addRing(&ext) != OGRERR_NONE) {
    return nullptr;
  }
  return std::unique_ptr<OGRGeometry>(ogr.clone());
}

inline PolygonWithHoles polygon_from_ogr(const OGRPolygon* ogr_poly) {
  PolygonWithHoles poly;
  if (!ogr_poly) {
    return poly;
  }

  const OGRLinearRing* ext_ring = ogr_poly->getExteriorRing();
  if (!ext_ring || ext_ring->getNumPoints() < 3) {
    return poly;
  }
  for (int pi = 0; pi < ext_ring->getNumPoints(); pi++) {
    poly.exterior.emplace_back(ext_ring->getX(pi), ext_ring->getY(pi));
  }
  for (int hi = 0; hi < ogr_poly->getNumInteriorRings(); hi++) {
    const OGRLinearRing* int_ring = ogr_poly->getInteriorRing(hi);
    std::vector<Coordinate2D<double>> hole;
    for (int pi = 0; pi < int_ring->getNumPoints(); pi++) {
      hole.emplace_back(int_ring->getX(pi), int_ring->getY(pi));
    }
    poly.holes.push_back(std::move(hole));
  }
  normalize_polygon(poly);
  return poly;
}

inline void append_polygons_from_ogr(const OGRGeometry* geometry,
                                     std::vector<PolygonWithHoles>& out) {
  if (!geometry || geometry->IsEmpty()) {
    return;
  }

  const OGRwkbGeometryType type = wkbFlatten(geometry->getGeometryType());
  if (type == wkbPolygon) {
    out.push_back(polygon_from_ogr(static_cast<const OGRPolygon*>(geometry)));
  } else if (type == wkbMultiPolygon) {
    const auto* multi = static_cast<const OGRMultiPolygon*>(geometry);
    for (int i = 0; i < multi->getNumGeometries(); i++) {
      out.push_back(polygon_from_ogr(static_cast<const OGRPolygon*>(multi->getGeometryRef(i))));
    }
  }
}

inline void append_ogr_polygons(const OGRGeometry* geometry,
                                std::vector<std::unique_ptr<OGRGeometry>>& out) {
  if (!geometry || geometry->IsEmpty()) {
    return;
  }

  const OGRwkbGeometryType type = wkbFlatten(geometry->getGeometryType());
  if (type == wkbPolygon) {
    out.push_back(std::unique_ptr<OGRGeometry>(geometry->clone()));
  } else if (type == wkbMultiPolygon) {
    const auto* multi = static_cast<const OGRMultiPolygon*>(geometry);
    for (int i = 0; i < multi->getNumGeometries(); i++) {
      out.push_back(std::unique_ptr<OGRGeometry>(multi->getGeometryRef(i)->clone()));
    }
  }
}

// Uniform grid index for bbox overlap queries (e.g. matching forest to nearby cutouts).
class ExtentSpatialIndex {
  double m_cell_size;
  std::unordered_map<int64_t, std::vector<size_t>> m_cells;

  static int64_t cell_key(int cx, int cy) {
    return (static_cast<int64_t>(static_cast<uint32_t>(cx)) << 32) | static_cast<uint32_t>(cy);
  }

  int cell_coord(double v) const { return static_cast<int>(std::floor(v / m_cell_size)); }

 public:
  explicit ExtentSpatialIndex(double cell_size) : m_cell_size(std::max(cell_size, 1.0)) {}

  void insert(size_t index, const Extent2D& ext) {
    const int min_cx = cell_coord(ext.minx);
    const int max_cx = cell_coord(ext.maxx);
    const int min_cy = cell_coord(ext.miny);
    const int max_cy = cell_coord(ext.maxy);
    for (int cy = min_cy; cy <= max_cy; ++cy) {
      for (int cx = min_cx; cx <= max_cx; ++cx) {
        m_cells[cell_key(cx, cy)].push_back(index);
      }
    }
  }

  void query(const Extent2D& ext, std::vector<size_t>& out) const {
    out.clear();
    const int min_cx = cell_coord(ext.minx);
    const int max_cx = cell_coord(ext.maxx);
    const int min_cy = cell_coord(ext.miny);
    const int max_cy = cell_coord(ext.maxy);
    for (int cy = min_cy; cy <= max_cy; ++cy) {
      for (int cx = min_cx; cx <= max_cx; ++cx) {
        auto it = m_cells.find(cell_key(cx, cy));
        if (it == m_cells.end()) {
          continue;
        }
        for (size_t index : it->second) {
          out.push_back(index);
        }
      }
    }
    std::sort(out.begin(), out.end());
    out.erase(std::unique(out.begin(), out.end()), out.end());
  }
};

inline std::unique_ptr<OGRGeometry> build_cutout_union(
    const std::vector<PolygonWithHoles>& cutouts) {
  std::vector<std::unique_ptr<OGRGeometry>> geoms;
  geoms.reserve(cutouts.size());
  for (const PolygonWithHoles& cutout : cutouts) {
    if (cutout.exterior.size() < 3) {
      continue;
    }
    PolygonWithHoles normalized = cutout;
    normalize_polygon(normalized);
    auto cut_geom = polygon_to_ogr(normalized);
    if (cut_geom) {
      geoms.push_back(std::move(cut_geom));
    }
  }
  if (geoms.empty()) {
    return nullptr;
  }
  while (geoms.size() > 1) {
    std::vector<std::unique_ptr<OGRGeometry>> next;
    next.reserve((geoms.size() + 1) / 2);
    for (size_t i = 0; i < geoms.size(); i += 2) {
      if (i + 1 < geoms.size()) {
        std::unique_ptr<OGRGeometry> merged(geoms[i]->Union(geoms[i + 1].get()));
        if (merged && !merged->IsEmpty()) {
          next.push_back(std::move(merged));
        } else if (geoms[i] && !geoms[i]->IsEmpty()) {
          next.push_back(std::move(geoms[i]));
        } else if (geoms[i + 1] && !geoms[i + 1]->IsEmpty()) {
          next.push_back(std::move(geoms[i + 1]));
        }
      } else {
        next.push_back(std::move(geoms[i]));
      }
    }
    geoms = std::move(next);
  }
  return std::move(geoms[0]);
}

}  // namespace detail

// Subtract cutout polygons from `host`. Returns one or more polygons after boolean
// difference (e.g. a cutout may split the host into separate pieces).
// Ring orientation is normalized on output: CCW exteriors, CW holes.
//
// TODO: replace GEOS/OGR backend with an in-house implementation.
inline std::vector<PolygonWithHoles> subtract_polygon(
    const PolygonWithHoles& host, const std::vector<PolygonWithHoles>& cutouts) {
  ensure_gdal_initialized();

  if (host.exterior.size() < 3) {
    return {};
  }

  PolygonWithHoles normalized_host = host;
  normalize_polygon(normalized_host);

  const Extent2D host_ext = ring_extent(normalized_host.exterior);
  std::vector<PolygonWithHoles> active_cutouts;
  active_cutouts.reserve(cutouts.size());
  for (const PolygonWithHoles& cutout : cutouts) {
    if (cutout.exterior.size() < 3) {
      continue;
    }
    if (!ring_extent(cutout.exterior).overlaps(host_ext)) {
      continue;
    }
    active_cutouts.push_back(cutout);
  }
  if (active_cutouts.empty()) {
    return {normalized_host};
  }

  std::unique_ptr<OGRGeometry> cut_union = detail::build_cutout_union(active_cutouts);
  if (!cut_union || cut_union->IsEmpty()) {
    return {normalized_host};
  }

  auto host_geom = detail::polygon_to_ogr(normalized_host);
  if (!host_geom) {
    return {};
  }

  std::unique_ptr<OGRGeometry> diff(host_geom->Difference(cut_union.get()));
  if (!diff || diff->IsEmpty()) {
    return {};
  }

  std::vector<PolygonWithHoles> result;
  detail::append_polygons_from_ogr(diff.get(), result);
  return result;
}

// Subtract a pre-built cutout union from `host`. The union should cover all cutouts
// that might apply; host/cutout overlap is checked via bounding boxes first.
inline std::vector<PolygonWithHoles> subtract_polygon_with_union(const PolygonWithHoles& host,
                                                                 const OGRGeometry* cut_union) {
  ensure_gdal_initialized();

  if (host.exterior.size() < 3 || !cut_union || cut_union->IsEmpty()) {
    return {};
  }

  PolygonWithHoles normalized_host = host;
  normalize_polygon(normalized_host);

  const Extent2D host_ext = ring_extent(normalized_host.exterior);
  OGREnvelope cut_env;
  cut_union->getEnvelope(&cut_env);
  if (!host_ext.overlaps({cut_env.MinX, cut_env.MaxX, cut_env.MinY, cut_env.MaxY})) {
    return {normalized_host};
  }

  auto host_geom = detail::polygon_to_ogr(normalized_host);
  if (!host_geom) {
    return {};
  }

  std::unique_ptr<OGRGeometry> diff(host_geom->Difference(cut_union));
  if (!diff || diff->IsEmpty()) {
    return {};
  }

  std::vector<PolygonWithHoles> result;
  detail::append_polygons_from_ogr(diff.get(), result);
  return result;
}

// Intersect `host` with `clip`. Returns one or more polygons after boolean
// intersection (e.g. clipping may split the host into separate pieces).
// Ring orientation is normalized on output: CCW exteriors, CW holes.
inline std::vector<PolygonWithHoles> intersect_polygon(const PolygonWithHoles& host,
                                                       const PolygonWithHoles& clip) {
  ensure_gdal_initialized();

  if (host.exterior.size() < 3 || clip.exterior.size() < 3) {
    return {};
  }

  PolygonWithHoles normalized_host = host;
  PolygonWithHoles normalized_clip = clip;
  normalize_polygon(normalized_host);
  normalize_polygon(normalized_clip);

  auto host_geom = detail::polygon_to_ogr(normalized_host);
  auto clip_geom = detail::polygon_to_ogr(normalized_clip);
  if (!host_geom || !clip_geom) {
    return {};
  }

  std::unique_ptr<OGRGeometry> intersection(host_geom->Intersection(clip_geom.get()));
  if (!intersection || intersection->IsEmpty()) {
    return {};
  }

  std::vector<PolygonWithHoles> result;
  detail::append_polygons_from_ogr(intersection.get(), result);
  return result;
}

// Clip a polygon-with-holes to an axis-aligned extent. Hole-free polygons use fast
// Sutherland-Hodgman; polygons with holes use GEOS intersection so bisected holes
// become exterior boundary rather than spurious interior rings.
inline std::vector<PolygonWithHoles> clip_polygon_to_extent(const PolygonWithHoles& poly,
                                                            const Extent2D& bounds) {
  if (poly.exterior.size() < 3) {
    return {};
  }
  if (poly.holes.empty()) {
    return clip_polygon_hole_free_to_extent(poly, bounds);
  }
  return intersect_polygon(poly, polygon_from_extent(bounds));
}
