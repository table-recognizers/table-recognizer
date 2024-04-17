#ifndef TABLE_RECOGNIZER_CLIENT_LINE_DETECTOR_H_
#define TABLE_RECOGNIZER_CLIENT_LINE_DETECTOR_H_

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

#include "utils/inc/line.h"

namespace table_recognizer::client::image_processing {

namespace utils = table_recognizer::utils;

std::vector<utils::Line> DetectLines(const cv::Mat& image);
std::vector<utils::Line> DetectLines(const cv::Mat& image, cv::Mat& detected_edges);

}  // namespace table_recognizer::client::image_processing

#endif  // TABLE_RECOGNIZER_CLIENT_LINE_DETECTOR_H_
