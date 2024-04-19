#include "client/image_processing/line_detector_adjuster.h"

namespace table_recognizer::client::image_processing {

namespace utils = table_recognizer::utils;

LineDetectorAdjuster::LineDetectorAdjuster(const cv::Mat& image,
                                           const CannyParameters canny_params,
                                           const HoughParameters hough_params) {
  line_detector_ =
      std::make_shared<LineDetector>(image, canny_params, hough_params);
  trackbars_ = {
      {"C.Threshold1", static_cast<int>(canny_params.threshold1), 500,
       [&](int value) { line_detector_->setCannyThreshold1((double)value); }},
      {"C.Threshold 2", static_cast<int>(canny_params.threshold2), 1000,
       [&](int value) { line_detector_->setCannyThreshold2((double)value); }},
      {"H.Rho", static_cast<int>(hough_params.rho), 10,
       [&](int value) { line_detector_->setHoughRho((double)value); }},
      {"H.Theta", static_cast<int>(M_PI / hough_params.theta), 1000,
       [&](int value) { line_detector_->setHoughTheta(M_PI / value); }},
      {"H.Threshold", hough_params.threshold, 500,
       [&](int value) { line_detector_->setHoughThreshold(value); }},
      {"H.MinLineLength", static_cast<int>(hough_params.min_line_length), 500,
       [&](int value) {
         line_detector_->setHoughMinLineLength((double)value);
       }},
      {"H.MaxLineGap", static_cast<int>(hough_params.max_line_gap), 1000,
       [&](int value) { line_detector_->setHoughMaxLineGap((double)value); }}};
}

static void ShowLinesOnEdges(std::vector<utils::Line>& lines, cv::Mat edges,
                             std::string window_name) {
  cv::Mat image_with_lines;
  cv::cvtColor(edges, image_with_lines, cv::COLOR_GRAY2BGR);

  for (size_t i = 0; i < lines.size(); ++i) {
    cv::Scalar color = cv::Scalar(i * 10 % 255, i * 20 % 255, i * 30 % 255);
    cv::line(image_with_lines, lines[i].start, lines[i].end, color, cv::LINE_4);
  }
  cv::imshow(window_name, image_with_lines);
}

static void OnTrackbarChange(int new_value, void* userdata) {
  auto casted_userdata =
      static_cast<std::pair<LineDetectorAdjuster*, std::function<void(int)>>*>(
          userdata);
  LineDetectorAdjuster* self = casted_userdata->first;
  std::function<void(int)> setValueFunction = casted_userdata->second;
  auto line_detector = self->getLineDetector();
  casted_userdata->second(new_value);
  auto detected_lines = line_detector->DetectLines();
  ShowLinesOnEdges(detected_lines, line_detector->getDetectedEdges(),
                   casted_userdata->first->getWindowName());
}

std::shared_ptr<LineDetector> LineDetectorAdjuster::getLineDetector() const {
  return line_detector_;
}
std::string LineDetectorAdjuster::getWindowName() const { return window_name_; }

void LineDetectorAdjuster::Run() {
  cv::namedWindow(window_name_, cv::WindowFlags::WINDOW_GUI_EXPANDED);

  std::cout << trackbars_.size() << std::endl;
  for (auto& trackbar : trackbars_) {
    auto userdata =
        new std::pair<LineDetectorAdjuster*, std::function<void(int)>>(
            std::make_pair(this, trackbar.setValue));
    cv::createTrackbar(trackbar.name, window_name_, &trackbar.value,
                       trackbar.max_value, OnTrackbarChange, userdata);
  }

  cv::waitKey(0);
}

}  // namespace table_recognizer::client::image_processing
