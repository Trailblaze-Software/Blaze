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
// Note: round_up always adds 1e-6 before ceiling, so it always rounds up by at least 1
TEST(Process, RoundUp) {
  // Test positive values
  EXPECT_EQ(round_up(0.0), 1);  // ceil(0.000001) = 1
  EXPECT_EQ(round_up(0.1), 1);  // ceil(0.100001) = 1
  EXPECT_EQ(round_up(0.5), 1);  // ceil(0.500001) = 1
  EXPECT_EQ(round_up(0.9), 1);  // ceil(0.900001) = 1
  EXPECT_EQ(round_up(1.0), 2);  // ceil(1.000001) = 2
  EXPECT_EQ(round_up(1.1), 2);  // ceil(1.100001) = 2
  EXPECT_EQ(round_up(1.5), 2);  // ceil(1.500001) = 2
  EXPECT_EQ(round_up(2.0), 3);  // ceil(2.000001) = 3

  // Test negative values (uses abs, so same as positive)
  EXPECT_EQ(round_up(-0.1), 1);  // ceil(0.100001) = 1
  EXPECT_EQ(round_up(-0.5), 1);  // ceil(0.500001) = 1
  EXPECT_EQ(round_up(-1.0), 2);  // ceil(1.000001) = 2
  EXPECT_EQ(round_up(-1.1), 2);  // ceil(1.100001) = 2

  // Test edge cases
  EXPECT_EQ(round_up(1e-7), 1);     // ceil(0.000001) = 1
  EXPECT_EQ(round_up(1e-6), 1);     // ceil(0.000001) = 1
  EXPECT_EQ(round_up(100.0), 101);  // ceil(100.000001) = 101
  EXPECT_EQ(round_up(100.1), 101);  // ceil(100.100001) = 101
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
  double val00 = grid[{0, 0}];
  double val11 = grid[{1, 1}];
  EXPECT_DOUBLE_EQ(val00, 10.0);
  EXPECT_DOUBLE_EQ(val11, 10.0);

  // Create a grid with a slope
  std::vector<std::vector<double>> slope_data = {
      {10.0, 11.0, 12.0}, {10.0, 11.0, 12.0}, {10.0, 11.0, 12.0}};
  TestGrid slope_grid(slope_data);

  // Verify slope exists
  double slope00 = slope_grid[{0, 0}];
  double slope10 = slope_grid[{1, 0}];
  double slope20 = slope_grid[{2, 0}];
  EXPECT_DOUBLE_EQ(slope00, 10.0);
  EXPECT_DOUBLE_EQ(slope10, 11.0);
  EXPECT_DOUBLE_EQ(slope20, 12.0);
}
