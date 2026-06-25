

# File image.hpp

[**File List**](files.md) **>** [**grid**](dir_b440d1ddeab29faa8ab1c63476ee276f.md) **>** [**image.hpp**](image_8hpp.md)

[Go to the documentation of this file](image_8hpp.md)


```C++
#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <memory>

#include "isom/colors.hpp"

namespace blaze {

// Simple 2D point for drawing operations
struct Point {
  int x;
  int y;
  Point() : x(0), y(0) {}
  Point(int x_, int y_) : x(x_), y(y_) {}
  Point(double x_, double y_) : x(static_cast<int>(x_)), y(static_cast<int>(y_)) {}
};

// Simple rectangle for image operations
struct Rect {
  int x;
  int y;
  int width;
  int height;

  Rect() : x(0), y(0), width(0), height(0) {}
  Rect(int x_, int y_, int w, int h) : x(x_), y(y_), width(w), height(h) {}

  int right() const { return static_cast<int>(static_cast<int64_t>(x) + width); }
  int bottom() const { return static_cast<int>(static_cast<int64_t>(y) + height); }

  bool contains(int px, int py) const {
    return px >= x && px < right() && py >= y && py < bottom();
  }

  // Intersection operator
  Rect operator&(const Rect& other) const {
    int x1 = std::max(x, other.x);
    int y1 = std::max(y, other.y);
    int x2 = std::min(right(), other.right());
    int y2 = std::min(bottom(), other.bottom());
    if (x2 <= x1 || y2 <= y1) {
      return Rect(0, 0, 0, 0);
    }
    return Rect(x1, y1, x2 - x1, y2 - y1);
  }
};

// Size type for resize operations
struct Size {
  int width;
  int height;
  Size() : width(0), height(0) {}
  Size(int w, int h) : width(w), height(h) {}
};

enum class InterpolationMode { NEAREST, LINEAR };

// Simple 4-channel BGRA image for drawing operations
// Stores pixels in row-major order as BGRA
class Image {
 public:
  Image();
  Image(int width, int height);
  ~Image();

  Image(const Image& other);
  Image& operator=(const Image& other);
  Image(Image&& other) noexcept;
  Image& operator=(Image&& other) noexcept;

  int width() const { return m_width; }
  int height() const { return m_height; }
  int rows() const { return m_height; }
  int cols() const { return m_width; }
  int channels() const { return 4; }  // Always BGRA

  uint8_t* data() { return m_data.get(); }
  const uint8_t* data() const { return m_data.get(); }

  // Access pixel as RGBColor
  RGBColor at(int row, int col) const;
  void set(int row, int col, const RGBColor& color);

  // Get pointer to start of row
  uint8_t* row_ptr(int row) { return m_data.get() + row * m_width * 4; }
  const uint8_t* row_ptr(int row) const { return m_data.get() + row * m_width * 4; }

  // Extract a rectangular region
  Image slice(const Rect& rect) const;

  // Resize image
  void resize(Image& dst, const Size& size,
              InterpolationMode mode = InterpolationMode::NEAREST) const;

  // Copy image
  void copy_to(Image& dst) const;

  // Extract single channel
  void extract_channel(Image& dst, int channel_index) const;

  // Convert with scale and offset
  void convert_to(Image& dst, double alpha = 1.0, double beta = 0.0) const;

  // Drawing operations
  void draw_circle(const Point& center, int radius, const RGBColor& color, int thickness = -1);
  void draw_polyline(const Point* points, int num_points, bool closed, const RGBColor& color,
                     int thickness = 1);

 private:
  int m_width;
  int m_height;
  std::unique_ptr<uint8_t[]> m_data;

  void draw_line(const Point& p1, const Point& p2, const RGBColor& color, int thickness);
  void draw_filled_circle(const Point& center, int radius, const RGBColor& color);
  void set_pixel_safe(int x, int y, const RGBColor& color);
};

}  // namespace blaze
```


