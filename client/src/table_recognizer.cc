#include "client/inc/table_recognizer.h"

namespace table_recognizer::client::table_recognizer {

table::Table Recognizer::Recognize(cv::Mat image) {
  table::Table tab(1, 1);
  return tab;
}

}  // namespace table_recognizer::client::table_recognizer
