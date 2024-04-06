#ifndef TABLE_RECOGNIZER_CLIENT_TABLE_RECOGNIZER_H_
#define TABLE_RECOGNIZER_CLIENT_TABLE_RECOGNIZER_H_

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>
#include <opencv2/opencv.hpp>

#include "client/inc/table.h"

namespace table_recognizer::client::table_recognizer {

class Recogniser {

table::Table recogise (cv::Mat image);

};

}  // namespace table_recognizer::client::table_recognizer

#endif