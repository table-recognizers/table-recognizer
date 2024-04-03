#include "client/inc/ImageLoader.h"
namespace table_recognizer::client {

// namespace Table = table_recognizer::client::Table;
// std::string path1 = "C:\\Users\\grigo\\Downloads\\test";

cv::Mat LoadImage(std::string path) {
  cv::Mat image = cv::imread(path);
  return image;
}  // namespace table_recognizer::client::Table

}  // namespace table_recognizer::client
