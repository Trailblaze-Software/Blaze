#pragma once

#include <ogrsf_frmts.h>

#include <algorithm>
#include <cmath>
#include <limits>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "assert/assert.hpp"
#include "config_input/config_input.hpp"
#include "contour/contour.hpp"
#include "contour/contour_gen.hpp"
#include "geometry/polygon.hpp"
#include "geometry/polygon_subtract.hpp"
#include "grid/grid.hpp"
#include "io/gdal_init.hpp"
#include "io/gpkg.hpp"
#include "printing/to_string.hpp"
#include "utilities/coordinate.hpp"
#include "utilities/filesystem.hpp"
#include "utilities/timer.hpp"

// =============================================================================
// VegePolygon — a vegetation polygon with layer classification
// =============================================================================

struct VegePolygon {
  std::string layer;  // CRT layer name, e.g. "405_Forest"
  std::string name;   // symbolic number extracted from layer, e.g. "405"
  std::vector<Coordinate2D<double>> exterior_ring;
  std::vector<std::vector<Coordinate2D<double>>> holes;
};

// =============================================================================
// extract_threshold_layers — extract {threshold → layer_name} from a VegeHeightConfig
// =============================================================================

inline std::string threshold_layer_name(const VegeHeightConfig& config,
                                        const BlockingThresholdColorPair& btc) {
  if (!btc.layer.empty()) {
    return btc.layer;
  }
  const std::string& prefix = config.name.empty() ? "Vegetation" : config.name;
  return prefix + "_" + double_to_string(btc.blocking_threshold);
}

inline std::map<double, std::string> extract_threshold_layers(const VegeHeightConfig& config) {
  std::map<double, std::string> layers;
  for (const auto& btc : config.colors) {
    layers[btc.blocking_threshold] = threshold_layer_name(config, btc);
  }
  return layers;
}

// Extract the numeric layer name from a full layer string like "405_Forest" → "405".
inline std::string layer_number(const std::string& layer) {
  auto underscore_pos = layer.find('_');
  if (underscore_pos != std::string::npos) {
    return layer.substr(0, underscore_pos);
  }
  return layer;
}

// Subtract cutout polygons from `host`. Returns one or more host polygons after
// boolean difference (e.g. a cutout may split the host into separate pieces).
inline std::vector<VegePolygon> subtract_from_polygon(const VegePolygon& host,
                                                      const std::vector<VegePolygon>& cutouts) {
  PolygonWithHoles host_poly{host.exterior_ring, host.holes};
  std::vector<PolygonWithHoles> cut_polys;
  cut_polys.reserve(cutouts.size());
  for (const VegePolygon& cutout : cutouts) {
    if (cutout.exterior_ring.size() >= 3) {
      cut_polys.push_back({cutout.exterior_ring, cutout.holes});
    }
  }

  std::vector<VegePolygon> result;
  for (const PolygonWithHoles& piece : subtract_polygon(host_poly, cut_polys)) {
    VegePolygon poly;
    poly.layer = host.layer;
    poly.name = host.name;
    poly.exterior_ring = piece.exterior;
    poly.holes = piece.holes;
    result.push_back(std::move(poly));
  }
  return result;
}

// Clip vegetation polygons to the export extent (same bounds used for raster export).
inline void trim_vege_polygons_to_extent(std::vector<VegePolygon>& polygons,
                                         const Extent2D& bounds) {
  if (polygons.empty()) {
    return;
  }

  const PolygonWithHoles clip = polygon_from_extent(bounds);
  if (clip.exterior.size() < 3) {
    return;
  }

  std::vector<VegePolygon> trimmed;
  trimmed.reserve(polygons.size());
  for (const VegePolygon& poly : polygons) {
    if (poly.exterior_ring.size() < 3) {
      continue;
    }
    if (!ring_extent(poly.exterior_ring).overlaps(bounds)) {
      continue;
    }

    for (const PolygonWithHoles& piece :
         intersect_polygon({poly.exterior_ring, poly.holes}, clip)) {
      if (piece.exterior.size() < 3) {
        continue;
      }
      VegePolygon out;
      out.layer = poly.layer;
      out.name = poly.name;
      out.exterior_ring = piece.exterior;
      out.holes = piece.holes;
      trimmed.push_back(std::move(out));
    }
  }
  polygons = std::move(trimmed);
}

// Remove holes that are smaller than the minimum hole area for their layer.
// This should be called before min-area polygon filtering and before cutting
// understory out of forest.
inline void filter_small_holes(std::vector<VegePolygon>& polygons,
                               const std::map<std::string, double>& min_hole_areas) {
  for (VegePolygon& poly : polygons) {
    auto it = min_hole_areas.find(poly.layer);
    if (it == min_hole_areas.end()) continue;
    double min_m2 = it->second;
    if (min_m2 <= 0) continue;
    poly.holes.erase(std::remove_if(poly.holes.begin(), poly.holes.end(),
                                    [&](const std::vector<Coordinate2D<double>>& hole) {
                                      return std::abs(signed_area(hole)) < min_m2;
                                    }),
                     poly.holes.end());
  }
}

// Net polygon area in m² (exterior minus holes). Hole rings are CW (negative).
inline double polygon_net_area_m2(const VegePolygon& poly) {
  double area = signed_area(poly.exterior_ring);
  for (const auto& hole : poly.holes) {
    area += signed_area(hole);
  }
  return area;
}

// Filter polygons by minimum area in m². Ring coordinates are already in
// projection units (meters for projected CRSes), so signed_area returns m².
inline void filter_by_min_area(std::vector<VegePolygon>& polygons,
                               const std::map<std::string, double>& min_areas) {
  polygons.erase(std::remove_if(polygons.begin(), polygons.end(),
                                [&](const VegePolygon& p) {
                                  auto it = min_areas.find(p.layer);
                                  if (it == min_areas.end()) return false;
                                  double min_m2 = it->second;
                                  if (min_m2 <= 0) return false;
                                  return std::abs(polygon_net_area_m2(p)) < min_m2;
                                }),
                 polygons.end());
}

inline std::vector<VegePolygon> contours_to_polygons(
    const std::map<double, std::vector<Contour>>& contours_by_height,
    const std::map<double, std::string>& height_to_layer) {
  // Contours from generate_contours_at_heights are oriented so higher values are
  // on the left: CCW outers (positive signed area), CW holes (negative signed area).
  struct RingInfo {
    std::vector<Coordinate2D<double>> points;
    double threshold;
    double abs_area;
    bool consumed = false;  // already assigned as a hole in something
  };

  std::vector<RingInfo> all_rings;

  for (const auto& [height, contours] : contours_by_height) {
    for (size_t idx = 0; idx < contours.size(); idx++) {
      const Contour& c = contours[idx];
      Assert(c.is_loop(), "vegetation contours must be closed loops");
      AssertGE(c.points().size(), 3u);

      std::vector<Coordinate2D<double>> ring = c.points();
      // Snap the ring closed for OGR: make the last point exactly equal to the first.
      if (ring.size() > 1) {
        ring.back() = ring.front();
      }

      double area = std::abs(signed_area(ring));
      all_rings.push_back({std::move(ring), height, area, false});
    }
  }

  // Sort by area descending within each threshold so outer rings (larger area)
  // are processed before potential holes.
  std::sort(all_rings.begin(), all_rings.end(), [](const RingInfo& a, const RingInfo& b) {
    if (a.threshold != b.threshold) return a.threshold > b.threshold;
    return a.abs_area > b.abs_area;
  });

  // Second pass: determine outer rings vs holes by containment within each threshold.
  std::vector<VegePolygon> polygons;

  for (size_t i = 0; i < all_rings.size(); i++) {
    if (all_rings[i].consumed) continue;

    auto layer_it = height_to_layer.find(all_rings[i].threshold);
    if (layer_it == height_to_layer.end()) continue;

    // Exteriors are CCW (positive signed area). CW rings are holes only.
    if (signed_area(all_rings[i].points) <= 0.0) continue;

    all_rings[i].consumed = true;

    VegePolygon poly;
    poly.layer = layer_it->second;
    poly.name = layer_number(poly.layer);
    poly.exterior_ring = all_rings[i].points;
    AssertGT(signed_area(poly.exterior_ring), 0.0);

    // Same-threshold CW rings inside this exterior become holes when they are the
    // direct child (not nested inside another CW hole ring within this exterior).
    for (size_t j = i + 1; j < all_rings.size(); j++) {
      if (all_rings[j].consumed) continue;
      if (all_rings[j].threshold != all_rings[i].threshold) continue;
      if (signed_area(all_rings[j].points) >= 0.0) continue;
      if (!point_in_ring(all_rings[j].points[0], poly.exterior_ring)) continue;

      bool nested_in_other_hole = false;
      for (size_t k = i + 1; k < all_rings.size(); k++) {
        if (k == j) continue;
        if (all_rings[k].threshold != all_rings[i].threshold) continue;
        if (signed_area(all_rings[k].points) >= 0.0) continue;
        if (!point_in_ring(all_rings[k].points[0], poly.exterior_ring)) continue;
        if (point_in_ring(all_rings[j].points[0], all_rings[k].points)) {
          nested_in_other_hole = true;
          break;
        }
      }
      if (nested_in_other_hole) continue;

      poly.holes.push_back(all_rings[j].points);
      all_rings[j].consumed = true;
    }

    polygons.push_back(std::move(poly));
  }

  // CCW rings not consumed above are independent polygons (e.g. an island inside
  // a hole, or a separate patch at another density rendered on top in OCAD/OOM).
  for (size_t i = 0; i < all_rings.size(); i++) {
    if (all_rings[i].consumed) continue;
    auto layer_it = height_to_layer.find(all_rings[i].threshold);
    if (layer_it == height_to_layer.end()) continue;
    if (signed_area(all_rings[i].points) <= 0.0) continue;

    VegePolygon poly;
    poly.layer = layer_it->second;
    poly.name = layer_number(poly.layer);
    poly.exterior_ring = all_rings[i].points;
    AssertGT(signed_area(poly.exterior_ring), 0.0);
    polygons.push_back(std::move(poly));
  }

  return polygons;
}

// =============================================================================
// generate_vege_polygons — full pipeline: grids → contours → polygons → filter → cut
// =============================================================================

inline std::vector<VegePolygon> generate_vege_polygons(
    const VegeConfig& vege_config, const std::map<std::string, GeoGrid<float>>& vege_maps) {
  // Collect polygons from all height configs
  std::vector<VegePolygon> all_polygons;
  for (const VegeHeightConfig& vc : vege_config.height_configs) {
    std::map<double, std::string> threshold_layers = extract_threshold_layers(vc);
    if (threshold_layers.empty()) continue;

    auto it = vege_maps.find(vc.name);
    if (it == vege_maps.end()) continue;

    const GeoGrid<float>& grid = it->second;

    std::vector<double> thresholds;
    for (const auto& [t, _] : threshold_layers) {
      thresholds.push_back(t);
    }

    auto contours = generate_contours_at_heights(grid, thresholds, /*min_points=*/5, 0.0f);
    auto polygons = contours_to_polygons(contours, threshold_layers);

    // Rough open land: same forest threshold but pad 1.0 so the tile edge reads as
    // forest and open areas polygonize with forest islands as holes.
    if (!thresholds.empty()) {
      double lowest = thresholds.front();
      std::string lowest_layer = threshold_layers.at(lowest);
      if (lowest_layer.rfind("405_", 0) == 0) {
        auto open_contours = generate_contours_at_heights(grid, {lowest}, /*min_points=*/5, 1.0f);
        // orient_consistent puts above-threshold values on the left; rough open land
        // polygons enclose below-threshold regions, so flip ring direction.
        for (auto& [height, open_height_contours] : open_contours) {
          for (Contour& c : open_height_contours) {
            std::reverse(c.points().begin(), c.points().end());
          }
        }
        std::map<double, std::string> open_layer = {{lowest, "403_Rough_Open_Land"}};
        for (VegePolygon& poly : contours_to_polygons(open_contours, open_layer)) {
          poly.name = "403";
          all_polygons.push_back(std::move(poly));
        }
      }
    }

    for (VegePolygon& poly : polygons) {
      all_polygons.push_back(std::move(poly));
    }
  }

  // Build min-area / min-hole maps from config
  std::map<std::string, double> min_areas, min_hole_areas;
  for (const VegeHeightConfig& vc : vege_config.height_configs) {
    for (const auto& btc : vc.colors) {
      const std::string layer = threshold_layer_name(vc, btc);
      if (btc.min_area_m2 > 0) min_areas[layer] = btc.min_area_m2;
      if (btc.min_hole_area_m2 > 0) min_hole_areas[layer] = btc.min_hole_area_m2;
    }
  }
  // Cross-map the two 405_Forest config thresholds onto rough open land:
  //   403 min hole ← 405 min area, 403 min area ← 405 min hole
  if (auto forest_area = min_areas.find("405_Forest"); forest_area != min_areas.end()) {
    if (forest_area->second > 0) {
      min_hole_areas["403_Rough_Open_Land"] = forest_area->second;
    }
  }
  if (auto forest_hole = min_hole_areas.find("405_Forest"); forest_hole != min_hole_areas.end()) {
    if (forest_hole->second > 0) {
      min_areas["403_Rough_Open_Land"] = forest_hole->second;
    }
  }

  filter_small_holes(all_polygons, min_hole_areas);
  filter_by_min_area(all_polygons, min_areas);

  // Subtract green understory from Forest polygons
  {
    std::vector<VegePolygon> understory;
    for (const VegePolygon& p : all_polygons) {
      if (p.layer == "406_Slow_Running" || p.layer == "408_Walk" || p.layer == "410_Fight") {
        understory.push_back(p);
      }
    }
    if (!understory.empty()) {
      std::vector<VegePolygon> updated;
      updated.reserve(all_polygons.size());
      for (VegePolygon& p : all_polygons) {
        if (p.layer == "405_Forest") {
          for (VegePolygon& piece : subtract_from_polygon(p, understory)) {
            updated.push_back(std::move(piece));
          }
        } else {
          updated.push_back(std::move(p));
        }
      }
      all_polygons = std::move(updated);
    }
  }

  filter_small_holes(all_polygons, min_hole_areas);

  // Drop polygons that fell below min area after subtraction (e.g. forest slivers).
  filter_by_min_area(all_polygons, min_areas);

  return all_polygons;
}

// =============================================================================
// read_vege_polygons — read VegePolygon vector from a vegetation GPKG file
// =============================================================================

inline std::vector<VegePolygon> read_vege_polygons(const fs::path& gpkg_path) {
  std::vector<VegePolygon> all_polygons;
  if (!fs::exists(gpkg_path)) return all_polygons;

  ensure_gdal_initialized();
  GDALDataset* dataset = (GDALDataset*)GDALOpenEx(gpkg_path.string().c_str(), GDAL_OF_VECTOR,
                                                  nullptr, nullptr, nullptr);
  if (!dataset) {
    std::cerr << "Warning: failed to open " << gpkg_path << std::endl;
    return all_polygons;
  }

  for (int li = 0; li < dataset->GetLayerCount(); li++) {
    OGRLayer* layer = dataset->GetLayer(li);
    if (!layer) continue;

    OGRFeatureDefn* defn = layer->GetLayerDefn();
    if (!defn || wkbFlatten(defn->GetGeomType()) != wkbPolygon) continue;

    OGRFeature* feature;
    layer->ResetReading();
    while ((feature = layer->GetNextFeature()) != nullptr) {
      OGRGeometry* geometry = feature->GetGeometryRef();
      if (!geometry || wkbFlatten(geometry->getGeometryType()) != wkbPolygon) {
        OGRFeature::DestroyFeature(feature);
        continue;
      }

      OGRPolygon* ogr_poly = (OGRPolygon*)geometry;
      const OGRLinearRing* ext_ring = ogr_poly->getExteriorRing();
      if (!ext_ring || ext_ring->getNumPoints() < 3) {
        OGRFeature::DestroyFeature(feature);
        continue;
      }

      VegePolygon poly;
      int layer_idx = feature->GetFieldIndex("layer");
      int name_idx = feature->GetFieldIndex("name");
      poly.layer = layer_idx >= 0 ? feature->GetFieldAsString(layer_idx) : "";
      poly.name = name_idx >= 0 ? feature->GetFieldAsString(name_idx) : "";

      for (int pi = 0; pi < ext_ring->getNumPoints(); pi++) {
        poly.exterior_ring.emplace_back(ext_ring->getX(pi), ext_ring->getY(pi));
      }
      for (int hi = 0; hi < ogr_poly->getNumInteriorRings(); hi++) {
        const OGRLinearRing* int_ring = ogr_poly->getInteriorRing(hi);
        std::vector<Coordinate2D<double>> hole;
        for (int pi = 0; pi < int_ring->getNumPoints(); pi++) {
          hole.emplace_back(int_ring->getX(pi), int_ring->getY(pi));
        }
        poly.holes.push_back(std::move(hole));
      }

      OGRFeature::DestroyFeature(feature);

      if (!poly.layer.empty()) {
        all_polygons.push_back(std::move(poly));
      }
    }
  }

  GDALClose(dataset);
  return all_polygons;
}

// =============================================================================
// combine_vege_gpkgs — merge per-tile vegetation GPKGs into a single combined file
// =============================================================================

inline void combine_vege_gpkgs(const std::vector<fs::path>& tile_dirs, const fs::path& combined_dir,
                               const std::string& projection) {
  std::map<std::string, std::vector<VegePolygon>> polygons_by_layer;
  for (const fs::path& dir : tile_dirs) {
    for (VegePolygon& poly : read_vege_polygons(dir / "vegetation.gpkg")) {
      polygons_by_layer[poly.layer].push_back(std::move(poly));
    }
  }

  if (polygons_by_layer.empty()) return;

  GPKGWriter writer((combined_dir / "vegetation.gpkg").string(), projection, "vegetation");
  for (const auto& [layer_name, polys] : polygons_by_layer) {
    for (const VegePolygon& poly : polys) {
      writer.write_polygon(poly.layer, poly.name, poly.exterior_ring, poly.holes);
    }
  }
}
