#ifndef TABLE_RECOGNIZER_CLIENT_LINE_DETECTOR_ADJUSTER_H_
#define TABLE_RECOGNIZER_CLIENT_LINE_DETECTOR_ADJUSTER_H_

#include "client/image_processing/line_detector.h"

namespace table_recognizer::client::image_processing {

class LineDetectorAdjuster {
  struct TrackbarInfo {
    std::string name;
    int value;
    int max_value;
    std::function<void(int)> setValue;
  };

 private:
  std::shared_ptr<LineDetector> line_detector_;
  const std::string window_name_ = "Line Detector Adjuster";
  std::vector<TrackbarInfo> trackbars_;

 public:
  LineDetectorAdjuster(const cv::Mat &image, const CannyParameters canny_params,
                       const HoughParameters hough_params);

  std::shared_ptr<LineDetector> getLineDetector() const;
  std::string getWindowName() const;

  void Run();
};

}  // namespace table_recognizer::client::image_processing

#endif  // TABLE_RECOGNIZER_CLIENT_LINE_DETECTOR_ADJUSTER_H_
