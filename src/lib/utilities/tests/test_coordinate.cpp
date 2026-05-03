#include <gtest/gtest.h>

#include <cmath>
#include <limits>

#include "utilities/coordinate.hpp"

// =============================================================================
// Coordinate2D tests
// =============================================================================

TEST(Coordinate2D, Construction) {
  Coordinate2D<double> c(3.0, 4.0);
  EXPECT_DOUBLE_EQ(c.x(), 3.0);
  EXPECT_DOUBLE_EQ(c.y(), 4.0);
}

TEST(Coordinate2D, DefaultConstruction) {
  Coordinate2D<int> c;
  // Default-constructed, values are indeterminate but should not crash
  (void)c;
}

TEST(Coordinate2D, Addition) {
  Coordinate2D<double> a(1.0, 2.0);
  Coordinate2D<double> b(3.0, 5.0);
  Coordinate2D<double> result = a + b;
  EXPECT_DOUBLE_EQ(result.x(), 4.0);
  EXPECT_DOUBLE_EQ(result.y(), 7.0);
}

TEST(Coordinate2D, Subtraction) {
  Coordinate2D<double> a(5.0, 7.0);
  Coordinate2D<double> b(2.0, 3.0);
  Coordinate2D<double> result = a - b;
  EXPECT_DOUBLE_EQ(result.x(), 3.0);
  EXPECT_DOUBLE_EQ(result.y(), 4.0);
}

TEST(Coordinate2D, Equality) {
  Coordinate2D<int> a(1, 2);
  Coordinate2D<int> b(1, 2);
  Coordinate2D<int> c(1, 3);
  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a == c);
}

TEST(Coordinate2D, MagnitudeSquared) {
  Coordinate2D<double> c(3.0, 4.0);
  EXPECT_DOUBLE_EQ(c.magnitude_sqd(), 25.0);
}

TEST(Coordinate2D, Magnitude) {
  Coordinate2D<double> c(3.0, 4.0);
  EXPECT_DOUBLE_EQ(c.magnitude(), 5.0);

  Coordinate2D<double> zero(0.0, 0.0);
  EXPECT_DOUBLE_EQ(zero.magnitude(), 0.0);
}

TEST(Coordinate2D, MagnitudeUnit) {
  Coordinate2D<double> c(1.0, 0.0);
  EXPECT_DOUBLE_EQ(c.magnitude(), 1.0);

  Coordinate2D<double> d(0.0, 1.0);
  EXPECT_DOUBLE_EQ(d.magnitude(), 1.0);
}

TEST(Coordinate2D, OffsetToCenter) {
  Coordinate2D<size_t> c(3, 4);
  Coordinate2D<double> centered = c.offset_to_center();
  EXPECT_DOUBLE_EQ(centered.x(), 3.5);
  EXPECT_DOUBLE_EQ(centered.y(), 4.5);
}

TEST(Coordinate2D, AddDirection) {
  Coordinate2D<int> c(5, 5);

  Coordinate2D<int> up = c + Direction2D::UP;
  EXPECT_EQ(up.x(), 5);
  EXPECT_EQ(up.y(), 4);

  Coordinate2D<int> down = c + Direction2D::DOWN;
  EXPECT_EQ(down.x(), 5);
  EXPECT_EQ(down.y(), 6);

  Coordinate2D<int> left = c + Direction2D::LEFT;
  EXPECT_EQ(left.x(), 4);
  EXPECT_EQ(left.y(), 5);

  Coordinate2D<int> right = c + Direction2D::RIGHT;
  EXPECT_EQ(right.x(), 6);
  EXPECT_EQ(right.y(), 5);

  Coordinate2D<int> ur = c + Direction2D::UR;
  EXPECT_EQ(ur.x(), 6);
  EXPECT_EQ(ur.y(), 4);

  Coordinate2D<int> ul = c + Direction2D::UL;
  EXPECT_EQ(ul.x(), 4);
  EXPECT_EQ(ul.y(), 4);

  Coordinate2D<int> dr = c + Direction2D::DR;
  EXPECT_EQ(dr.x(), 6);
  EXPECT_EQ(dr.y(), 6);

  Coordinate2D<int> dl = c + Direction2D::DL;
  EXPECT_EQ(dl.x(), 4);
  EXPECT_EQ(dl.y(), 6);
}

TEST(Coordinate2D, TypeConversion) {
  Coordinate2D<double> d(3.7, 4.2);
  Coordinate2D<int> i = d;
  EXPECT_EQ(i.x(), 3);
  EXPECT_EQ(i.y(), 4);
}

TEST(Coordinate2D, OrthogonalNeighbors) {
  Coordinate2D<int> c(5, 5);
  auto neighbors = orthogonal_neighbors(c);
  EXPECT_EQ(neighbors.size(), 4);
  EXPECT_TRUE(neighbors[0] == Coordinate2D<int>(4, 5));
  EXPECT_TRUE(neighbors[1] == Coordinate2D<int>(6, 5));
  EXPECT_TRUE(neighbors[2] == Coordinate2D<int>(5, 4));
  EXPECT_TRUE(neighbors[3] == Coordinate2D<int>(5, 6));
}

// =============================================================================
// Direction2D tests
// =============================================================================

TEST(Direction2D, DxDy) {
  EXPECT_EQ(Direction2D(Direction2D::UP).dx(), 0);
  EXPECT_EQ(Direction2D(Direction2D::UP).dy(), -1);

  EXPECT_EQ(Direction2D(Direction2D::DOWN).dx(), 0);
  EXPECT_EQ(Direction2D(Direction2D::DOWN).dy(), 1);

  EXPECT_EQ(Direction2D(Direction2D::LEFT).dx(), -1);
  EXPECT_EQ(Direction2D(Direction2D::LEFT).dy(), 0);

  EXPECT_EQ(Direction2D(Direction2D::RIGHT).dx(), 1);
  EXPECT_EQ(Direction2D(Direction2D::RIGHT).dy(), 0);

  EXPECT_EQ(Direction2D(Direction2D::UR).dx(), 1);
  EXPECT_EQ(Direction2D(Direction2D::UR).dy(), -1);

  EXPECT_EQ(Direction2D(Direction2D::UL).dx(), -1);
  EXPECT_EQ(Direction2D(Direction2D::UL).dy(), -1);

  EXPECT_EQ(Direction2D(Direction2D::DR).dx(), 1);
  EXPECT_EQ(Direction2D(Direction2D::DR).dy(), 1);

  EXPECT_EQ(Direction2D(Direction2D::DL).dx(), -1);
  EXPECT_EQ(Direction2D(Direction2D::DL).dy(), 1);
}

TEST(Direction2D, Opposite) {
  EXPECT_EQ(Direction2D(Direction2D::UP).opposite(), Direction2D::DOWN);
  EXPECT_EQ(Direction2D(Direction2D::DOWN).opposite(), Direction2D::UP);
  EXPECT_EQ(Direction2D(Direction2D::LEFT).opposite(), Direction2D::RIGHT);
  EXPECT_EQ(Direction2D(Direction2D::RIGHT).opposite(), Direction2D::LEFT);
  EXPECT_EQ(Direction2D(Direction2D::UR).opposite(), Direction2D::DL);
  EXPECT_EQ(Direction2D(Direction2D::UL).opposite(), Direction2D::DR);
  EXPECT_EQ(Direction2D(Direction2D::DR).opposite(), Direction2D::UL);
  EXPECT_EQ(Direction2D(Direction2D::DL).opposite(), Direction2D::UR);
}

TEST(Direction2D, OrthogonalDirs) {
  auto up_ortho = Direction2D(Direction2D::UP).orthogonal_dirs();
  EXPECT_EQ(up_ortho[0], Direction2D::LEFT);
  EXPECT_EQ(up_ortho[1], Direction2D::RIGHT);

  auto down_ortho = Direction2D(Direction2D::DOWN).orthogonal_dirs();
  EXPECT_EQ(down_ortho[0], Direction2D::LEFT);
  EXPECT_EQ(down_ortho[1], Direction2D::RIGHT);

  auto left_ortho = Direction2D(Direction2D::LEFT).orthogonal_dirs();
  EXPECT_EQ(left_ortho[0], Direction2D::UP);
  EXPECT_EQ(left_ortho[1], Direction2D::DOWN);

  auto right_ortho = Direction2D(Direction2D::RIGHT).orthogonal_dirs();
  EXPECT_EQ(right_ortho[0], Direction2D::UP);
  EXPECT_EQ(right_ortho[1], Direction2D::DOWN);
}

TEST(Direction2D, OrthogonalTo) {
  EXPECT_TRUE(Direction2D(Direction2D::UP).orthogonal_to(Direction2D::LEFT));
  EXPECT_TRUE(Direction2D(Direction2D::UP).orthogonal_to(Direction2D::RIGHT));
  EXPECT_TRUE(Direction2D(Direction2D::DOWN).orthogonal_to(Direction2D::LEFT));
  EXPECT_TRUE(Direction2D(Direction2D::DOWN).orthogonal_to(Direction2D::RIGHT));
  EXPECT_TRUE(Direction2D(Direction2D::LEFT).orthogonal_to(Direction2D::UP));
  EXPECT_TRUE(Direction2D(Direction2D::LEFT).orthogonal_to(Direction2D::DOWN));

  EXPECT_FALSE(Direction2D(Direction2D::UP).orthogonal_to(Direction2D::UP));
  EXPECT_FALSE(Direction2D(Direction2D::UP).orthogonal_to(Direction2D::DOWN));
  EXPECT_FALSE(Direction2D(Direction2D::LEFT).orthogonal_to(Direction2D::RIGHT));
  EXPECT_FALSE(Direction2D(Direction2D::LEFT).orthogonal_to(Direction2D::LEFT));
}

// =============================================================================
// Extent2D tests
// =============================================================================

TEST(Extent2D, DefaultConstruction) {
  Extent2D e;
  EXPECT_EQ(e.minx, std::numeric_limits<double>::infinity());
  EXPECT_EQ(e.maxx, -std::numeric_limits<double>::infinity());
  EXPECT_EQ(e.miny, std::numeric_limits<double>::infinity());
  EXPECT_EQ(e.maxy, -std::numeric_limits<double>::infinity());
}

TEST(Extent2D, Contains) {
  Extent2D e{0.0, 10.0, 0.0, 10.0};
  EXPECT_TRUE(e.contains(5.0, 5.0));
  EXPECT_TRUE(e.contains(0.0, 0.0));    // On boundary
  EXPECT_TRUE(e.contains(10.0, 10.0));  // On boundary
  EXPECT_FALSE(e.contains(-1.0, 5.0));
  EXPECT_FALSE(e.contains(11.0, 5.0));
  EXPECT_FALSE(e.contains(5.0, -1.0));
  EXPECT_FALSE(e.contains(5.0, 11.0));
}

TEST(Extent2D, Grow) {
  Extent2D a{0.0, 5.0, 0.0, 5.0};
  Extent2D b{3.0, 10.0, 3.0, 10.0};
  a.grow(b);
  EXPECT_DOUBLE_EQ(a.minx, 0.0);
  EXPECT_DOUBLE_EQ(a.maxx, 10.0);
  EXPECT_DOUBLE_EQ(a.miny, 0.0);
  EXPECT_DOUBLE_EQ(a.maxy, 10.0);
}

TEST(Extent2D, GrowNonOverlapping) {
  Extent2D a{0.0, 1.0, 0.0, 1.0};
  Extent2D b{5.0, 6.0, 5.0, 6.0};
  a.grow(b);
  EXPECT_DOUBLE_EQ(a.minx, 0.0);
  EXPECT_DOUBLE_EQ(a.maxx, 6.0);
  EXPECT_DOUBLE_EQ(a.miny, 0.0);
  EXPECT_DOUBLE_EQ(a.maxy, 6.0);
}

// =============================================================================
// Extent3D tests
// =============================================================================

TEST(Extent3D, GrowByPoint) {
  Extent3D e;
  e.grow(1.0, 2.0, 3.0);
  EXPECT_DOUBLE_EQ(e.minx, 1.0);
  EXPECT_DOUBLE_EQ(e.maxx, 1.0);
  EXPECT_DOUBLE_EQ(e.miny, 2.0);
  EXPECT_DOUBLE_EQ(e.maxy, 2.0);
  EXPECT_DOUBLE_EQ(e.minz, 3.0);
  EXPECT_DOUBLE_EQ(e.maxz, 3.0);

  e.grow(0.0, 0.0, 0.0);
  EXPECT_DOUBLE_EQ(e.minx, 0.0);
  EXPECT_DOUBLE_EQ(e.maxx, 1.0);
  EXPECT_DOUBLE_EQ(e.minz, 0.0);
  EXPECT_DOUBLE_EQ(e.maxz, 3.0);
}

TEST(Extent3D, GrowByBorder) {
  Extent3D e(0.0, 10.0, 0.0, 10.0, 0.0, 10.0);
  e.grow(2.0);
  EXPECT_DOUBLE_EQ(e.minx, -2.0);
  EXPECT_DOUBLE_EQ(e.maxx, 12.0);
  EXPECT_DOUBLE_EQ(e.miny, -2.0);
  EXPECT_DOUBLE_EQ(e.maxy, 12.0);
  EXPECT_DOUBLE_EQ(e.minz, -2.0);
  EXPECT_DOUBLE_EQ(e.maxz, 12.0);
}

TEST(Extent3D, GrowByExtent) {
  Extent3D a(0.0, 5.0, 0.0, 5.0, 0.0, 5.0);
  Extent3D b(3.0, 10.0, 3.0, 10.0, 3.0, 10.0);
  a.grow(b);
  EXPECT_DOUBLE_EQ(a.minx, 0.0);
  EXPECT_DOUBLE_EQ(a.maxx, 10.0);
  EXPECT_DOUBLE_EQ(a.miny, 0.0);
  EXPECT_DOUBLE_EQ(a.maxy, 10.0);
  EXPECT_DOUBLE_EQ(a.minz, 0.0);
  EXPECT_DOUBLE_EQ(a.maxz, 10.0);
}

TEST(Extent3D, Intersects) {
  Extent3D a(0.0, 5.0, 0.0, 5.0, 0.0, 5.0);
  Extent3D b(3.0, 10.0, 3.0, 10.0, 3.0, 10.0);
  EXPECT_TRUE(a.intersects(b));
  EXPECT_TRUE(b.intersects(a));

  Extent3D c(6.0, 10.0, 6.0, 10.0, 6.0, 10.0);
  EXPECT_FALSE(a.intersects(c));
  EXPECT_FALSE(c.intersects(a));
}

TEST(Extent3D, IntersectsEdge) {
  // Touching at a boundary IS considered an intersection (uses strict < and >)
  Extent3D a(0.0, 5.0, 0.0, 5.0, 0.0, 5.0);
  Extent3D b(5.0, 10.0, 0.0, 5.0, 0.0, 5.0);
  EXPECT_TRUE(a.intersects(b));

  // Just past the boundary is NOT an intersection
  Extent3D c(5.1, 10.0, 5.1, 10.0, 5.1, 10.0);
  EXPECT_FALSE(a.intersects(c));
}

TEST(Extent3D, Center) {
  Extent3D e(0.0, 10.0, 2.0, 8.0, -4.0, 6.0);
  Coordinate3D<double> c = e.center();
  EXPECT_DOUBLE_EQ(c.x(), 5.0);
  EXPECT_DOUBLE_EQ(c.y(), 5.0);
  EXPECT_DOUBLE_EQ(c.z(), 1.0);
}

TEST(Extent3D, MaxExtent) {
  Extent3D e(0.0, 10.0, 0.0, 5.0, 0.0, 3.0);
  EXPECT_DOUBLE_EQ(e.max_extent(), 10.0);

  Extent3D e2(0.0, 3.0, 0.0, 5.0, 0.0, 20.0);
  EXPECT_DOUBLE_EQ(e2.max_extent(), 20.0);
}

TEST(Extent3D, Intersection) {
  Extent3D a(0.0, 10.0, 0.0, 10.0, 0.0, 10.0);
  Extent3D b(5.0, 15.0, 5.0, 15.0, 5.0, 15.0);
  Extent3D result = a.intersection(b);
  EXPECT_DOUBLE_EQ(result.minx, 5.0);
  EXPECT_DOUBLE_EQ(result.maxx, 10.0);
  EXPECT_DOUBLE_EQ(result.miny, 5.0);
  EXPECT_DOUBLE_EQ(result.maxy, 10.0);
  EXPECT_DOUBLE_EQ(result.minz, 5.0);
  EXPECT_DOUBLE_EQ(result.maxz, 10.0);
}

TEST(Extent3D, NotEqual) {
  Extent3D a(0.0, 10.0, 0.0, 10.0, 0.0, 10.0);
  Extent3D b(0.0, 10.0, 0.0, 10.0, 0.0, 10.0);
  Extent3D c(1.0, 10.0, 0.0, 10.0, 0.0, 10.0);
  EXPECT_FALSE(a != b);
  EXPECT_TRUE(a != c);
}

TEST(Extent3D, SubtractOffset) {
  Extent3D e(5.0, 15.0, 5.0, 15.0, 5.0, 15.0);
  Coordinate3D<double> offset(5.0, 5.0, 5.0);
  Extent3D result = e - offset;
  EXPECT_DOUBLE_EQ(result.minx, 0.0);
  EXPECT_DOUBLE_EQ(result.maxx, 10.0);
  EXPECT_DOUBLE_EQ(result.miny, 0.0);
  EXPECT_DOUBLE_EQ(result.maxy, 10.0);
  EXPECT_DOUBLE_EQ(result.minz, 0.0);
  EXPECT_DOUBLE_EQ(result.maxz, 10.0);
}

// =============================================================================
// LineCoord2D tests
// =============================================================================

TEST(LineCoord2D, StartEnd) {
  LineCoord2D<size_t> lc(3, 4, Direction2D::RIGHT);
  EXPECT_EQ(lc.start().x(), 3);
  EXPECT_EQ(lc.start().y(), 4);
  EXPECT_EQ(lc.end().x(), 4);
  EXPECT_EQ(lc.end().y(), 4);
  EXPECT_EQ(lc.dir(), Direction2D::RIGHT);

  LineCoord2D<size_t> lc2(3, 4, Direction2D::DOWN);
  EXPECT_EQ(lc2.end().x(), 3);
  EXPECT_EQ(lc2.end().y(), 5);
}

// =============================================================================
// Coordinate3D tests
// =============================================================================

TEST(Coordinate3D, Construction) {
  Coordinate3D<double> c(1.0, 2.0, 3.0);
  EXPECT_DOUBLE_EQ(c.x(), 1.0);
  EXPECT_DOUBLE_EQ(c.y(), 2.0);
  EXPECT_DOUBLE_EQ(c.z(), 3.0);
}
