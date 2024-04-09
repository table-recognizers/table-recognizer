#ifndef TABLE_RECOGNIZER_UTILS_LINE_H_
#define TABLE_RECOGNIZER_UTILS_LINE_H_

#include <opencv2/opencv.hpp>

namespace table_recognizer::utils {

struct Line {
  cv::Point2f start;
  cv::Point2f end;
};

}  // namespace table_recognizer::utils

#endif  // TABLE_RECOGNIZER_UTILS_LINE_H_
