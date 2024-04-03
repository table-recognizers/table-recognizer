#ifndef TABLE_RECOGNIZER_CLIENT_ImageLoader_H
#define TABLE_RECOGNIZER_CLIENT_ImageLoader_H

#include <iostream>

#include <opencv2/opencv.hpp>


namespace table_recognizer::client {

cv::Mat LoadImage(std::string path);

}  // namespace table_recognizer::client

#endif