#pragma once

#include <algorithm>
#include <cstdint>

namespace blaze {

struct Point {
  int x;
  int y;
  Point() : x(0), y(0) {}
  Point(int x_, int y_) : x(x_), y(y_) {}
  Point(double x_, double y_) : x(static_cast<int>(x_)), y(static_cast<int>(y_)) {}
};

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

struct Size {
  int width;
  int height;
  Size() : width(0), height(0) {}
  Size(int w, int h) : width(w), height(h) {}
};

enum class InterpolationMode { NEAREST, LINEAR };

}  // namespace blaze
