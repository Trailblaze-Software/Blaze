#pragma once

#include <opencv2/imgproc.hpp>
#include "au/io.hh"
#include "contour/contour.hpp"
#include "printing/to_string.hpp"
#include "isom/colors.hpp"

class ImgGrid : public GridData {
  protected:
   cv::Mat m_img;
  public:
   ImgGrid(size_t height, size_t width, int type = CV_8UC4) : GridData(height, width), m_img(height, width, type) {}

};

class GeoImgGrid : public ImgGrid, public GeoGridData {
  public:
  GeoImgGrid(size_t width, size_t height, GeoTransform &&transform, GeoProjection &&projection)
      : ImgGrid(width, height), GeoGridData(std::move(transform), std::move(projection)) {}

  template<typename ColorT, typename = std::enable_if_t<std::is_base_of_v<Color, ColorT>>>
  GeoImgGrid(const GeoGrid<ColorT> &grid) : ImgGrid(grid.width(), grid.height()), GeoGridData(grid) {
    for (size_t i = 0; i < grid.height(); i++) {
      for (size_t j = 0; j < grid.width(); j++) {
        const RGBColor color = grid[{j, i}].toRGB();
        m_img.at<cv::Vec4b>(i, j) = cv::Vec4b(color.getBlue(), color.getGreen(), color.getRed(),
            color.getAlpha());
      }
    }
  }

  void draw(const GeoImgGrid &other, int interpolation = cv::INTER_NEAREST) {
    Coordinate2D<double> top_left = transform().projection_to_pixel(other.transform().pixel_to_projection({0, 0}));
    double dx_ratio = other.transform().dx() / transform().dx();
    double dy_ratio = other.transform().dy() / transform().dy();
    cv::Rect roi(top_left.x(), top_left.y(), other.width() * dx_ratio, other.height() * dy_ratio);
    cv::Mat resized_img;
    cv::resize(other.m_img, resized_img, cv::Size(other.width()*dx_ratio, other.height()*dy_ratio),
          0, 0, interpolation);
    //if (resized_img.channels() == 4 && m_img.channels() == 4) {
        //// Separate alpha channels
        //cv::Mat alpha_other, alpha_m_img;
        //std::vector<cv::Mat> channels_other, channels_m_img;
        //cv::split(resized_img, channels_other);
        //cv::split(m_img(roi), channels_m_img);
        //alpha_other = channels_other[3];
        //alpha_m_img = channels_m_img[3];
//
        //// Normalize alpha channels to range [0, 1]
        //alpha_other.convertTo(alpha_other, CV_32F, 1.0 / 255.0);
        //alpha_m_img.convertTo(alpha_m_img, CV_32F, 1.0 / 255.0);
//
        //// Blend images based on alpha channels
        //cv::Mat blended_img;
        //cv::addWeighted(resized_img(cv::Rect(0, 0, resized_img.cols, resized_img.rows - 1)),
                        //alpha_other, m_img(roi), alpha_m_img, 0.0, blended_img);
//
        //// Copy blended image to the specified region of the existing image
        //blended_img.copyTo(m_img(roi));
    //} else {
        //// If the images don't have alpha channels, simply copy
        resized_img.copyTo(m_img(roi));
    //}
  }

  void draw(const Contour& contour, const ColorVariant& color, au::QuantityD<au::Meters> width) {
    std::vector<std::vector<cv::Point>> points;
    points.push_back({});
    for (const auto& point : contour.points()) {
      Coordinate2D<double> pixel_coord = transform().projection_to_pixel(point);
      points[0].push_back({cv::Point(pixel_coord.x(), pixel_coord.y())});
    }
    int line_width_pixels = width / transform().dx_m();
    cv::polylines(m_img, points, false, to_rgb(color).toScalar(), line_width_pixels, cv::LINE_8);
  }

  void save_to(const fs::path &path) {
    cv::imwrite(path.string(), m_img);
  }

};


