

# File crs.hpp

[**File List**](files.md) **>** [**io**](dir_65bc51589f8002bfcb72faf47ab41180.md) **>** [**crs.hpp**](crs_8hpp.md)

[Go to the documentation of this file](crs_8hpp.md)


```C++
#pragma once

#include <ogr_spatialref.h>

#include <array>
#include <cmath>
#include <memory>
#include <string>

#include "assert/assert.hpp"
#include "grid/grid.hpp"
#include "utilities/coordinate.hpp"

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

// Result of attempting to parse a user-supplied CRS string. `ok` is true iff
// parsing succeeded; for empty input parsing trivially succeeds and `wkt` is
// empty. On failure, `wkt` is empty and `error` carries a human-readable
// reason suitable for surfacing in the UI.
struct UserCrsParseResult {
  bool ok;
  std::string wkt;
  std::string error;
};

// Non-throwing variant of user_crs_to_wkt(). Use this in interactive contexts
// (e.g. the GUI) where a parse failure should be reported rather than abort.
inline UserCrsParseResult try_user_crs_to_wkt(const std::string& user_crs) {
  if (user_crs.empty()) return {true, {}, {}};
  OGRSpatialReference srs;
  if (srs.SetFromUserInput(user_crs.c_str()) != OGRERR_NONE) {
    return {false,
            {},
            "Could not interpret CRS '" + user_crs +
                "'. Expected an EPSG code (e.g. 'EPSG:28355'), proj.4 string, or WKT."};
  }
  srs.StripVertical();
  srs.AutoIdentifyEPSG();
  char* wkt = nullptr;
  srs.exportToWkt(&wkt);
  std::string wkt_string = wkt ? wkt : std::string{};
  CPLFree(wkt);
  return {true, std::move(wkt_string), {}};
}

// Convert a user-supplied CRS string ("EPSG:28355", proj.4 string, WKT, ...)
// into a canonical 2D-normalized WKT string. Returns empty string if the
// input was empty. Aborts with a helpful error if the input is non-empty but
// cannot be parsed.
inline std::string user_crs_to_wkt(const std::string& user_crs) {
  UserCrsParseResult result = try_user_crs_to_wkt(user_crs);
  if (!result.ok) Fail(result.error);
  return std::move(result.wkt);
}

// Returns true if two WKT strings describe the same CRS (tolerating cosmetic
// differences in the WKT representation). Empty strings are never "same".
inline bool wkt_parses(const std::string& wkt) {
  if (wkt.empty()) return false;
  OGRSpatialReference srs;
  return srs.importFromWkt(wkt.c_str()) == OGRERR_NONE;
}

inline bool wkt_matches(const std::string& a, const std::string& b) {
  if (a.empty() || b.empty()) return false;
  if (a == b) return true;
  OGRSpatialReference srs_a;
  OGRSpatialReference srs_b;
  if (srs_a.importFromWkt(a.c_str()) != OGRERR_NONE) return false;
  if (srs_b.importFromWkt(b.c_str()) != OGRERR_NONE) return false;
  return srs_a.IsSame(&srs_b) == TRUE;
}

// True when two CRSes are identical, or when both are projected CRSes with the
// same parameters (e.g. GDA94 MGA zone 55 vs GDA2020 MGA zone 55). The latter
// may be offset by a datum shift but is close enough for 3D visualisation.
inline bool crs_compatible_for_viewing(const std::string& a, const std::string& b) {
  if (a.empty() || b.empty()) return true;
  const std::string norm_a = normalize_crs_wkt(a);
  const std::string norm_b = normalize_crs_wkt(b);
  if (wkt_matches(norm_a, norm_b)) return true;

  OGRSpatialReference srs_a;
  OGRSpatialReference srs_b;
  if (srs_a.importFromWkt(norm_a.c_str()) != OGRERR_NONE) return false;
  if (srs_b.importFromWkt(norm_b.c_str()) != OGRERR_NONE) return false;
  if (!srs_a.IsProjected() || !srs_b.IsProjected()) return false;

  auto param_matches = [&](const char* key) {
    return std::abs(srs_a.GetProjParm(key, 0.0) - srs_b.GetProjParm(key, 0.0)) < 1e-6;
  };

  return param_matches(SRS_PP_LATITUDE_OF_ORIGIN) && param_matches(SRS_PP_CENTRAL_MERIDIAN) &&
         param_matches(SRS_PP_FALSE_EASTING) && param_matches(SRS_PP_FALSE_NORTHING) &&
         param_matches(SRS_PP_SCALE_FACTOR);
}

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
  src_srs.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);
  dst_srs.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);
  std::unique_ptr<OGRCoordinateTransformation> ct(
      OGRCreateCoordinateTransformation(&src_srs, &dst_srs));
  if (!ct) {
    Fail("Could not construct coordinate transformation between CRSes.");
  }
  return ct;
}

// Horizontal-only reprojection of a single x/y pair. Returns false on failure.
inline bool transform_xy_h(OGRCoordinateTransformation* ct, double& x, double& y) {
  if (!ct) return true;
  int success = 0;
  if (!ct->Transform(1, &x, &y, nullptr, &success) || !success) {
    return false;
  }
  return true;
}

// Reproject the horizontal footprint of an Extent3D, preserving z limits.
inline Extent3D reproject_extent3d_horizontal(const Extent3D& extent,
                                              OGRCoordinateTransformation* ct) {
  if (!ct) return extent;
  const std::array<double, 4> xs = {extent.minx, extent.maxx, extent.minx, extent.maxx};
  const std::array<double, 4> ys = {extent.miny, extent.miny, extent.maxy, extent.maxy};
  Extent3D out;
  out.minz = extent.minz;
  out.maxz = extent.maxz;
  for (size_t i = 0; i < xs.size(); ++i) {
    double x = xs[i];
    double y = ys[i];
    if (!transform_xy_h(ct, x, y)) {
      Fail("Failed to reproject extent corner between CRSes.");
    }
    out.grow(x, y, extent.minz);
    out.grow(x, y, extent.maxz);
  }
  return out;
}
```


