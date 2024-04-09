#include "client/inc/line_detector.h"

namespace table_recognizer::client::line_detector {

namespace utils = table_recognizer::utils;

std::vector<utils::Line> DetectLines(const cv::Mat& image) {
  cv::Mat edges;
  return DetectLines(image, edges);
}

std::vector<utils::Line> DetectLines(const cv::Mat& image,
                                     cv::Mat& detected_edges) {
  cv::Mat gray;
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

  cv::Canny(gray, detected_edges, 50, 200);

  std::vector<cv::Vec4f> vec_lines;
  cv::HoughLinesP(detected_edges, vec_lines, 1, M_PI / 180, 220, 10, 250);
  auto lines = std::vector<utils::Line>(vec_lines.size());
  for (size_t i = 0; i < vec_lines.size(); i++) {
    lines[i].start = cv::Point2f(vec_lines[i][0], vec_lines[i][1]);
    lines[i].end = cv::Point2f(vec_lines[i][2], vec_lines[i][3]);
  }

  return lines;
}

}  // namespace table_recognizer::client::line_detector
