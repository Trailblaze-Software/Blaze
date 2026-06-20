#pragma once

#include <opencv2/core.hpp>
#include <string>

bool blaze_cv_imwrite(const std::string& path, const cv::Mat& img);

void blaze_cv_resize(const cv::Mat& src, cv::Mat& dst, cv::Size size, int interpolation);

void blaze_cv_extract_channel(const cv::Mat& src, cv::Mat& channel, int index);

void blaze_cv_convert_to(const cv::Mat& src, cv::Mat& dst, int rtype, double alpha, double beta);

void blaze_cv_copy_to(const cv::Mat& src, cv::Mat& dst);

void blaze_cv_circle(cv::Mat& img, cv::Point center, int radius, const cv::Scalar& color,
                     int thickness);

void blaze_cv_polylines(cv::Mat& img, const cv::Point* points, int npoints, bool is_closed,
                        const cv::Scalar& color, int thickness);
