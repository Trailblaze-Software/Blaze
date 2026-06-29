#include <gtest/gtest.h>

#include "geometry/polygon.hpp"
#include "grid/grid.hpp"
#include "grid/img_grid.hpp"
#include "isom/colors.hpp"
#include "utilities/progress_tracker.hpp"

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

GeoImgGrid make_solid_img_grid(size_t width, size_t height, const RGBColor& color) {
  return GeoImgGrid(make_solid_color_grid(width, height, color));
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

TEST(GeoGridRGB, DrawAlphaBlendsOverlappingPixels) {
  const RGBColor background_color(0, 0, 255, 255);
  const RGBColor foreground_color(255, 0, 0, 128);

  GeoGrid<RGBColor> background(make_solid_color_grid(2, 2, background_color));
  const GeoGrid<RGBColor> foreground(make_solid_color_grid(2, 2, foreground_color));

  background.draw(foreground, ProgressTracker());

  const RGBColor expected = expected_alpha_blend(foreground_color, background_color);
  const RGBColor blended = background[{0, 0}];
  EXPECT_EQ(blended.getRed(), expected.getRed());
  EXPECT_EQ(blended.getGreen(), expected.getGreen());
  EXPECT_EQ(blended.getBlue(), expected.getBlue());
  EXPECT_EQ(blended.getAlpha(), expected.getAlpha());
}

TEST(GeoGridRGB, DrawNonSquareGrid) {
  const RGBColor foreground_color(255, 0, 0, 255);
  GeoGrid<RGBColor> background(make_solid_color_grid(5, 3, RGBColor(0, 0, 255, 255)));
  const GeoGrid<RGBColor> foreground(make_solid_color_grid(5, 3, foreground_color));

  background.draw(foreground, ProgressTracker());

  const RGBColor blended = background[{1, 1}];
  EXPECT_EQ(blended.getRed(), foreground_color.getRed());
  EXPECT_EQ(blended.getGreen(), foreground_color.getGreen());
  EXPECT_EQ(blended.getBlue(), foreground_color.getBlue());
}

TEST(GeoGridRGB, DrawOpaqueForegroundReplacesBackground) {
  const RGBColor background_color(0, 0, 255, 128);
  const RGBColor foreground_color(255, 0, 0, 255);

  GeoGrid<RGBColor> background(make_solid_color_grid(1, 1, background_color));
  const GeoGrid<RGBColor> foreground(make_solid_color_grid(1, 1, foreground_color));

  background.draw(foreground, ProgressTracker());

  const RGBColor blended = background[{0, 0}];
  EXPECT_EQ(blended.getRed(), 255);
  EXPECT_EQ(blended.getGreen(), 0);
  EXPECT_EQ(blended.getBlue(), 0);
  EXPECT_EQ(blended.getAlpha(), 255);
}

TEST(GeoImgGrid, DrawFilledPolygonFillsInterior) {
  GeoImgGrid img(10, 10, GeoTransform({0.0, 0.0}, 1.0), GeoProjection());
  img.fill(RGBColor(0, 0, 0, 255));

  PolygonWithHoles square{{{2.0, -2.0}, {6.0, -2.0}, {6.0, -6.0}, {2.0, -6.0}, {2.0, -2.0}}, {}};
  img.draw_filled_polygon(square, RGBColor(255, 0, 0, 255));

  EXPECT_EQ((img[{4, 4}].getRed()), 255);
  EXPECT_EQ((img[{0, 0}].getRed()), 0);
}

TEST(GeoImgGrid, DrawOverlaySkipsTransparentPixels) {
  GeoImgGrid background = make_solid_img_grid(4, 4, RGBColor(255, 255, 255, 255));
  GeoImgGrid overlay = make_solid_img_grid(4, 4, RGBColor(255, 0, 0, 0));

  background.draw(overlay, ProgressTracker(), GeoGridCompositeMode::OpaqueCopy);
  EXPECT_EQ((background[{2, 2}].getRed()), 255);
  EXPECT_EQ((background[{2, 2}].getGreen()), 255);
  EXPECT_EQ((background[{2, 2}].getBlue()), 255);
}

TEST(GeoImgGrid, DrawOverlayCopiesOpaquePixels) {
  GeoImgGrid background = make_solid_img_grid(4, 4, RGBColor(255, 255, 255, 255));
  GeoImgGrid overlay = make_solid_img_grid(4, 4, RGBColor(0, 0, 0, 0));
  overlay.draw_filled_polygon(
      PolygonWithHoles{{{1.0, -1.0}, {3.0, -1.0}, {3.0, -3.0}, {1.0, -3.0}, {1.0, -1.0}}, {}},
      RGBColor(0, 0, 255, 255));

  background.draw(overlay, ProgressTracker(), GeoGridCompositeMode::OpaqueCopy);
  EXPECT_EQ((background[{2, 2}].getBlue()), 255);
  EXPECT_EQ((background[{0, 0}].getBlue()), 255);
}

TEST(GeoImgGrid, DrawSkipsFullyTransparentForeground) {
  GeoImgGrid background = make_solid_img_grid(2, 2, RGBColor(255, 255, 255, 255));
  const GeoImgGrid foreground = make_solid_img_grid(2, 2, RGBColor(255, 0, 0, 0));

  background.draw(foreground, ProgressTracker());
  EXPECT_EQ((background[{0, 0}].getRed()), 255);
  EXPECT_EQ((background[{0, 0}].getGreen()), 255);
  EXPECT_EQ((background[{0, 0}].getBlue()), 255);
}
