#include <gtest/gtest.h>

#include <set>
#include <vector>

#include "config_input/config_input.hpp"
#include "contour/contour.hpp"
#include "contour/contour_gen.hpp"
#include "geometry/polygon.hpp"
#include "isom/colors.hpp"
#include "lib/grid/grid.hpp"

TEST(ContourGen, ContourGen) {
  std::vector<std::vector<double>> data = {{0.5, 0.5, 0.5}, {0.5, 1.5, 0.5}, {0.5, 0.5, 0.5}};
  GeoGrid<double> grid(data);

  ContourConfigs configs({{"normal", ContourConfig{1.0, 1, RGBColor(0, 0, 0, 0), 0.14}}});
  std::vector<Contour> contours = generate_contours(
      grid, ContourConfigs({{"normal", ContourConfig{1.0, 1, RGBColor(0, 0, 0, 0), 0.14}}}),
      ProgressTracker());
  EXPECT_EQ(contours.size(), 1);
  EXPECT_EQ(contours[0].points().size(), 5);
  EXPECT_DOUBLE_EQ(contours[0].height(), 1.0);
  EXPECT_TRUE(contours[0].is_loop());
}

TEST(ContourGen, ContourGen2) {
  std::vector<std::vector<double>> data = {{0.5, 0.5, 0.5, 0.5, 0.5}, {0.5, 1.5, 1.5, 1.5, 0.5},
                                           {0.5, 1.5, 2.1, 1.5, 0.5}, {0.5, 1.5, 2.1, 1.5, 0.5},
                                           {0.5, 1.5, 1.5, 1.5, 1.5}, {0.5, 0.5, 0.5, 1.5, 1.5}};
  GeoGrid<double> grid(data);

  std::vector<Contour> contours = generate_contours(
      grid, ContourConfigs{{{"normal", ContourConfig{1.0, 1, RGBColor(0, 0, 0, 0), 0.14}}}},
      ProgressTracker());
  EXPECT_EQ(contours.size(), 2);

  EXPECT_EQ(contours[0].points().size(), 14);
  EXPECT_DOUBLE_EQ(contours[0].height(), 1.0);
  EXPECT_FALSE(contours[0].is_loop());

  EXPECT_EQ(contours[1].points().size(), 7);
  EXPECT_DOUBLE_EQ(contours[1].height(), 2.0);
  EXPECT_TRUE(contours[1].is_loop());
}

TEST(IdentifyContoursAtHeights, SingleHeightCrossing) {
  std::vector<std::vector<float>> data = {{0.3f, 0.7f}, {0.3f, 0.7f}};
  GeoGrid<float> grid(data);

  std::set<double> heights = {0.5};
  GridGraph<std::set<double>> result = identify_contours_at_heights(grid, heights);

  LineCoord2D<size_t> crossing_edge({0, 0}, Direction2D::RIGHT);
  EXPECT_TRUE(result.in_bounds(crossing_edge));
  EXPECT_TRUE(result[crossing_edge].contains(0.5));

  LineCoord2D<size_t> crossing_edge2({0, 1}, Direction2D::RIGHT);
  EXPECT_TRUE(result.in_bounds(crossing_edge2));
  EXPECT_TRUE(result[crossing_edge2].contains(0.5));
}

TEST(IdentifyContoursAtHeights, NoCrossing) {
  std::vector<std::vector<float>> data = {{0.1f, 0.2f}, {0.1f, 0.2f}};
  GeoGrid<float> grid(data);

  std::set<double> heights = {0.5};
  GridGraph<std::set<double>> result = identify_contours_at_heights(grid, heights);

  for (size_t i = 0; i < result.height(); i++) {
    for (size_t j = 0; j < result.width(); j++) {
      for (Direction2D dir : {Direction2D::DOWN, Direction2D::RIGHT}) {
        LineCoord2D<size_t> edge({j, i}, dir);
        if (result.in_bounds(edge)) {
          EXPECT_TRUE(result[edge].empty());
        }
      }
    }
  }
}

TEST(IdentifyContoursAtHeights, MultipleHeights) {
  std::vector<std::vector<float>> data = {{0.1f, 0.4f, 0.8f}};
  GeoGrid<float> grid(data);

  std::set<double> heights = {0.25, 0.5};
  GridGraph<std::set<double>> result = identify_contours_at_heights(grid, heights);

  LineCoord2D<size_t> edge1({0, 0}, Direction2D::RIGHT);
  EXPECT_TRUE(result[edge1].contains(0.25));
  EXPECT_FALSE(result[edge1].contains(0.5));

  LineCoord2D<size_t> edge2({1, 0}, Direction2D::RIGHT);
  EXPECT_FALSE(result[edge2].contains(0.25));
  EXPECT_TRUE(result[edge2].contains(0.5));
}

TEST(IdentifyContoursAtHeights, ExactThresholdValue) {
  std::vector<std::vector<float>> data = {{0.3f, 0.5f}};
  GeoGrid<float> grid(data);

  std::set<double> heights = {0.5};
  GridGraph<std::set<double>> result = identify_contours_at_heights(grid, heights);

  LineCoord2D<size_t> edge({0, 0}, Direction2D::RIGHT);
  EXPECT_TRUE(result[edge].contains(0.5));
}

TEST(IdentifyContoursAtHeights, MinExactlyAtThreshold) {
  std::vector<std::vector<float>> data = {{0.5f, 0.7f}};
  GeoGrid<float> grid(data);

  std::set<double> heights = {0.5};
  GridGraph<std::set<double>> result = identify_contours_at_heights(grid, heights);

  LineCoord2D<size_t> edge({0, 0}, Direction2D::RIGHT);
  EXPECT_FALSE(result[edge].contains(0.5));
}

TEST(GenerateContoursAtHeights, SinglePeakClosedLoop) {
  std::vector<std::vector<float>> data = {
      {0.6f, 0.6f},
      {0.6f, 0.6f},
  };
  GeoGrid<float> grid(data);

  std::vector<double> heights = {0.5};
  auto contours_by_height = generate_contours_at_heights(grid, heights, 1, 0.0f);

  EXPECT_EQ(contours_by_height.size(), 1u);
  EXPECT_TRUE(contours_by_height.contains(0.5));

  const auto& contours = contours_by_height.at(0.5);
  ASSERT_EQ(contours.size(), 1u);

  const Contour& c = contours[0];
  EXPECT_TRUE(c.is_loop());
  EXPECT_EQ(c.points().size(), 9u);
  EXPECT_DOUBLE_EQ(c.height(), 0.5);
}

TEST(GenerateContoursAtHeights, EdgeContoursAreClosed) {
  std::vector<std::vector<float>> data = {
      {0.7f, 0.7f, 0.2f},
      {0.7f, 0.7f, 0.2f},
      {0.2f, 0.2f, 0.2f},
  };
  GeoGrid<float> grid(data);

  std::vector<double> heights = {0.5};
  auto contours_by_height = generate_contours_at_heights(grid, heights, 1, 0.0f);

  EXPECT_EQ(contours_by_height.size(), 1u);
  const auto& contours = contours_by_height.at(0.5);

  for (const Contour& c : contours) {
    EXPECT_TRUE(c.is_loop()) << "Contour at height " << c.height() << " should be closed";
  }
}

TEST(GenerateContoursAtHeights, MultipleDisjointPatches) {
  std::vector<std::vector<float>> data = {
      {0.7f, 0.2f, 0.7f},
  };
  GeoGrid<float> grid(data);

  std::vector<double> heights = {0.5};
  auto contours_by_height = generate_contours_at_heights(grid, heights, 3, 0.0f);

  const auto& contours = contours_by_height.at(0.5);
  EXPECT_EQ(contours.size(), 2u);

  for (const Contour& c : contours) {
    EXPECT_TRUE(c.is_loop());
    EXPECT_EQ(c.points().size(), 5u);
  }
}

TEST(GenerateContoursAtHeights, AllZerosNoContours) {
  std::vector<std::vector<float>> data = {
      {0.0f, 0.0f, 0.0f},
      {0.0f, 0.0f, 0.0f},
      {0.0f, 0.0f, 0.0f},
  };
  GeoGrid<float> grid(data);

  std::vector<double> heights = {0.5};
  auto contours_by_height = generate_contours_at_heights(grid, heights, 1, 0.0f);

  EXPECT_EQ(contours_by_height.count(0.5), 0u);

  contours_by_height = generate_contours_at_heights(grid, heights, 1, 1.0f);
  EXPECT_EQ(contours_by_height.count(0.5), 1u);
  EXPECT_EQ(contours_by_height.at(0.5).size(), 1u);
  EXPECT_EQ(contours_by_height.at(0.5)[0].points().size(), 13u);
}

TEST(GenerateContoursAtHeights, MultipleHeights) {
  std::vector<std::vector<float>> data = {
      {0.3f, 0.5f, 0.3f},
      {0.5f, 0.9f, 0.5f},
      {0.3f, 0.5f, 0.3f},
  };
  GeoGrid<float> grid(data);

  std::vector<double> heights = {0.2, 0.4, 0.7};
  auto contours_by_height = generate_contours_at_heights(grid, heights, 3, 0.0f);

  EXPECT_EQ(contours_by_height.size(), 3u);
  EXPECT_TRUE(contours_by_height.contains(0.2));
  EXPECT_TRUE(contours_by_height.contains(0.4));
  EXPECT_TRUE(contours_by_height.contains(0.7));
}

TEST(GenerateContoursAtHeights, FilteredByMinPoints) {
  std::vector<std::vector<float>> data = {{0.8f}};
  GeoGrid<float> grid(data);

  std::vector<double> heights = {0.5};

  auto contours_low = generate_contours_at_heights(grid, heights, 1, 0.0f);
  EXPECT_EQ(contours_low[0.5].size(), 1u);

  auto contours_high = generate_contours_at_heights(grid, heights, 100, 0.0f);
  EXPECT_EQ(contours_high[0.5].size(), 0u);
}

TEST(GenerateContoursAtHeights, OrientsDonutRings) {
  std::vector<std::vector<float>> data = {
      {0.8f, 0.8f, 0.8f, 0.8f, 0.8f},
      {0.8f, 0.0f, 0.0f, 0.0f, 0.8f},
      {0.8f, 0.0f, 0.0f, 0.0f, 0.8f},
      {0.8f, 0.8f, 0.8f, 0.8f, 0.8f},
  };
  GeoGrid<float> grid(data);

  auto contours_by_height = generate_contours_at_heights(grid, {0.5}, 3, 0.0f);

  ASSERT_EQ(contours_by_height[0.5].size(), 2u);
  const Contour* outer = nullptr;
  const Contour* inner = nullptr;
  for (const Contour& c : contours_by_height[0.5]) {
    if (signed_area(c.points()) > 0.0) {
      outer = &c;
    } else if (signed_area(c.points()) < 0.0) {
      inner = &c;
    }
  }
  ASSERT_NE(outer, nullptr);
  ASSERT_NE(inner, nullptr);
  EXPECT_TRUE(point_in_ring(inner->points()[0], outer->points()));
}
