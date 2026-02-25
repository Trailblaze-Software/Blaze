#include <gtest/gtest.h>

#include <cmath>
#include <limits>

#include "grid/grid.hpp"
#include "grid/grid_ops.hpp"

// Helper to avoid brace-initialization inside GTest macros (MSVC preprocessor issue)
static Coordinate2D<size_t> coord(size_t x, size_t y) { return Coordinate2D<size_t>(x, y); }

// =============================================================================
// GeoTransform tests
// =============================================================================

TEST(GeoTransform, DefaultConstruction) {
  GeoTransform t;
  EXPECT_DOUBLE_EQ(t.x(), 0.0);
  EXPECT_DOUBLE_EQ(t.y(), 0.0);
  EXPECT_DOUBLE_EQ(t.dx(), 1.0);
  EXPECT_DOUBLE_EQ(t.dy(), -1.0);
  EXPECT_DOUBLE_EQ(t.rot_x(), 0.0);
  EXPECT_DOUBLE_EQ(t.rot_y(), 0.0);
}

TEST(GeoTransform, ConstructionWithValues) {
  GeoTransform t(100.0, 200.0, 0.5, -0.5);
  EXPECT_DOUBLE_EQ(t.x(), 100.0);
  EXPECT_DOUBLE_EQ(t.y(), 200.0);
  EXPECT_DOUBLE_EQ(t.dx(), 0.5);
  EXPECT_DOUBLE_EQ(t.dy(), -0.5);
}

TEST(GeoTransform, ConstructionFromCoordinate) {
  Coordinate2D<double> upper_left(100.0, 200.0);
  GeoTransform t(upper_left, 2.0);
  EXPECT_DOUBLE_EQ(t.x(), 100.0);
  EXPECT_DOUBLE_EQ(t.y(), 200.0);
  EXPECT_DOUBLE_EQ(t.dx(), 2.0);
  EXPECT_DOUBLE_EQ(t.dy(), -2.0);
}

TEST(GeoTransform, PixelToProjection) {
  // Default transform: origin at (0,0), dx=1, dy=-1
  GeoTransform t;
  Coordinate2D<double> pixel(3.0, 4.0);
  Coordinate2D<double> proj = t.pixel_to_projection(pixel);
  EXPECT_DOUBLE_EQ(proj.x(), 3.0);
  EXPECT_DOUBLE_EQ(proj.y(), -4.0);
}

TEST(GeoTransform, PixelToProjectionWithOffset) {
  GeoTransform t(100.0, 200.0, 2.0, -2.0);
  Coordinate2D<double> pixel(5.0, 3.0);
  Coordinate2D<double> proj = t.pixel_to_projection(pixel);
  EXPECT_DOUBLE_EQ(proj.x(), 100.0 + 5.0 * 2.0);
  EXPECT_DOUBLE_EQ(proj.y(), 200.0 + 3.0 * (-2.0));
}

TEST(GeoTransform, ProjectionToPixel) {
  GeoTransform t(100.0, 200.0, 2.0, -2.0);
  Coordinate2D<double> proj(110.0, 194.0);
  Coordinate2D<double> pixel = t.projection_to_pixel(proj);
  EXPECT_NEAR(pixel.x(), 5.0, 1e-10);
  EXPECT_NEAR(pixel.y(), 3.0, 1e-10);
}

TEST(GeoTransform, PixelProjectionRoundTrip) {
  GeoTransform t(500.0, 1000.0, 0.25, -0.25);
  Coordinate2D<double> original_pixel(10.5, 20.3);
  Coordinate2D<double> proj = t.pixel_to_projection(original_pixel);
  Coordinate2D<double> round_trip = t.projection_to_pixel(proj);
  EXPECT_NEAR(round_trip.x(), original_pixel.x(), 1e-10);
  EXPECT_NEAR(round_trip.y(), original_pixel.y(), 1e-10);
}

TEST(GeoTransform, WithNewResolution) {
  GeoTransform t(100.0, 200.0, 1.0, -1.0);
  GeoTransform t2 = t.with_new_resolution(2.0);
  EXPECT_DOUBLE_EQ(t2.x(), 100.0);
  EXPECT_DOUBLE_EQ(t2.y(), 200.0);
  EXPECT_DOUBLE_EQ(t2.dx(), 2.0);
  EXPECT_DOUBLE_EQ(t2.dy(), -2.0);
}

// =============================================================================
// Grid basic operations tests
// =============================================================================

TEST(Grid, ConstructionAndAccess) {
  Grid<double> g(3, 2);
  g[coord(0, 0)] = 1.0;
  g[coord(1, 0)] = 2.0;
  g[coord(2, 0)] = 3.0;
  g[coord(0, 1)] = 4.0;
  g[coord(1, 1)] = 5.0;
  g[coord(2, 1)] = 6.0;

  double v00 = g[coord(0, 0)];
  double v10 = g[coord(1, 0)];
  double v20 = g[coord(2, 0)];
  double v01 = g[coord(0, 1)];
  double v11 = g[coord(1, 1)];
  double v21 = g[coord(2, 1)];

  EXPECT_DOUBLE_EQ(v00, 1.0);
  EXPECT_DOUBLE_EQ(v10, 2.0);
  EXPECT_DOUBLE_EQ(v20, 3.0);
  EXPECT_DOUBLE_EQ(v01, 4.0);
  EXPECT_DOUBLE_EQ(v11, 5.0);
  EXPECT_DOUBLE_EQ(v21, 6.0);
}

TEST(Grid, Fill) {
  Grid<double> g(3, 3);
  g.fill(42.0);
  for (size_t i = 0; i < 3; i++) {
    for (size_t j = 0; j < 3; j++) {
      double val = g[coord(j, i)];
      EXPECT_DOUBLE_EQ(val, 42.0);
    }
  }
}

TEST(Grid, MinMax) {
  Grid<double> g(3, 2);
  g[coord(0, 0)] = 3.0;
  g[coord(1, 0)] = 1.0;
  g[coord(2, 0)] = 5.0;
  g[coord(0, 1)] = 2.0;
  g[coord(1, 1)] = 8.0;
  g[coord(2, 1)] = 4.0;

  EXPECT_DOUBLE_EQ(g.min_value(), 1.0);
  EXPECT_DOUBLE_EQ(g.max_value(), 8.0);
}

TEST(Grid, CopyFrom) {
  Grid<double> a(2, 2);
  a[coord(0, 0)] = 1.0;
  a[coord(1, 0)] = 2.0;
  a[coord(0, 1)] = 3.0;
  a[coord(1, 1)] = 4.0;

  Grid<double> b(2, 2);
  b.copy_from(a);

  double v00 = b[coord(0, 0)];
  double v10 = b[coord(1, 0)];
  double v01 = b[coord(0, 1)];
  double v11 = b[coord(1, 1)];

  EXPECT_DOUBLE_EQ(v00, 1.0);
  EXPECT_DOUBLE_EQ(v10, 2.0);
  EXPECT_DOUBLE_EQ(v01, 3.0);
  EXPECT_DOUBLE_EQ(v11, 4.0);
}

TEST(Grid, InBounds) {
  GridData gd(5, 3);
  EXPECT_TRUE(gd.in_bounds(Coordinate2D<size_t>(0, 0)));
  EXPECT_TRUE(gd.in_bounds(Coordinate2D<size_t>(4, 2)));
  // size_t wraps so we can't test negative but can test overflow
  EXPECT_FALSE(gd.in_bounds(Coordinate2D<size_t>(5, 0)));
  EXPECT_FALSE(gd.in_bounds(Coordinate2D<size_t>(0, 3)));
}

TEST(Grid, FillFrom) {
  Grid<double> big(5, 5);
  big.fill(0.0);

  Grid<double> small_grid(2, 2);
  small_grid[coord(0, 0)] = 10.0;
  small_grid[coord(1, 0)] = 20.0;
  small_grid[coord(0, 1)] = 30.0;
  small_grid[coord(1, 1)] = 40.0;

  big.fill_from(small_grid, Coordinate2D<size_t>(1, 1));

  double v00 = big[coord(0, 0)];
  double v11 = big[coord(1, 1)];
  double v21 = big[coord(2, 1)];
  double v12 = big[coord(1, 2)];
  double v22 = big[coord(2, 2)];
  double v33 = big[coord(3, 3)];

  EXPECT_DOUBLE_EQ(v00, 0.0);
  EXPECT_DOUBLE_EQ(v11, 10.0);
  EXPECT_DOUBLE_EQ(v21, 20.0);
  EXPECT_DOUBLE_EQ(v12, 30.0);
  EXPECT_DOUBLE_EQ(v22, 40.0);
  EXPECT_DOUBLE_EQ(v33, 0.0);
}

// =============================================================================
// GeoGrid tests
// =============================================================================

TEST(GeoGrid, Extent) {
  GeoGrid<double> grid(10, 5, GeoTransform(100.0, 200.0, 1.0, -1.0), GeoProjection());
  auto ext = grid.extent();
  EXPECT_DOUBLE_EQ(ext->minx, 100.0);
  EXPECT_DOUBLE_EQ(ext->maxx, 110.0);
  EXPECT_DOUBLE_EQ(ext->miny, 195.0);
  EXPECT_DOUBLE_EQ(ext->maxy, 200.0);
}

// =============================================================================
// interpolate_value tests
// =============================================================================

TEST(InterpolateValue, CenterOfCell) {
  // Create a 3x3 grid with known values
  GeoGrid<double> grid(3, 3, GeoTransform(), GeoProjection());
  grid[coord(0, 0)] = 1.0;
  grid[coord(1, 0)] = 2.0;
  grid[coord(2, 0)] = 3.0;
  grid[coord(0, 1)] = 4.0;
  grid[coord(1, 1)] = 5.0;
  grid[coord(2, 1)] = 6.0;
  grid[coord(0, 2)] = 7.0;
  grid[coord(1, 2)] = 8.0;
  grid[coord(2, 2)] = 9.0;

  // At exact center of cell (1,1), the projection coord is (1.5, -1.5)
  // which should give interpolated value = 5.0 (exact center of the cell)
  double val = interpolate_value(grid, Coordinate2D<double>(1.5, -1.5));
  EXPECT_NEAR(val, 5.0, 1e-10);
}

TEST(InterpolateValue, MidpointBetweenCells) {
  GeoGrid<double> grid(3, 3, GeoTransform(), GeoProjection());
  grid[coord(0, 0)] = 0.0;
  grid[coord(1, 0)] = 10.0;
  grid[coord(2, 0)] = 0.0;
  grid[coord(0, 1)] = 0.0;
  grid[coord(1, 1)] = 10.0;
  grid[coord(2, 1)] = 0.0;
  grid[coord(0, 2)] = 0.0;
  grid[coord(1, 2)] = 0.0;
  grid[coord(2, 2)] = 0.0;

  // Between cells (0,0) and (1,0): projection coord x=1.0 is the midpoint
  double val = interpolate_value(grid, Coordinate2D<double>(1.0, -0.5));
  // This is at the boundary between cells - should be a finite number
  EXPECT_TRUE(std::isfinite(val));
}

// =============================================================================
// GridGraph tests
// =============================================================================

TEST(GridGraph, ConstructionAndAccess) {
  Grid<double> base(3, 3);
  GridGraph<int> graph(base);

  // Horizontal edges: (3-1)x3 = 2x3
  EXPECT_EQ(graph.horizontal().width(), 2u);
  EXPECT_EQ(graph.horizontal().height(), 3u);

  // Vertical edges: 3x(3-1) = 3x2
  EXPECT_EQ(graph.vertical().width(), 3u);
  EXPECT_EQ(graph.vertical().height(), 2u);

  // Set and read values via LineCoord2D
  LineCoord2D<size_t> right_edge(Coordinate2D<size_t>(0, 0), Direction2D::RIGHT);
  graph[right_edge] = 42;
  EXPECT_EQ(graph[right_edge], 42);

  LineCoord2D<size_t> down_edge(Coordinate2D<size_t>(0, 0), Direction2D::DOWN);
  graph[down_edge] = 99;
  EXPECT_EQ(graph[down_edge], 99);
}

TEST(GridGraph, InBounds) {
  Grid<double> base(3, 3);
  GridGraph<int> graph(base);

  // Valid horizontal edge
  EXPECT_TRUE(graph.in_bounds(LineCoord2D<size_t>(0, 0, Direction2D::RIGHT)));
  EXPECT_TRUE(graph.in_bounds(LineCoord2D<size_t>(1, 2, Direction2D::RIGHT)));
  // Out of bounds horizontal edge
  EXPECT_FALSE(graph.in_bounds(LineCoord2D<size_t>(2, 0, Direction2D::RIGHT)));

  // Valid vertical edge
  EXPECT_TRUE(graph.in_bounds(LineCoord2D<size_t>(0, 0, Direction2D::DOWN)));
  EXPECT_TRUE(graph.in_bounds(LineCoord2D<size_t>(2, 1, Direction2D::DOWN)));
  // Out of bounds vertical edge
  EXPECT_FALSE(graph.in_bounds(LineCoord2D<size_t>(0, 2, Direction2D::DOWN)));
}
