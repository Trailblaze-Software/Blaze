

# File img\_grid.cpp

[**File List**](files.md) **>** [**grid**](dir_b440d1ddeab29faa8ab1c63476ee276f.md) **>** [**img\_grid.cpp**](img__grid_8cpp.md)

[Go to the documentation of this file](img__grid_8cpp.md)


```C++
#include "img_grid.hpp"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

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
ImgGrid::ImgGrid(size_t height, size_t width, std::optional<int> type)
    : GridData(height, width),
      m_img(std::make_unique<cv::Mat>(width, height, type.value_or(CV_8UC4))) {}
void ImgGrid::save_to(const fs::path& path) { cv::imwrite(path.string(), *m_img); }
RGBColor ImgGrid::get_rgb_color(size_t row, size_t col) const {
  cv::Vec4b v = m_img->at<cv::Vec4b>(row, col);
  return RGBColor(v[2], v[1], v[0], v[3]);
}

template <typename ColorT, typename>
GeoImgGrid::GeoImgGrid(const GeoGrid<ColorT>& grid)
    : ImgGrid(grid.width(), grid.height()), GeoGridData(grid) {
#pragma omp parallel for
  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      const RGBColor color = grid[{j, i}].toRGB();
      m_img->at<cv::Vec4b>(i, j) =
          cv::Vec4b(color.getBlue(), color.getGreen(), color.getRed(), color.getAlpha());
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
  cv::Rect roi(top_left.x(), top_left.y(), other.width() * dx_ratio, other.height() * dy_ratio);
  cv::Mat resized_img;
  cv::resize(*other.m_img, resized_img,
             cv::Size(other.width() * dx_ratio, other.height() * dy_ratio), 0, 0,
             interpolation.value_or(cv::INTER_NEAREST));
  if (resized_img.channels() == 4 && m_img->channels() == 4) {
    cv::Mat alpha_other, alpha_m_img;
    std::vector<cv::Mat> channels_other, channels_m_img;
    cv::split(resized_img, channels_other);
    cv::split((*m_img)(roi), channels_m_img);
    alpha_other = channels_other[3];
    alpha_m_img = channels_m_img[3];

    alpha_other.convertTo(alpha_other, CV_32F, 1.0 / 255.0);
    alpha_m_img.convertTo(alpha_m_img, CV_32F, 1.0 / 255.0);

    cv::Mat blended_img = cv::Mat::zeros((*m_img)(roi).size(), CV_8UC4);
#pragma omp parallel for
    for (int y = 0; y < (*m_img)(roi).rows; ++y) {
      for (int x = 0; x < (*m_img)(roi).cols; ++x) {
        float alpha = alpha_other.at<float>(y, x);
        float beta = alpha_m_img.at<float>(y, x);

        cv::Vec4b color_resized = resized_img.at<cv::Vec4b>(y, x);
        cv::Vec4b color_m_img = (*m_img)(roi).at<cv::Vec4b>(y, x);

        for (int c = 0; c < 3; ++c) {
          blended_img.at<cv::Vec4b>(y, x)[c] =
              (alpha * color_resized[c] + beta * color_m_img[c] * (1 - alpha)) /
              (alpha + beta * (1 - alpha));
        }
        blended_img.at<cv::Vec4b>(y, x)[3] = 255;  // Set alpha channel to 255
      }
    }

    blended_img.copyTo((*m_img)(roi));
  } else {
    resized_img.copyTo((*m_img)(roi));
  }
}
void GeoImgGrid::draw_point(const Coordinate2D<double>& point, const ColorVariant& color,
                            double size) {
  Coordinate2D<double> pixel_coord = transform().projection_to_pixel(point);
  cv::circle(*m_img, cv::Point(pixel_coord.x(), pixel_coord.y()), size / transform().dx(),
             to_rgb(color).toScalar(), -1);
}
void GeoImgGrid::draw(const Contour& contour, const ColorVariant& color, double width) {
  std::vector<std::vector<cv::Point>> points;
  points.push_back({});
  for (const auto& point : contour.points()) {
    Coordinate2D<double> pixel_coord = transform().projection_to_pixel(point);
    points[0].push_back({cv::Point(pixel_coord.x(), pixel_coord.y())});
  }
  int line_width_pixels = width / transform().dx();
  cv::polylines(*m_img, points, false, to_rgb(color).toScalar(), line_width_pixels, cv::LINE_8);
}
void GeoImgGrid::draw(const std::vector<Coordinate2D<double>>& in_points, const ColorVariant& color,
                      double width) {
  std::vector<std::vector<cv::Point>> points;
  points.push_back({});
  for (const auto& point : in_points) {
    Coordinate2D<double> pixel_coord = transform().projection_to_pixel(point);
    points[0].push_back({cv::Point(pixel_coord.x(), pixel_coord.y())});
  }
  int line_width_pixels = width / transform().dx();
  cv::polylines(*m_img, points, false, to_rgb(color).toScalar(), line_width_pixels, cv::LINE_8);
}
```


