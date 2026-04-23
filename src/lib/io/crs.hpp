#pragma once

#include <ogr_spatialref.h>

#include <string>

#include "assert/assert.hpp"
#include "grid/grid.hpp"

// Normalize a WKT CRS string for downstream use by blaze:
//   - Strip any vertical (3D / COMPD_CS) component, since blaze only works in 2D.
//   - Best-effort auto-identify an EPSG code on the horizontal CRS, so QGIS can
//     recognize it on sight instead of showing "unknown CRS".
// Falls back to returning the input unchanged if the WKT can't be parsed.
inline std::string normalize_crs_wkt(const std::string& wkt) {
  if (wkt.empty()) return {};
  OGRSpatialReference srs;
  if (srs.importFromWkt(wkt.c_str()) != OGRERR_NONE) return wkt;
  srs.StripVertical();
  srs.AutoIdentifyEPSG();
  char* out_wkt = nullptr;
  srs.exportToWkt(&out_wkt);
  std::string result = out_wkt ? out_wkt : wkt;
  CPLFree(out_wkt);
  return result;
}

// If `wkt` is a compound (horizontal + vertical) CRS, return a WKT describing
// a compound CRS with:
//   - the horizontal component replaced with `normalized_horizontal` (which
//     should be the EPSG-identified 2D CRS produced by normalize_crs_wkt),
//   - the original vertical component preserved verbatim.
// If `wkt` has no vertical component, returns `normalized_horizontal` unchanged.
// Falls back to `normalized_horizontal` if anything goes wrong.
inline std::string build_compound_crs_wkt(const std::string& wkt,
                                          const std::string& normalized_horizontal) {
  if (wkt.empty()) return normalized_horizontal;
  OGRSpatialReference srs;
  if (srs.importFromWkt(wkt.c_str()) != OGRERR_NONE) return normalized_horizontal;
  if (!srs.IsCompound()) return normalized_horizontal;

  const OGR_SRSNode* root = srs.GetRoot();
  if (!root) return normalized_horizontal;
  const OGR_SRSNode* vert_node = nullptr;
  for (int i = 0; i < root->GetChildCount(); i++) {
    const OGR_SRSNode* child = root->GetChild(i);
    const char* name = child->GetValue();
    if (name && std::string(name) == "VERT_CS") {
      vert_node = child;
      break;
    }
  }
  if (!vert_node) return normalized_horizontal;

  OGRSpatialReference horizontal_srs;
  if (horizontal_srs.importFromWkt(normalized_horizontal.c_str()) != OGRERR_NONE) {
    return normalized_horizontal;
  }
  OGRSpatialReference vertical_srs;
  char* vert_wkt = nullptr;
  const_cast<OGR_SRSNode*>(vert_node)->exportToWkt(&vert_wkt);
  if (!vert_wkt || vertical_srs.importFromWkt(vert_wkt) != OGRERR_NONE) {
    CPLFree(vert_wkt);
    return normalized_horizontal;
  }
  CPLFree(vert_wkt);

  OGRSpatialReference compound_srs;
  const char* compound_name = root->GetChildCount() > 0 ? root->GetChild(0)->GetValue() : "";
  if (compound_srs.SetCompoundCS(compound_name ? compound_name : "", &horizontal_srs,
                                 &vertical_srs) != OGRERR_NONE) {
    return normalized_horizontal;
  }
  char* out_wkt = nullptr;
  compound_srs.exportToWkt(&out_wkt);
  std::string result = out_wkt ? out_wkt : normalized_horizontal;
  CPLFree(out_wkt);
  return result;
}

// Build a GeoProjection from a raw WKT (possibly compound), producing a
// 2D-normalized horizontal WKT for general-purpose use and a compound WKT
// that preserves any original vertical datum for elevation outputs.
inline GeoProjection make_projection_from_wkt(const std::string& raw_wkt) {
  if (raw_wkt.empty()) return GeoProjection{};
  const std::string horizontal = normalize_crs_wkt(raw_wkt);
  const std::string compound = build_compound_crs_wkt(raw_wkt, horizontal);
  return GeoProjection(horizontal, compound);
}
