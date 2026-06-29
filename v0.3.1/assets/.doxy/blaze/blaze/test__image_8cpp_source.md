

# File test\_image.cpp

[**File List**](files.md) **>** [**grid**](dir_b440d1ddeab29faa8ab1c63476ee276f.md) **>** [**tests**](dir_7abe1d2e6c271935b6731dcf9a13a0e9.md) **>** [**test\_image.cpp**](test__image_8cpp.md)

[Go to the documentation of this file](test__image_8cpp.md)


```C++
#include <gtest/gtest.h>

#include <array>

#include "grid/grid.hpp"
#include "grid/img_grid.hpp"
#include "isom/colors.hpp"

TEST(RGBGrid, SetAndGetPixel) {
  Grid<RGBColor> image(2, 2);
  const RGBColor red(255, 0, 0, 128);
  image[{1, 0}] = red;
  const RGBColor read = image[{1, 0}];
  EXPECT_EQ(read.getRed(), 255);
  EXPECT_EQ(read.getGreen(), 0);
  EXPECT_EQ(read.getBlue(), 0);
  EXPECT_EQ(read.getAlpha(), 128);
}

TEST(RGBGrid, OutOfBoundsThrows) {
  Grid<RGBColor> image(2, 2);
  const Coordinate2D<size_t> oob(0, 2);
  EXPECT_THROW(image[oob], std::out_of_range);
  EXPECT_THROW(image[oob] = RGBColor(255, 0, 0, 255), std::out_of_range);
}

TEST(RGBGrid, SliceCopiesRegion) {
  Grid<RGBColor> image(4, 4);
  image[{2, 1}] = RGBColor(10, 20, 30, 255);
  const Grid<RGBColor> region = image.slice_rect(blaze::Rect(2, 1, 2, 2));
  EXPECT_EQ(region.width(), 2u);
  EXPECT_EQ(region.height(), 2u);
  const RGBColor read = region[{0, 0}];
  EXPECT_EQ(read.getRed(), 10);
  EXPECT_EQ(read.getGreen(), 20);
  EXPECT_EQ(read.getBlue(), 30);
}

TEST(RGBGrid, RectIntersection) {
  const blaze::Rect a(0, 0, 4, 4);
  const blaze::Rect b(2, 2, 4, 4);
  const blaze::Rect intersection = a & b;
  EXPECT_EQ(intersection.x, 2);
  EXPECT_EQ(intersection.y, 2);
  EXPECT_EQ(intersection.width, 2);
  EXPECT_EQ(intersection.height, 2);
}

TEST(RGBGrid, ResizeNearestNeighbor) {
  Grid<RGBColor> image(2, 2);
  image[{0, 0}] = RGBColor(255, 0, 0, 255);
  image[{1, 0}] = RGBColor(0, 255, 0, 255);
  image[{0, 1}] = RGBColor(0, 0, 255, 255);
  image[{1, 1}] = RGBColor(255, 255, 255, 255);

  Grid<RGBColor> resized(0, 0);
  image.resize_to(resized, blaze::Size(4, 4), blaze::InterpolationMode::NEAREST);
  EXPECT_EQ(resized.width(), 4u);
  EXPECT_EQ(resized.height(), 4u);
  const RGBColor corner = resized[{0, 0}];
  EXPECT_EQ(corner.getRed(), 255);
  EXPECT_EQ(corner.getGreen(), 0);
  EXPECT_EQ(corner.getBlue(), 0);
}

TEST(RGBGrid, ResizeNearestNeighborMapsEdges) {
  Grid<RGBColor> image(4, 1);
  image[{0, 0}] = RGBColor(255, 0, 0, 255);
  image[{3, 0}] = RGBColor(0, 0, 255, 255);

  Grid<RGBColor> resized(0, 0);
  image.resize_to(resized, blaze::Size(2, 1), blaze::InterpolationMode::NEAREST);
  const RGBColor left = resized[Coordinate2D<size_t>{0, 0}];
  const RGBColor right = resized[Coordinate2D<size_t>{1, 0}];
  EXPECT_EQ(left.getRed(), 255);
  EXPECT_EQ(right.getBlue(), 255);
}

TEST(RGBGrid, ResizeZeroDestinationClearsOutput) {
  Grid<RGBColor> image(2, 2);
  image[{0, 0}] = RGBColor(255, 0, 0, 255);

  Grid<RGBColor> resized(2, 2);
  image.resize_to(resized, blaze::Size(0, 4), blaze::InterpolationMode::NEAREST);
  EXPECT_EQ(resized.width(), 0u);
  EXPECT_EQ(resized.height(), 0u);
}

TEST(RGBGrid, DrawLineSetsPixels) {
  Grid<RGBColor> image(8, 8);
  image.draw_polyline(std::array<blaze::Point, 2>{blaze::Point(0, 0), blaze::Point(3, 0)}.data(), 2,
                      false, RGBColor(0, 0, 255, 255), 1);
  const RGBColor mid = image[{2, 0}];
  EXPECT_EQ(mid.getBlue(), 255);
}
```


