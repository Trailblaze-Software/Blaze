

# File img\_grid.cpp

[**File List**](files.md) **>** [**grid**](dir_b440d1ddeab29faa8ab1c63476ee276f.md) **>** [**img\_grid.cpp**](img__grid_8cpp.md)

[Go to the documentation of this file](img__grid_8cpp.md)


```C++
#include "img_grid.hpp"

#include <stdexcept>

#include "image.hpp"
#include "tif/tif.hpp"

ImgGrid::~ImgGrid() = default;

void GeoImgGrid::save_to(const fs::path& path, const Extent2D& extent) {
  if (path.extension() == ".tif" || path.extension() == ".tiff") {
    GeoGrid<RGBColor> grid(GeoGrid<RGBColor>::FromGeoImg(*this));
    write_to_tif(grid.slice(extent), path);
  } else {
    ImgGrid::save_to(path);
  }
}

ImgGrid::ImgGrid(size_t width, size_t height)
    : GridData(width, height), m_img(std::make_unique<blaze::Image>(width, height)) {}

void ImgGrid::save_to(const fs::path& path) {
  // All image output goes through GDAL write_to_tif, not direct image writing
  (void)path;
  throw std::runtime_error(
      "ImgGrid::save_to() called but is not supported. All image output should use "
      "write_to_tif().");
}

RGBColor ImgGrid::get_rgb_color(size_t row, size_t col) const { return m_img->at(row, col); }

template <typename ColorT, typename>
GeoImgGrid::GeoImgGrid(const GeoGrid<ColorT>& grid)
    : ImgGrid(grid.width(), grid.height()), GeoGridData(grid) {
#pragma omp parallel for
  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      const RGBColor color = grid[{j, i}].toRGB();
      m_img->set(i, j, color);
    }
  }
}

template GeoImgGrid::GeoImgGrid(const GeoGrid<RGBColor>& grid);
template GeoImgGrid::GeoImgGrid(const GeoGrid<CMYKColor>& grid);

void GeoImgGrid::draw(const GeoImgGrid& other, std::optional<int> interpolation) {
  Coordinate2D<double> top_left =
      transform().projection_to_pixel(other.transform().pixel_to_projection({0, 0}));
  double dx_ratio = other.transform().dx() / transform().dx();
  double dy_ratio = other.transform().dy() / transform().dy();
  const int full_w = static_cast<int>(other.width() * dx_ratio);
  const int full_h = static_cast<int>(other.height() * dy_ratio);
  const blaze::Rect roi_full(static_cast<int>(top_left.x()), static_cast<int>(top_left.y()), full_w,
                             full_h);

  blaze::Image resized_img;
  blaze::InterpolationMode mode = (interpolation.value_or(0) == 1)
                                      ? blaze::InterpolationMode::LINEAR
                                      : blaze::InterpolationMode::NEAREST;
  other.m_img->resize(resized_img, blaze::Size(full_w, full_h), mode);

  const blaze::Rect img_bounds(0, 0, m_img->cols(), m_img->rows());
  const blaze::Rect roi = roi_full & img_bounds;
  if (roi.width <= 0 || roi.height <= 0) {
    return;
  }

  const blaze::Rect src_rect(roi.x - roi_full.x, roi.y - roi_full.y, roi.width, roi.height);
  blaze::Image resized_roi = resized_img.slice(src_rect);
  blaze::Image dest_roi = m_img->slice(roi);

  if (resized_roi.channels() == 4 && m_img->channels() == 4) {
    blaze::Image blended_img(dest_roi.width(), dest_roi.height());
#pragma omp parallel for
    for (int y = 0; y < dest_roi.rows(); ++y) {
      for (int x = 0; x < dest_roi.cols(); ++x) {
        RGBColor color_resized = resized_roi.at(y, x);
        RGBColor color_m_img = dest_roi.at(y, x);
        float alpha = color_resized.getAlpha() / 255.0f;
        float beta = color_m_img.getAlpha() / 255.0f;

        // Standard alpha blending: result = foreground * alpha + background * (1 - alpha)
        // When both have alpha: result = (fg * a_fg + bg * a_bg * (1 - a_fg)) / (a_fg + a_bg * (1 -
        // a_fg))
        float denom = alpha + beta * (1.0f - alpha);

        uint8_t b, g, r;
        if (denom > 0.001f) {
          b = static_cast<uint8_t>(
              (alpha * color_resized.getBlue() + beta * color_m_img.getBlue() * (1.0f - alpha)) /
              denom);
          g = static_cast<uint8_t>(
              (alpha * color_resized.getGreen() + beta * color_m_img.getGreen() * (1.0f - alpha)) /
              denom);
          r = static_cast<uint8_t>(
              (alpha * color_resized.getRed() + beta * color_m_img.getRed() * (1.0f - alpha)) /
              denom);
        } else {
          // Both fully transparent, keep background
          b = color_m_img.getBlue();
          g = color_m_img.getGreen();
          r = color_m_img.getRed();
        }

        blended_img.set(y, x, RGBColor(r, g, b, 255));
      }
    }

    // Copy blended result back to destination ROI
    for (int y = 0; y < roi.height; ++y) {
      for (int x = 0; x < roi.width; ++x) {
        m_img->set(roi.y + y, roi.x + x, blended_img.at(y, x));
      }
    }
  } else {
    // Simple copy without alpha blending
    for (int y = 0; y < roi.height; ++y) {
      for (int x = 0; x < roi.width; ++x) {
        m_img->set(roi.y + y, roi.x + x, resized_roi.at(y, x));
      }
    }
  }
}
void GeoImgGrid::draw_point(const Coordinate2D<double>& point, const ColorVariant& color,
                            double size) {
  Coordinate2D<double> pixel_coord = transform().projection_to_pixel(point);
  m_img->draw_circle(blaze::Point(pixel_coord.x(), pixel_coord.y()), size / transform().dx(),
                     to_rgb(color), -1);
}

void GeoImgGrid::draw(const Contour& contour, const ColorVariant& color, double width) {
  std::vector<blaze::Point> points;
  points.reserve(contour.points().size());
  for (const auto& point : contour.points()) {
    Coordinate2D<double> pixel_coord = transform().projection_to_pixel(point);
    points.emplace_back(pixel_coord.x(), pixel_coord.y());
  }
  m_img->draw_polyline(points.data(), static_cast<int>(points.size()), false, to_rgb(color),
                       width / transform().dx());
}

void GeoImgGrid::draw(const std::vector<Coordinate2D<double>>& in_points, const ColorVariant& color,
                      double width) {
  std::vector<blaze::Point> points;
  points.reserve(in_points.size());
  for (const auto& point : in_points) {
    Coordinate2D<double> pixel_coord = transform().projection_to_pixel(point);
    points.emplace_back(pixel_coord.x(), pixel_coord.y());
  }
  m_img->draw_polyline(points.data(), static_cast<int>(points.size()), false, to_rgb(color),
                       width / transform().dx());
}
```


