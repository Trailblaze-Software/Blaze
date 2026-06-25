#pragma once

#include <cmath>
#include <stdexcept>
#include <string>

#include "contour/contour.hpp"
#include "grid/grid.hpp"
#include "tif/tif.hpp"

namespace {

inline void set_pixel_safe(Grid<RGBColor>& grid, int x, int y, const RGBColor& color) {
  if (x < 0 || y < 0) {
    return;
  }
  const size_t ux = static_cast<size_t>(x);
  const size_t uy = static_cast<size_t>(y);
  if (ux < grid.width() && uy < grid.height()) {
    grid[{ux, uy}] = color;
  }
}

inline void draw_filled_circle(Grid<RGBColor>& grid, const blaze::Point& center, int radius,
                               const RGBColor& color) {
  const int x0 = center.x;
  const int y0 = center.y;
  const int r2 = radius * radius;

  for (int y = -radius; y <= radius; ++y) {
    for (int x = -radius; x <= radius; ++x) {
      if (x * x + y * y <= r2) {
        set_pixel_safe(grid, x0 + x, y0 + y, color);
      }
    }
  }
}

inline void draw_line(Grid<RGBColor>& grid, const blaze::Point& p1, const blaze::Point& p2,
                      const RGBColor& color, int thickness) {
  int x0 = p1.x;
  int y0 = p1.y;
  int x1 = p2.x;
  int y1 = p2.y;

  const int dx = std::abs(x1 - x0);
  const int dy = std::abs(y1 - y0);
  const int sx = (x0 < x1) ? 1 : -1;
  const int sy = (y0 < y1) ? 1 : -1;
  int err = dx - dy;

  while (true) {
    if (thickness > 1) {
      draw_filled_circle(grid, blaze::Point(x0, y0), thickness / 2, color);
    } else {
      set_pixel_safe(grid, x0, y0, color);
    }

    if (x0 == x1 && y0 == y1) {
      break;
    }

    const int e2 = 2 * err;
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

inline RGBColor blend_rgba(const RGBColor& foreground, const RGBColor& background) {
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

template <typename ColorT>
Grid<RGBColor> rgb_grid_from_geo_grid(const Geo<Grid<ColorT>>& grid) {
  Grid<RGBColor> rgb_grid(grid.width(), grid.height());
#pragma omp parallel for
  for (size_t y = 0; y < grid.height(); ++y) {
    for (size_t x = 0; x < grid.width(); ++x) {
      rgb_grid[{x, y}] = grid[{x, y}].toRGB();
    }
  }
  return rgb_grid;
}

template <typename ColorT>
void draw_geo_grid(GeoImgGrid& dest, const Geo<Grid<ColorT>>& other,
                   std::optional<blaze::InterpolationMode> interpolation) {
  Coordinate2D<double> top_left =
      dest.transform().projection_to_pixel(other.transform().pixel_to_projection({0, 0}));
  const double dx_ratio = other.transform().dx() / dest.transform().dx();
  const double dy_ratio = other.transform().dy() / dest.transform().dy();
  const int full_w = static_cast<int>(other.width() * dx_ratio);
  const int full_h = static_cast<int>(other.height() * dy_ratio);
  const blaze::Rect roi_full(static_cast<int>(top_left.x()), static_cast<int>(top_left.y()), full_w,
                             full_h);

  Grid<RGBColor> source_grid = [&]() {
    if constexpr (std::same_as<ColorT, RGBColor>) {
      return static_cast<Grid<RGBColor>>(other);
    } else {
      return rgb_grid_from_geo_grid(other);
    }
  }();

  Grid<RGBColor> resized_grid(0, 0);
  const blaze::InterpolationMode mode = interpolation.value_or(blaze::InterpolationMode::NEAREST);
  source_grid.resize_to(resized_grid, blaze::Size(full_w, full_h), mode);

  const blaze::Rect img_bounds(0, 0, static_cast<int>(dest.width()),
                               static_cast<int>(dest.height()));
  const blaze::Rect roi = roi_full & img_bounds;
  if (roi.width <= 0 || roi.height <= 0) {
    return;
  }

  const blaze::Rect src_rect(roi.x - roi_full.x, roi.y - roi_full.y, roi.width, roi.height);
  const Grid<RGBColor> resized_roi = resized_grid.slice_rect(src_rect);

#pragma omp parallel for
  for (int y = 0; y < roi.height; ++y) {
    for (int x = 0; x < roi.width; ++x) {
      const RGBColor foreground = resized_roi[{static_cast<size_t>(x), static_cast<size_t>(y)}];
      const size_t dest_x = static_cast<size_t>(roi.x + x);
      const size_t dest_y = static_cast<size_t>(roi.y + y);
      const RGBColor background = dest[{dest_x, dest_y}];
      dest[{dest_x, dest_y}] = blend_rgba(foreground, background);
    }
  }
}

}  // namespace

template <typename U>
inline Grid<RGBColor> Grid<U>::slice_rect(const blaze::Rect& rect) const
  requires std::same_as<U, RGBColor>
{
  Grid<RGBColor> result(static_cast<size_t>(rect.width), static_cast<size_t>(rect.height));
  for (int y = 0; y < rect.height; ++y) {
    for (int x = 0; x < rect.width; ++x) {
      const int src_x = rect.x + x;
      const int src_y = rect.y + y;
      if (src_x >= 0 && static_cast<size_t>(src_x) < width() && src_y >= 0 &&
          static_cast<size_t>(src_y) < height()) {
        result[{static_cast<size_t>(x), static_cast<size_t>(y)}] =
            (*this)[{static_cast<size_t>(src_x), static_cast<size_t>(src_y)}];
      }
    }
  }
  return result;
}

template <typename U>
inline void Grid<U>::resize_to(Grid<RGBColor>& dst, const blaze::Size& size,
                               blaze::InterpolationMode mode) const
  requires std::same_as<U, RGBColor>
{
  if (this == &dst) {
    Grid<RGBColor> temp = *this;
    temp.resize_to(dst, size, mode);
    return;
  }
  if (size.width <= 0 || size.height <= 0) {
    dst = Grid<RGBColor>(0, 0);
    return;
  }
  if (width() == 0 || height() == 0) {
    dst = Grid<RGBColor>(static_cast<size_t>(size.width), static_cast<size_t>(size.height));
    return;
  }

  dst = Grid<RGBColor>(static_cast<size_t>(size.width), static_cast<size_t>(size.height));

  const int src_width = static_cast<int>(width());
  const int src_height = static_cast<int>(height());

  if (mode == blaze::InterpolationMode::NEAREST) {
    const float x_ratio =
        (size.width == 1) ? 0.0f : static_cast<float>(src_width - 1) / (size.width - 1);
    const float y_ratio =
        (size.height == 1) ? 0.0f : static_cast<float>(src_height - 1) / (size.height - 1);

    for (int y = 0; y < size.height; ++y) {
      for (int x = 0; x < size.width; ++x) {
        const int src_x = static_cast<int>(std::round(x * x_ratio));
        const int src_y = static_cast<int>(std::round(y * y_ratio));
        dst[{static_cast<size_t>(x), static_cast<size_t>(y)}] =
            (*this)[{static_cast<size_t>(src_x), static_cast<size_t>(src_y)}];
      }
    }
    return;
  }

  const float x_ratio =
      (size.width == 1) ? 0.0f : static_cast<float>(src_width - 1) / (size.width - 1);
  const float y_ratio =
      (size.height == 1) ? 0.0f : static_cast<float>(src_height - 1) / (size.height - 1);

  for (int y = 0; y < size.height; ++y) {
    for (int x = 0; x < size.width; ++x) {
      const float src_x = x * x_ratio;
      const float src_y = y * y_ratio;

      const int x1 = static_cast<int>(src_x);
      const int y1 = static_cast<int>(src_y);
      const int x2 = std::min(x1 + 1, src_width - 1);
      const int y2 = std::min(y1 + 1, src_height - 1);

      const float x_weight = src_x - x1;
      const float y_weight = src_y - y1;

      const RGBColor c11 = (*this)[{static_cast<size_t>(x1), static_cast<size_t>(y1)}];
      const RGBColor c21 = (*this)[{static_cast<size_t>(x2), static_cast<size_t>(y1)}];
      const RGBColor c12 = (*this)[{static_cast<size_t>(x1), static_cast<size_t>(y2)}];
      const RGBColor c22 = (*this)[{static_cast<size_t>(x2), static_cast<size_t>(y2)}];

      const uint8_t b = static_cast<uint8_t>(c11.getBlue() * (1 - x_weight) * (1 - y_weight) +
                                             c21.getBlue() * x_weight * (1 - y_weight) +
                                             c12.getBlue() * (1 - x_weight) * y_weight +
                                             c22.getBlue() * x_weight * y_weight);
      const uint8_t g = static_cast<uint8_t>(c11.getGreen() * (1 - x_weight) * (1 - y_weight) +
                                             c21.getGreen() * x_weight * (1 - y_weight) +
                                             c12.getGreen() * (1 - x_weight) * y_weight +
                                             c22.getGreen() * x_weight * y_weight);
      const uint8_t r = static_cast<uint8_t>(c11.getRed() * (1 - x_weight) * (1 - y_weight) +
                                             c21.getRed() * x_weight * (1 - y_weight) +
                                             c12.getRed() * (1 - x_weight) * y_weight +
                                             c22.getRed() * x_weight * y_weight);
      const uint8_t a = static_cast<uint8_t>(c11.getAlpha() * (1 - x_weight) * (1 - y_weight) +
                                             c21.getAlpha() * x_weight * (1 - y_weight) +
                                             c12.getAlpha() * (1 - x_weight) * y_weight +
                                             c22.getAlpha() * x_weight * y_weight);

      dst[{static_cast<size_t>(x), static_cast<size_t>(y)}] = RGBColor(r, g, b, a);
    }
  }
}

template <typename U>
inline void Grid<U>::draw_circle(const blaze::Point& center, int radius, const RGBColor& color,
                                 int thickness)
  requires std::same_as<U, RGBColor>
{
  if (thickness < 0) {
    draw_filled_circle(*this, center, radius, color);
    return;
  }
  if (thickness == 0 || thickness == 1) {
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
      set_pixel_safe(*this, center.x + x, center.y + y, color);
      set_pixel_safe(*this, center.x + y, center.y + x, color);
      set_pixel_safe(*this, center.x - y, center.y + x, color);
      set_pixel_safe(*this, center.x - x, center.y + y, color);
      set_pixel_safe(*this, center.x - x, center.y - y, color);
      set_pixel_safe(*this, center.x - y, center.y - x, color);
      set_pixel_safe(*this, center.x + y, center.y - x, color);
      set_pixel_safe(*this, center.x + x, center.y - y, color);

      if (err <= 0) {
        y += 1;
        err += 2 * y + 1;
      }
      if (err > 0) {
        x -= 1;
        err -= 2 * x + 1;
      }
    }
    return;
  }

  for (int r = radius - thickness / 2; r <= radius + thickness / 2; ++r) {
    if (r > 0) {
      draw_circle(center, r, color, 1);
    }
  }
}

template <typename U>
inline void Grid<U>::draw_polyline(const blaze::Point* points, int num_points, bool closed,
                                   const RGBColor& color, int thickness)
  requires std::same_as<U, RGBColor>
{
  if (num_points < 2) {
    return;
  }

  for (int i = 0; i < num_points - 1; ++i) {
    draw_line(*this, points[i], points[i + 1], color, thickness);
  }

  if (closed && num_points > 2) {
    draw_line(*this, points[num_points - 1], points[0], color, thickness);
  }
}

template <typename GridT>
inline void Geo<GridT>::draw(const Geo<Grid<RGBColor>>& other,
                             std::optional<blaze::InterpolationMode> interpolation)
  requires std::same_as<GridT, Grid<RGBColor>>
{
  draw_geo_grid(*this, other, interpolation);
}

template <typename GridT>
inline void Geo<GridT>::draw(const Geo<Grid<CMYKColor>>& other,
                             std::optional<blaze::InterpolationMode> interpolation)
  requires std::same_as<GridT, Grid<RGBColor>>
{
  draw_geo_grid(*this, other, interpolation);
}

template <typename GridT>
inline void Geo<GridT>::draw_point(const Coordinate2D<double>& point, const ColorVariant& color,
                                   double size)
  requires std::same_as<GridT, Grid<RGBColor>>
{
  const Coordinate2D<double> pixel_coord = transform().projection_to_pixel(point);
  this->draw_circle(blaze::Point(pixel_coord.x(), pixel_coord.y()),
                    static_cast<int>(size / transform().dx()), to_rgb(color), -1);
}

template <typename GridT>
inline void Geo<GridT>::draw(const Contour& contour, const ColorVariant& color, double width)
  requires std::same_as<GridT, Grid<RGBColor>>
{
  std::vector<blaze::Point> points;
  points.reserve(contour.points().size());
  for (const auto& contour_point : contour.points()) {
    const Coordinate2D<double> pixel_coord = transform().projection_to_pixel(contour_point);
    points.emplace_back(pixel_coord.x(), pixel_coord.y());
  }
  this->draw_polyline(points.data(), static_cast<int>(points.size()), false, to_rgb(color),
                      static_cast<int>(width / transform().dx()));
}

template <typename GridT>
inline void Geo<GridT>::draw(const std::vector<Coordinate2D<double>>& in_points,
                             const ColorVariant& color, double width)
  requires std::same_as<GridT, Grid<RGBColor>>
{
  std::vector<blaze::Point> points;
  points.reserve(in_points.size());
  for (const auto& point : in_points) {
    const Coordinate2D<double> pixel_coord = transform().projection_to_pixel(point);
    points.emplace_back(pixel_coord.x(), pixel_coord.y());
  }
  this->draw_polyline(points.data(), static_cast<int>(points.size()), false, to_rgb(color),
                      static_cast<int>(width / transform().dx()));
}

template <typename GridT>
inline void Geo<GridT>::save_to(const fs::path& path, const Extent2D& extent)
  requires std::same_as<GridT, Grid<RGBColor>>
{
  if (path.extension() == ".tif" || path.extension() == ".tiff") {
    write_to_tif(slice(extent), path);
    return;
  }
  throw std::runtime_error(
      "GeoImgGrid::save_to() called with unsupported format. All image output should use "
      "write_to_tif().");
}
