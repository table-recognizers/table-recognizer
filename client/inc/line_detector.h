#ifndef TABLE_RECOGNIZER_CLIENT_LINE_DETECTOR_H_
#define TABLE_RECOGNIZER_CLIENT_LINE_DETECTOR_H_

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

namespace table_recognizer::client::line_detector {

struct Line {
  cv::Point2f start;
  cv::Point2f end;
};

std::vector<Line> DetectLines(const cv::Mat& image);
std::vector<Line> DetectLines(const cv::Mat& image, cv::Mat& detected_edges);

}  // namespace table_recognizer::client::line_detector

#endif  // TABLE_RECOGNIZER_CLIENT_LINE_DETECTOR_H_
