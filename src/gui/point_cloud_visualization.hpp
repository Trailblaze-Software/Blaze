#pragma once

#include <array>
#include <cstdint>

#include "gui/point_octree.hpp"

enum class PointColorMode { File, Classification, Fixed };

inline std::array<uint8_t, 3> classification_palette_color(uint8_t classification) {
  switch (classification) {
    case 2:
      return {160, 120, 80};  // ground
    case 3:
      return {100, 180, 100};  // low vegetation
    case 4:
      return {60, 140, 60};  // medium vegetation
    case 5:
      return {30, 100, 30};  // high vegetation
    case 6:
      return {200, 80, 80};  // building
    case 7:
      return {120, 120, 120};  // low point
    case 8:
      return {255, 200, 0};  // model key point
    case 9:
      return {60, 120, 220};  // water
    case 17:
      return {180, 180, 180};  // bridge deck
    default:
      return {200, 200, 200};
  }
}

inline std::array<float, 4> point_display_color(const OctreePoint& point, PointColorMode mode,
                                                const std::array<uint8_t, 3>& fixed_color,
                                                float alpha = 1.0f) {
  std::array<uint8_t, 3> rgb = fixed_color;
  switch (mode) {
    case PointColorMode::File:
      if (point.has_file_rgb) {
        rgb = {point.file_r, point.file_g, point.file_b};
      } else {
        const uint8_t gray = static_cast<uint8_t>(point.intensity >> 8);
        rgb = {gray, gray, gray};
      }
      break;
    case PointColorMode::Classification:
      rgb = classification_palette_color(point.classification);
      break;
    case PointColorMode::Fixed:
      break;
  }
  return {rgb[0] / 255.f, rgb[1] / 255.f, rgb[2] / 255.f, alpha};
}
