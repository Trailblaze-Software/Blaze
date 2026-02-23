

# File test\_contour\_utils.cpp

[**File List**](files.md) **>** [**contour**](dir_168d7404e8aa1148a0abea8bd7ba0546.md) **>** [**tests**](dir_af1ec3f63b3290d3c0b6a16b438b915c.md) **>** [**test\_contour\_utils.cpp**](test__contour__utils_8cpp.md)

[Go to the documentation of this file](test__contour__utils_8cpp.md)


```C++
#include <gtest/gtest.h>

#include <cmath>
#include <set>

#include "contour/contour.hpp"
#include "utilities/coordinate.hpp"

// Test round_down function
TEST(ContourUtils, RoundDown) {
  // Test positive values
  EXPECT_DOUBLE_EQ(round_down(10.0, 5.0), 10.0);
  EXPECT_DOUBLE_EQ(round_down(12.0, 5.0), 10.0);
  EXPECT_DOUBLE_EQ(round_down(14.9, 5.0), 10.0);
  EXPECT_DOUBLE_EQ(round_down(15.0, 5.0), 15.0);
  EXPECT_DOUBLE_EQ(round_down(17.0, 5.0), 15.0);

  // Test negative values
  EXPECT_DOUBLE_EQ(round_down(-10.0, 5.0), -10.0);
  EXPECT_DOUBLE_EQ(round_down(-12.0, 5.0), -15.0);
  EXPECT_DOUBLE_EQ(round_down(-14.9, 5.0), -15.0);
  EXPECT_DOUBLE_EQ(round_down(-15.0, 5.0), -15.0);

  // Test with different intervals
  EXPECT_DOUBLE_EQ(round_down(10.0, 2.0), 10.0);
  EXPECT_DOUBLE_EQ(round_down(11.0, 2.0), 10.0);
  EXPECT_DOUBLE_EQ(round_down(12.0, 2.0), 12.0);

  // Test zero
  EXPECT_DOUBLE_EQ(round_down(0.0, 5.0), 0.0);
}

// Test crosses_contour function
TEST(ContourUtils, CrossesContour) {
  // Test cases that should cross
  EXPECT_TRUE(crosses_contour({5.0, 15.0}, 10.0));   // Crosses 10.0
  EXPECT_TRUE(crosses_contour({15.0, 5.0}, 10.0));   // Reversed
  EXPECT_TRUE(crosses_contour({8.0, 12.0}, 10.0));   // Crosses 10.0
  EXPECT_TRUE(crosses_contour({18.0, 22.0}, 10.0));  // Crosses 20.0

  // Test cases that should not cross
  EXPECT_FALSE(crosses_contour({5.0, 8.0}, 10.0));    // Both below 10.0
  EXPECT_FALSE(crosses_contour({12.0, 15.0}, 10.0));  // Both above 10.0, below 20.0
  EXPECT_FALSE(crosses_contour({10.0, 15.0}, 10.0));  // Starts exactly on contour - doesn't cross
  EXPECT_TRUE(crosses_contour({5.0, 10.0}, 10.0));    // Ends exactly on contour - crosses

  // Test negative values
  EXPECT_TRUE(crosses_contour({-15.0, -5.0}, 10.0));    // Crosses -10.0
  EXPECT_TRUE(crosses_contour({-5.0, -15.0}, 10.0));    // Reversed
  EXPECT_FALSE(crosses_contour({-15.0, -12.0}, 10.0));  // Both below -10.0, doesn't cross
  EXPECT_FALSE(crosses_contour({-8.0, -5.0}, 10.0));   // Both above -10.0, below 0.0, doesn't cross
  EXPECT_TRUE(crosses_contour({-5.0, 5.0}, 10.0));     // Crosses 0.0 (negative to positive)
  EXPECT_TRUE(crosses_contour({-12.0, -8.0}, 10.0));   // Crosses -10.0
  EXPECT_FALSE(crosses_contour({-10.0, -5.0}, 10.0));  // Starts exactly on contour - doesn't cross
  EXPECT_TRUE(crosses_contour({-15.0, -10.0}, 10.0));  // Ends exactly on contour - crosses

  // Test with different intervals
  EXPECT_TRUE(crosses_contour({4.0, 6.0}, 5.0));   // Crosses 5.0
  EXPECT_FALSE(crosses_contour({4.0, 4.5}, 5.0));  // Doesn't cross
}

// Test get_contour_heights function
TEST(ContourUtils, GetContourHeights) {
  // Test basic case
  std::set<double> heights1 = get_contour_heights({5.0, 25.0}, 10.0);
  EXPECT_EQ(heights1.size(), 2);
  EXPECT_TRUE(heights1.find(10.0) != heights1.end());
  EXPECT_TRUE(heights1.find(20.0) != heights1.end());

  // Test reversed
  std::set<double> heights2 = get_contour_heights({25.0, 5.0}, 10.0);
  EXPECT_EQ(heights2.size(), 2);
  EXPECT_TRUE(heights2.find(10.0) != heights2.end());
  EXPECT_TRUE(heights2.find(20.0) != heights2.end());

  // Test single crossing
  std::set<double> heights3 = get_contour_heights({8.0, 12.0}, 10.0);
  EXPECT_EQ(heights3.size(), 1);
  EXPECT_TRUE(heights3.find(10.0) != heights3.end());

  // Test no crossing
  std::set<double> heights4 = get_contour_heights({5.0, 8.0}, 10.0);
  EXPECT_EQ(heights4.size(), 0);

  // Test multiple crossings
  std::set<double> heights5 = get_contour_heights({5.0, 45.0}, 10.0);
  EXPECT_EQ(heights5.size(), 4);
  EXPECT_TRUE(heights5.find(10.0) != heights5.end());
  EXPECT_TRUE(heights5.find(20.0) != heights5.end());
  EXPECT_TRUE(heights5.find(30.0) != heights5.end());
  EXPECT_TRUE(heights5.find(40.0) != heights5.end());

  // Test with different intervals
  std::set<double> heights6 = get_contour_heights({2.0, 8.0}, 2.0);
  // round_down(8.0, 2.0) = 8.0, then loop: 8.0, 6.0, 4.0 (3 values)
  EXPECT_EQ(heights6.size(), 3);
  EXPECT_TRUE(heights6.find(4.0) != heights6.end());
  EXPECT_TRUE(heights6.find(6.0) != heights6.end());
  EXPECT_TRUE(heights6.find(8.0) != heights6.end());
}

// Test interpolate_coordinates function
TEST(ContourUtils, InterpolateCoordinates) {
  Coordinate2D<double> a(0.0, 0.0);
  Coordinate2D<double> b(10.0, 10.0);

  // Test midpoint (target between a and b)
  Coordinate2D<double> mid = interpolate_coordinates(a, b, 0.0, 10.0, 5.0);
  EXPECT_NEAR(mid.x(), 5.0, 1e-10);
  EXPECT_NEAR(mid.y(), 5.0, 1e-10);

  // Test at a
  Coordinate2D<double> at_a = interpolate_coordinates(a, b, 0.0, 10.0, 0.0);
  EXPECT_NEAR(at_a.x(), 0.0, 1e-10);
  EXPECT_NEAR(at_a.y(), 0.0, 1e-10);

  // Test at b
  Coordinate2D<double> at_b = interpolate_coordinates(a, b, 0.0, 10.0, 10.0);
  EXPECT_NEAR(at_b.x(), 10.0, 1e-10);
  EXPECT_NEAR(at_b.y(), 10.0, 1e-10);

  // Test when a_val == b_val (should return midpoint)
  Coordinate2D<double> equal = interpolate_coordinates(a, b, 5.0, 5.0, 5.0);
  EXPECT_NEAR(equal.x(), 5.0, 1e-10);
  EXPECT_NEAR(equal.y(), 5.0, 1e-10);

  // Test different values
  Coordinate2D<double> c(0.0, 0.0);
  Coordinate2D<double> d(20.0, 0.0);
  Coordinate2D<double> result = interpolate_coordinates(c, d, 0.0, 20.0, 10.0);
  EXPECT_NEAR(result.x(), 10.0, 1e-10);
  EXPECT_NEAR(result.y(), 0.0, 1e-10);

  // Test interpolation closer to a
  Coordinate2D<double> close_a = interpolate_coordinates(a, b, 0.0, 10.0, 2.0);
  EXPECT_NEAR(close_a.x(), 2.0, 1e-10);
  EXPECT_NEAR(close_a.y(), 2.0, 1e-10);

  // Test interpolation closer to b
  Coordinate2D<double> close_b = interpolate_coordinates(a, b, 0.0, 10.0, 8.0);
  EXPECT_NEAR(close_b.x(), 8.0, 1e-10);
  EXPECT_NEAR(close_b.y(), 8.0, 1e-10);
}

// Test Contour class basic functionality
TEST(ContourUtils, ContourBasic) {
  std::vector<Coordinate2D<double>> points = {
      Coordinate2D<double>(0.0, 0.0), Coordinate2D<double>(1.0, 0.0),
      Coordinate2D<double>(1.0, 1.0), Coordinate2D<double>(0.0, 1.0)};

  Contour contour(10.0, std::move(points));
  EXPECT_DOUBLE_EQ(contour.height(), 10.0);
  EXPECT_EQ(contour.points().size(), 4);
  EXPECT_FALSE(contour.is_loop());  // Not a loop because first != last

  // Create a loop
  std::vector<Coordinate2D<double>> loop_points = {
      Coordinate2D<double>(0.0, 0.0), Coordinate2D<double>(1.0, 0.0),
      Coordinate2D<double>(1.0, 1.0), Coordinate2D<double>(0.0, 1.0),
      Coordinate2D<double>(0.0, 0.0)  // Close the loop
  };

  Contour loop_contour(10.0, std::move(loop_points));
  EXPECT_TRUE(loop_contour.is_loop());

  // Test empty contour
  std::vector<Coordinate2D<double>> empty_points;
  Contour empty_contour(5.0, std::move(empty_points));
  EXPECT_DOUBLE_EQ(empty_contour.height(), 5.0);
  EXPECT_EQ(empty_contour.points().size(), 0);
  EXPECT_FALSE(empty_contour.is_loop());
}
```


