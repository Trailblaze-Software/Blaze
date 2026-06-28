#include <gtest/gtest.h>

#include <iomanip>

#include "lib/grid/grid.hpp"
#include "methods/water/water.hpp"
#include "utilities/progress_tracker.hpp"

TEST(Water, FillHoles3x3) {
  std::vector<std::vector<double>> data = {{0.5, 0.5, 0.5}, {0.5, 0.4, 0.5}, {0.5, 0.5, 0.5}};
  GeoGrid<double> grid(data);

  GeoGrid<double> filled = fill_depressions(grid, ProgressTracker());

  ASSERT_GE((filled[{1, 1}]), 0.5);
}

TEST(Water, FillHoles5x5) {
  std::vector<std::vector<double>> data = {{0.7, 0.6, 0.5, 0.6, 0.7},
                                           {0.6, 0.45, 0.4, 0.45, 0.6},
                                           {1, 0.4, 0.3, 0.4, 1},
                                           {0.6, 0.45, 0.4, 0.45, 0.6},
                                           {1, 1, 1, 1, 1}};
  GeoGrid<double> grid(data);

  GeoGrid<double> filled = fill_depressions(grid, ProgressTracker());

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
  GeoGrid<double> grid(data);

  GeoGrid<double> filled = fill_depressions(grid, ProgressTracker());

  std::cout << std::setprecision(10) << filled << std::endl;
  for (size_t i = 0; i < filled.height(); i++) {
    for (size_t j = 0; j < filled.width(); j++) {
      ASSERT_GE((filled[{j, i}]), 0.5);
    }
  }
}
