#ifndef TABLE_RECOGNIZER_CLIENT_IMAGE_LOADER_H_
#define TABLE_RECOGNIZER_CLIENT_IMAGE_LOADER_H_

#include <iostream>
#include <opencv2/opencv.hpp>

namespace table_recognizer::client::image_loader {

cv::Mat LoadImage(std::string path);

}  // namespace table_recognizer::client::image_loader

#endif  // TABLE_RECOGNIZER_CLIENT_IMAGE_LOADER_H_
