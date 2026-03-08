#include <gtest/gtest.h>

#include <cmath>

#include "grid/grid.hpp"
#include "vegetation/vegetation.hpp"

// Helper to create a small GeoGrid<float> for testing
static GeoGrid<float> make_float_grid(const std::vector<std::vector<float>>& data) {
  size_t h = data.size();
  size_t w = data[0].size();
  GeoGrid<float> grid(w, h, GeoTransform(), GeoProjection());
  for (size_t i = 0; i < h; i++) {
    for (size_t j = 0; j < w; j++) {
      grid[{j, i}] = data[i][j];
    }
  }
  return grid;
}

static GeoGrid<std::optional<float>> make_opt_float_grid(
    const std::vector<std::vector<std::optional<float>>>& data) {
  size_t h = data.size();
  size_t w = data[0].size();
  GeoGrid<std::optional<float>> grid(w, h, GeoTransform(), GeoProjection());
  for (size_t i = 0; i < h; i++) {
    for (size_t j = 0; j < w; j++) {
      grid[{j, i}] = data[i][j];
    }
  }
  return grid;
}

// =============================================================================
// low_pass filter tests (GeoGrid<float> overload)
// =============================================================================

TEST(Vegetation, LowPassUniformGrid) {
  // A uniform grid should stay the same after low-pass filtering
  std::vector<std::vector<float>> data(20, std::vector<float>(20, 5.0f));
  GeoGrid<float> grid = make_float_grid(data);

  GeoGrid<float> result = low_pass(grid, 3);

  // Center values should remain ~5.0
  float center_val = result[{10, 10}];
  EXPECT_NEAR(center_val, 5.0f, 0.01f);
}

TEST(Vegetation, LowPassSmoothing) {
  // A grid with a high center value should be smoothed by low-pass
  constexpr size_t N = 20;
  std::vector<std::vector<float>> data(N, std::vector<float>(N, 0.0f));
  data[10][10] = 100.0f;  // single spike
  GeoGrid<float> grid = make_float_grid(data);

  GeoGrid<float> result = low_pass(grid, 3);

  // The spike should be reduced
  float spike_val = result[{10, 10}];
  EXPECT_LT(spike_val, 100.0f);
  EXPECT_GT(spike_val, 0.0f);

  // Neighbors should be elevated
  float neighbor_val = result[{11, 10}];
  EXPECT_GT(neighbor_val, 0.0f);
}

TEST(Vegetation, LowPassSmallDelta) {
  // With delta=2, neighbors within radius 2 are weighted
  constexpr size_t N = 5;
  std::vector<std::vector<float>> data(N, std::vector<float>(N, 0.0f));
  data[2][2] = 10.0f;
  GeoGrid<float> grid = make_float_grid(data);

  GeoGrid<float> result = low_pass(grid, 2);

  // Center should still be the largest but reduced (neighbors dilute it)
  float center = result[{2, 2}];
  EXPECT_LT(center, 10.0f);
  EXPECT_GT(center, 0.0f);

  // Corner values far from center should remain near 0
  float corner = result[{0, 0}];
  EXPECT_NEAR(corner, 0.0f, 0.01f);
}

// =============================================================================
// low_pass filter tests (GeoGrid<std::optional<float>> overload)
// =============================================================================

TEST(Vegetation, LowPassOptionalUniform) {
  constexpr size_t N = 20;
  std::vector<std::vector<std::optional<float>>> data(N,
                                                      std::vector<std::optional<float>>(N, 5.0f));
  GeoGrid<std::optional<float>> grid = make_opt_float_grid(data);

  GeoGrid<float> result = low_pass(grid, 3);

  float center_val = result[{10, 10}];
  EXPECT_NEAR(center_val, 5.0f, 0.01f);
}

TEST(Vegetation, LowPassOptionalWithNulls) {
  // Grid with some null values - they should be skipped
  constexpr size_t N = 10;
  std::vector<std::vector<std::optional<float>>> data(N,
                                                      std::vector<std::optional<float>>(N, 5.0f));
  // Set some values to null
  data[5][5] = std::nullopt;
  data[5][6] = std::nullopt;
  data[6][5] = std::nullopt;
  GeoGrid<std::optional<float>> grid = make_opt_float_grid(data);

  GeoGrid<float> result = low_pass(grid, 3);

  // Center should still be close to 5.0 since nulls are skipped
  float val = result[{3, 3}];
  EXPECT_NEAR(val, 5.0f, 0.1f);
}

TEST(Vegetation, LowPassOptionalAllNull) {
  // All nulls should produce 0 values
  constexpr size_t N = 5;
  std::vector<std::vector<std::optional<float>>> data(
      N, std::vector<std::optional<float>>(N, std::nullopt));
  GeoGrid<std::optional<float>> grid = make_opt_float_grid(data);

  GeoGrid<float> result = low_pass(grid, 2);

  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      float val = result[{j, i}];
      EXPECT_FLOAT_EQ(val, 0.0f);
    }
  }
}

TEST(Vegetation, LowPassPreservesGridDimensions) {
  std::vector<std::vector<float>> data = {
      {1.0f, 2.0f, 3.0f},
      {4.0f, 5.0f, 6.0f},
      {7.0f, 8.0f, 9.0f},
  };
  GeoGrid<float> grid = make_float_grid(data);

  GeoGrid<float> result = low_pass(grid, 2);

  EXPECT_EQ(result.width(), 3u);
  EXPECT_EQ(result.height(), 3u);
}
