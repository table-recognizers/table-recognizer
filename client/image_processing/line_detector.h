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

struct CannyParameters {
  double threshold1;
  double threshold2;
  CannyParameters(double threshold1, double threshold2)
      : threshold1(threshold1), threshold2(threshold2) {}
};

struct HoughParameters {
  double rho;
  double theta;
  int threshold;
  double min_line_length;
  double max_line_gap;
  HoughParameters(double rho, double theta, int threshold,
                  double min_line_length, double max_line_gap)
      : rho(rho),
        theta(theta),
        threshold(threshold),
        min_line_length(min_line_length),
        max_line_gap(max_line_gap) {}
};

class LineDetector {
 private:
  cv::Mat image_;
  CannyParameters canny_params_;
  HoughParameters hough_params_;
  cv::Mat detected_edges_;

 public:
  LineDetector(const cv::Mat& image, const CannyParameters& canny_params,
               const HoughParameters& hough_params);

  void setImage(const cv::Mat& image);
  void setCannyThreshold1(const double threshold1);
  void setCannyThreshold2(const double threshold2);
  void setHoughRho(const double rho);
  void setHoughTheta(const double theta);
  void setHoughThreshold(const int threshold);
  void setHoughMinLineLength(const double min_line_length);
  void setHoughMaxLineGap(const double max_line_gap);
  cv::Mat getImage() const;
  double getCannyThreshold1() const;
  double getCannyThreshold2() const;
  double getHoughRho() const;
  double getHoughTheta() const;
  int getHoughThreshold() const;
  double getHoughMinLineLength() const;
  double getHoughMaxLineGap() const;
  cv::Mat getDetectedEdges() const;

  std::vector<utils::Line> DetectLines();
};

}  // namespace table_recognizer::client::image_processing

#endif  // TABLE_RECOGNIZER_CLIENT_LINE_DETECTOR_H_
