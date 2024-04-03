#include "client/inc/image_loader.h"

namespace table_recognizer::client {

cv::Mat LoadImage(std::string path) {
  cv::Mat image = cv::imread(path);
  return image;
}

}  // namespace table_recognizer::client
