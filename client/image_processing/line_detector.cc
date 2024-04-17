#include "client/image_processing/line_detector.h"

namespace table_recognizer::client::image_processing {

namespace utils = table_recognizer::utils;

LineDetector::LineDetector(const cv::Mat& image,
                           const CannyParameters& canny_params,
                           const HoughParameters& hough_params)
    : image_(image), canny_params_(canny_params), hough_params_(hough_params) {}

void LineDetector::setImage(const cv::Mat& image) { image_ = image; }
void LineDetector::setCannyThreshold1(const double threshold1) {
  canny_params_.threshold1 = threshold1;
}
void LineDetector::setCannyThreshold2(const double threshold2) {
  canny_params_.threshold2 = threshold2;
}
void LineDetector::setHoughRho(const double rho) { hough_params_.rho = rho; }
void LineDetector::setHoughTheta(const double theta) {
  hough_params_.theta = theta;
}
void LineDetector::setHoughThreshold(const int threshold) {
  hough_params_.threshold = threshold;
}
void LineDetector::setHoughMinLineLength(const double min_line_length) {
  hough_params_.min_line_length = min_line_length;
}
void LineDetector::setHoughMaxLineGap(const double max_line_gap) {
  hough_params_.max_line_gap = max_line_gap;
}
cv::Mat LineDetector::getImage() const { return image_; }
double LineDetector::getCannyThreshold1() const {
  return canny_params_.threshold1;
}
double LineDetector::getCannyThreshold2() const {
  return canny_params_.threshold2;
}
double LineDetector::getHoughRho() const { return hough_params_.rho; }
double LineDetector::getHoughTheta() const { return hough_params_.theta; }
int LineDetector::getHoughThreshold() const { return hough_params_.threshold; }
double LineDetector::getHoughMinLineLength() const {
  return hough_params_.min_line_length;
}
double LineDetector::getHoughMaxLineGap() const {
  return hough_params_.max_line_gap;
}
cv::Mat LineDetector::getDetectedEdges() const { return detected_edges_; }

std::vector<utils::Line> LineDetector::DetectLines() {
  cv::Mat gray;
  cv::cvtColor(image_, gray, cv::COLOR_BGR2GRAY);

  cv::Canny(gray, detected_edges_, canny_params_.threshold1,
            canny_params_.threshold2);

  std::vector<cv::Vec4f> vec_lines;
  cv::HoughLinesP(detected_edges_, vec_lines, hough_params_.rho,
                  hough_params_.theta, hough_params_.threshold,
                  hough_params_.min_line_length, hough_params_.max_line_gap);
  auto lines = std::vector<utils::Line>(vec_lines.size());
  for (size_t i = 0; i < vec_lines.size(); i++) {
    lines[i].start = cv::Point2f(vec_lines[i][0], vec_lines[i][1]);
    lines[i].end = cv::Point2f(vec_lines[i][2], vec_lines[i][3]);
  }

  return lines;
}

}  // namespace table_recognizer::client::image_processing
