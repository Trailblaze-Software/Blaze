#include <gtest/gtest.h>

#include "isom/colors.hpp"

// =============================================================================
// RGBColor tests
// =============================================================================

TEST(RGBColor, Construction) {
  RGBColor c(128, 64, 32);
  EXPECT_EQ(c.getRed(), 128);
  EXPECT_EQ(c.getGreen(), 64);
  EXPECT_EQ(c.getBlue(), 32);
  EXPECT_EQ(c.getAlpha(), 255);  // Default alpha
}

TEST(RGBColor, ConstructionWithAlpha) {
  RGBColor c(128, 64, 32, 100);
  EXPECT_EQ(c.getRed(), 128);
  EXPECT_EQ(c.getGreen(), 64);
  EXPECT_EQ(c.getBlue(), 32);
  EXPECT_EQ(c.getAlpha(), 100);
}

TEST(RGBColor, DefaultConstruction) {
  RGBColor c;
  EXPECT_EQ(c.getRed(), 0);
  EXPECT_EQ(c.getGreen(), 0);
  EXPECT_EQ(c.getBlue(), 0);
  EXPECT_EQ(c.getAlpha(), 0);
}

TEST(RGBColor, IndexOperator) {
  RGBColor c(10, 20, 30, 40);
  EXPECT_EQ(c[0], 10);
  EXPECT_EQ(c[1], 20);
  EXPECT_EQ(c[2], 30);
  EXPECT_EQ(c[3], 40);
}

// =============================================================================
// CMYKColor tests
// =============================================================================

TEST(CMYKColor, Construction) {
  CMYKColor c(50, 30, 20, 10);
  EXPECT_EQ(c.getCyan(), 50);
  EXPECT_EQ(c.getMagenta(), 30);
  EXPECT_EQ(c.getYellow(), 20);
  EXPECT_EQ(c.getBlack(), 10);
}

TEST(CMYKColor, DefaultConstruction) {
  CMYKColor c;
  EXPECT_EQ(c.getCyan(), 0);
  EXPECT_EQ(c.getMagenta(), 0);
  EXPECT_EQ(c.getYellow(), 0);
  EXPECT_EQ(c.getBlack(), 0);
}

TEST(CMYKColor, Addition) {
  CMYKColor a(30, 20, 10, 5);
  CMYKColor b(40, 50, 60, 70);
  CMYKColor result = a + b;
  EXPECT_EQ(result.getCyan(), 70);
  EXPECT_EQ(result.getMagenta(), 70);
  EXPECT_EQ(result.getYellow(), 70);
  EXPECT_EQ(result.getBlack(), 75);
}

TEST(CMYKColor, AdditionClamping) {
  CMYKColor a(80, 80, 80, 80);
  CMYKColor b(30, 30, 30, 30);
  CMYKColor result = a + b;
  // Should be clamped to 100
  EXPECT_EQ(result.getCyan(), 100);
  EXPECT_EQ(result.getMagenta(), 100);
  EXPECT_EQ(result.getYellow(), 100);
  EXPECT_EQ(result.getBlack(), 100);
}

TEST(CMYKColor, Multiply) {
  CMYKColor c(50, 40, 30, 20);
  CMYKColor result = c * 0.5;
  EXPECT_EQ(result.getCyan(), 25);
  EXPECT_EQ(result.getMagenta(), 20);
  EXPECT_EQ(result.getYellow(), 15);
  EXPECT_EQ(result.getBlack(), 10);
}

// =============================================================================
// CMYK <-> RGB conversion tests
// =============================================================================

TEST(ColorConversion, CMYKToRGB_Black) {
  CMYKColor cmyk(0, 0, 0, 100);
  RGBColor rgb = cmyk.toRGB();
  EXPECT_EQ(rgb.getRed(), 0);
  EXPECT_EQ(rgb.getGreen(), 0);
  EXPECT_EQ(rgb.getBlue(), 0);
}

TEST(ColorConversion, CMYKToRGB_White) {
  CMYKColor cmyk(0, 0, 0, 0);
  RGBColor rgb = cmyk.toRGB();
  EXPECT_EQ(rgb.getRed(), 255);
  EXPECT_EQ(rgb.getGreen(), 255);
  EXPECT_EQ(rgb.getBlue(), 255);
}

TEST(ColorConversion, CMYKToRGB_Red) {
  CMYKColor cmyk(0, 100, 100, 0);
  RGBColor rgb = cmyk.toRGB();
  EXPECT_EQ(rgb.getRed(), 255);
  EXPECT_EQ(rgb.getGreen(), 0);
  EXPECT_EQ(rgb.getBlue(), 0);
}

TEST(ColorConversion, CMYKToRGB_Green) {
  CMYKColor cmyk(100, 0, 100, 0);
  RGBColor rgb = cmyk.toRGB();
  EXPECT_EQ(rgb.getRed(), 0);
  EXPECT_EQ(rgb.getGreen(), 255);
  EXPECT_EQ(rgb.getBlue(), 0);
}

TEST(ColorConversion, CMYKToRGB_Blue) {
  CMYKColor cmyk(100, 100, 0, 0);
  RGBColor rgb = cmyk.toRGB();
  EXPECT_EQ(rgb.getRed(), 0);
  EXPECT_EQ(rgb.getGreen(), 0);
  EXPECT_EQ(rgb.getBlue(), 255);
}

TEST(ColorConversion, RGBToCMYK_Black) {
  RGBColor rgb(0, 0, 0);
  CMYKColor cmyk = rgb.toCMYK();
  EXPECT_EQ(cmyk.getCyan(), 0);
  EXPECT_EQ(cmyk.getMagenta(), 0);
  EXPECT_EQ(cmyk.getYellow(), 0);
  EXPECT_EQ(cmyk.getBlack(), 100);
}

TEST(ColorConversion, RGBToCMYK_White) {
  RGBColor rgb(255, 255, 255);
  CMYKColor cmyk = rgb.toCMYK();
  EXPECT_EQ(cmyk.getCyan(), 0);
  EXPECT_EQ(cmyk.getMagenta(), 0);
  EXPECT_EQ(cmyk.getYellow(), 0);
  EXPECT_EQ(cmyk.getBlack(), 0);
}

TEST(ColorConversion, RGBToCMYK_Red) {
  RGBColor rgb(255, 0, 0);
  CMYKColor cmyk = rgb.toCMYK();
  EXPECT_EQ(cmyk.getCyan(), 0);
  EXPECT_EQ(cmyk.getMagenta(), 100);
  EXPECT_EQ(cmyk.getYellow(), 100);
  EXPECT_EQ(cmyk.getBlack(), 0);
}

TEST(ColorConversion, RGBToCMYK_Green) {
  RGBColor rgb(0, 255, 0);
  CMYKColor cmyk = rgb.toCMYK();
  EXPECT_EQ(cmyk.getCyan(), 100);
  EXPECT_EQ(cmyk.getMagenta(), 0);
  EXPECT_EQ(cmyk.getYellow(), 100);
  EXPECT_EQ(cmyk.getBlack(), 0);
}

TEST(ColorConversion, RGBToCMYK_Blue) {
  RGBColor rgb(0, 0, 255);
  CMYKColor cmyk = rgb.toCMYK();
  EXPECT_EQ(cmyk.getCyan(), 100);
  EXPECT_EQ(cmyk.getMagenta(), 100);
  EXPECT_EQ(cmyk.getYellow(), 0);
  EXPECT_EQ(cmyk.getBlack(), 0);
}

TEST(ColorConversion, RoundTripRGBToCMYKToRGB) {
  // A mid-range color
  RGBColor original(128, 64, 192);
  CMYKColor cmyk = original.toCMYK();
  RGBColor back = cmyk.toRGB();

  // Allow some tolerance due to integer rounding in CMYK (0-100 range)
  EXPECT_NEAR(back.getRed(), original.getRed(), 5);
  EXPECT_NEAR(back.getGreen(), original.getGreen(), 5);
  EXPECT_NEAR(back.getBlue(), original.getBlue(), 5);
}

// =============================================================================
// ColorVariant helper tests
// =============================================================================

TEST(ColorVariant, ToRGB) {
  ColorVariant cv_rgb = RGBColor(100, 200, 50);
  RGBColor rgb = to_rgb(cv_rgb);
  EXPECT_EQ(rgb.getRed(), 100);
  EXPECT_EQ(rgb.getGreen(), 200);
  EXPECT_EQ(rgb.getBlue(), 50);

  ColorVariant cv_cmyk = CMYKColor(0, 0, 0, 0);
  RGBColor rgb_from_cmyk = to_rgb(cv_cmyk);
  EXPECT_EQ(rgb_from_cmyk.getRed(), 255);
  EXPECT_EQ(rgb_from_cmyk.getGreen(), 255);
  EXPECT_EQ(rgb_from_cmyk.getBlue(), 255);
}

TEST(ColorVariant, ToCMYK) {
  ColorVariant cv_cmyk = CMYKColor(50, 30, 20, 10);
  CMYKColor cmyk = to_cmyk(cv_cmyk);
  EXPECT_EQ(cmyk.getCyan(), 50);
  EXPECT_EQ(cmyk.getMagenta(), 30);
  EXPECT_EQ(cmyk.getYellow(), 20);
  EXPECT_EQ(cmyk.getBlack(), 10);
}
