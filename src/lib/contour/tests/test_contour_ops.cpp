#include <gtest/gtest.h>

#include <cmath>
#include <vector>

#include "contour/contour.hpp"
#include "contour/contour_gen.hpp"
#include "polyline/polyline.hpp"

// =============================================================================
// join_contours tests
// =============================================================================

TEST(ContourOps, JoinContoursAppend) {
  // Two contours at the same height that can be joined end-to-end
  // a: (0,0) -> (1,0)   b: (1,0) -> (2,0)
  // a.back = (1,0), b.front = (1,0) -> should append b to a
  std::vector<Coordinate2D<double>> pts_a = {Coordinate2D<double>(0.0, 0.0),
                                             Coordinate2D<double>(1.0, 0.0)};
  std::vector<Coordinate2D<double>> pts_b = {Coordinate2D<double>(1.0, 0.0),
                                             Coordinate2D<double>(2.0, 0.0)};

  std::vector<Contour> contours;
  contours.emplace_back(Contour(10.0, std::move(pts_a)));
  contours.emplace_back(Contour(10.0, std::move(pts_b)));

  std::vector<Contour> joined = join_contours(std::move(contours));
  EXPECT_EQ(joined.size(), 1);
  EXPECT_EQ(joined[0].points().size(), 3);
  EXPECT_DOUBLE_EQ(joined[0].points()[0].x(), 0.0);
  EXPECT_DOUBLE_EQ(joined[0].points()[1].x(), 1.0);
  EXPECT_DOUBLE_EQ(joined[0].points()[2].x(), 2.0);
}

TEST(ContourOps, JoinContoursPrepend) {
  // a: (1,0) -> (2,0)   b: (0,0) -> (1,0)
  // a.front = (1,0), b.back = (1,0) -> should prepend b to a
  std::vector<Coordinate2D<double>> pts_a = {Coordinate2D<double>(1.0, 0.0),
                                             Coordinate2D<double>(2.0, 0.0)};
  std::vector<Coordinate2D<double>> pts_b = {Coordinate2D<double>(0.0, 0.0),
                                             Coordinate2D<double>(1.0, 0.0)};

  std::vector<Contour> contours;
  contours.emplace_back(Contour(10.0, std::move(pts_a)));
  contours.emplace_back(Contour(10.0, std::move(pts_b)));

  std::vector<Contour> joined = join_contours(std::move(contours));
  EXPECT_EQ(joined.size(), 1);
  EXPECT_EQ(joined[0].points().size(), 3);
  EXPECT_DOUBLE_EQ(joined[0].points().front().x(), 0.0);
  EXPECT_DOUBLE_EQ(joined[0].points().back().x(), 2.0);
}

TEST(ContourOps, JoinContoursNoJoin) {
  // Two contours that are far apart - should not join
  std::vector<Coordinate2D<double>> pts_a = {Coordinate2D<double>(0.0, 0.0),
                                             Coordinate2D<double>(1.0, 0.0)};
  std::vector<Coordinate2D<double>> pts_b = {Coordinate2D<double>(100.0, 0.0),
                                             Coordinate2D<double>(101.0, 0.0)};

  std::vector<Contour> contours;
  contours.emplace_back(Contour(10.0, std::move(pts_a)));
  contours.emplace_back(Contour(10.0, std::move(pts_b)));

  std::vector<Contour> joined = join_contours(std::move(contours));
  EXPECT_EQ(joined.size(), 2);
}

TEST(ContourOps, JoinContoursEmpty) {
  std::vector<Contour> contours;
  std::vector<Contour> joined = join_contours(std::move(contours));
  EXPECT_EQ(joined.size(), 0);
}

TEST(ContourOps, JoinContoursSingle) {
  std::vector<Coordinate2D<double>> pts = {Coordinate2D<double>(0.0, 0.0),
                                           Coordinate2D<double>(1.0, 0.0)};
  std::vector<Contour> contours;
  contours.emplace_back(Contour(10.0, std::move(pts)));

  std::vector<Contour> joined = join_contours(std::move(contours));
  EXPECT_EQ(joined.size(), 1);
  EXPECT_EQ(joined[0].points().size(), 2);
}

TEST(ContourOps, JoinContoursChain) {
  // Three contours forming a chain
  std::vector<Coordinate2D<double>> pts_a = {Coordinate2D<double>(0.0, 0.0),
                                             Coordinate2D<double>(1.0, 0.0)};
  std::vector<Coordinate2D<double>> pts_b = {Coordinate2D<double>(1.0, 0.0),
                                             Coordinate2D<double>(2.0, 0.0)};
  std::vector<Coordinate2D<double>> pts_c = {Coordinate2D<double>(2.0, 0.0),
                                             Coordinate2D<double>(3.0, 0.0)};

  std::vector<Contour> contours;
  contours.emplace_back(Contour(10.0, std::move(pts_a)));
  contours.emplace_back(Contour(10.0, std::move(pts_b)));
  contours.emplace_back(Contour(10.0, std::move(pts_c)));

  std::vector<Contour> joined = join_contours(std::move(contours));
  EXPECT_EQ(joined.size(), 1);
  EXPECT_DOUBLE_EQ(joined[0].points().front().x(), 0.0);
  EXPECT_DOUBLE_EQ(joined[0].points().back().x(), 3.0);
}

// =============================================================================
// trim_contours tests
// =============================================================================

TEST(ContourOps, TrimContoursAllInside) {
  std::vector<Coordinate2D<double>> pts = {
      Coordinate2D<double>(1.0, 1.0), Coordinate2D<double>(2.0, 1.0),
      Coordinate2D<double>(3.0, 1.0), Coordinate2D<double>(4.0, 1.0)};
  Contour c(10.0, std::move(pts));
  std::vector<Contour> contours = {std::move(c)};

  Extent2D bounds{0.0, 5.0, 0.0, 5.0};
  std::vector<Contour> trimmed = trim_contours(contours, bounds);
  EXPECT_EQ(trimmed.size(), 1);
  EXPECT_EQ(trimmed[0].points().size(), 4);
}

TEST(ContourOps, TrimContoursAllOutside) {
  std::vector<Coordinate2D<double>> pts = {Coordinate2D<double>(10.0, 10.0),
                                           Coordinate2D<double>(11.0, 10.0),
                                           Coordinate2D<double>(12.0, 10.0)};
  Contour c(10.0, std::move(pts));
  std::vector<Contour> contours = {std::move(c)};

  Extent2D bounds{0.0, 5.0, 0.0, 5.0};
  std::vector<Contour> trimmed = trim_contours(contours, bounds);
  EXPECT_EQ(trimmed.size(), 0);
}

TEST(ContourOps, TrimContoursSplit) {
  // Contour crosses boundary: inside, outside, inside -> should become 2 contours
  std::vector<Coordinate2D<double>> pts = {
      Coordinate2D<double>(1.0, 1.0), Coordinate2D<double>(2.0, 1.0),
      Coordinate2D<double>(6.0, 1.0),  // outside
      Coordinate2D<double>(3.0, 1.0), Coordinate2D<double>(4.0, 1.0)};
  Contour c(10.0, std::move(pts));
  std::vector<Contour> contours = {std::move(c)};

  Extent2D bounds{0.0, 5.0, 0.0, 5.0};
  std::vector<Contour> trimmed = trim_contours(contours, bounds);
  EXPECT_EQ(trimmed.size(), 2);
  EXPECT_EQ(trimmed[0].points().size(), 2);
  EXPECT_EQ(trimmed[1].points().size(), 2);
}

TEST(ContourOps, TrimContoursEmpty) {
  std::vector<Contour> contours;
  Extent2D bounds{0.0, 5.0, 0.0, 5.0};
  std::vector<Contour> trimmed = trim_contours(contours, bounds);
  EXPECT_EQ(trimmed.size(), 0);
}

// =============================================================================
// Contour::from_polyline / to_polyline tests
// =============================================================================

TEST(ContourOps, ContourToPolyline) {
  std::vector<Coordinate2D<double>> pts = {Coordinate2D<double>(0.0, 0.0),
                                           Coordinate2D<double>(1.0, 0.0),
                                           Coordinate2D<double>(2.0, 0.0)};
  Contour contour(15.0, std::move(pts));

  // Create a config that maps height 15.0 to "normal" (interval 5.0)
  ContourConfigs configs({{"normal", ContourConfig{5.0, 1, RGBColor(0, 0, 0, 0), 0.14}}});

  Polyline poly = contour.to_polyline(configs);
  EXPECT_EQ(poly.name, "15.000000");
  EXPECT_EQ(poly.vertices.size(), 3);
  EXPECT_EQ(poly.layer, "101_Contour");
}

TEST(ContourOps, ContourFromPolyline) {
  Polyline poly;
  poly.name = "25.5";
  poly.layer = "test";
  poly.vertices = {Coordinate2D<double>(0.0, 0.0), Coordinate2D<double>(1.0, 1.0),
                   Coordinate2D<double>(2.0, 2.0)};

  Contour c = Contour::from_polyline(poly);
  EXPECT_DOUBLE_EQ(c.height(), 25.5);
  EXPECT_EQ(c.points().size(), 3);
}

TEST(ContourOps, ContourFromPolylineInvalidName) {
  Polyline poly;
  poly.name = "not_a_number";
  poly.layer = "test";
  poly.vertices = {Coordinate2D<double>(0.0, 0.0)};

  Contour c = Contour::from_polyline(poly);
  // Should default to 0 height and empty points
  EXPECT_DOUBLE_EQ(c.height(), 0.0);
  EXPECT_EQ(c.points().size(), 0);
}

// =============================================================================
// Contour::push_back tests
// =============================================================================

TEST(ContourOps, PushBackCreatesLoop) {
  std::vector<Coordinate2D<double>> pts = {Coordinate2D<double>(0.0, 0.0),
                                           Coordinate2D<double>(1.0, 0.0),
                                           Coordinate2D<double>(1.0, 1.0)};
  Contour c(10.0, std::move(pts));
  EXPECT_FALSE(c.is_loop());

  c.push_back(Coordinate2D<double>(0.0, 0.0));
  EXPECT_TRUE(c.is_loop());
}

TEST(ContourOps, PushBackNotLoop) {
  std::vector<Coordinate2D<double>> pts = {Coordinate2D<double>(0.0, 0.0),
                                           Coordinate2D<double>(1.0, 0.0)};
  Contour c(10.0, std::move(pts));
  EXPECT_FALSE(c.is_loop());

  c.push_back(Coordinate2D<double>(2.0, 0.0));
  EXPECT_FALSE(c.is_loop());
}
