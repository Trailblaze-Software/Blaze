

# File img\_grid.hpp

[**File List**](files.md) **>** [**grid**](dir_b440d1ddeab29faa8ab1c63476ee276f.md) **>** [**img\_grid.hpp**](img__grid_8hpp.md)

[Go to the documentation of this file](img__grid_8hpp.md)


```C++
#pragma once

#include <atomic>
#include <cmath>
#include <span>
#include <stdexcept>
#include <string>

#include "config_input/config_input.hpp"
#include "contour/contour.hpp"
#include "geometry/polygon.hpp"
#include "grid/grid.hpp"
#include "isom/colors.hpp"
#include "methods/water/water.hpp"
#include "tif/tif.hpp"
#include "utilities/progress_tracker.hpp"

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
  if (thickness > 1) {
    const double x0 = p1.x + 0.5;
    const double y0 = p1.y + 0.5;
    const double x1 = p2.x + 0.5;
    const double y1 = p2.y + 0.5;
    const double dx = x1 - x0;
    const double dy = y1 - y0;
    const double len2 = dx * dx + dy * dy;
    if (len2 < 1e-12) {
      draw_filled_circle(grid, p1, thickness / 2, color);
      return;
    }

    const double radius = thickness * 0.5;
    const double r2 = radius * radius;
    const int min_x = std::max(0, static_cast<int>(std::floor(std::min(x0, x1) - radius)));
    const int max_x = std::min(static_cast<int>(grid.width()) - 1,
                               static_cast<int>(std::ceil(std::max(x0, x1) + radius)));
    const int min_y = std::max(0, static_cast<int>(std::floor(std::min(y0, y1) - radius)));
    const int max_y = std::min(static_cast<int>(grid.height()) - 1,
                               static_cast<int>(std::ceil(std::max(y0, y1) + radius)));

    for (int y = min_y; y <= max_y; ++y) {
      const double py = y + 0.5;
      for (int x = min_x; x <= max_x; ++x) {
        const double px = x + 0.5;
        double t = ((px - x0) * dx + (py - y0) * dy) / len2;
        t = std::clamp(t, 0.0, 1.0);
        const double closest_x = x0 + t * dx;
        const double closest_y = y0 + t * dy;
        const double dist2 =
            (px - closest_x) * (px - closest_x) + (py - closest_y) * (py - closest_y);
        if (dist2 <= r2) {
          set_pixel_safe(grid, x, y, color);
        }
      }
    }
    return;
  }

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
    set_pixel_safe(grid, x0, y0, color);

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

inline Grid<RGBColor> resized_rgb_roi(const GeoImgGrid& dest, const Geo<Grid<RGBColor>>& other,
                                      std::optional<blaze::InterpolationMode> interpolation,
                                      blaze::Rect& out_roi) {
  const Coordinate2D<double> top_left =
      dest.transform().projection_to_pixel(other.transform().pixel_to_projection({0, 0}));
  const double dx_ratio = other.transform().dx() / dest.transform().dx();
  const double dy_ratio = other.transform().dy() / dest.transform().dy();
  const int full_w = static_cast<int>(other.width() * dx_ratio);
  const int full_h = static_cast<int>(other.height() * dy_ratio);
  const blaze::Rect roi_full(static_cast<int>(top_left.x()), static_cast<int>(top_left.y()), full_w,
                             full_h);

  Grid<RGBColor> resized_grid(0, 0);
  const blaze::InterpolationMode mode = interpolation.value_or(blaze::InterpolationMode::NEAREST);
  other.resize_to(resized_grid, blaze::Size(full_w, full_h), mode);

  const blaze::Rect img_bounds(0, 0, static_cast<int>(dest.width()),
                               static_cast<int>(dest.height()));
  out_roi = roi_full & img_bounds;
  if (out_roi.width <= 0 || out_roi.height <= 0) {
    return Grid<RGBColor>(0, 0);
  }

  const blaze::Rect src_rect(out_roi.x - roi_full.x, out_roi.y - roi_full.y, out_roi.width,
                             out_roi.height);
  return resized_grid.slice_rect(src_rect);
}

inline void append_scanline_intersections(double scan_y,
                                          const std::vector<Coordinate2D<double>>& ring,
                                          std::vector<double>& intersections) {
  if (ring.size() < 3) {
    return;
  }
  for (size_t i = 0, j = ring.size() - 1; i < ring.size(); j = i++) {
    const double y0 = ring[j].y();
    const double y1 = ring[i].y();
    if ((y0 > scan_y) == (y1 > scan_y)) {
      continue;
    }
    const double x0 = ring[j].x();
    const double x1 = ring[i].x();
    intersections.push_back(x0 + (scan_y - y0) * (x1 - x0) / (y1 - y0));
  }
}

template <typename GridT>
  requires std::same_as<GridT, Grid<RGBColor>>
void draw_filled_polygon_impl(Geo<GridT>& grid, const PolygonWithHoles& poly,
                              const RGBColor& fill_color) {
  if (poly.exterior.size() < 3) {
    return;
  }

  const Extent2D extent = ring_extent(poly.exterior);
  const Coordinate2D<double> top_left_px =
      grid.transform().projection_to_pixel({extent.minx, extent.maxy});
  const Coordinate2D<double> bottom_right_px =
      grid.transform().projection_to_pixel({extent.maxx, extent.miny});

  const int col_min = std::max(0, static_cast<int>(std::floor(top_left_px.x())));
  const int col_max = std::min(static_cast<int>(grid.width()) - 1,
                               static_cast<int>(std::ceil(bottom_right_px.x())) - 1);
  const int row_min = std::max(0, static_cast<int>(std::floor(top_left_px.y())));
  const int row_max = std::min(static_cast<int>(grid.height()) - 1,
                               static_cast<int>(std::ceil(bottom_right_px.y())) - 1);
  if (col_min > col_max || row_min > row_max) {
    return;
  }

  std::vector<double> intersections;
  intersections.reserve(poly.exterior.size() + 8);
  for (int row = row_min; row <= row_max; ++row) {
    const double scan_y = grid.transform().pixel_to_projection({0.0, row + 0.5}).y();
    intersections.clear();
    append_scanline_intersections(scan_y, poly.exterior, intersections);
    for (const std::vector<Coordinate2D<double>>& hole : poly.holes) {
      append_scanline_intersections(scan_y, hole, intersections);
    }
    if (intersections.size() < 2) {
      continue;
    }
    std::sort(intersections.begin(), intersections.end());
    for (size_t i = 0; i + 1 < intersections.size(); i += 2) {
      const Coordinate2D<double> start_px =
          grid.transform().projection_to_pixel({intersections[i], scan_y});
      const Coordinate2D<double> end_px =
          grid.transform().projection_to_pixel({intersections[i + 1], scan_y});
      const int span_col_min =
          std::max(col_min, static_cast<int>(std::floor(std::min(start_px.x(), end_px.x()))));
      const int span_col_max =
          std::min(col_max, static_cast<int>(std::ceil(std::max(start_px.x(), end_px.x()))) - 1);
      for (int col = span_col_min; col <= span_col_max; ++col) {
        grid[{static_cast<size_t>(col), static_cast<size_t>(row)}] = fill_color;
      }
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
inline void Geo<GridT>::draw(const Geo<Grid<RGBColor>>& other, ProgressTracker&& progress_tracker,
                             GeoGridCompositeMode composite_mode,
                             std::optional<blaze::InterpolationMode> interpolation)
  requires std::same_as<GridT, Grid<RGBColor>>
{
  START_TRACKER(composite_mode == GeoGridCompositeMode::AlphaBlend ? "drawing raster layer"
                                                                   : "drawing overlay layer");

  blaze::Rect roi;
  const Grid<RGBColor> resized_roi = resized_rgb_roi(*this, other, interpolation, roi);
  if (roi.width <= 0 || roi.height <= 0) {
    return;
  }

#pragma omp parallel for
  for (int y = 0; y < roi.height; ++y) {
    for (int x = 0; x < roi.width; ++x) {
      const RGBColor foreground = resized_roi[{static_cast<size_t>(x), static_cast<size_t>(y)}];
      if (foreground.getAlpha() == 0) {
        continue;
      }
      const size_t dest_x = static_cast<size_t>(roi.x + x);
      const size_t dest_y = static_cast<size_t>(roi.y + y);
      if (composite_mode == GeoGridCompositeMode::AlphaBlend) {
        (*this)[{dest_x, dest_y}] = blend_rgba(foreground, (*this)[{dest_x, dest_y}]);
      } else {
        (*this)[{dest_x, dest_y}] =
            RGBColor(foreground.getRed(), foreground.getGreen(), foreground.getBlue(), 255);
      }
    }
  }
}

template <typename GridT>
inline void Geo<GridT>::draw_filled_polygon(const PolygonWithHoles& poly, const ColorVariant& color)
  requires std::same_as<GridT, Grid<RGBColor>>
{
  const RGBColor rgb = to_rgb(color);
  draw_filled_polygon_impl(*this, poly, RGBColor(rgb.getRed(), rgb.getGreen(), rgb.getBlue(), 255));
}

template <typename GridT>
inline void Geo<GridT>::rasterize_filled_polygons(const std::vector<PolygonWithHoles>& polygons,
                                                  const ColorVariant& color,
                                                  ProgressTracker&& progress_tracker)
  requires std::same_as<GridT, Grid<RGBColor>>
{
  const RGBColor rgb = to_rgb(color);
  const RGBColor fill_color(rgb.getRed(), rgb.getGreen(), rgb.getBlue(), 255);

  const int count = static_cast<int>(polygons.size());
  if (count == 0) {
    return;
  }

  for (int i = 0; i < count; ++i) {
    draw_filled_polygon_impl(*this, polygons[static_cast<size_t>(i)], fill_color);
    progress_tracker.set_proportion(static_cast<double>(i) / count);
  }
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

inline void draw_geo_polyline(GeoImgGrid& grid, std::span<const Coordinate2D<double>> geo_points,
                              const ColorVariant& color, double width) {
  if (geo_points.size() < 2) {
    return;
  }
  std::vector<blaze::Point> points;
  points.reserve(geo_points.size());
  for (const Coordinate2D<double>& geo_point : geo_points) {
    const Coordinate2D<double> pixel = grid.transform().projection_to_pixel(geo_point);
    points.emplace_back(pixel.x(), pixel.y());
  }
  const int thickness = static_cast<int>(width / grid.transform().dx());
  grid.draw_polyline(points.data(), static_cast<int>(points.size()), false, to_rgb(color),
                     thickness);
}

template <typename GridT>
inline void Geo<GridT>::draw_contours(const std::vector<Contour>& contours,
                                      const ContourConfigs& configs, const double render_scale,
                                      const bool base_layer_only,
                                      ProgressTracker&& progress_tracker)
  requires std::same_as<GridT, Grid<RGBColor>>
{
  START_TRACKER(base_layer_only ? "drawing base contours" : "drawing form lines");
  const double line_width_scale = render_scale / 1000.0;
  for (const Contour& contour : contours) {
    const bool is_form_line = configs.layer_name_from_height(contour.height()) == "103_Form_Line";
    if (base_layer_only == is_form_line) {
      continue;
    }
    const ContourConfig& contour_config = configs.pick_from_height(contour.height());
    draw_geo_polyline(*this, contour.points(), contour_config.color,
                      contour_config.width * line_width_scale);
  }
}

template <typename GridT>
inline void Geo<GridT>::draw_streams(const std::vector<Stream>& streams, const WaterConfigs& water,
                                     const double render_scale, ProgressTracker&& progress_tracker)
  requires std::same_as<GridT, Grid<RGBColor>>
{
  START_TRACKER("drawing streams");
  const double line_width_scale = render_scale / 1000.0;
  for (const Stream& stream : streams) {
    const WaterConfig& water_config = water.config_from_catchment(stream.catchment);
    draw_geo_polyline(*this, stream.coords, water_config.color,
                      water_config.width * line_width_scale);
  }
}

template <typename GridT>
inline void Geo<GridT>::save_to(const fs::path& path, const Extent2D& extent,
                                ProgressTracker&& progress_tracker)
  requires std::same_as<GridT, Grid<RGBColor>>
{
  if (path.extension() == ".tif" || path.extension() == ".tiff") {
    write_to_tif(slice(extent), path, std::move(progress_tracker));
    return;
  }
  throw std::runtime_error(
      "GeoImgGrid::save_to() called with unsupported format. All image output should use "
      "write_to_tif().");
}
```


