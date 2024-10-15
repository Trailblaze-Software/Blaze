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

  std::vector<Contour> contours = generate_contours(
      grid, ContourConfigs{{{"normal", ContourConfig{au::meters(1.0), 1, RGBColor(0, 0, 0, 0),
                                                     au::milli(au::meters)(0.14)}}}});
  ASSERT_EQ(contours.size(), 1);
  ASSERT_EQ(contours[0].points().size(), 4);
}

TEST(ContourGen, ContourGen2) {
  std::vector<std::vector<double>> data = {{0.5, 0.5, 0.5, 0.5, 0.5}, {0.5, 1.5, 1.5, 1.5, 0.5},
                                           {0.5, 1.5, 2.1, 1.5, 0.5}, {0.5, 1.5, 2.1, 1.5, 0.5},
                                           {0.5, 1.5, 1.5, 1.5, 0.5}, {0.5, 0.5, 0.5, 0.5, 0.5}};
  TestGrid grid(data);

  std::vector<Contour> contours = generate_contours(
      grid, ContourConfigs{{{"normal", ContourConfig{au::meters(1.0), 1, RGBColor(0, 0, 0, 0),
                                                     au::milli(au::meters)(0.14)}}}});
  ASSERT_EQ(contours.size(), 2);
  ASSERT_EQ(contours[0].points().size(), 14);
  ASSERT_EQ(contours[1].points().size(), 6);
}
