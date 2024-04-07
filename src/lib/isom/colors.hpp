#pragma once

#include <array>
#include <ostream>

class RGBColor;
class CMYKColor;

class Color {
  public:
  virtual RGBColor toRGB() const = 0;
  virtual CMYKColor toCMYK() const = 0;
  virtual ~Color() = default;
};

class RGBColor : public Color
{
  std::array<unsigned char, 3> m_data;

  public:
   RGBColor(unsigned char r, unsigned char g, unsigned char b);

   virtual RGBColor toRGB() const override { return *this; }
   virtual CMYKColor toCMYK() const override;

   static RGBColor FromCMYK(const CMYKColor& cmyk);

   unsigned char getRed() const { return m_data[0]; }
   unsigned char getGreen() const { return m_data[1]; }
   unsigned char getBlue() const { return m_data[2]; }

   unsigned char operator[](int index) const { return m_data[index]; }

   friend std::ostream& operator<<(std::ostream& os, const RGBColor& c) {
     return os << "(" << c.getRed() << ", " << c.getGreen() << ", " << c.getBlue() << ")";
    }

  virtual ~RGBColor(){};
};

class CMYKColor : public Color
{
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
   return CMYKColor(std::min(getCyan() + other.getCyan(), 100), std::min(getMagenta() + other.getMagenta(), 100),
                    std::min(getYellow() + other.getYellow(), 100), std::min(getBlack() + other.getBlack(), 100));
 }

 CMYKColor operator*(double factor) const {
   return CMYKColor(getCyan() * factor, getMagenta() * factor, getYellow() * factor,
                    getBlack() * factor);
 }

 friend std::ostream& operator<<(std::ostream& os, const CMYKColor& c) {
   return os << "(" << c.getCyan() << ", " << c.getMagenta() << ", " << c.getYellow() << ", "
             << c.getBlack() << ")";
  }

 virtual ~CMYKColor(){};
};

inline CMYKColor Black(0, 0, 0, 100);
inline CMYKColor Blue(100, 0, 0, 0);
inline CMYKColor Yellow(0, 27, 79, 0);
inline CMYKColor Green(76, 0, 91, 0);
inline CMYKColor DarkGreen(100, 0, 80, 30);
inline CMYKColor Brown(0, 56, 100, 18);
inline CMYKColor Purple(35, 85, 0, 0);
inline CMYKColor White(0, 0, 0, 0);
