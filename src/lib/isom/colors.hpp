#pragma once

#include <array>
#include <map>
#include <ostream>
#include <variant>

class RGBColor;
class CMYKColor;

namespace cv {
template <typename T>
class Scalar_;
typedef Scalar_<double> Scalar;
}  // namespace cv

class Color {
 public:
  virtual RGBColor toRGB() const = 0;
  virtual CMYKColor toCMYK() const = 0;
  virtual ~Color() = default;
  Color& operator=(const Color&) = default;
  Color(const Color&) = default;
  Color() = default;
};

namespace cv {
template <typename T>
class Scalar_;
typedef Scalar_<double> Scalar;
}  // namespace cv

class RGBColor : public Color {
  std::array<unsigned char, 4> m_data;

 public:
  RGBColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
  RGBColor() { m_data.fill(0); };

  virtual RGBColor toRGB() const override { return *this; }
  virtual CMYKColor toCMYK() const override;

  static RGBColor FromCMYK(const CMYKColor& cmyk);

  unsigned char getRed() const { return m_data[0]; }
  unsigned char getGreen() const { return m_data[1]; }
  unsigned char getBlue() const { return m_data[2]; }
  unsigned char getAlpha() const { return m_data[3]; }

  const unsigned char& operator[](size_t index) const { return m_data[index]; }
  unsigned char& operator[](size_t index) { return m_data[index]; }
  cv::Scalar toScalar() const;

  friend std::ostream& operator<<(std::ostream& os, const RGBColor& c) {
    return os << "(" << c.getRed() << ", " << c.getGreen() << ", " << c.getBlue() << ")";
  }
};

class CMYKColor : public Color {
  std::array<unsigned char, 4> m_data;

 public:
  CMYKColor(unsigned char c, unsigned char m, unsigned char y, unsigned char k);
  CMYKColor() : CMYKColor(0, 0, 0, 0) {};

  virtual RGBColor toRGB() const override { return RGBColor::FromCMYK(*this); }
  virtual CMYKColor toCMYK() const override { return *this; }

  static CMYKColor FromRGB(const RGBColor& rgb);

  unsigned char getCyan() const { return m_data[0]; }
  unsigned char getMagenta() const { return m_data[1]; }
  unsigned char getYellow() const { return m_data[2]; }
  unsigned char getBlack() const { return m_data[3]; }

  unsigned char operator[](int index) const { return m_data[index]; }

  CMYKColor operator+(const CMYKColor& other) const {
    return CMYKColor(std::min(getCyan() + other.getCyan(), 100),
                     std::min(getMagenta() + other.getMagenta(), 100),
                     std::min(getYellow() + other.getYellow(), 100),
                     std::min(getBlack() + other.getBlack(), 100));
  }

  CMYKColor operator*(double factor) const {
    return CMYKColor(getCyan() * factor, getMagenta() * factor, getYellow() * factor,
                     getBlack() * factor);
  }

  friend std::ostream& operator<<(std::ostream& os, const CMYKColor& c) {
    return os << "(" << c.getCyan() << ", " << c.getMagenta() << ", " << c.getYellow() << ", "
              << c.getBlack() << ")";
  }
};

typedef std::variant<RGBColor, CMYKColor> ColorVariant;

inline RGBColor to_rgb(const ColorVariant& cv) {
  return std::visit([](auto&& arg) -> RGBColor { return arg.toRGB(); }, cv);
}
inline CMYKColor to_cmyk(const ColorVariant& cv) {
  return std::visit([](auto&& arg) -> CMYKColor { return arg.toCMYK(); }, cv);
}

extern std::map<std::string, ColorVariant> COLOR_MAP;
