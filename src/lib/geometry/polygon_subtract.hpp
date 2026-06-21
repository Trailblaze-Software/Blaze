#pragma once

#include <ogrsf_frmts.h>

#include <memory>
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

  std::vector<std::unique_ptr<OGRGeometry>> pieces;
  if (auto host_geom = detail::polygon_to_ogr(normalized_host)) {
    pieces.push_back(std::move(host_geom));
  }
  if (pieces.empty()) {
    return {};
  }

  for (PolygonWithHoles cutout : cutouts) {
    if (cutout.exterior.size() < 3) {
      continue;
    }
    normalize_polygon(cutout);
    auto cut_geom = detail::polygon_to_ogr(cutout);
    if (!cut_geom) {
      continue;
    }

    std::vector<std::unique_ptr<OGRGeometry>> next_pieces;
    for (auto& piece : pieces) {
      if (!piece || piece->IsEmpty()) {
        continue;
      }
      std::unique_ptr<OGRGeometry> diff(piece->Difference(cut_geom.get()));
      if (!diff || diff->IsEmpty()) {
        continue;
      }
      detail::append_ogr_polygons(diff.get(), next_pieces);
    }
    pieces = std::move(next_pieces);
    if (pieces.empty()) {
      return {};
    }
  }

  std::vector<PolygonWithHoles> result;
  for (const auto& piece : pieces) {
    detail::append_polygons_from_ogr(piece.get(), result);
  }
  return result;
}
