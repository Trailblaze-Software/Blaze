#include <gtest/gtest.h>

#include "grid/grid.hpp"
#include "grid/img_grid.hpp"
#include "isom/colors.hpp"

namespace {

GeoGrid<RGBColor> make_solid_color_grid(size_t width, size_t height, const RGBColor& color) {
  GeoGrid<RGBColor> grid(width, height, GeoTransform(), GeoProjection());
  for (size_t y = 0; y < height; ++y) {
    for (size_t x = 0; x < width; ++x) {
      grid[{x, y}] = color;
    }
  }
  return grid;
}

RGBColor expected_alpha_blend(const RGBColor& foreground, const RGBColor& background) {
  const float alpha = foreground.getAlpha() / 255.0f;
  const float beta = background.getAlpha() / 255.0f;
  const float denom = alpha + beta * (1.0f - alpha);
  if (denom <= 0.001f) {
    return RGBColor(background.getRed(), background.getGreen(), background.getBlue(), 255);
  }
  const uint8_t b = static_cast<uint8_t>(
      (alpha * foreground.getBlue() + beta * background.getBlue() * (1.0f - alpha)) / denom);
  const uint8_t g = static_cast<uint8_t>(
      (alpha * foreground.getGreen() + beta * background.getGreen() * (1.0f - alpha)) / denom);
  const uint8_t r = static_cast<uint8_t>(
      (alpha * foreground.getRed() + beta * background.getRed() * (1.0f - alpha)) / denom);
  return RGBColor(r, g, b, 255);
}

}  // namespace

TEST(GeoImgGrid, DrawAlphaBlendsOverlappingPixels) {
  const RGBColor background_color(0, 0, 255, 255);
  const RGBColor foreground_color(255, 0, 0, 128);

  GeoImgGrid background(make_solid_color_grid(2, 2, background_color));
  const GeoImgGrid foreground(make_solid_color_grid(2, 2, foreground_color));

  background.draw(foreground);

  const RGBColor expected = expected_alpha_blend(foreground_color, background_color);
  const RGBColor blended = background.get_rgb_color(0, 0);
  EXPECT_EQ(blended.getRed(), expected.getRed());
  EXPECT_EQ(blended.getGreen(), expected.getGreen());
  EXPECT_EQ(blended.getBlue(), expected.getBlue());
  EXPECT_EQ(blended.getAlpha(), expected.getAlpha());
}

TEST(GeoImgGrid, ConstructFromNonSquareGeoGrid) {
  constexpr size_t width = 3;
  constexpr size_t height = 2;
  GeoGrid<RGBColor> grid(width, height, GeoTransform(), GeoProjection());
  for (size_t y = 0; y < height; ++y) {
    for (size_t x = 0; x < width; ++x) {
      grid[{x, y}] = RGBColor(static_cast<uint8_t>(x * 10 + y), 0, 0, 255);
    }
  }

  const GeoImgGrid img_grid(grid);
  for (size_t y = 0; y < height; ++y) {
    for (size_t x = 0; x < width; ++x) {
      const RGBColor pixel = img_grid.get_rgb_color(y, x);
      EXPECT_EQ(pixel.getRed(), static_cast<uint8_t>(x * 10 + y));
    }
  }
}

TEST(GeoImgGrid, DrawNonSquareGrid) {
  const RGBColor foreground_color(255, 0, 0, 255);
  GeoImgGrid background(make_solid_color_grid(5, 3, RGBColor(0, 0, 255, 255)));
  const GeoImgGrid foreground(make_solid_color_grid(5, 3, foreground_color));

  background.draw(foreground);

  const RGBColor blended = background.get_rgb_color(1, 1);
  EXPECT_EQ(blended.getRed(), foreground_color.getRed());
  EXPECT_EQ(blended.getGreen(), foreground_color.getGreen());
  EXPECT_EQ(blended.getBlue(), foreground_color.getBlue());
}

TEST(GeoImgGrid, DrawOpaqueForegroundReplacesBackground) {
  const RGBColor background_color(0, 0, 255, 128);
  const RGBColor foreground_color(255, 0, 0, 255);

  GeoImgGrid background(make_solid_color_grid(1, 1, background_color));
  const GeoImgGrid foreground(make_solid_color_grid(1, 1, foreground_color));

  background.draw(foreground);

  const RGBColor blended = background.get_rgb_color(0, 0);
  EXPECT_EQ(blended.getRed(), 255);
  EXPECT_EQ(blended.getGreen(), 0);
  EXPECT_EQ(blended.getBlue(), 0);
  EXPECT_EQ(blended.getAlpha(), 255);
}
