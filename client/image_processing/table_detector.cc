#include "client/image_processing/table_detector.h"

namespace table_recognizer::client::image_processing {

Table TableDetector::Recognize(cv::Mat image) {
  Table tab(1, 1);
  return tab;
}

}  // namespace table_recognizer::client::image_processing
