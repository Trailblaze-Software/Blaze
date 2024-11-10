#include <gtest/gtest.h>

#include "config_input/config_input.hpp"
#include "contour/contour.hpp"
#include "contour/contour_gen.hpp"
#include "isom/colors.hpp"
#include "lib/grid/grid.hpp"

class TestGrid : public GeoGrid<double> {
 public:
  explicit TestGrid(const std::vector<std::vector<double>> &data)
      : GeoGrid<double>(data[0].size(), data.size(), GeoTransform(), GeoProjection()) {
    for (size_t i = 0; i < data.size(); i++) {
      for (size_t j = 0; j < data[0].size(); j++) {
        (*this)[{j, i}] = data[i][j];
      }
    }
  }
};

TEST(ContourGen, ContourGen) {
  std::vector<std::vector<double>> data = {{0.5, 0.5, 0.5}, {0.5, 1.5, 0.5}, {0.5, 0.5, 0.5}};
  TestGrid grid(data);

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
  TestGrid grid(data);

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
