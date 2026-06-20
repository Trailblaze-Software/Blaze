#pragma once

#include <string>

namespace cv {
class Mat;
}

bool blaze_cv_imwrite(const std::string& path, const cv::Mat& img);
