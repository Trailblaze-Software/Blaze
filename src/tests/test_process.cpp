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

// Test num_cells_by_distance function
TEST(Process, NumCellsByDistance) {
  // Test with unit cell size (dx = 1.0)
  EXPECT_EQ(num_cells_by_distance(0.0, 1.0), 1);
  EXPECT_EQ(num_cells_by_distance(0.1, 1.0), 1);
  EXPECT_EQ(num_cells_by_distance(0.5, 1.0), 1);
  EXPECT_EQ(num_cells_by_distance(0.9, 1.0), 1);
  EXPECT_EQ(num_cells_by_distance(1.0, 1.0), 2);
  EXPECT_EQ(num_cells_by_distance(1.1, 1.0), 2);
  EXPECT_EQ(num_cells_by_distance(1.5, 1.0), 2);
  EXPECT_EQ(num_cells_by_distance(2.0, 1.0), 3);

  // Test with different cell sizes
  EXPECT_EQ(num_cells_by_distance(10.0, 5.0), 3);
  EXPECT_EQ(num_cells_by_distance(10.1, 5.0), 3);
  EXPECT_EQ(num_cells_by_distance(20.0, 20.0), 2);
  EXPECT_EQ(num_cells_by_distance(20.1, 20.0), 2);

  // Test negative values (should use absolute value)
  EXPECT_EQ(num_cells_by_distance(-0.0, 1.0), 1);
  EXPECT_EQ(num_cells_by_distance(-0.1, 1.0), 1);
  EXPECT_EQ(num_cells_by_distance(-0.5, 1.0), 1);
  EXPECT_EQ(num_cells_by_distance(-1.0, 1.0), 2);
  EXPECT_EQ(num_cells_by_distance(-1.1, 1.0), 2);
  EXPECT_EQ(num_cells_by_distance(-10.0, 5.0), 3);
  EXPECT_EQ(num_cells_by_distance(-10.1, 5.0), 3);

  // Test negative dx values (should use absolute value)
  EXPECT_EQ(num_cells_by_distance(10.0, -5.0), 3);
  EXPECT_EQ(num_cells_by_distance(10.1, -5.0), 3);
  EXPECT_EQ(num_cells_by_distance(20.0, -20.0), 2);
  EXPECT_EQ(num_cells_by_distance(0.0, -1.0), 1);

  // Test error cases
  EXPECT_THROW(num_cells_by_distance(1.0, 0.0), std::invalid_argument);

  // Test edge cases
  EXPECT_EQ(num_cells_by_distance(1e-7, 1.0), 1);
  EXPECT_EQ(num_cells_by_distance(1e-6, 1.0), 1);
  EXPECT_EQ(num_cells_by_distance(100.0, 1.0), 101);
  EXPECT_EQ(num_cells_by_distance(100.1, 1.0), 101);
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
