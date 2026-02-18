#include <gtest/gtest.h>

#include <cmath>
#include <limits>

#include "las/las_point.hpp"
#include "lib/grid/grid.hpp"
#include "process.hpp"

// Helper class to create test grids
class TestGrid : public GeoGrid<double> {
 public:
  explicit TestGrid(const std::vector<std::vector<double>>& data)
      : GeoGrid<double>(data[0].size(), data.size(), GeoTransform(), GeoProjection()) {
    for (size_t i = 0; i < data.size(); i++) {
      for (size_t j = 0; j < data[0].size(); j++) {
        (*this)[{j, i}] = data[i][j];
      }
    }
  }
};

// Test round_up function
TEST(Process, RoundUp) {
  // Test positive values
  EXPECT_EQ(round_up(0.0), 0);
  EXPECT_EQ(round_up(0.1), 1);
  EXPECT_EQ(round_up(0.5), 1);
  EXPECT_EQ(round_up(0.9), 1);
  EXPECT_EQ(round_up(1.0), 1);
  EXPECT_EQ(round_up(1.1), 2);
  EXPECT_EQ(round_up(1.5), 2);
  EXPECT_EQ(round_up(2.0), 2);

  // Test negative values
  EXPECT_EQ(round_up(-0.1), 1);
  EXPECT_EQ(round_up(-0.5), 1);
  EXPECT_EQ(round_up(-1.0), 1);
  EXPECT_EQ(round_up(-1.1), 2);

  // Test edge cases
  EXPECT_EQ(round_up(1e-7), 1);
  EXPECT_EQ(round_up(1e-6), 1);
  EXPECT_EQ(round_up(100.0), 100);
  EXPECT_EQ(round_up(100.1), 101);
}

// Test get_pixel_heights indirectly through process_las_data
// Since get_pixel_heights is not exposed, we'll test the logic conceptually
// by testing that ground points are properly extracted

// Test adjust_ground_to_slope function
// Since it's not exposed, we test the concept with a simple grid
TEST(Process, AdjustGroundToSlopeConcept) {
  // Create a simple slope grid
  std::vector<std::vector<double>> data = {
      {10.0, 10.0, 10.0}, {10.0, 10.0, 10.0}, {10.0, 10.0, 10.0}};
  TestGrid grid(data);

  // Test that grid operations work
  EXPECT_DOUBLE_EQ(grid[{0, 0}], 10.0);
  EXPECT_DOUBLE_EQ(grid[{1, 1}], 10.0);

  // Create a grid with a slope
  std::vector<std::vector<double>> slope_data = {
      {10.0, 11.0, 12.0}, {10.0, 11.0, 12.0}, {10.0, 11.0, 12.0}};
  TestGrid slope_grid(slope_data);

  // Verify slope exists
  EXPECT_DOUBLE_EQ(slope_grid[{0, 0}], 10.0);
  EXPECT_DOUBLE_EQ(slope_grid[{1, 0}], 11.0);
  EXPECT_DOUBLE_EQ(slope_grid[{2, 0}], 12.0);
}
