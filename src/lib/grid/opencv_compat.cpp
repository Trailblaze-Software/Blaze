// Release OpenCV binaries use the standard libstdc++ container ABI. Compile this
// file without _GLIBCXX_DEBUG so OpenCV API calls link and run correctly against
// system OpenCV. See CV_IGNORE_DEBUG_BUILD_GUARD in CMakeLists.txt.
#ifdef _GLIBCXX_DEBUG
#undef _GLIBCXX_DEBUG
#endif
#ifdef _GLIBCXX_DEBUG_PEDANTIC
#undef _GLIBCXX_DEBUG_PEDANTIC
#endif

#include "opencv_compat.hpp"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

bool blaze_cv_imwrite(const std::string& path, const cv::Mat& img) {
  return cv::imwrite(path, img);
}

void blaze_cv_resize(const cv::Mat& src, cv::Mat& dst, cv::Size size, int interpolation) {
  cv::resize(src, dst, size, 0, 0, interpolation);
}

void blaze_cv_extract_channel(const cv::Mat& src, cv::Mat& channel, int index) {
  std::vector<cv::Mat> channels;
  cv::split(src, channels);
  channel = channels.at(index);
}

void blaze_cv_convert_to(const cv::Mat& src, cv::Mat& dst, int rtype, double alpha, double beta) {
  src.convertTo(dst, rtype, alpha, beta);
}

void blaze_cv_copy_to(const cv::Mat& src, cv::Mat& dst) { src.copyTo(dst); }

void blaze_cv_circle(cv::Mat& img, cv::Point center, int radius, const cv::Scalar& color,
                     int thickness) {
  cv::circle(img, center, radius, color, thickness);
}

void blaze_cv_polylines(cv::Mat& img, const cv::Point* points, int npoints, bool is_closed,
                        const cv::Scalar& color, int thickness) {
  const cv::Point* const pts[] = {points};
  const int npts[] = {npoints};
  cv::polylines(img, pts, npts, 1, is_closed, color, thickness, cv::LINE_8);
}
