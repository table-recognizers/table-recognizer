#ifndef TABLE_RECOGNIZER_UTILS_LINE_H_
#define TABLE_RECOGNIZER_UTILS_LINE_H_

#include <opencv2/opencv.hpp>

namespace table_recognizer::utils {

struct Line {
  cv::Point start;
  cv::Point end;
};

}  // namespace table_recognizer::utils

#endif  // TABLE_RECOGNIZER_UTILS_LINE_H_
