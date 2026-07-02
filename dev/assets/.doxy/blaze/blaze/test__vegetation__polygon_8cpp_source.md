

# File test\_vegetation\_polygon.cpp

[**File List**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**vegetation**](dir_b743e47c5a2b15e05ebb68ed1bfc6ebf.md) **>** [**tests**](dir_f363110a8f8d8c62b28512efb8187aa9.md) **>** [**test\_vegetation\_polygon.cpp**](test__vegetation__polygon_8cpp.md)

[Go to the documentation of this file](test__vegetation__polygon_8cpp.md)


```C++
#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <vector>

#include "config_input/config_input.hpp"
#include "contour/contour.hpp"
#include "contour/contour_gen.hpp"
#include "geometry/polygon.hpp"
#include "grid/grid.hpp"
#include "utilities/progress_tracker.hpp"
#include "vegetation/vegetation_polygon.hpp"

namespace {

VegeConfig canopy_config(double forest_min_area_m2, double forest_min_hole_area_m2) {
  VegeConfig config;
  config.background_color = ColorVariant(RGBColor(255, 255, 255, 255));
  VegeHeightConfig canopy;
  canopy.name = "canopy";
  canopy.min_height = 2.5;
  canopy.max_height = 100.0;
  canopy.colors.push_back({0.1, ColorVariant(RGBColor(0, 0, 0, 0)), "405_Forest",
                           forest_min_area_m2, forest_min_hole_area_m2});
  config.height_configs.push_back(std::move(canopy));
  return config;
}

VegeConfig forest_and_green_config() {
  VegeConfig config;
  config.background_color = ColorVariant(RGBColor(255, 255, 255, 255));

  VegeHeightConfig canopy;
  canopy.name = "canopy";
  canopy.min_height = 2.5;
  canopy.max_height = 100.0;
  canopy.colors.push_back({0.1, ColorVariant(RGBColor(0, 0, 0, 0)), "405_Forest", 0, 0});

  VegeHeightConfig green;
  green.name = "green";
  green.min_height = 0.5;
  green.max_height = 2.5;
  green.colors.push_back({0.1, ColorVariant(RGBColor(0, 0, 0, 0)), "408_Walk", 0, 0});

  config.height_configs.push_back(std::move(canopy));
  config.height_configs.push_back(std::move(green));
  return config;
}

bool point_in_polygon(const Coordinate2D<double>& pt, const VegePolygon& poly) {
  if (!point_in_ring(pt, poly.exterior_ring)) return false;
  for (const auto& hole : poly.holes) {
    if (point_in_ring(pt, hole)) return false;
  }
  return true;
}

const VegePolygon* largest_forest_with_hole(const std::vector<VegePolygon>& polygons) {
  const VegePolygon* best = nullptr;
  double best_area = 0.0;
  for (const VegePolygon& poly : polygons) {
    if (poly.layer != "405_Forest" || poly.holes.empty()) continue;
    double area = signed_area(poly.exterior_ring);
    if (area > best_area) {
      best_area = area;
      best = &poly;
    }
  }
  return best;
}

GeoGrid<float> grid_at_3m(const std::vector<std::vector<float>>& data) {
  const double height_m = static_cast<double>(data.size()) * 3.0;
  return GeoGrid<float>(data, GeoTransform(0.0, height_m, 3.0, -3.0));
}

const VegePolygon* find_polygon(const std::vector<VegePolygon>& polygons,
                                const std::string& layer) {
  for (const VegePolygon& poly : polygons) {
    if (poly.layer == layer) return &poly;
  }
  return nullptr;
}

size_t count_layer(const std::vector<VegePolygon>& polygons, const std::string& layer) {
  size_t count = 0;
  for (const VegePolygon& poly : polygons) {
    if (poly.layer == layer) ++count;
  }
  return count;
}

std::vector<Coordinate2D<double>> square_ccw(double x0, double y0, double x1, double y1) {
  return {{x0, y0}, {x1, y0}, {x1, y1}, {x0, y1}, {x0, y0}};
}

std::vector<Coordinate2D<double>> square_cw(double x0, double y0, double x1, double y1) {
  return reverse_ring(square_ccw(x0, y0, x1, y1));
}

Contour loop_contour(double threshold, std::vector<Coordinate2D<double>> ring) {
  return Contour(threshold, std::move(ring));
}

}  // namespace

TEST(ExtractThresholdLayers, UsesDefaultLayerName) {
  VegeHeightConfig config;
  config.name = "green";
  config.colors = {
      {0.3, ColorVariant(RGBColor(0, 0, 0, 0)), "406_Slow_Running"},
      {0.6, ColorVariant(RGBColor(0, 0, 0, 0)), ""},
      {0.85, ColorVariant(RGBColor(0, 0, 0, 0)), "410_Fight"},
  };

  std::map<double, std::string> layers = extract_threshold_layers(config);

  EXPECT_EQ(layers.size(), 3u);
  EXPECT_EQ(layers.at(0.3), "406_Slow_Running");
  EXPECT_EQ(layers.at(0.6), "408_Walk");
  EXPECT_EQ(layers.at(0.85), "410_Fight");
}

TEST(ExtractThresholdLayers, SortedByThreshold) {
  VegeHeightConfig config;
  config.colors = {
      {0.85, ColorVariant(RGBColor(0, 0, 0, 0)), "410_Fight"},
      {0.3, ColorVariant(RGBColor(0, 0, 0, 0)), "406_Slow_Running"},
      {0.6, ColorVariant(RGBColor(0, 0, 0, 0)), "408_Walk"},
  };

  std::map<double, std::string> layers = extract_threshold_layers(config);

  EXPECT_EQ(layers.size(), 3u);

  // Verify sorted order (map is ordered by key)
  auto it = layers.begin();
  EXPECT_DOUBLE_EQ(it->first, 0.3);
  EXPECT_EQ(it->second, "406_Slow_Running");
  ++it;
  EXPECT_DOUBLE_EQ(it->first, 0.6);
  EXPECT_EQ(it->second, "408_Walk");
  ++it;
  EXPECT_DOUBLE_EQ(it->first, 0.85);
  EXPECT_EQ(it->second, "410_Fight");
}

TEST(ExtractThresholdLayers, EmptyConfig) {
  VegeHeightConfig config;
  config.colors = {};

  std::map<double, std::string> layers = extract_threshold_layers(config);
  EXPECT_TRUE(layers.empty());
}

// =============================================================================
// ContoursToPolygons tests
// =============================================================================

TEST(ContoursToPolygons, SingleThresholdNoHoles) {
  // Create a simple closed contour at threshold 0.5
  const std::vector<Coordinate2D<double>> expected_ring = {
      {0.0, 0.0}, {10.0, 0.0}, {10.0, 10.0}, {0.0, 10.0}, {0.0, 0.0},
  };
  Contour c(0.5, std::vector<Coordinate2D<double>>(expected_ring));
  EXPECT_TRUE(c.is_loop());

  std::map<double, std::vector<Contour>> contours_by_height;
  contours_by_height[0.5].push_back(std::move(c));

  std::map<double, std::string> height_to_layer = {{0.5, "405_Forest"}};

  std::vector<VegePolygon> polygons = contours_to_polygons(contours_by_height, height_to_layer);

  ASSERT_EQ(polygons.size(), 1u);
  EXPECT_EQ(polygons[0].layer, "405_Forest");
  EXPECT_EQ(polygons[0].name, "405");
  EXPECT_EQ(polygons[0].exterior_ring.size(), 5u);
  EXPECT_EQ(polygons[0].exterior_ring, expected_ring);
  EXPECT_TRUE(polygons[0].holes.empty());
}

TEST(ContoursToPolygons, NestedContoursAreIndependent) {
  // Outer contour (0.25 threshold) containing an inner contour (0.5 threshold).
  // Higher thresholds should be independent, overlapping polygons — NOT holes.
  // OCAD/OOM renders higher-density symbols on top of lower ones.
  std::vector<Coordinate2D<double>> outer_ring = {
      {0.0, 0.0}, {20.0, 0.0}, {20.0, 20.0}, {0.0, 20.0}, {0.0, 0.0},
  };
  std::vector<Coordinate2D<double>> inner_ring = {
      {5.0, 5.0}, {15.0, 5.0}, {15.0, 15.0}, {5.0, 15.0}, {5.0, 5.0},
  };

  Contour outer(0.25, std::move(outer_ring));
  Contour inner(0.5, std::move(inner_ring));

  std::map<double, std::vector<Contour>> contours_by_height;
  contours_by_height[0.25].push_back(std::move(outer));
  contours_by_height[0.5].push_back(std::move(inner));

  std::map<double, std::string> height_to_layer = {
      {0.25, "405_Forest"},
      {0.5, "408_Walk"},
  };

  std::vector<VegePolygon> polygons = contours_to_polygons(contours_by_height, height_to_layer);

  // Both should be independent polygons, no cross-threshold holes
  ASSERT_EQ(polygons.size(), 2u);

  bool has_forest = false, has_walk = false;
  for (const auto& p : polygons) {
    if (p.layer == "405_Forest") {
      has_forest = true;
      EXPECT_EQ(p.exterior_ring.size(), 5u);
    }
    if (p.layer == "408_Walk") {
      has_walk = true;
      EXPECT_EQ(p.exterior_ring.size(), 5u);
    }
    EXPECT_TRUE(p.holes.empty());
  }
  EXPECT_TRUE(has_forest);
  EXPECT_TRUE(has_walk);
}

TEST(ContoursToPolygons, DetectsOuterRingVsHole) {
  // Donut-shaped density patch: high ring around a low interior. At one threshold
  // this yields two closed contours; the inner one is classified as a hole.
  std::vector<std::vector<float>> data = {
      {0.8f, 0.8f, 0.8f, 0.8f, 0.8f},
      {0.8f, 0.0f, 0.0f, 0.0f, 0.8f},
      {0.8f, 0.0f, 0.0f, 0.0f, 0.8f},
      {0.8f, 0.8f, 0.8f, 0.8f, 0.8f},
  };
  GeoGrid<float> grid(data);
  std::vector<double> heights = {0.5};
  auto contours_by_height = generate_contours_at_heights(grid, heights, ProgressTracker(), 3, 0.0f);

  ASSERT_EQ(contours_by_height[0.5].size(), 2u);
  for (const auto& c : contours_by_height[0.5]) {
    EXPECT_TRUE(c.is_loop());
  }

  std::map<double, std::string> height_to_layer = {{0.5, "405_Forest"}};
  std::vector<VegePolygon> polygons = contours_to_polygons(contours_by_height, height_to_layer);

  ASSERT_EQ(polygons.size(), 1u);
  EXPECT_EQ(polygons[0].layer, "405_Forest");
  EXPECT_EQ(polygons[0].exterior_ring.size(), 19u);
  ASSERT_EQ(polygons[0].holes.size(), 1u);
  EXPECT_EQ(polygons[0].holes[0].size(), 11u);
  EXPECT_GT(signed_area(polygons[0].exterior_ring), 0.0);
  EXPECT_LT(signed_area(polygons[0].holes[0]), 0.0);
  EXPECT_TRUE(point_in_ring(polygons[0].holes[0][0], polygons[0].exterior_ring));
}

TEST(ContoursToPolygons, CwOnlyRingProducesNoPolygon) {
  // CW rings are holes only; a mis-oriented outer loop is not promoted to an exterior.
  std::vector<Coordinate2D<double>> cw_outer = {
      {0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}, {1.0, 0.0}, {0.0, 0.0},
  };
  Contour outer(0.1, std::move(cw_outer));
  ASSERT_LT(signed_area(outer.points()), 0.0);

  std::map<double, std::vector<Contour>> contours_by_height;
  contours_by_height[0.1].push_back(std::move(outer));
  std::map<double, std::string> height_to_layer = {{0.1, "405_Forest"}};

  std::vector<VegePolygon> polygons = contours_to_polygons(contours_by_height, height_to_layer);
  EXPECT_TRUE(polygons.empty());
}

TEST(TrimVegePolygons, ClipsToExportExtent) {
  VegePolygon poly;
  poly.layer = "405_Forest";
  poly.name = "405";
  poly.exterior_ring = square_ccw(0, 0, 100, 100);
  poly.holes.push_back(square_cw(10, 10, 90, 90));

  std::vector<VegePolygon> polygons = {poly};
  trim_vege_polygons_to_extent(polygons, {50.0, 100.0, 0.0, 100.0}, ProgressTracker());

  ASSERT_EQ(polygons.size(), 1u);
  for (const Coordinate2D<double>& p : polygons[0].exterior_ring) {
    EXPECT_GE(p.x(), 50.0 - 1e-9);
    EXPECT_LE(p.x(), 100.0 + 1e-9);
  }
  EXPECT_EQ(polygons[0].layer, "405_Forest");
}

TEST(TrimVegePolygons, RemovesPolygonOutsideExtent) {
  VegePolygon poly;
  poly.layer = "405_Forest";
  poly.name = "405";
  poly.exterior_ring = square_ccw(0, 0, 10, 10);

  std::vector<VegePolygon> polygons = {poly};
  trim_vege_polygons_to_extent(polygons, {20.0, 30.0, 0.0, 10.0}, ProgressTracker());
  EXPECT_TRUE(polygons.empty());
}

TEST(ContoursToPolygons, DeepNestedPolygonInHoleInPolygon) {
  // Four nesting levels: outer → hole → island → hole → island → hole → island.
  // Expect four polygons; the three outermost each have one direct hole; the innermost has none.
  constexpr double THRESHOLD = 0.1;
  std::map<double, std::vector<Contour>> contours_by_height;
  contours_by_height[THRESHOLD] = {
      loop_contour(THRESHOLD, square_ccw(0, 0, 100, 100)),  // E0
      loop_contour(THRESHOLD, square_cw(10, 10, 90, 90)),   // H1
      loop_contour(THRESHOLD, square_ccw(20, 20, 80, 80)),  // E1
      loop_contour(THRESHOLD, square_cw(30, 30, 70, 70)),   // H2
      loop_contour(THRESHOLD, square_ccw(40, 40, 60, 60)),  // E2
      loop_contour(THRESHOLD, square_cw(45, 45, 55, 55)),   // H3
      loop_contour(THRESHOLD, square_ccw(47, 47, 53, 53)),  // E3
  };
  std::map<double, std::string> height_to_layer = {{THRESHOLD, "405_Forest"}};

  std::vector<VegePolygon> polygons = contours_to_polygons(contours_by_height, height_to_layer);
  ASSERT_EQ(polygons.size(), 4u);

  auto by_exterior_area = polygons;
  std::sort(by_exterior_area.begin(), by_exterior_area.end(),
            [](const VegePolygon& a, const VegePolygon& b) {
              return signed_area(a.exterior_ring) > signed_area(b.exterior_ring);
            });

  EXPECT_EQ(by_exterior_area[0].holes.size(), 1u);
  EXPECT_EQ(by_exterior_area[1].holes.size(), 1u);
  EXPECT_EQ(by_exterior_area[2].holes.size(), 1u);
  EXPECT_TRUE(by_exterior_area[3].holes.empty());

  for (const VegePolygon& poly : by_exterior_area) {
    EXPECT_GT(signed_area(poly.exterior_ring), 0.0);
    for (const auto& hole : poly.holes) {
      EXPECT_LT(signed_area(hole), 0.0);
    }
  }

  const Coordinate2D<double> e1_pt{25.0, 50.0};  // E1 solid (outside H2)
  const Coordinate2D<double> e2_pt{42.0, 50.0};  // E2 solid (outside H3)
  const Coordinate2D<double> e3_pt{50.0, 50.0};  // innermost island
  EXPECT_TRUE(point_in_polygon(e1_pt, by_exterior_area[1]));
  EXPECT_TRUE(point_in_polygon(e2_pt, by_exterior_area[2]));
  EXPECT_TRUE(point_in_polygon(e3_pt, by_exterior_area[3]));
  EXPECT_TRUE(point_in_ring(e1_pt, by_exterior_area[0].holes[0]));
  EXPECT_TRUE(point_in_ring(e2_pt, by_exterior_area[1].holes[0]));
  EXPECT_TRUE(point_in_ring(e3_pt, by_exterior_area[2].holes[0]));
}

TEST(ContoursToPolygons, TwoSeparatePeaks) {
  // Two separate dense patches at the same threshold → two polygons
  std::vector<std::vector<float>> data = {
      {0.8f, 0.8f, 0.0f, 0.8f, 0.0f},
      {0.8f, 0.8f, 0.0f, 0.0f, 0.0f},
  };
  GeoGrid<float> grid(data);
  std::vector<double> heights = {0.5};
  auto contours_by_height = generate_contours_at_heights(grid, heights, ProgressTracker(), 3, 0.0f);

  std::map<double, std::string> height_to_layer = {{0.5, "405_Forest"}};
  std::vector<VegePolygon> polygons = contours_to_polygons(contours_by_height, height_to_layer);

  ASSERT_EQ(polygons.size(), 2u);
  std::vector<size_t> ring_sizes;
  for (const auto& p : polygons) {
    EXPECT_EQ(p.layer, "405_Forest");
    ring_sizes.push_back(p.exterior_ring.size());
  }
  std::sort(ring_sizes.begin(), ring_sizes.end());
  EXPECT_EQ(ring_sizes, (std::vector<size_t>{5, 9}));
}

TEST(ContoursToPolygons, LayerAssignmentFromThreshold) {
  // Verify that different thresholds get assigned the correct layer names
  std::vector<std::vector<float>> data = {
      {0.4f, 0.4f, 0.4f},
      {0.4f, 0.9f, 0.4f},
      {0.4f, 0.4f, 0.4f},
  };
  GeoGrid<float> grid(data);
  std::vector<double> heights = {0.3, 0.7};
  auto contours_by_height = generate_contours_at_heights(grid, heights, ProgressTracker(), 3, 0.0f);

  std::map<double, std::string> height_to_layer = {
      {0.3, "406_Slow_Running"},
      {0.7, "410_Fight"},
  };

  std::vector<VegePolygon> polygons = contours_to_polygons(contours_by_height, height_to_layer);

  ASSERT_EQ(polygons.size(), 2u);
  bool has_slow_running = false;
  bool has_fight = false;
  for (const auto& p : polygons) {
    if (p.layer == "406_Slow_Running") {
      has_slow_running = true;
      EXPECT_EQ(p.exterior_ring.size(), 13u);
    }
    if (p.layer == "410_Fight") {
      has_fight = true;
      EXPECT_EQ(p.exterior_ring.size(), 5u);
    }
  }
  EXPECT_TRUE(has_slow_running);
  EXPECT_TRUE(has_fight);
}

// =============================================================================
// Minimum area filter tests
// =============================================================================

TEST(FilterByMinArea, RemovesSmallPolygons) {
  std::vector<VegePolygon> polygons;

  VegePolygon large;
  large.layer = "405_Forest";
  large.name = "405";
  large.exterior_ring = {{0, 0}, {100, 0}, {100, 100}, {0, 100}};  // 10000 m²
  polygons.push_back(large);

  VegePolygon small;
  small.layer = "405_Forest";
  small.name = "405";
  small.exterior_ring = {{0, 0}, {5, 0}, {5, 5}, {0, 5}};  // 25 m²
  polygons.push_back(small);

  std::map<std::string, double> min_areas = {{"405_Forest", 30.0}};
  filter_by_min_area(polygons, min_areas, ProgressTracker());

  ASSERT_EQ(polygons.size(), 1u);
  EXPECT_EQ(polygons[0].layer, "405_Forest");
  EXPECT_DOUBLE_EQ(signed_area(polygons[0].exterior_ring), 10000.0);
}

TEST(FilterByMinArea, KeepsAllWhenNoThreshold) {
  std::vector<VegePolygon> polygons;

  VegePolygon p;
  p.layer = "408_Walk";
  p.name = "408";
  p.exterior_ring = {{0, 0}, {3, 0}, {3, 3}, {0, 3}};  // 9 m²
  polygons.push_back(p);

  std::map<std::string, double> min_areas;  // empty → keep all
  filter_by_min_area(polygons, min_areas, ProgressTracker());

  EXPECT_EQ(polygons.size(), 1u);
}

TEST(FilterByMinArea, RespectsDifferentLimits) {
  std::vector<VegePolygon> polygons;

  VegePolygon fight;
  fight.layer = "410_Fight";
  fight.name = "410";
  fight.exterior_ring = {{0, 0}, {5, 0}, {5, 5}, {0, 5}};  // 25 m²
  polygons.push_back(fight);

  VegePolygon walk;
  walk.layer = "408_Walk";
  walk.name = "408";
  walk.exterior_ring = {{0, 0}, {6, 0}, {6, 6}, {0, 6}};  // 36 m²
  polygons.push_back(walk);

  std::map<std::string, double> min_areas = {
      {"410_Fight", 45},   // Fight < 45 → removed
      {"408_Walk", 15.0},  // Walk >= 15 → kept
  };
  filter_by_min_area(polygons, min_areas, ProgressTracker());

  ASSERT_EQ(polygons.size(), 1u);
  EXPECT_EQ(polygons[0].layer, "408_Walk");
}

TEST(FilterByMinArea, UsesNetAreaNotExterior) {
  // Large exterior but thin forest ring: net area below min should be dropped.
  std::vector<VegePolygon> polygons;
  VegePolygon donut;
  donut.layer = "405_Forest";
  donut.name = "405";
  donut.exterior_ring = {{0, 0}, {8, 0}, {8, 8}, {0, 8}};
  donut.holes.push_back({{0.5, 7.5}, {7.5, 7.5}, {7.5, 0.5}, {0.5, 0.5}});
  polygons.push_back(donut);

  EXPECT_GT(std::abs(signed_area(donut.exterior_ring)), 30.0);
  EXPECT_LT(polygon_net_area_m2(donut), 30.0);

  std::map<std::string, double> min_areas = {{"405_Forest", 30.0}};
  filter_by_min_area(polygons, min_areas, ProgressTracker());

  EXPECT_TRUE(polygons.empty());
}

// =============================================================================
// Filter small holes tests
// =============================================================================

TEST(FilterSmallHoles, RemovesTinyHoles) {
  std::vector<VegePolygon> polygons;

  VegePolygon forest;
  forest.layer = "405_Forest";
  forest.exterior_ring = {{0, 0}, {100, 0}, {100, 100}, {0, 100}};
  // Add a tiny 2x2 hole (4 m²) and a bigger 10x10 hole (100 m²), CW for OGR
  forest.holes.push_back({{20, 22}, {20, 20}, {22, 20}, {22, 22}});
  forest.holes.push_back({{50, 60}, {60, 60}, {60, 50}, {50, 50}});
  polygons.push_back(forest);

  std::map<std::string, double> min_hole = {{"405_Forest", 30.0}};
  filter_small_holes(polygons, min_hole, ProgressTracker());

  ASSERT_EQ(polygons.size(), 1u);
  // Only the 100 m² hole should remain
  EXPECT_EQ(polygons[0].holes.size(), 1u);
  EXPECT_DOUBLE_EQ(signed_area(polygons[0].holes[0]), -100.0);
}

TEST(FilterSmallHoles, NoFilterWhenZero) {
  std::vector<VegePolygon> polygons;
  VegePolygon p;
  p.layer = "408_Walk";
  p.exterior_ring = {{0, 0}, {50, 0}, {50, 50}, {0, 50}};
  p.holes.push_back({{5, 5}, {10, 5}, {10, 10}, {5, 10}});  // 25 m²
  polygons.push_back(p);

  std::map<std::string, double> empty;
  filter_small_holes(polygons, empty, ProgressTracker());

  EXPECT_EQ(polygons[0].holes.size(), 1u);  // kept
}

TEST(FilterSmallHoles, DifferentPerLayer) {
  std::vector<VegePolygon> polygons;

  VegePolygon forest;
  forest.layer = "405_Forest";
  forest.exterior_ring = {{0, 0}, {100, 0}, {100, 100}, {0, 100}};
  forest.holes.push_back({{5, 5}, {10, 5}, {10, 10}, {5, 10}});  // 25 m²
  polygons.push_back(forest);

  VegePolygon walk;
  walk.layer = "408_Walk";
  walk.exterior_ring = {{0, 0}, {100, 0}, {100, 100}, {0, 100}};
  walk.holes.push_back({{5, 5}, {10, 5}, {10, 10}, {5, 10}});  // 25 m²
  polygons.push_back(walk);

  // Forest min hole 100 m², Walk min hole 0
  std::map<std::string, double> min_hole = {{"405_Forest", 100.0}};
  filter_small_holes(polygons, min_hole, ProgressTracker());

  // Forest: hole removed (25 < 100), Walk: hole kept (no filter)
  bool found_forest = false, found_walk = false;
  for (const auto& p : polygons) {
    if (p.layer == "405_Forest") {
      EXPECT_EQ(p.holes.size(), 0u);
      found_forest = true;
    }
    if (p.layer == "408_Walk") {
      EXPECT_EQ(p.holes.size(), 1u);
      found_walk = true;
    }
  }
  EXPECT_TRUE(found_forest);
  EXPECT_TRUE(found_walk);
}

// =============================================================================
// Polygon subtraction — vegetation wrapper
// =============================================================================

TEST(SubtractFromPolygon, PreservesLayerMetadata) {
  VegePolygon forest;
  forest.layer = "405_Forest";
  forest.name = "405";
  forest.exterior_ring = {{0, 0}, {100, 0}, {100, 100}, {0, 100}};

  VegePolygon walk;
  walk.layer = "408_Walk";
  walk.exterior_ring = {{40, 0}, {60, 0}, {60, 100}, {40, 100}};

  std::vector<VegePolygon> result = subtract_from_polygon(forest, {walk});

  ASSERT_EQ(result.size(), 2u);
  for (const auto& piece : result) {
    EXPECT_EQ(piece.layer, "405_Forest");
    EXPECT_EQ(piece.name, "405");
  }
}

TEST(SubtractFromPolygon, GreenDonutLeavesForestRing) {
  VegePolygon forest;
  forest.layer = "405_Forest";
  forest.name = "405";
  forest.exterior_ring = {{0, 0}, {100, 0}, {100, 100}, {0, 100}};

  VegePolygon walk;
  walk.layer = "408_Walk";
  walk.exterior_ring = {{20, 20}, {80, 20}, {80, 80}, {20, 80}};
  walk.holes.push_back({{30, 30}, {70, 30}, {70, 70}, {30, 70}});

  const double forest_before = polygon_net_area_m2(forest);

  std::vector<VegePolygon> result = subtract_from_polygon(forest, {walk});

  ASSERT_EQ(result.size(), 2u);
  const VegePolygon* outer_donut = largest_forest_with_hole(result);
  ASSERT_NE(outer_donut, nullptr);
  EXPECT_EQ(outer_donut->layer, "405_Forest");
  ASSERT_EQ(outer_donut->holes.size(), 1u);
  EXPECT_DOUBLE_EQ(polygon_net_area_m2(*outer_donut), 6400.0);
  double forest_after = 0.0;
  for (const VegePolygon& piece : result) {
    forest_after += polygon_net_area_m2(piece);
  }
  EXPECT_LT(forest_after, forest_before);
  EXPECT_TRUE(point_in_polygon({5, 5}, *outer_donut));
  EXPECT_TRUE(point_in_ring({35, 35}, outer_donut->holes[0]));
  EXPECT_FALSE(point_in_polygon({25, 50}, *outer_donut));
}

TEST(SubtractFromPolygon, SmallGeosSliverHolesRemovedAfterCut) {
  // After green is cut from forest, only tiny GEOS sliver holes (< 1 m²) are dropped.
  VegePolygon forest;
  forest.layer = "405_Forest";
  forest.name = "405";
  forest.exterior_ring = {{0, 0}, {60, 0}, {60, 60}, {0, 60}};

  VegePolygon walk;
  walk.layer = "408_Walk";
  walk.exterior_ring = {{29.75, 29.75}, {30.25, 29.75}, {30.25, 30.25}, {29.75, 30.25}};

  std::vector<VegePolygon> result = subtract_from_polygon(forest, {walk});
  ASSERT_EQ(result.size(), 1u);
  ASSERT_EQ(result[0].holes.size(), 1u);
  EXPECT_LT(-signed_area(result[0].holes[0]), 1.0);

  std::map<std::string, double> post_cut_hole = {{"405_Forest", 1.0}};
  filter_small_holes(result, post_cut_hole, ProgressTracker());

  EXPECT_TRUE(result[0].holes.empty());
}

TEST(SubtractFromPolygon, UnderstoryCutHolesSurvivePostCutFilter) {
  // Legitimate understory cutouts must not be removed by the post-cut hole filter.
  VegePolygon forest;
  forest.layer = "405_Forest";
  forest.name = "405";
  forest.exterior_ring = {{0, 0}, {100, 0}, {100, 100}, {0, 100}};

  VegePolygon walk;
  walk.layer = "408_Walk";
  walk.exterior_ring = {{30, 30}, {70, 30}, {70, 70}, {30, 70}};

  std::vector<VegePolygon> result = subtract_from_polygon(forest, {walk});
  ASSERT_EQ(result.size(), 1u);
  ASSERT_EQ(result[0].holes.size(), 1u);
  EXPECT_DOUBLE_EQ(-signed_area(result[0].holes[0]), 1600.0);

  std::map<std::string, double> post_cut_hole = {{"405_Forest", 1.0}};
  filter_small_holes(result, post_cut_hole, ProgressTracker());

  ASSERT_EQ(result[0].holes.size(), 1u);
  EXPECT_TRUE(point_in_ring({50, 50}, result[0].holes[0]));
}

// =============================================================================
// generate_vege_polygons — rough open land hole quality
// =============================================================================

TEST(GenerateVegePolygons, RoughOpenLandHolesMatchRemainingForest) {
  // Rough open land is contoured from the same canopy grid as forest (pad 1.0).
  // Small speckles below min_area_m2 are dropped from 405_Forest and should not
  // appear as holes in rough open land either.
  VegeConfig config = canopy_config(/*min_area_m2=*/100.0, /*min_hole_area_m2=*/100.0);

  std::vector<std::vector<float>> data(20, std::vector<float>(20, 0.0f));
  // Large forest patch (~324 m² at 3 m resolution)
  for (int y = 2; y < 8; ++y) {
    for (int x = 2; x < 8; ++x) data[y][x] = 0.9f;
  }
  // Small canopy speckle (~36 m²) — below min_area_m2 and min_hole_area_m2
  for (int y = 14; y < 16; ++y) {
    for (int x = 14; x < 16; ++x) data[y][x] = 0.9f;
  }

  GeoGrid<float> grid = grid_at_3m(data);
  std::map<std::string, GeoGrid<float>> vege_maps = {{"canopy", grid}};
  std::vector<VegePolygon> polygons = generate_vege_polygons(config, vege_maps, ProgressTracker());

  EXPECT_EQ(count_layer(polygons, "405_Forest"), 1u)
      << "small canopy speckles below min_area_m2 should be dropped";

  const VegePolygon* rough_open = find_polygon(polygons, "403_Rough_Open_Land");
  ASSERT_NE(rough_open, nullptr);

  EXPECT_EQ(rough_open->holes.size(), 1u)
      << "rough open land should have one hole per remaining forest patch";
  EXPECT_GE(-signed_area(rough_open->holes[0]), 100.0)
      << "rough open land min hole uses forest min_area from config";
}

TEST(GenerateVegePolygons, RoughOpenLandHasNoTinySpeckleHoles) {
  // Default-style config: min_area_m2=30, min_hole_area_m2=100 on 405_Forest.
  // Rough open land min hole ← 30 (forest min area); min area ← 100 (forest min hole).
  VegeConfig config = canopy_config(/*min_area_m2=*/30.0, /*min_hole_area_m2=*/100.0);

  std::vector<std::vector<float>> data(15, std::vector<float>(15, 0.0f));
  // One legitimate forest patch (~144 m²)
  for (int y = 2; y < 6; ++y) {
    for (int x = 2; x < 6; ++x) data[y][x] = 0.9f;
  }
  // Several sub-threshold speckles (2×2 cells = 36 m² each)
  const std::pair<int, int> speckles[] = {{10, 2}, {12, 5}, {8, 10}, {11, 12}};
  for (auto [sy, sx] : speckles) {
    for (int y = sy; y < sy + 2; ++y) {
      for (int x = sx; x < sx + 2; ++x) data[y][x] = 0.9f;
    }
  }

  GeoGrid<float> grid = grid_at_3m(data);
  std::map<std::string, GeoGrid<float>> vege_maps = {{"canopy", grid}};
  std::vector<VegePolygon> polygons = generate_vege_polygons(config, vege_maps, ProgressTracker());

  const VegePolygon* rough_open = find_polygon(polygons, "403_Rough_Open_Land");
  ASSERT_NE(rough_open, nullptr);

  for (const auto& hole : rough_open->holes) {
    EXPECT_GE(-signed_area(hole), 30.0)
        << "rough open land min hole uses forest min_area (30 m²), not min_hole";
  }
}

TEST(GenerateVegePolygons, GreenDonutCutLeavesForestRing) {
  // Solid white forest with a ring-shaped green understory patch. After cutting
  // green out of forest, 405 should include an outer donut with an inner hole.
  VegeConfig config = forest_and_green_config();

  const int n = 15;
  std::vector<std::vector<float>> canopy(n, std::vector<float>(n, 0.0f));
  std::vector<std::vector<float>> green(n, std::vector<float>(n, 0.0f));

  for (int y = 2; y < 13; ++y) {
    for (int x = 2; x < 13; ++x) canopy[y][x] = 0.9f;
  }

  // Green ring (408) with open center inside the forest block.
  for (int x = 5; x <= 9; ++x) {
    green[5][x] = 0.8f;
    green[9][x] = 0.8f;
  }
  for (int y = 6; y <= 8; ++y) {
    green[y][5] = 0.8f;
    green[y][9] = 0.8f;
  }

  std::map<std::string, GeoGrid<float>> vege_maps = {
      {"canopy", grid_at_3m(canopy)},
      {"green", grid_at_3m(green)},
  };
  std::vector<VegePolygon> polygons = generate_vege_polygons(config, vege_maps, ProgressTracker());

  const VegePolygon* walk = find_polygon(polygons, "408_Walk");
  ASSERT_NE(walk, nullptr);
  EXPECT_EQ(walk->holes.size(), 1u) << "green understory should polygonize as a donut";

  const VegePolygon* outer_donut = largest_forest_with_hole(polygons);
  ASSERT_NE(outer_donut, nullptr)
      << "forest should include an outer ring polygon with an inner hole";
  EXPECT_EQ(outer_donut->holes.size(), 1u);
  EXPECT_GT(signed_area(outer_donut->exterior_ring), 0.0);
  EXPECT_LT(signed_area(outer_donut->holes[0]), 0.0);
  EXPECT_LT(polygon_net_area_m2(*outer_donut), signed_area(outer_donut->exterior_ring))
      << "cutting the green ring should reduce forest to a donut, not a solid fill";
  EXPECT_TRUE(point_in_ring(walk->holes[0][0], outer_donut->holes[0]))
      << "forest and green should share the same open center hole";
}

// =============================================================================
// Forest winding on soft near-threshold canopy (act_2025 regressions)
// =============================================================================

std::vector<VegePolygon> forest_contours_polygonize(const GeoGrid<float>& grid) {
  constexpr double FOREST_THRESHOLD = 0.1;
  std::map<double, std::string> layers = {{FOREST_THRESHOLD, "405_Forest"}};
  auto contours = generate_contours_at_heights(grid, {FOREST_THRESHOLD}, ProgressTracker(),
                                               /*min_points=*/5, 0.0f);
  return contours_to_polygons(contours, layers);
}

TEST(ContoursToPolygons, NestedHoles) {
  std::vector<std::vector<float>> data = {
      {0.20f, 0.13f, 0.18f, 0.38f, 0.20f}, {0.19f, 0.03f, 0.05f, 0.07f, 0.23f},
      {0.23f, 0.06f, 0.16f, 0.09f, 0.43f}, {0.24f, 0.06f, 0.07f, 0.03f, 0.26f},
      {0.23f, 0.29f, 0.15f, 0.20f, 0.59f},
  };

  auto polygons = forest_contours_polygonize(grid_at_3m(data));
  EXPECT_EQ(polygons.size(), 2u);
}

TEST(ContoursToPolygons, BigGrid) {
  std::vector<std::vector<float>> data = {
      {0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f},
      {0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f},
      {0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f},
      {0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f},
      {0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f},
      {0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f},
      {0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.749016f, 0.02f, 0.749016f, 0.9f, 0.9f, 0.9f, 0.9f,
       0.9f, 0.9f},
      {0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.02f, 0.02f, 0.02f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f},
      {0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.749016f, 0.02f, 0.749016f, 0.9f, 0.9f, 0.9f, 0.9f,
       0.9f, 0.9f},
      {0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f},
      {0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f},
      {0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f},
      {0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f},
      {0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f},
      {0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f},
  };

  auto polygons = forest_contours_polygonize(grid_at_3m(data));
  EXPECT_EQ(polygons.size(), 1u);
}
```


