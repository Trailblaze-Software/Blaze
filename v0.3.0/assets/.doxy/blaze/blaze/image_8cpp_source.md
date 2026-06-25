

# File image.cpp

[**File List**](files.md) **>** [**grid**](dir_b440d1ddeab29faa8ab1c63476ee276f.md) **>** [**image.cpp**](image_8cpp.md)

[Go to the documentation of this file](image_8cpp.md)


```C++
#include "image.hpp"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>

#include "assert/assert.hpp"

namespace blaze {

Image::Image() : m_width(0), m_height(0), m_data(nullptr) {}

Image::Image(int width, int height) : m_width(width), m_height(height) {
  if (width <= 0 || height <= 0) {
    m_width = 0;
    m_height = 0;
    m_data = nullptr;
    return;
  }
  size_t num_bytes = static_cast<size_t>(width) * static_cast<size_t>(height) * 4;
  m_data = std::make_unique<uint8_t[]>(num_bytes);
  std::memset(m_data.get(), 0, num_bytes);
}

Image::~Image() = default;

Image::Image(const Image& other) : m_width(other.m_width), m_height(other.m_height) {
  if (other.m_data) {
    size_t num_bytes = static_cast<size_t>(m_width) * static_cast<size_t>(m_height) * 4;
    m_data = std::make_unique<uint8_t[]>(num_bytes);
    std::memcpy(m_data.get(), other.m_data.get(), num_bytes);
  }
}

Image& Image::operator=(const Image& other) {
  if (this != &other) {
    if (other.m_data) {
      size_t num_bytes =
          static_cast<size_t>(other.m_width) * static_cast<size_t>(other.m_height) * 4;
      auto new_data = std::make_unique<uint8_t[]>(num_bytes);
      std::memcpy(new_data.get(), other.m_data.get(), num_bytes);
      m_data = std::move(new_data);
    } else {
      m_data.reset();
    }
    m_width = other.m_width;
    m_height = other.m_height;
  }
  return *this;
}

Image::Image(Image&& other) noexcept
    : m_width(other.m_width), m_height(other.m_height), m_data(std::move(other.m_data)) {
  other.m_width = 0;
  other.m_height = 0;
}

Image& Image::operator=(Image&& other) noexcept {
  if (this != &other) {
    m_width = other.m_width;
    m_height = other.m_height;
    m_data = std::move(other.m_data);
    other.m_width = 0;
    other.m_height = 0;
  }
  return *this;
}

RGBColor Image::at(int row, int col) const {
  Assert(row >= 0 && row < m_height && col >= 0 && col < m_width && m_data,
         "Image::at() out of bounds or null data (row=" + std::to_string(row) +
             ", col=" + std::to_string(col) + ", height=" + std::to_string(m_height) +
             ", width=" + std::to_string(m_width) + ")");
  const uint8_t* ptr = m_data.get() + (row * m_width + col) * 4;
  // Stored as BGRA, convert to RGB for RGBColor constructor
  return RGBColor(ptr[2], ptr[1], ptr[0], ptr[3]);
}

void Image::set(int row, int col, const RGBColor& color) {
  Assert(row >= 0 && row < m_height && col >= 0 && col < m_width && m_data,
         "Image::set() out of bounds or null data (row=" + std::to_string(row) +
             ", col=" + std::to_string(col) + ", height=" + std::to_string(m_height) +
             ", width=" + std::to_string(m_width) + ")");
  uint8_t* ptr = m_data.get() + (row * m_width + col) * 4;
  // Store as BGRA
  ptr[0] = color.getBlue();
  ptr[1] = color.getGreen();
  ptr[2] = color.getRed();
  ptr[3] = color.getAlpha();
}

Image Image::slice(const Rect& rect) const {
  Image result(rect.width, rect.height);
  for (int y = 0; y < rect.height; ++y) {
    for (int x = 0; x < rect.width; ++x) {
      int src_y = rect.y + y;
      int src_x = rect.x + x;
      if (src_y >= 0 && src_y < m_height && src_x >= 0 && src_x < m_width) {
        result.set(y, x, at(src_y, src_x));
      }
    }
  }
  return result;
}

void Image::resize(Image& dst, const Size& size, InterpolationMode mode) const {
  if (this == &dst) {
    Image temp(*this);
    temp.resize(dst, size, mode);
    return;
  }
  if (size.width <= 0 || size.height <= 0) {
    dst = Image();
    return;
  }
  if (m_width <= 0 || m_height <= 0) {
    dst = Image(size.width, size.height);
    return;
  }

  dst = Image(size.width, size.height);

  if (mode == InterpolationMode::NEAREST) {
    // Nearest neighbor interpolation
    const float x_ratio =
        (size.width == 1) ? 0.0f : static_cast<float>(m_width - 1) / (size.width - 1);
    const float y_ratio =
        (size.height == 1) ? 0.0f : static_cast<float>(m_height - 1) / (size.height - 1);

    for (int y = 0; y < size.height; ++y) {
      for (int x = 0; x < size.width; ++x) {
        int src_x = static_cast<int>(std::round(x * x_ratio));
        int src_y = static_cast<int>(std::round(y * y_ratio));
        dst.set(y, x, at(src_y, src_x));
      }
    }
  } else {
    // Bilinear interpolation
    const float x_ratio =
        (size.width == 1) ? 0.0f : static_cast<float>(m_width - 1) / (size.width - 1);
    const float y_ratio =
        (size.height == 1) ? 0.0f : static_cast<float>(m_height - 1) / (size.height - 1);

    for (int y = 0; y < size.height; ++y) {
      for (int x = 0; x < size.width; ++x) {
        float src_x = x * x_ratio;
        float src_y = y * y_ratio;

        int x1 = static_cast<int>(src_x);
        int y1 = static_cast<int>(src_y);
        int x2 = std::min(x1 + 1, m_width - 1);
        int y2 = std::min(y1 + 1, m_height - 1);

        float x_weight = src_x - x1;
        float y_weight = src_y - y1;

        RGBColor c11 = at(y1, x1);
        RGBColor c21 = at(y1, x2);
        RGBColor c12 = at(y2, x1);
        RGBColor c22 = at(y2, x2);

        uint8_t b = static_cast<uint8_t>(c11.getBlue() * (1 - x_weight) * (1 - y_weight) +
                                         c21.getBlue() * x_weight * (1 - y_weight) +
                                         c12.getBlue() * (1 - x_weight) * y_weight +
                                         c22.getBlue() * x_weight * y_weight);
        uint8_t g = static_cast<uint8_t>(c11.getGreen() * (1 - x_weight) * (1 - y_weight) +
                                         c21.getGreen() * x_weight * (1 - y_weight) +
                                         c12.getGreen() * (1 - x_weight) * y_weight +
                                         c22.getGreen() * x_weight * y_weight);
        uint8_t r = static_cast<uint8_t>(c11.getRed() * (1 - x_weight) * (1 - y_weight) +
                                         c21.getRed() * x_weight * (1 - y_weight) +
                                         c12.getRed() * (1 - x_weight) * y_weight +
                                         c22.getRed() * x_weight * y_weight);
        uint8_t a = static_cast<uint8_t>(c11.getAlpha() * (1 - x_weight) * (1 - y_weight) +
                                         c21.getAlpha() * x_weight * (1 - y_weight) +
                                         c12.getAlpha() * (1 - x_weight) * y_weight +
                                         c22.getAlpha() * x_weight * y_weight);

        dst.set(y, x, RGBColor(r, g, b, a));
      }
    }
  }
}

void Image::copy_to(Image& dst) const { dst = *this; }

void Image::extract_channel(Image& dst, int channel_index) const {
  if (!m_data) return;

  // Clamp channel_index to valid range
  if (channel_index < 0) channel_index = 0;
  if (channel_index > 3) channel_index = 3;

  if (this == &dst) {
    Image temp(*this);
    temp.extract_channel(dst, channel_index);
    return;
  }

  dst = Image(m_width, m_height);
  for (int y = 0; y < m_height; ++y) {
    for (int x = 0; x < m_width; ++x) {
      const uint8_t* src_ptr = m_data.get() + (y * m_width + x) * 4;
      uint8_t* dst_ptr = dst.m_data.get() + (y * m_width + x) * 4;
      uint8_t value = src_ptr[channel_index];
      dst_ptr[0] = dst_ptr[1] = dst_ptr[2] = value;
      dst_ptr[3] = 255;
    }
  }
}

void Image::convert_to(Image& dst, double alpha, double beta) const {
  if (!m_data) return;

  if (this == &dst) {
    Image temp(*this);
    temp.convert_to(dst, alpha, beta);
    return;
  }

  dst = Image(m_width, m_height);
  for (int y = 0; y < m_height; ++y) {
    for (int x = 0; x < m_width; ++x) {
      const uint8_t* src_ptr = m_data.get() + (y * m_width + x) * 4;
      uint8_t* dst_ptr = dst.m_data.get() + (y * m_width + x) * 4;
      for (int c = 0; c < 4; ++c) {
        double value = src_ptr[c] * alpha + beta;
        dst_ptr[c] = static_cast<uint8_t>(std::clamp(value, 0.0, 255.0));
      }
    }
  }
}

void Image::set_pixel_safe(int x, int y, const RGBColor& color) {
  if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
    set(y, x, color);
  }
}

void Image::draw_line(const Point& p1, const Point& p2, const RGBColor& color, int thickness) {
  // Bresenham's line algorithm
  int x0 = p1.x, y0 = p1.y;
  int x1 = p2.x, y1 = p2.y;

  int dx = std::abs(x1 - x0);
  int dy = std::abs(y1 - y0);
  int sx = (x0 < x1) ? 1 : -1;
  int sy = (y0 < y1) ? 1 : -1;
  int err = dx - dy;

  while (true) {
    // Draw thickness by drawing a circle at each point
    if (thickness > 1) {
      draw_filled_circle(Point(x0, y0), thickness / 2, color);
    } else {
      set_pixel_safe(x0, y0, color);
    }

    if (x0 == x1 && y0 == y1) break;

    int e2 = 2 * err;
    if (e2 > -dy) {
      err -= dy;
      x0 += sx;
    }
    if (e2 < dx) {
      err += dx;
      y0 += sy;
    }
  }
}

void Image::draw_filled_circle(const Point& center, int radius, const RGBColor& color) {
  int x0 = center.x;
  int y0 = center.y;
  int r2 = radius * radius;

  for (int y = -radius; y <= radius; ++y) {
    for (int x = -radius; x <= radius; ++x) {
      if (x * x + y * y <= r2) {
        set_pixel_safe(x0 + x, y0 + y, color);
      }
    }
  }
}

void Image::draw_circle(const Point& center, int radius, const RGBColor& color, int thickness) {
  if (thickness < 0) {
    // Filled circle
    draw_filled_circle(center, radius, color);
  } else if (thickness == 0 || thickness == 1) {
    // Thin outline using midpoint circle algorithm
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
      set_pixel_safe(center.x + x, center.y + y, color);
      set_pixel_safe(center.x + y, center.y + x, color);
      set_pixel_safe(center.x - y, center.y + x, color);
      set_pixel_safe(center.x - x, center.y + y, color);
      set_pixel_safe(center.x - x, center.y - y, color);
      set_pixel_safe(center.x - y, center.y - x, color);
      set_pixel_safe(center.x + y, center.y - x, color);
      set_pixel_safe(center.x + x, center.y - y, color);

      if (err <= 0) {
        y += 1;
        err += 2 * y + 1;
      }
      if (err > 0) {
        x -= 1;
        err -= 2 * x + 1;
      }
    }
  } else {
    // Thick outline: draw multiple circles
    for (int r = radius - thickness / 2; r <= radius + thickness / 2; ++r) {
      if (r > 0) {
        draw_circle(center, r, color, 1);
      }
    }
  }
}

void Image::draw_polyline(const Point* points, int num_points, bool closed, const RGBColor& color,
                          int thickness) {
  if (num_points < 2) return;

  for (int i = 0; i < num_points - 1; ++i) {
    draw_line(points[i], points[i + 1], color, thickness);
  }

  if (closed && num_points > 2) {
    draw_line(points[num_points - 1], points[0], color, thickness);
  }
}

}  // namespace blaze
```


