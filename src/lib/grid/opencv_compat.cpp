// Release OpenCV binaries use the standard libstdc++ container ABI. Compile this
// file without _GLIBCXX_DEBUG so cv::imwrite links against system OpenCV.
// See CV_IGNORE_DEBUG_BUILD_GUARD in CMakeLists.txt.
#ifdef _GLIBCXX_DEBUG
#undef _GLIBCXX_DEBUG
#endif
#ifdef _GLIBCXX_DEBUG_PEDANTIC
#undef _GLIBCXX_DEBUG_PEDANTIC
#endif

#include "opencv_compat.hpp"

#include <opencv2/imgcodecs.hpp>

bool blaze_cv_imwrite(const std::string& path, const cv::Mat& img) {
  return cv::imwrite(path, img);
}
