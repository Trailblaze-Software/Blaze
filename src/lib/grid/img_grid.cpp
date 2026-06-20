#include "img_grid.hpp"

#include <opencv2/imgproc.hpp>

#include "opencv_compat.hpp"
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
void ImgGrid::save_to(const fs::path& path) { blaze_cv_imwrite(path.string(), *m_img); }
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
  const int full_w = static_cast<int>(other.width() * dx_ratio);
  const int full_h = static_cast<int>(other.height() * dy_ratio);
  const cv::Rect roi_full(static_cast<int>(top_left.x()), static_cast<int>(top_left.y()), full_w,
                          full_h);
  cv::Mat resized_img;
  blaze_cv_resize(*other.m_img, resized_img, cv::Size(full_w, full_h),
                  interpolation.value_or(cv::INTER_NEAREST));

  const cv::Rect img_bounds(0, 0, m_img->cols, m_img->rows);
  const cv::Rect roi = roi_full & img_bounds;
  if (roi.width <= 0 || roi.height <= 0) {
    return;
  }
  const cv::Rect src_rect(roi.x - roi_full.x, roi.y - roi_full.y, roi.width, roi.height);
  cv::Mat resized_roi = resized_img(src_rect);
  cv::Mat dest_roi = (*m_img)(roi);

  if (resized_roi.channels() == 4 && m_img->channels() == 4) {
    cv::Mat alpha_other, alpha_m_img;
    blaze_cv_extract_channel(resized_roi, alpha_other, 3);
    blaze_cv_extract_channel(dest_roi, alpha_m_img, 3);

    blaze_cv_convert_to(alpha_other, alpha_other, CV_32F, 1.0 / 255.0, 0);
    blaze_cv_convert_to(alpha_m_img, alpha_m_img, CV_32F, 1.0 / 255.0, 0);

    cv::Mat blended_img = cv::Mat::zeros(dest_roi.size(), CV_8UC4);
#pragma omp parallel for
    for (int y = 0; y < dest_roi.rows; ++y) {
      for (int x = 0; x < dest_roi.cols; ++x) {
        float alpha = alpha_other.at<float>(y, x);
        float beta = alpha_m_img.at<float>(y, x);

        cv::Vec4b color_resized = resized_roi.at<cv::Vec4b>(y, x);
        cv::Vec4b color_m_img = dest_roi.at<cv::Vec4b>(y, x);

        for (int c = 0; c < 3; ++c) {
          blended_img.at<cv::Vec4b>(y, x)[c] =
              (alpha * color_resized[c] + beta * color_m_img[c] * (1 - alpha)) /
              (alpha + beta * (1 - alpha));
        }
        blended_img.at<cv::Vec4b>(y, x)[3] = 255;  // Set alpha channel to 255
      }
    }

    blaze_cv_copy_to(blended_img, dest_roi);
  } else {
    blaze_cv_copy_to(resized_roi, dest_roi);
  }
}
void GeoImgGrid::draw_point(const Coordinate2D<double>& point, const ColorVariant& color,
                            double size) {
  Coordinate2D<double> pixel_coord = transform().projection_to_pixel(point);
  blaze_cv_circle(*m_img, cv::Point(pixel_coord.x(), pixel_coord.y()), size / transform().dx(),
                  to_rgb(color).toScalar(), -1);
}
void GeoImgGrid::draw(const Contour& contour, const ColorVariant& color, double width) {
  std::vector<cv::Point> points;
  points.reserve(contour.points().size());
  for (const auto& point : contour.points()) {
    Coordinate2D<double> pixel_coord = transform().projection_to_pixel(point);
    points.emplace_back(pixel_coord.x(), pixel_coord.y());
  }
  blaze_cv_polylines(*m_img, points.data(), static_cast<int>(points.size()), false,
                     to_rgb(color).toScalar(), width / transform().dx());
}
void GeoImgGrid::draw(const std::vector<Coordinate2D<double>>& in_points, const ColorVariant& color,
                      double width) {
  std::vector<cv::Point> points;
  points.reserve(in_points.size());
  for (const auto& point : in_points) {
    Coordinate2D<double> pixel_coord = transform().projection_to_pixel(point);
    points.emplace_back(pixel_coord.x(), pixel_coord.y());
  }
  blaze_cv_polylines(*m_img, points.data(), static_cast<int>(points.size()), false,
                     to_rgb(color).toScalar(), width / transform().dx());
}
