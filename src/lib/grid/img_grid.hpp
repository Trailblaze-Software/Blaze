#pragma once

#include <opencv2/imgproc.hpp>

#include "contour/contour.hpp"
#include "isom/colors.hpp"

class ImgGrid : public GridData {
 protected:
  cv::Mat m_img;

 public:
  ImgGrid(size_t height, size_t width, int type = CV_8UC4)
      : GridData(height, width), m_img(width, height, type) {}

  void save_to(const fs::path &path) { cv::imwrite(path.string(), m_img); }

  RGBColor get_rgb_color(size_t row, size_t col) const {
    cv::Vec4b v = m_img.at<cv::Vec4b>(row, col);
    return RGBColor(v[2], v[1], v[0], v[3]);
  }
};

class GeoImgGrid : public ImgGrid, public GeoGridData {
 public:
  GeoImgGrid(size_t width, size_t height, GeoTransform &&transform, GeoProjection &&projection)
      : ImgGrid(width, height), GeoGridData(std::move(transform), std::move(projection)) {}

  template <typename ColorT, typename = std::enable_if_t<std::is_base_of_v<Color, ColorT>>>
  GeoImgGrid(const GeoGrid<ColorT> &grid)
      : ImgGrid(grid.width(), grid.height()), GeoGridData(grid) {
    for (size_t i = 0; i < grid.height(); i++) {
      for (size_t j = 0; j < grid.width(); j++) {
        const RGBColor color = grid[{j, i}].toRGB();
        m_img.at<cv::Vec4b>(i, j) =
            cv::Vec4b(color.getBlue(), color.getGreen(), color.getRed(), color.getAlpha());
      }
    }
  }

  void draw(const GeoImgGrid &other, int interpolation = cv::INTER_NEAREST) {
    Coordinate2D<double> top_left =
        transform().projection_to_pixel(other.transform().pixel_to_projection({0, 0}));
    double dx_ratio = other.transform().dx() / transform().dx();
    double dy_ratio = other.transform().dy() / transform().dy();
    std::cout << "Width: " << other.width() << " Height: " << other.height() << std::endl;
    std::cout << "dx_ratio: " << dx_ratio << " dy_ratio: " << dy_ratio << std::endl;
    cv::Rect roi(top_left.x(), top_left.y(), other.width() * dx_ratio, other.height() * dy_ratio);
    cv::Mat resized_img;
    cv::resize(other.m_img, resized_img,
               cv::Size(other.width() * dx_ratio, other.height() * dy_ratio), 0, 0, interpolation);
    if (resized_img.channels() == 4 && m_img.channels() == 4) {
      cv::Mat alpha_other, alpha_m_img;
      std::vector<cv::Mat> channels_other, channels_m_img;
      cv::split(resized_img, channels_other);
      std::cout << roi << " " << m_img.size() << std::endl;
      std::cout << roi.width << " " << m_img.size().width << std::endl;
      cv::split(m_img(roi), channels_m_img);
      alpha_other = channels_other[3];
      alpha_m_img = channels_m_img[3];

      alpha_other.convertTo(alpha_other, CV_32F, 1.0 / 255.0);
      alpha_m_img.convertTo(alpha_m_img, CV_32F, 1.0 / 255.0);

      cv::Mat blended_img = cv::Mat::zeros(m_img(roi).size(), CV_8UC4);
      for (int y = 0; y < m_img(roi).rows; ++y) {
        for (int x = 0; x < m_img(roi).cols; ++x) {
          float alpha = alpha_other.at<float>(y, x);
          float beta = alpha_m_img.at<float>(y, x);

          cv::Vec4b color_resized = resized_img.at<cv::Vec4b>(y, x);
          cv::Vec4b color_m_img = m_img(roi).at<cv::Vec4b>(y, x);

          for (int c = 0; c < 3; ++c) {
            blended_img.at<cv::Vec4b>(y, x)[c] =
                (alpha * color_resized[c] + beta * color_m_img[c] * (1 - alpha)) /
                (alpha + beta * (1 - alpha));
          }
          blended_img.at<cv::Vec4b>(y, x)[3] = 255;  // Set alpha channel to 255
        }
      }

      blended_img.copyTo(m_img(roi));
    } else {
      resized_img.copyTo(m_img(roi));
    }
  }

  void draw(const Contour &contour, const ColorVariant &color, au::QuantityD<au::Meters> width) {
    std::vector<std::vector<cv::Point>> points;
    points.push_back({});
    for (const auto &point : contour.points()) {
      Coordinate2D<double> pixel_coord = transform().projection_to_pixel(point);
      points[0].push_back({cv::Point(pixel_coord.x(), pixel_coord.y())});
    }
    int line_width_pixels = width / transform().dx_m();
    cv::polylines(m_img, points, false, to_rgb(color).toScalar(), line_width_pixels, cv::LINE_8);
  }

  void save_to(const fs::path &path);
};
