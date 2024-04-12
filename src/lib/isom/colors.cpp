#include "colors.hpp"

#include "lib/assert/assert.hpp"

RGBColor RGBColor::FromCMYK(const CMYKColor& cmyk) {
  double c = cmyk.getCyan() / 100.0;
  double m = cmyk.getMagenta() / 100.0;
  double y = cmyk.getYellow() / 100.0;
  double k = cmyk.getBlack() / 100.0;
  double r = 255 * (1 - c) * (1 - k);
  double g = 255 * (1 - m) * (1 - k);
  double b = 255 * (1 - y) * (1 - k);
  return RGBColor(r, g, b);
}

RGBColor::RGBColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : m_data{r, g, b, a} {
  for (auto i : m_data) {
    Assert(i >= 0 && i <= 255, "Invalid color value");
  }
}

CMYKColor::CMYKColor(unsigned char c, unsigned char m, unsigned char y, unsigned char k)
    : m_data{c, m, y, k} {
  for (auto i : m_data) {
    Assert(i >= 0 && i <= 100, "Invalid color value");
  }
}
CMYKColor CMYKColor::FromRGB(const RGBColor& rgb) {
  double c = 1 - rgb.getRed() / 255.0;
  double m = 1 - rgb.getGreen() / 255.0;
  double y = 1 - rgb.getBlue() / 255.0;
  double k = std::min({c, m, y});
  if (k == 1) {
    return CMYKColor(0, 0, 0, 100);
  }
  c = (c - k) / (1 - k);
  m = (m - k) / (1 - k);
  y = (y - k) / (1 - k);
  return CMYKColor(c, m, y, k);
}
CMYKColor RGBColor::toCMYK() const { return CMYKColor::FromRGB(*this); }


std::map<std::string, ColorVariant> COLOR_MAP;
