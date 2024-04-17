#ifndef TABLE_RECOGNIZER_CLIENT_TABLE_RECOGNIZER_H_
#define TABLE_RECOGNIZER_CLIENT_TABLE_RECOGNIZER_H_

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>
#include <opencv2/opencv.hpp>

#include "client/image_processing/table.h"

namespace table_recognizer::client::image_processing {

class Recognizer {
 public:
  Table Recognize(cv::Mat image);
};

}  // namespace table_recognizer::client::image_processing

#endif  // TABLE_RECOGNIZER_CLIENT_TABLE_RECOGNIZER_H_
