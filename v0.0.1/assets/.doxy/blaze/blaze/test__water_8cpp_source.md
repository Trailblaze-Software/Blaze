

# File test\_water.cpp

[**File List**](files.md) **>** [**methods**](dir_0525f968218f30056a0344f59b10bbbb.md) **>** [**water**](dir_9906ac72c69ac5c4da1443f27a433c13.md) **>** [**tests**](dir_bea8c7e26f40f75291ccc2650200ba17.md) **>** [**test\_water.cpp**](test__water_8cpp.md)

[Go to the documentation of this file](test__water_8cpp.md)


```C++
#include <gtest/gtest.h>

#include <iomanip>

#include "lib/grid/grid.hpp"
#include "methods/water/water.hpp"

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

TEST(Water, FillHoles3x3) {
  std::vector<std::vector<double>> data = {{0.5, 0.5, 0.5}, {0.5, 0.4, 0.5}, {0.5, 0.5, 0.5}};
  TestGrid grid(data);

  GeoGrid<double> filled = fill_depressions(grid);

  ASSERT_GE((filled[{1, 1}]), 0.5);
}

TEST(Water, FillHoles5x5) {
  std::vector<std::vector<double>> data = {{0.7, 0.6, 0.5, 0.6, 0.7},
                                           {0.6, 0.45, 0.4, 0.45, 0.6},
                                           {1, 0.4, 0.3, 0.4, 1},
                                           {0.6, 0.45, 0.4, 0.45, 0.6},
                                           {1, 1, 1, 1, 1}};
  TestGrid grid(data);

  GeoGrid<double> filled = fill_depressions(grid);

  for (size_t i = 0; i < filled.height(); i++) {
    for (size_t j = 0; j < filled.width(); j++) {
      ASSERT_GE((filled[{j, i}]), 0.5);
    }
  }
}

TEST(Water, FillHoles5x5_2) {
  std::vector<std::vector<double>> data = {{0.7, 0.6, 0.5, 0.6, 0.7},
                                           {0.6, 0.6, 0.6, 0.6, 0.6},
                                           {1, 0.6, 0.3, 0.6, 1},
                                           {0.6, 0.6, 0.6, 0.6, 0.6},
                                           {1, 1, 1, 1, 1}};
  TestGrid grid(data);

  GeoGrid<double> filled = fill_depressions(grid);

  std::cout << std::setprecision(10) << filled << std::endl;
  for (size_t i = 0; i < filled.height(); i++) {
    for (size_t j = 0; j < filled.width(); j++) {
      ASSERT_GE((filled[{j, i}]), 0.5);
    }
  }
}
```


