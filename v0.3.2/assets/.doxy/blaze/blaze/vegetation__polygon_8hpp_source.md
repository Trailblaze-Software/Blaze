

# File vegetation\_polygon.hpp

[**File List**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**vegetation**](dir_b743e47c5a2b15e05ebb68ed1bfc6ebf.md) **>** [**vegetation\_polygon.hpp**](vegetation__polygon_8hpp.md)

[Go to the documentation of this file](vegetation__polygon_8hpp.md)


```C++
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
#include "utilities/progress_tracker.hpp"
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

inline std::string default_isom_layer_name(const VegeHeightConfig& config, size_t threshold_rank) {
  if (config.name == "green") {
    static constexpr const char* kGreenLayers[] = {"406_Slow_Running", "408_Walk", "410_Fight"};
    if (threshold_rank < std::size(kGreenLayers)) {
      return kGreenLayers[threshold_rank];
    }
  }
  if (config.name == "canopy" || config.name == "forest") {
    return "405_Forest";
  }
  return {};
}

inline std::string threshold_layer_name(
    const VegeHeightConfig& config, const BlockingThresholdColorPair& btc,
    size_t threshold_rank = std::numeric_limits<size_t>::max()) {
  if (!btc.layer.empty()) {
    return btc.layer;
  }
  if (threshold_rank != std::numeric_limits<size_t>::max()) {
    if (const std::string isom_layer = default_isom_layer_name(config, threshold_rank);
        !isom_layer.empty()) {
      return isom_layer;
    }
  }
  const std::string& prefix = config.name.empty() ? "Vegetation" : config.name;
  return prefix + "_" + double_to_string(btc.blocking_threshold);
}

inline std::map<double, std::string> extract_threshold_layers(const VegeHeightConfig& config) {
  std::vector<const BlockingThresholdColorPair*> sorted;
  sorted.reserve(config.colors.size());
  for (const BlockingThresholdColorPair& btc : config.colors) {
    sorted.push_back(&btc);
  }
  std::sort(sorted.begin(), sorted.end(),
            [](const BlockingThresholdColorPair* a, const BlockingThresholdColorPair* b) {
              return a->blocking_threshold < b->blocking_threshold;
            });

  std::map<double, std::string> layers;
  for (size_t i = 0; i < sorted.size(); ++i) {
    layers[sorted[i]->blocking_threshold] = threshold_layer_name(config, *sorted[i], i);
  }
  return layers;
}

// Map CRT layer names (e.g. "405_Forest") to render colors from the vegetation config.
inline std::map<std::string, ColorVariant> vege_layer_colors(const VegeConfig& vege_config) {
  std::map<std::string, ColorVariant> colors;
  for (const VegeHeightConfig& vc : vege_config.height_configs) {
    std::vector<const BlockingThresholdColorPair*> sorted;
    sorted.reserve(vc.colors.size());
    for (const BlockingThresholdColorPair& btc : vc.colors) {
      sorted.push_back(&btc);
    }
    std::sort(sorted.begin(), sorted.end(),
              [](const BlockingThresholdColorPair* a, const BlockingThresholdColorPair* b) {
                return a->blocking_threshold < b->blocking_threshold;
              });
    for (size_t i = 0; i < sorted.size(); ++i) {
      colors.emplace(threshold_layer_name(vc, *sorted[i], i), sorted[i]->color);
    }
  }
  colors.emplace("403_Rough_Open_Land", vege_config.background_color);
  return colors;
}

// Bottom-to-top draw order for vector vegetation rendering.
inline int vege_layer_draw_priority(const std::string& layer) {
  if (layer == "401_Open_Land" || layer == "403_Rough_Open_Land") {
    return 10;
  }
  if (layer == "405_Forest") {
    return 20;
  }
  if (layer == "406_Slow_Running") {
    return 30;
  }
  if (layer == "408_Walk") {
    return 40;
  }
  if (layer == "410_Fight") {
    return 50;
  }
  return 100;
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

inline std::vector<VegePolygon> subtract_from_polygon(const VegePolygon& host,
                                                      const OGRGeometry* cut_union) {
  std::vector<VegePolygon> result;
  for (const PolygonWithHoles& piece :
       subtract_polygon_with_union({host.exterior_ring, host.holes}, cut_union)) {
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
// When `snap_extents` is non-empty, vertices near those edges are snapped and each
// polygon is repaired before output (stabilizes cross-tile union at seams).
inline void trim_vege_polygons_to_extent(std::vector<VegePolygon>& polygons, const Extent2D& bounds,
                                         ProgressTracker&& progress_tracker,
                                         const std::vector<Extent2D>& snap_extents = {},
                                         double snap_tolerance = 0.01) {
  if (polygons.empty()) {
    return;
  }

  START_TRACKER("trimming vegetation polygons");

  std::vector<Extent2D> snap_targets =
      snap_extents.empty() ? std::vector<Extent2D>{bounds} : snap_extents;

  std::vector<std::vector<VegePolygon>> trimmed_batches(polygons.size());

#pragma omp parallel for schedule(dynamic)
  for (size_t i = 0; i < polygons.size(); i++) {
    const VegePolygon& poly = polygons[i];
    if (poly.exterior_ring.size() < 3) {
      continue;
    }
    const Extent2D poly_ext = ring_extent(poly.exterior_ring);
    if (!poly_ext.overlaps(bounds)) {
      continue;
    }

    std::vector<PolygonWithHoles> pieces;
    if (extent_contains(bounds, poly_ext)) {
      pieces.push_back({poly.exterior_ring, poly.holes});
    } else {
      pieces = clip_polygon_to_extent({poly.exterior_ring, poly.holes}, bounds);
    }

    for (const PolygonWithHoles& clipped : pieces) {
      for (PolygonWithHoles& finalized :
           finalize_polygon_with_holes(clipped, snap_targets, snap_tolerance)) {
        if (finalized.exterior.size() < 3) {
          continue;
        }
        VegePolygon out;
        out.layer = poly.layer;
        out.name = poly.name;
        out.exterior_ring = std::move(finalized.exterior);
        out.holes = std::move(finalized.holes);
        trimmed_batches[i].push_back(std::move(out));
      }
    }
  }

  std::vector<VegePolygon> trimmed;
  size_t total = 0;
  for (const std::vector<VegePolygon>& batch : trimmed_batches) {
    total += batch.size();
  }
  trimmed.reserve(total);
  for (std::vector<VegePolygon>& batch : trimmed_batches) {
    for (VegePolygon& poly : batch) {
      trimmed.push_back(std::move(poly));
    }
  }
  polygons = std::move(trimmed);
  progress_tracker.set_proportion(1.0);
}

// Write vegetation polygons to a GeoPackage.
inline void write_vege_polygons_gpkg(const std::vector<VegePolygon>& polygons,
                                     const fs::path& gpkg_path, const std::string& projection,
                                     ProgressTracker&& progress_tracker) {
  if (polygons.empty()) {
    return;
  }

  START_TRACKER("writing vegetation GPKG " + gpkg_path.filename().string());

  GPKGWriter writer(gpkg_path.string(), projection, "vegetation");
  const size_t report_interval = std::max<size_t>(1, polygons.size() / 20);
  for (size_t i = 0; i < polygons.size(); i++) {
    const VegePolygon& poly = polygons[i];
    writer.write_polygon(poly.layer, poly.name, poly.exterior_ring, poly.holes);
    if (i % report_interval == 0 || i + 1 == polygons.size()) {
      progress_tracker.set_proportion(static_cast<double>(i + 1) / polygons.size());
    }
  }
}

// Remove holes that are smaller than the minimum hole area for their layer.
// This should be called before min-area polygon filtering and before cutting
// understory out of forest.
inline void filter_small_holes(std::vector<VegePolygon>& polygons,
                               const std::map<std::string, double>& min_hole_areas,
                               ProgressTracker&& progress_tracker) {
  START_TRACKER("filtering small holes");
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
                               const std::map<std::string, double>& min_areas,
                               ProgressTracker&& progress_tracker) {
  START_TRACKER("filtering by minimum area");
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
      if (!c.is_loop()) {
        continue;
      }
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
    std::vector<size_t> hole_candidates;
    hole_candidates.reserve(all_rings.size() - i);
    for (size_t j = i + 1; j < all_rings.size(); j++) {
      if (all_rings[j].consumed) continue;
      if (all_rings[j].threshold != all_rings[i].threshold) continue;
      if (signed_area(all_rings[j].points) >= 0.0) continue;
      if (!point_in_ring(all_rings[j].points[0], poly.exterior_ring)) continue;
      hole_candidates.push_back(j);
    }

    for (size_t j : hole_candidates) {
      bool nested_in_other_hole = false;
      for (size_t k : hole_candidates) {
        if (k == j) continue;
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

inline void cut_understory_from_forest(std::vector<VegePolygon>& polygons,
                                       ProgressTracker&& progress_tracker) {
  START_TRACKER("cutting understory from forest");

  struct UnderstoryCutout {
    PolygonWithHoles poly;
    Extent2D extent;
  };
  std::vector<UnderstoryCutout> cutouts;
  cutouts.reserve(polygons.size());
  Extent2D cutout_bounds;
  for (const VegePolygon& polygon : polygons) {
    if (polygon.layer != "406_Slow_Running" && polygon.layer != "408_Walk" &&
        polygon.layer != "410_Fight") {
      continue;
    }
    if (polygon.exterior_ring.size() < 3) {
      continue;
    }
    const Extent2D ext = ring_extent(polygon.exterior_ring);
    cutout_bounds.grow(ext);
    cutouts.push_back({{polygon.exterior_ring, polygon.holes}, ext});
  }

  if (cutouts.empty()) {
    return;
  }

  const double cutout_width = cutout_bounds.maxx - cutout_bounds.minx;
  const double cutout_height = cutout_bounds.maxy - cutout_bounds.miny;
  const double cell_size =
      std::max(50.0, std::sqrt(cutout_width * cutout_height / std::max(cutouts.size(), size_t(1))));
  detail::ExtentSpatialIndex cutout_index(cell_size);
  for (size_t ci = 0; ci < cutouts.size(); ++ci) {
    cutout_index.insert(ci, cutouts[ci].extent);
  }

  std::vector<size_t> forest_indices;
  forest_indices.reserve(polygons.size());
  for (size_t i = 0; i < polygons.size(); i++) {
    if (polygons[i].layer == "405_Forest") {
      forest_indices.push_back(i);
    }
  }

  std::vector<std::vector<VegePolygon>> forest_pieces(forest_indices.size());
#pragma omp parallel for schedule(dynamic)
  for (size_t fi = 0; fi < forest_indices.size(); fi++) {
    const VegePolygon& forest = polygons[forest_indices[fi]];
    const Extent2D forest_ext = ring_extent(forest.exterior_ring);
    std::vector<size_t> candidate_idxs;
    cutout_index.query(forest_ext, candidate_idxs);

    std::vector<PolygonWithHoles> active_cutouts;
    active_cutouts.reserve(candidate_idxs.size());
    for (size_t ci : candidate_idxs) {
      if (cutouts[ci].extent.overlaps(forest_ext)) {
        active_cutouts.push_back(cutouts[ci].poly);
      }
    }

    if (active_cutouts.empty()) {
      forest_pieces[fi].push_back(forest);
      continue;
    }

    for (const PolygonWithHoles& piece :
         subtract_polygon({forest.exterior_ring, forest.holes}, active_cutouts)) {
      VegePolygon poly;
      poly.layer = forest.layer;
      poly.name = forest.name;
      poly.exterior_ring = piece.exterior;
      poly.holes = piece.holes;
      forest_pieces[fi].push_back(std::move(poly));
    }
  }

  std::vector<VegePolygon> updated;
  updated.reserve(polygons.size());
  size_t next_forest = 0;
  for (size_t i = 0; i < polygons.size(); i++) {
    if (polygons[i].layer == "405_Forest") {
      for (VegePolygon& piece : forest_pieces[next_forest]) {
        updated.push_back(std::move(piece));
      }
      ++next_forest;
    } else {
      updated.push_back(std::move(polygons[i]));
    }
  }
  polygons = std::move(updated);
}

// =============================================================================
// generate_vege_polygons — full pipeline: grids → contours → polygons → filter → cut
// =============================================================================

inline std::vector<VegePolygon> generate_vege_polygons(
    const VegeConfig& vege_config, const std::map<std::string, GeoGrid<float>>& vege_maps,
    ProgressTracker&& progress_tracker) {
  START_TRACKER("generating vegetation polygons");

  constexpr double CONTOUR_PROGRESS_END = 0.40;
  constexpr double OPEN_LAND_PROGRESS_END = 0.55;
  constexpr double FILTER_PROGRESS_END = 0.70;
  constexpr double CUT_PROGRESS_END = 0.90;

  struct VegeContourJob {
    const GeoGrid<float>& grid;
    std::map<double, std::string> threshold_layers;
    std::vector<double> thresholds;
    std::string config_name;
    bool needs_open_land = false;
  };

  std::vector<VegeContourJob> jobs;
  jobs.reserve(vege_config.height_configs.size());
  for (const VegeHeightConfig& vc : vege_config.height_configs) {
    std::map<double, std::string> threshold_layers = extract_threshold_layers(vc);
    if (threshold_layers.empty()) {
      continue;
    }
    auto it = vege_maps.find(vc.name);
    if (it == vege_maps.end()) {
      continue;
    }
    std::vector<double> thresholds;
    for (const auto& [threshold, _] : threshold_layers) {
      thresholds.push_back(threshold);
    }
    if (thresholds.empty()) {
      continue;
    }
    const std::string& lowest_layer = threshold_layers.at(thresholds.front());
    jobs.push_back({it->second, std::move(threshold_layers), std::move(thresholds), vc.name,
                    lowest_layer.rfind("405_", 0) == 0});
  }

  std::vector<VegePolygon> all_polygons;
  const size_t job_count = jobs.size();
  for (size_t job_idx = 0; job_idx < job_count; ++job_idx) {
    const VegeContourJob& job = jobs[job_idx];
    progress_tracker.text_update("Contouring " + job.config_name);
    auto contours = generate_contours_at_heights(
        job.grid, job.thresholds,
        SUBTRACKER(CONTOUR_PROGRESS_END * static_cast<double>(job_idx) / job_count,
                   CONTOUR_PROGRESS_END * static_cast<double>(job_idx + 1) / job_count,
                   progress_tracker),
        /*min_points=*/5, 0.0f, vege_config.saddle_policy);
    for (VegePolygon& poly : contours_to_polygons(contours, job.threshold_layers)) {
      all_polygons.push_back(std::move(poly));
    }
  }

  const size_t open_land_count = std::count_if(
      jobs.begin(), jobs.end(), [](const VegeContourJob& job) { return job.needs_open_land; });
  if (open_land_count > 0) {
    const double open_land_span = OPEN_LAND_PROGRESS_END - CONTOUR_PROGRESS_END;
    size_t open_land_idx = 0;
    for (const VegeContourJob& job : jobs) {
      if (!job.needs_open_land) {
        continue;
      }
      const double lowest = job.thresholds.front();
      auto open_contours = generate_contours_at_heights(
          job.grid, {lowest},
          SUBTRACKER(CONTOUR_PROGRESS_END +
                         open_land_span * static_cast<double>(open_land_idx) / open_land_count,
                     CONTOUR_PROGRESS_END +
                         open_land_span * static_cast<double>(open_land_idx + 1) / open_land_count,
                     progress_tracker),
          /*min_points=*/5, 1.0f, opposite_saddle_policy(vege_config.saddle_policy));
      for (auto& [height, open_height_contours] : open_contours) {
        for (Contour& contour : open_height_contours) {
          std::reverse(contour.points().begin(), contour.points().end());
        }
        (void)height;
      }
      std::map<double, std::string> open_layer = {{lowest, "403_Rough_Open_Land"}};
      for (VegePolygon& poly : contours_to_polygons(open_contours, open_layer)) {
        poly.name = "403";
        all_polygons.push_back(std::move(poly));
      }
      ++open_land_idx;
    }
  }

  std::map<std::string, double> min_areas, min_hole_areas;
  for (const VegeHeightConfig& vc : vege_config.height_configs) {
    std::vector<const BlockingThresholdColorPair*> sorted;
    sorted.reserve(vc.colors.size());
    for (const BlockingThresholdColorPair& btc : vc.colors) {
      sorted.push_back(&btc);
    }
    std::sort(sorted.begin(), sorted.end(),
              [](const BlockingThresholdColorPair* a, const BlockingThresholdColorPair* b) {
                return a->blocking_threshold < b->blocking_threshold;
              });
    for (size_t i = 0; i < sorted.size(); ++i) {
      const std::string layer = threshold_layer_name(vc, *sorted[i], i);
      if (sorted[i]->min_area_m2 > 0) min_areas[layer] = sorted[i]->min_area_m2;
      if (sorted[i]->min_hole_area_m2 > 0) min_hole_areas[layer] = sorted[i]->min_hole_area_m2;
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

  const double filter_mid = (OPEN_LAND_PROGRESS_END + FILTER_PROGRESS_END) * 0.5;
  const double final_filter_mid = (CUT_PROGRESS_END + 1.0) * 0.5;

  filter_small_holes(all_polygons, min_hole_areas,
                     SUBTRACKER_HIDDEN(OPEN_LAND_PROGRESS_END, filter_mid, progress_tracker));
  filter_by_min_area(all_polygons, min_areas,
                     SUBTRACKER_HIDDEN(filter_mid, FILTER_PROGRESS_END, progress_tracker));

  cut_understory_from_forest(
      all_polygons, SUBTRACKER_HIDDEN(FILTER_PROGRESS_END, CUT_PROGRESS_END, progress_tracker));

  // After cutting understory from forest, only drop tiny GEOS sliver holes in 405_Forest.
  // Using the normal forest min_hole_area_m2 here would remove legitimate understory cutouts
  // whenever the green patch is smaller than that threshold (e.g. 50–100 m² walk patches).
  std::map<std::string, double> post_cut_hole_areas = min_hole_areas;
  post_cut_hole_areas["405_Forest"] = 1.0;
  filter_small_holes(all_polygons, post_cut_hole_areas,
                     SUBTRACKER_HIDDEN(CUT_PROGRESS_END, final_filter_mid, progress_tracker));
  filter_by_min_area(all_polygons, min_areas,
                     SUBTRACKER_HIDDEN(final_filter_mid, 1.0, progress_tracker));

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
                               const std::string& projection, ProgressTracker&& progress_tracker) {
  START_TRACKER("combining vegetation GPKGs");

  std::vector<VegePolygon> all_polygons;
  const size_t dir_count = tile_dirs.size();
  size_t dir_index = 0;
  for (const fs::path& dir : tile_dirs) {
    progress_tracker.text_update("Reading " + (dir / "vegetation.gpkg").filename().string());
    for (VegePolygon& poly : read_vege_polygons(dir / "vegetation.gpkg")) {
      all_polygons.push_back(std::move(poly));
    }
    ++dir_index;
    if (dir_count > 0) {
      progress_tracker.set_proportion(0.25 * static_cast<double>(dir_index) / dir_count);
    }
  }

  if (all_polygons.empty()) {
    return;
  }

  std::map<std::string, std::vector<VegePolygon>> by_layer;
  for (VegePolygon& poly : all_polygons) {
    by_layer[poly.layer].push_back(std::move(poly));
  }
  all_polygons.clear();

  std::vector<VegePolygon> merged;
  const size_t layer_count = by_layer.size();
  size_t layer_index = 0;
  for (auto& [layer, layer_polygons] : by_layer) {
    progress_tracker.text_update("Unioning " + layer);
    std::vector<PolygonWithHoles> pieces;
    pieces.reserve(layer_polygons.size());
    for (const VegePolygon& poly : layer_polygons) {
      pieces.push_back({poly.exterior_ring, poly.holes});
    }
    for (const PolygonWithHoles& united : union_overlapping_polygons(pieces)) {
      if (united.exterior.size() < 3) {
        continue;
      }
      VegePolygon out;
      out.layer = layer;
      out.name = layer_number(layer);
      out.exterior_ring = united.exterior;
      out.holes = united.holes;
      merged.push_back(std::move(out));
    }
    ++layer_index;
    if (layer_count > 0) {
      progress_tracker.set_proportion(0.25 + 0.45 * static_cast<double>(layer_index) / layer_count);
    }
  }

  cut_understory_from_forest(merged, SUBTRACKER(0.70, 0.85, progress_tracker));

  write_vege_polygons_gpkg(merged, combined_dir / "vegetation.gpkg", projection,
                           SUBTRACKER(0.85, 1.0));
}
```


