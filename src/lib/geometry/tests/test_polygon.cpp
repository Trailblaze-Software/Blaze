#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <vector>

#include "geometry/polygon.hpp"
#include "geometry/polygon_subtract.hpp"

namespace {

PolygonWithHoles ccw_square(double x, double y, double size) {
  return {{{x, y}, {x + size, y}, {x + size, y + size}, {x, y + size}}, {}};
}

void expect_exterior_area(const PolygonWithHoles& poly, double area) {
  ASSERT_GE(poly.exterior.size(), 3u);
  EXPECT_GT(signed_area(poly.exterior), 0.0) << "exterior ring should be CCW";
  EXPECT_DOUBLE_EQ(signed_area(poly.exterior), area);
}

void expect_hole_area(const std::vector<Coordinate2D<double>>& hole, double area) {
  ASSERT_GE(hole.size(), 3u);
  EXPECT_LT(signed_area(hole), 0.0) << "hole ring should be CW";
  EXPECT_DOUBLE_EQ(signed_area(hole), -area);
}

double net_area(const PolygonWithHoles& poly) {
  double area = signed_area(poly.exterior);
  for (const auto& hole : poly.holes) {
    area += signed_area(hole);
  }
  return area;
}

double total_net_area(const std::vector<PolygonWithHoles>& polys) {
  double area = 0.0;
  for (const auto& poly : polys) {
    area += net_area(poly);
  }
  return area;
}

}  // namespace

TEST(SignedArea, CcwSquareIsPositive) {
  std::vector<Coordinate2D<double>> ring = {{0, 0}, {10, 0}, {10, 10}, {0, 10}};
  EXPECT_DOUBLE_EQ(signed_area(ring), 100.0);
}

TEST(SignedArea, CwSquareIsNegative) {
  std::vector<Coordinate2D<double>> ring = {{0, 0}, {0, 10}, {10, 10}, {10, 0}};
  EXPECT_DOUBLE_EQ(signed_area(ring), -100.0);
}

TEST(SignedArea, TooFewPointsIsZero) {
  EXPECT_DOUBLE_EQ(signed_area({{0, 0}, {1, 0}}), 0.0);
  EXPECT_DOUBLE_EQ(signed_area({}), 0.0);
}

TEST(PointInRing, InsideSquare) {
  std::vector<Coordinate2D<double>> ring = {{0, 0}, {10, 0}, {10, 10}, {0, 10}};
  EXPECT_TRUE(point_in_ring({5, 5}, ring));
}

TEST(PointInRing, OutsideSquare) {
  std::vector<Coordinate2D<double>> ring = {{0, 0}, {10, 0}, {10, 10}, {0, 10}};
  EXPECT_FALSE(point_in_ring({15, 5}, ring));
  EXPECT_FALSE(point_in_ring({-1, 5}, ring));
}

TEST(PointInRing, TooFewPointsIsFalse) { EXPECT_FALSE(point_in_ring({0, 0}, {{0, 0}, {1, 0}})); }

TEST(ReverseRing, NegatesSignedArea) {
  std::vector<Coordinate2D<double>> ccw = {{0, 0}, {10, 0}, {10, 10}, {0, 10}};
  std::vector<Coordinate2D<double>> reversed = reverse_ring(ccw);
  EXPECT_DOUBLE_EQ(signed_area(ccw), 100.0);
  EXPECT_DOUBLE_EQ(signed_area(reversed), -100.0);
  EXPECT_EQ(reversed.front(), ccw.back());
  EXPECT_EQ(reversed.back(), ccw.front());
}

TEST(NormalizePolygon, FixesExteriorAndHoleWinding) {
  PolygonWithHoles poly;
  poly.exterior = {{0, 0}, {0, 10}, {10, 10}, {10, 0}};    // CW
  poly.holes.push_back({{2, 2}, {2, 4}, {4, 4}, {4, 2}});  // CCW

  normalize_polygon(poly);

  EXPECT_GT(signed_area(poly.exterior), 0.0);
  EXPECT_LT(signed_area(poly.holes[0]), 0.0);
}

TEST(PolygonIntersection, FullContainment) {
  std::vector<Coordinate2D<double>> subject = {{5, 5}, {15, 5}, {15, 15}, {5, 15}};
  std::vector<Coordinate2D<double>> clip = {{0, 0}, {20, 0}, {20, 20}, {0, 20}};

  auto result = intersect_polygons(subject, clip);

  ASSERT_EQ(result.size(), 4u);
  EXPECT_DOUBLE_EQ(signed_area(result), 100.0);
}

TEST(PolygonIntersection, PartialOverlap) {
  std::vector<Coordinate2D<double>> subject = {{10, 0}, {20, 0}, {20, 10}, {10, 10}};
  std::vector<Coordinate2D<double>> clip = {{0, 0}, {15, 0}, {15, 15}, {0, 15}};

  auto result = intersect_polygons(subject, clip);

  ASSERT_EQ(result.size(), 4u);
  EXPECT_DOUBLE_EQ(signed_area(result), 50.0);
}

TEST(PolygonIntersection, NoOverlap) {
  std::vector<Coordinate2D<double>> subject = {{100, 100}, {110, 100}, {110, 110}, {100, 110}};
  std::vector<Coordinate2D<double>> clip = {{0, 0}, {10, 0}, {10, 10}, {0, 10}};

  auto result = intersect_polygons(subject, clip);

  EXPECT_TRUE(result.empty());
}

// =============================================================================
// Polygon subtraction — geometry-level contract tests
// =============================================================================

TEST(SubtractPolygon, NoCutouts) {
  auto host = ccw_square(0, 0, 100);

  std::vector<PolygonWithHoles> result = subtract_polygon(host, {});

  ASSERT_EQ(result.size(), 1u);
  expect_exterior_area(result[0], 10000.0);
  EXPECT_TRUE(result[0].holes.empty());
}

TEST(SubtractPolygonWithUnion, NullUnionReturnsHost) {
  const PolygonWithHoles host = ccw_square(0, 0, 100);

  const std::vector<PolygonWithHoles> result = subtract_polygon_with_union(host, nullptr);

  ASSERT_EQ(result.size(), 1u);
  expect_exterior_area(result[0], 10000.0);
  EXPECT_TRUE(result[0].holes.empty());
}

TEST(SubtractPolygon, CutoutOutsideHost) {
  auto host = ccw_square(0, 0, 50);
  auto cutout = ccw_square(100, 100, 10);

  std::vector<PolygonWithHoles> result = subtract_polygon(host, {cutout});

  ASSERT_EQ(result.size(), 1u);
  expect_exterior_area(result[0], 2500.0);
  EXPECT_TRUE(result[0].holes.empty());
}

TEST(SubtractPolygon, CutoutFullyCoversHost) {
  auto host = ccw_square(10, 10, 20);
  auto cutout = ccw_square(0, 0, 100);

  std::vector<PolygonWithHoles> result = subtract_polygon(host, {cutout});

  EXPECT_TRUE(result.empty());
}

TEST(SubtractPolygon, SingleCutoutFullyContained) {
  auto host = ccw_square(0, 0, 100);
  auto cutout = ccw_square(20, 20, 30);

  std::vector<PolygonWithHoles> result = subtract_polygon(host, {cutout});

  ASSERT_EQ(result.size(), 1u);
  expect_exterior_area(result[0], 10000.0);
  ASSERT_EQ(result[0].holes.size(), 1u);
  expect_hole_area(result[0].holes[0], 900.0);  // 30x30
  EXPECT_DOUBLE_EQ(net_area(result[0]), 9100.0);
  EXPECT_TRUE(point_in_ring({5, 5}, result[0].exterior));
  EXPECT_TRUE(point_in_ring({35, 35}, result[0].holes[0]));
}

TEST(SubtractPolygon, TwoDisjointCutouts) {
  auto host = ccw_square(0, 0, 100);
  auto cutout_a = ccw_square(10, 10, 10);
  auto cutout_b = ccw_square(70, 70, 10);

  std::vector<PolygonWithHoles> result = subtract_polygon(host, {cutout_a, cutout_b});

  ASSERT_EQ(result.size(), 1u);
  expect_exterior_area(result[0], 10000.0);
  ASSERT_EQ(result[0].holes.size(), 2u);
  expect_hole_area(result[0].holes[0], 100.0);
  expect_hole_area(result[0].holes[1], 100.0);
  EXPECT_DOUBLE_EQ(net_area(result[0]), 9800.0);
}

TEST(SubtractPolygon, NestedCutoutsNotDoubleCut) {
  // Host contains Walk, which contains Fight. Only the outer cutout should become a hole.
  auto host = ccw_square(0, 0, 100);
  auto walk = ccw_square(20, 20, 60);
  auto fight = ccw_square(30, 30, 20);

  std::vector<PolygonWithHoles> result = subtract_polygon(host, {walk, fight});

  ASSERT_EQ(result.size(), 1u);
  ASSERT_EQ(result[0].holes.size(), 1u);
  expect_hole_area(result[0].holes[0], 3600.0);  // 60x60
  EXPECT_DOUBLE_EQ(net_area(result[0]), 6400.0);
}

TEST(SubtractPolygon, PartialOverlapClipsHost) {
  auto host = ccw_square(0, 0, 50);
  auto cutout = ccw_square(25, 25, 50);

  std::vector<PolygonWithHoles> result = subtract_polygon(host, {cutout});

  ASSERT_EQ(result.size(), 1u);
  EXPECT_TRUE(result[0].holes.empty());
  // 50x50 host minus 25x25 overlap in the NE corner
  expect_exterior_area(result[0], 1875.0);
  EXPECT_TRUE(point_in_ring({10, 10}, result[0].exterior));
  EXPECT_FALSE(point_in_ring({40, 40}, result[0].exterior));
}

TEST(SubtractPolygon, SplitsHostIntoTwo) {
  auto host = ccw_square(0, 0, 100);
  PolygonWithHoles cutout;
  cutout.exterior = {{40, 0}, {60, 0}, {60, 100}, {40, 100}};

  std::vector<PolygonWithHoles> result = subtract_polygon(host, {cutout});

  ASSERT_EQ(result.size(), 2u);
  std::vector<double> areas;
  for (const auto& piece : result) {
    EXPECT_TRUE(piece.holes.empty());
    EXPECT_GT(signed_area(piece.exterior), 0.0) << "each piece exterior should be CCW";
    areas.push_back(signed_area(piece.exterior));
  }
  std::sort(areas.begin(), areas.end());
  EXPECT_DOUBLE_EQ(areas[0], 4000.0);  // 40x100
  EXPECT_DOUBLE_EQ(areas[1], 4000.0);
  EXPECT_DOUBLE_EQ(total_net_area(result), 8000.0);
}

TEST(SubtractPolygon, CutoutInsideExistingHole) {
  auto host = ccw_square(0, 0, 100);
  host.holes.push_back(ccw_square(10, 10, 80).exterior);
  normalize_polygon(host);
  auto cutout = ccw_square(30, 30, 20);

  std::vector<PolygonWithHoles> result = subtract_polygon(host, {cutout});

  ASSERT_EQ(result.size(), 1u);
  ASSERT_EQ(result[0].holes.size(), 1u);
  expect_hole_area(result[0].holes[0], 6400.0);  // 80x80 walk ring unchanged
  EXPECT_DOUBLE_EQ(net_area(result[0]), 3600.0);
}

TEST(SubtractPolygon, GreenDonutLeavesForestRing) {
  // Cutting a ring-shaped green patch from solid forest yields an outer white
  // forest donut (with an inner hole) plus a separate inner forest island.
  auto host = ccw_square(0, 0, 100);
  PolygonWithHoles green;
  green.exterior = ccw_square(20, 20, 60).exterior;
  green.holes.push_back(ccw_square(30, 30, 40).exterior);
  normalize_polygon(green);

  const double green_area = net_area(green);
  std::vector<PolygonWithHoles> result = subtract_polygon(host, {green});

  ASSERT_EQ(result.size(), 2u);
  const PolygonWithHoles* outer_donut = nullptr;
  const PolygonWithHoles* inner_island = nullptr;
  for (const PolygonWithHoles& piece : result) {
    if (!piece.holes.empty()) {
      outer_donut = &piece;
    } else {
      inner_island = &piece;
    }
  }
  ASSERT_NE(outer_donut, nullptr);
  ASSERT_NE(inner_island, nullptr);

  expect_exterior_area(*outer_donut, 10000.0);
  ASSERT_EQ(outer_donut->holes.size(), 1u);
  expect_hole_area(outer_donut->holes[0], 3600.0);  // 60x60 hole left by green outer ring
  expect_exterior_area(*inner_island, 1600.0);      // 40x40 forest inside green hole
  EXPECT_DOUBLE_EQ(total_net_area(result), net_area(host) - green_area);
  EXPECT_TRUE(point_in_ring({5, 5}, outer_donut->exterior));
  EXPECT_TRUE(point_in_ring({35, 35}, outer_donut->holes[0]));
  EXPECT_TRUE(point_in_ring({35, 35}, inner_island->exterior));
}

TEST(SubtractPolygon, NetAreaConservedAcrossOperations) {
  auto host = ccw_square(0, 0, 100);
  auto walk = ccw_square(20, 20, 30);
  auto fight = ccw_square(60, 60, 10);

  const double expected = net_area(host) - 900.0 - 100.0;
  std::vector<PolygonWithHoles> result = subtract_polygon(host, {walk, fight});

  EXPECT_DOUBLE_EQ(total_net_area(result), expected);
}

TEST(IntersectPolygon, ClipsExteriorToExtent) {
  auto host = ccw_square(0, 0, 100);
  auto clip = polygon_from_extent({50.0, 100.0, 0.0, 100.0});

  std::vector<PolygonWithHoles> result = intersect_polygon(host, clip);

  ASSERT_EQ(result.size(), 1u);
  expect_exterior_area(result[0], 5000.0);
  for (const Coordinate2D<double>& p : result[0].exterior) {
    EXPECT_GE(p.x(), 50.0 - 1e-9);
    EXPECT_LE(p.x(), 100.0 + 1e-9);
  }
}

TEST(IntersectPolygon, RemovesPolygonOutsideExtent) {
  auto host = ccw_square(0, 0, 10);
  auto clip = polygon_from_extent({20.0, 30.0, 0.0, 10.0});

  EXPECT_TRUE(intersect_polygon(host, clip).empty());
}

TEST(IntersectPolygon, ClipsPolygonWithHole) {
  PolygonWithHoles host = ccw_square(0, 0, 100);
  host.holes.push_back(ccw_square(20, 20, 60).exterior);
  normalize_polygon(host);
  auto clip = polygon_from_extent({50.0, 100.0, 0.0, 100.0});

  std::vector<PolygonWithHoles> result = intersect_polygon(host, clip);

  ASSERT_EQ(result.size(), 1u);
  EXPECT_GT(net_area(result[0]), 0.0);
  EXPECT_LT(net_area(result[0]), net_area(host));
}

TEST(ClipPolygonToExtent, MatchesGeosClipForSquare) {
  auto host = ccw_square(0, 0, 100);
  Extent2D bounds{50.0, 100.0, 0.0, 100.0};

  std::vector<PolygonWithHoles> fast = clip_polygon_to_extent(host, bounds);
  ASSERT_EQ(fast.size(), 1u);
  expect_exterior_area(fast[0], 5000.0);

  auto geos = intersect_polygon(host, polygon_from_extent(bounds));
  ASSERT_EQ(geos.size(), 1u);
  EXPECT_NEAR(net_area(fast[0]), net_area(geos[0]), 1e-6);
}

TEST(ClipPolygonToExtent, ClipsPolygonWithHole) {
  PolygonWithHoles host = ccw_square(0, 0, 100);
  host.holes.push_back(ccw_square(20, 20, 60).exterior);
  normalize_polygon(host);
  Extent2D bounds{50.0, 100.0, 0.0, 100.0};

  std::vector<PolygonWithHoles> clipped = clip_polygon_to_extent(host, bounds);
  ASSERT_EQ(clipped.size(), 1u);
  EXPECT_GT(net_area(clipped[0]), 0.0);
  EXPECT_LT(net_area(clipped[0]), net_area(host));
  EXPECT_NEAR(net_area(clipped[0]),
              net_area(intersect_polygon(host, polygon_from_extent(bounds))[0]), 1e-6);
}

TEST(ClipPolygonToExtent, BisectedDonutDropsHole) {
  // Clip through the hole: the cut edge should become exterior boundary, not a hole.
  PolygonWithHoles host = ccw_square(0, 0, 100);
  host.holes.push_back(ccw_square(40, 40, 20).exterior);
  normalize_polygon(host);
  Extent2D bounds{0.0, 50.0, 0.0, 100.0};

  std::vector<PolygonWithHoles> clipped = clip_polygon_to_extent(host, bounds);
  ASSERT_EQ(clipped.size(), 1u);
  EXPECT_EQ(clipped[0].holes.size(), 0u);

  auto geos = intersect_polygon(host, polygon_from_extent(bounds));
  ASSERT_EQ(geos.size(), 1u);
  EXPECT_EQ(geos[0].holes.size(), 0u);
  EXPECT_NEAR(net_area(clipped[0]), net_area(geos[0]), 1e-6);
}

TEST(UnionOverlappingPolygons, MergesOverlappingPolygons) {
  const PolygonWithHoles left = ccw_square(0, 0, 10);
  const PolygonWithHoles right = ccw_square(5, 0, 10);
  const std::vector<PolygonWithHoles> result = union_overlapping_polygons({left, right});
  ASSERT_EQ(result.size(), 1u);
  expect_exterior_area(result[0], 150.0);
}

TEST(UnionOverlappingPolygons, MergesTouchingEdges) {
  const PolygonWithHoles left = ccw_square(0, 0, 10);
  const PolygonWithHoles right = ccw_square(10, 0, 10);
  const std::vector<PolygonWithHoles> result = union_overlapping_polygons({left, right});
  ASSERT_EQ(result.size(), 1u);
  expect_exterior_area(result[0], 200.0);
}

TEST(UnionOverlappingPolygons, KeepsDisjointSeparate) {
  const PolygonWithHoles left = ccw_square(0, 0, 10);
  const PolygonWithHoles right = ccw_square(20, 0, 10);
  const std::vector<PolygonWithHoles> result = union_overlapping_polygons({left, right});
  EXPECT_EQ(result.size(), 2u);
  EXPECT_DOUBLE_EQ(total_net_area(result), 200.0);
}

TEST(UnionOverlappingPolygons, RepairsSelfIntersectingInputs) {
  const PolygonWithHoles bowtie{{{0, 0}, {10, 10}, {10, 0}, {0, 10}}, {}};
  const PolygonWithHoles square = ccw_square(5, 0, 10);
  const std::vector<PolygonWithHoles> result = union_overlapping_polygons({bowtie, square});
  ASSERT_GE(result.size(), 1u);
  EXPECT_GT(total_net_area(result), 0.0);
}

TEST(SnapRingToExtent, SnapsNearBoundaryVertices) {
  std::vector<Coordinate2D<double>> ring = {{49.995, 0}, {100, 50}, {50, 99.992}};
  snap_ring_to_extent(ring, {50.0, 100.0, 0.0, 100.0}, 0.01);
  EXPECT_DOUBLE_EQ(ring[0].x(), 50.0);
  EXPECT_DOUBLE_EQ(ring[2].y(), 100.0);
}

TEST(FinalizePolygonWithHoles, RepairsSelfIntersectingBowtie) {
  const PolygonWithHoles bowtie{{{0, 0}, {10, 10}, {10, 0}, {0, 10}}, {}};
  const std::vector<PolygonWithHoles> result = finalize_polygon_with_holes(bowtie);
  ASSERT_GE(result.size(), 1u);
  EXPECT_GT(total_net_area(result), 0.0);
}

TEST(FinalizePolygonWithHoles, SnapsToTileSeamBeforeRepair) {
  PolygonWithHoles poly = ccw_square(999.995, 0, 10);
  const std::vector<PolygonWithHoles> result =
      finalize_polygon_with_holes(poly, {{1000.0, 2000.0, 0.0, 1000.0}}, 0.01);
  ASSERT_EQ(result.size(), 1u);
  bool has_seam = false;
  for (const Coordinate2D<double>& p : result[0].exterior) {
    if (std::abs(p.x() - 1000.0) < 1e-12) {
      has_seam = true;
      break;
    }
  }
  EXPECT_TRUE(has_seam);
}
