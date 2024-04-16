#include "client/image_processing/image_loader.h"

namespace table_recognizer::client::image_loader {

cv::Mat LoadImage(std::string path) {
  cv::Mat image = cv::imread(path);
  return image;
}

}  // namespace table_recognizer::client::image_loader
