

# File test\_process.cpp

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**tests**](dir_d93a1d4020dea85bb71b237545b5e722.md) **>** [**test\_process.cpp**](test__process_8cpp.md)

[Go to the documentation of this file](test__process_8cpp.md)


```C++
#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <numbers>
#include <vector>

#include "las/las_point.hpp"
#include "lib/grid/grid.hpp"
#include "methods/hill_shade/hill_shade.hpp"
#include "process.hpp"

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

// ---- slope() tests -------------------------------------------------------

// A flat surface has zero gradient everywhere, so slope should be 0.
TEST(Slope, FlatSurface) {
  std::vector<std::vector<double>> data = {{10, 10, 10, 10, 10},
                                           {10, 10, 10, 10, 10},
                                           {10, 10, 10, 10, 10},
                                           {10, 10, 10, 10, 10},
                                           {10, 10, 10, 10, 10}};
  GeoGrid<double> flat(data);
  auto result = slope(flat);
  for (size_t i = 1; i < 4; i++) {
    for (size_t j = 1; j < 4; j++) {
      double val = result[{j, i}];
      EXPECT_NEAR(val, 0.0, 1e-9) << "at (" << j << "," << i << ")";
    }
  }
}

// A uniform 45-degree slope (rise = run = 1 cell) produces atan(1) = pi/4.
TEST(Slope, FortyFiveDegreeSlope) {
  std::vector<std::vector<double>> data = {
      {0, 0, 0, 0, 0}, {1, 1, 1, 1, 1}, {2, 2, 2, 2, 2}, {3, 3, 3, 3, 3}, {4, 4, 4, 4, 4}};
  GeoGrid<double> sloped(data);
  auto result = slope(sloped);
  for (size_t i = 1; i < 4; i++) {
    for (size_t j = 1; j < 4; j++) {
      double val = result[{j, i}];
      EXPECT_NEAR(val, std::numbers::pi / 4, 1e-9) << "at (" << j << "," << i << ")";
    }
  }
}

// Slope values are always non-negative (range [0, pi/2]).
TEST(Slope, AlwaysNonNegative) {
  std::vector<std::vector<double>> data = {
      {5, 3, 7, 1, 9}, {2, 8, 4, 6, 0}, {9, 1, 5, 3, 7}, {4, 6, 2, 8, 4}, {7, 0, 9, 5, 2}};
  GeoGrid<double> mixed(data);
  auto result = slope(mixed);
  for (size_t i = 1; i < 4; i++) {
    for (size_t j = 1; j < 4; j++) {
      double val = result[{j, i}];
      EXPECT_GE(val, 0.0) << "at (" << j << "," << i << ")";
    }
  }
}

// Slope values never exceed pi/2 (vertical).
TEST(Slope, NeverExceedsVertical) {
  std::vector<std::vector<double>> data = {{0, 0, 1e6, 0, 0},
                                           {0, 0, 1e6, 0, 0},
                                           {0, 0, 1e6, 0, 0},
                                           {0, 0, 1e6, 0, 0},
                                           {0, 0, 1e6, 0, 0}};
  GeoGrid<double> steep(data);
  auto result = slope(steep);
  for (size_t i = 1; i < 4; i++) {
    for (size_t j = 1; j < 4; j++) {
      double val = result[{j, i}];
      EXPECT_LE(val, std::numbers::pi / 2) << "at (" << j << "," << i << ")";
    }
  }
}
```


