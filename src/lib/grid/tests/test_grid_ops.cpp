#include <gtest/gtest.h>

#include <cmath>
#include <limits>

#include "grid/grid.hpp"
#include "grid/grid_ops.hpp"
#include "utilities/progress_tracker.hpp"

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

// Test downsample function with MEAN method
TEST(GridOps, DownsampleMean) {
  std::vector<std::vector<double>> data = {{1.0, 2.0, 3.0, 4.0},
                                           {5.0, 6.0, 7.0, 8.0},
                                           {9.0, 10.0, 11.0, 12.0},
                                           {13.0, 14.0, 15.0, 16.0}};
  TestGrid grid(data);

  GeoGrid<double> downsampled = downsample(grid, 2, ProgressTracker(), DownsampleMethod::MEAN);

  EXPECT_EQ(downsampled.width(), 2);
  EXPECT_EQ(downsampled.height(), 2);

  // First block: (1+2+5+6)/4 = 3.5
  double val00 = downsampled[{0, 0}];
  EXPECT_NEAR(val00, 3.5, 1e-10);
  // Second block: (3+4+7+8)/4 = 5.5
  double val10 = downsampled[{1, 0}];
  EXPECT_NEAR(val10, 5.5, 1e-10);
  // Third block: (9+10+13+14)/4 = 11.5
  double val01 = downsampled[{0, 1}];
  EXPECT_NEAR(val01, 11.5, 1e-10);
  // Fourth block: (11+12+15+16)/4 = 13.5
  double val11 = downsampled[{1, 1}];
  EXPECT_NEAR(val11, 13.5, 1e-10);
}

// Test downsample function with MEDIAN method
TEST(GridOps, DownsampleMedian) {
  std::vector<std::vector<double>> data = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
  TestGrid grid(data);

  GeoGrid<double> downsampled = downsample(grid, 2, ProgressTracker(), DownsampleMethod::MEDIAN);

  EXPECT_EQ(downsampled.width(), 2);
  EXPECT_EQ(downsampled.height(), 2);

  // Block (0,0): {1,2,4,5} -> sorted: [1,2,4,5], size=4 (even), median is (2+4)/2 = 3.0
  double median_val00 = downsampled[{0, 0}];
  EXPECT_NEAR(median_val00, 3.0, 1e-10);

  // Block (1,0): {3,6} -> sorted: [3,6], size=2 (even), median is (3+6)/2 = 4.5
  double median_val10 = downsampled[{1, 0}];
  EXPECT_NEAR(median_val10, 4.5, 1e-10);

  // Block (0,1): {7,8} -> sorted: [7,8], size=2 (even), median is (7+8)/2 = 7.5
  double median_val01 = downsampled[{0, 1}];
  EXPECT_NEAR(median_val01, 7.5, 1e-10);

  // Block (1,1): {9} -> sorted: [9], size=1 (odd), median is 9.0
  double median_val11 = downsampled[{1, 1}];
  EXPECT_NEAR(median_val11, 9.0, 1e-10);
}

// Test downsample with odd dimensions
TEST(GridOps, DownsampleOddDimensions) {
  std::vector<std::vector<double>> data = {{1.0, 2.0, 3.0, 4.0, 5.0}, {6.0, 7.0, 8.0, 9.0, 10.0}};
  TestGrid grid(data);

  GeoGrid<double> downsampled = downsample(grid, 2, ProgressTracker(), DownsampleMethod::MEAN);

  // Should round up: ceil(5/2) = 3, ceil(2/2) = 1
  EXPECT_EQ(downsampled.width(), 3);
  EXPECT_EQ(downsampled.height(), 1);
}

// Test remove_outliers function
TEST(GridOps, RemoveOutliers) {
  // Create a grid with an outlier
  std::vector<std::vector<double>> data = {{10.0, 10.0, 10.0},
                                           {10.0, 100.0, 10.0},  // Outlier in the middle
                                           {10.0, 10.0, 10.0}};
  TestGrid grid(data);

  GeoGrid<double> cleaned = remove_outliers(grid, ProgressTracker(), 1.0);

  // The outlier should be replaced with an average of neighbors
  // Center value should be closer to 10.0 than 100.0
  double center_val = cleaned[{1, 1}];
  EXPECT_LT(center_val, 50.0);
  EXPECT_GT(center_val, 5.0);

  // Edge values should remain unchanged
  double edge00 = cleaned[{0, 0}];
  double edge22 = cleaned[{2, 2}];
  EXPECT_DOUBLE_EQ(edge00, 10.0);
  EXPECT_DOUBLE_EQ(edge22, 10.0);
}

// Test remove_outliers with no outliers
TEST(GridOps, RemoveOutliersNoOutliers) {
  std::vector<std::vector<double>> data = {
      {10.0, 10.0, 10.0}, {10.0, 10.0, 10.0}, {10.0, 10.0, 10.0}};
  TestGrid grid(data);

  GeoGrid<double> cleaned = remove_outliers(grid, ProgressTracker(), 1.0);

  // All values should remain the same
  for (size_t i = 0; i < cleaned.height(); i++) {
    for (size_t j = 0; j < cleaned.width(); j++) {
      double val = cleaned[{j, i}];
      EXPECT_DOUBLE_EQ(val, 10.0);
    }
  }
}

// Test interpolate_holes function
TEST(GridOps, InterpolateHoles) {
  // Create a grid with a hole (NaN or large value)
  std::vector<std::vector<double>> data = {
      {10.0, 10.0, 10.0},
      {10.0, std::numeric_limits<double>::max(), 10.0},  // Hole in the middle
      {10.0, 10.0, 10.0}};
  TestGrid grid(data);

  GeoGrid<double> interpolated = interpolate_holes(grid, ProgressTracker());

  // The hole should be filled with interpolated value (should be close to 10.0)
  double hole_val = interpolated[{1, 1}];
  EXPECT_LT(hole_val, 1e6);  // Should be a valid value
  EXPECT_GT(hole_val, 0.0);

  // Other values should remain unchanged
  double val00 = interpolated[{0, 0}];
  double val22 = interpolated[{2, 2}];
  EXPECT_DOUBLE_EQ(val00, 10.0);
  EXPECT_DOUBLE_EQ(val22, 10.0);
}

// Test interpolate_holes with multiple holes
TEST(GridOps, InterpolateHolesMultiple) {
  std::vector<std::vector<double>> data = {
      {10.0, std::numeric_limits<double>::max(), 20.0},
      {std::numeric_limits<double>::max(), 15.0, std::numeric_limits<double>::max()},
      {30.0, 25.0, 35.0}};
  TestGrid grid(data);

  GeoGrid<double> interpolated = interpolate_holes(grid, ProgressTracker());

  // All holes should be filled
  for (size_t i = 0; i < interpolated.height(); i++) {
    for (size_t j = 0; j < interpolated.width(); j++) {
      double val = interpolated[{j, i}];
      EXPECT_LT(val, 1e6);
      EXPECT_TRUE(std::isfinite(val));
    }
  }
}

// Test interpolate_holes with isolated hole (no neighbors)
TEST(GridOps, InterpolateHolesIsolated) {
  std::vector<std::vector<double>> data = {
      {std::numeric_limits<double>::max(), std::numeric_limits<double>::max(),
       std::numeric_limits<double>::max()},
      {std::numeric_limits<double>::max(), std::numeric_limits<double>::max(),
       std::numeric_limits<double>::max()},
      {std::numeric_limits<double>::max(), std::numeric_limits<double>::max(),
       std::numeric_limits<double>::max()}};
  TestGrid grid(data);

  GeoGrid<double> interpolated = interpolate_holes(grid, ProgressTracker());

  // All should be set to 0 (no neighbors to interpolate from)
  for (size_t i = 0; i < interpolated.height(); i++) {
    for (size_t j = 0; j < interpolated.width(); j++) {
      double val = interpolated[{j, i}];
      EXPECT_DOUBLE_EQ(val, 0.0);
    }
  }
}

// Test has_value function
TEST(GridOps, HasValue) {
  EXPECT_TRUE(has_value(10.0));
  EXPECT_TRUE(has_value(0.0));
  EXPECT_TRUE(has_value(-10.0));
  EXPECT_TRUE(has_value(1e5));

  EXPECT_FALSE(has_value(std::numeric_limits<double>::infinity()));
  EXPECT_FALSE(has_value(-std::numeric_limits<double>::infinity()));
  EXPECT_FALSE(has_value(std::numeric_limits<double>::quiet_NaN()));
  EXPECT_FALSE(has_value(1e7));  // >= 1e6
}
