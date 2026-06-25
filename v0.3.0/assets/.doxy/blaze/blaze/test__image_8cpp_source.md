

# File test\_image.cpp

[**File List**](files.md) **>** [**grid**](dir_b440d1ddeab29faa8ab1c63476ee276f.md) **>** [**tests**](dir_7abe1d2e6c271935b6731dcf9a13a0e9.md) **>** [**test\_image.cpp**](test__image_8cpp.md)

[Go to the documentation of this file](test__image_8cpp.md)


```C++
#include <gtest/gtest.h>

#include <array>
#include <stdexcept>

#include "grid/image.hpp"
#include "isom/colors.hpp"

TEST(Image, SetAndGetPixel) {
  blaze::Image image(2, 2);
  const RGBColor red(255, 0, 0, 128);
  image.set(0, 1, red);
  const RGBColor read = image.at(0, 1);
  EXPECT_EQ(read.getRed(), 255);
  EXPECT_EQ(read.getGreen(), 0);
  EXPECT_EQ(read.getBlue(), 0);
  EXPECT_EQ(read.getAlpha(), 128);
}

TEST(Image, OutOfBoundsThrows) {
  blaze::Image image(2, 2);
  EXPECT_THROW(image.at(-1, 0), std::runtime_error);
  EXPECT_THROW(image.set(-1, 0, RGBColor(255, 0, 0, 255)), std::runtime_error);
}

TEST(Image, SliceCopiesRegion) {
  blaze::Image image(4, 4);
  image.set(1, 2, RGBColor(10, 20, 30, 255));
  const blaze::Image region = image.slice(blaze::Rect(2, 1, 2, 2));
  EXPECT_EQ(region.width(), 2);
  EXPECT_EQ(region.height(), 2);
  const RGBColor read = region.at(0, 0);
  EXPECT_EQ(read.getRed(), 10);
  EXPECT_EQ(read.getGreen(), 20);
  EXPECT_EQ(read.getBlue(), 30);
}

TEST(Image, RectIntersection) {
  const blaze::Rect a(0, 0, 4, 4);
  const blaze::Rect b(2, 2, 4, 4);
  const blaze::Rect intersection = a & b;
  EXPECT_EQ(intersection.x, 2);
  EXPECT_EQ(intersection.y, 2);
  EXPECT_EQ(intersection.width, 2);
  EXPECT_EQ(intersection.height, 2);
}

TEST(Image, ResizeNearestNeighbor) {
  blaze::Image image(2, 2);
  image.set(0, 0, RGBColor(255, 0, 0, 255));
  image.set(0, 1, RGBColor(0, 255, 0, 255));
  image.set(1, 0, RGBColor(0, 0, 255, 255));
  image.set(1, 1, RGBColor(255, 255, 255, 255));

  blaze::Image resized;
  image.resize(resized, blaze::Size(4, 4), blaze::InterpolationMode::NEAREST);
  EXPECT_EQ(resized.width(), 4);
  EXPECT_EQ(resized.height(), 4);
  const RGBColor corner = resized.at(0, 0);
  EXPECT_EQ(corner.getRed(), 255);
  EXPECT_EQ(corner.getGreen(), 0);
  EXPECT_EQ(corner.getBlue(), 0);
}

TEST(Image, ResizeNearestNeighborMapsEdges) {
  blaze::Image image(4, 1);
  image.set(0, 0, RGBColor(255, 0, 0, 255));
  image.set(0, 3, RGBColor(0, 0, 255, 255));

  blaze::Image resized;
  image.resize(resized, blaze::Size(2, 1), blaze::InterpolationMode::NEAREST);
  EXPECT_EQ(resized.at(0, 0).getRed(), 255);
  EXPECT_EQ(resized.at(0, 1).getBlue(), 255);
}

TEST(Image, ResizeZeroDestinationClearsOutput) {
  blaze::Image image(2, 2);
  image.set(0, 0, RGBColor(255, 0, 0, 255));

  blaze::Image resized(2, 2);
  image.resize(resized, blaze::Size(0, 4), blaze::InterpolationMode::NEAREST);
  EXPECT_EQ(resized.width(), 0);
  EXPECT_EQ(resized.height(), 0);
}

TEST(Image, DrawLineSetsPixels) {
  blaze::Image image(8, 8);
  image.draw_polyline(std::array<blaze::Point, 2>{blaze::Point(0, 0), blaze::Point(3, 0)}.data(), 2,
                      false, RGBColor(0, 0, 255, 255), 1);
  const RGBColor mid = image.at(0, 2);
  EXPECT_EQ(mid.getBlue(), 255);
}
```


