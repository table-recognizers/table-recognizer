#ifndef TABLE_RECOGNIZER_CLIENT_TABLE_DETECTOR_H_
#define TABLE_RECOGNIZER_CLIENT_TABLE_DETECTOR_H_

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>
#include <numeric>
#include <opencv2/opencv.hpp>

#include "client/image_processing/table.h"
#include "leptonica/allheaders.h"
#include "tesseract/baseapi.h"

namespace table_recognizer::client::image_processing {

class TableDetector {
 public:
  std::vector<cv::Rect> DetectCells(const cv::Mat input_image) const;
  Table Recognize(cv::Mat image);

 private:
  PIX *mat8ToPix(cv::Mat &mat8);
};

}  // namespace table_recognizer::client::image_processing

#endif  // TABLE_RECOGNIZER_CLIENT_TABLE_DETECTOR_H_
