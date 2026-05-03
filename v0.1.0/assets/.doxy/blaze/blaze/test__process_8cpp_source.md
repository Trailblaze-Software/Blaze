

# File test\_process.cpp

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**tests**](dir_d93a1d4020dea85bb71b237545b5e722.md) **>** [**test\_process.cpp**](test__process_8cpp.md)

[Go to the documentation of this file](test__process_8cpp.md)


```C++
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
```


