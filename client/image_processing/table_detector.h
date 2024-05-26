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

struct RectsTable {
 private:
  std::unique_ptr<std::vector<cv::Rect>> rects_;
  size_t width_;
  size_t height_;

 public:
  RectsTable(std::unique_ptr<std::vector<cv::Rect>> coords_of_cells,
             size_t width);
  size_t GetWidth() const;
  size_t GetHeight() const;
  cv::Rect GetCell(size_t x, size_t y) const;
  cv::Rect GetCell(size_t i) const;

  class Iterator {
   public:
    Iterator(const std::vector<cv::Rect>* rects, size_t index);
    cv::Rect operator*() const;
    Iterator& operator++();
    bool operator!=(const Iterator& other) const;

   private:
    const std::vector<cv::Rect>* rects_;
    size_t index_;
  };

  Iterator begin() const;
  Iterator end() const;
};

class TableDetector {
 public:
  std::vector<cv::Rect> DetectCells(const cv::Mat input_image) const;
  Table Recognize(cv::Mat image);

 private:
  PIX *mat8ToPix(cv::Mat &mat8);
};

}  // namespace table_recognizer::client::image_processing

#endif  // TABLE_RECOGNIZER_CLIENT_TABLE_DETECTOR_H_
