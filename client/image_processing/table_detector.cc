#include "client/image_processing/table_detector.h"

namespace table_recognizer::client::image_processing {

std::vector<cv::Rect> TableDetector::DetectCells(
    const cv::Mat input_image) const {
  cv::Mat gray_image;
  cv::cvtColor(input_image, gray_image, cv::COLOR_BGR2GRAY);

  // Binary threshold
  cv::Mat binary_threshold_image;
  cv::threshold(gray_image, binary_threshold_image, 128, 255,
                cv::THRESH_BINARY);
  binary_threshold_image = 255 - binary_threshold_image;

  // Otsu's threshold
  cv::Mat binary_otsu_image;
  cv::threshold(255 - gray_image, binary_otsu_image, 128, 255,
                cv::THRESH_BINARY | cv::THRESH_OTSU);

  // Vertical lines
  cv::Mat vertical_kernel = cv::getStructuringElement(
      cv::MORPH_RECT, cv::Size(1, gray_image.cols / 100));
  cv::Mat eroded_image;
  cv::erode(binary_otsu_image, eroded_image, vertical_kernel, cv::Point(-1, -1),
            3);
  cv::Mat vertical_lines;
  cv::dilate(eroded_image, vertical_lines, vertical_kernel, cv::Point(-1, -1),
             3);

  // Horizontal lines
  cv::Mat hor_kernel = cv::getStructuringElement(
      cv::MORPH_RECT, cv::Size(gray_image.cols / 100, 1));
  cv::Mat horizontal_lines;
  cv::erode(binary_threshold_image, horizontal_lines, hor_kernel,
            cv::Point(-1, -1), 5);
  cv::dilate(horizontal_lines, horizontal_lines, hor_kernel, cv::Point(-1, -1),
             5);

  // Combine vertical and horizontal lines
  cv::Mat vertical_horizontal_lines;
  cv::addWeighted(vertical_lines, 0.5, horizontal_lines, 0.5, 0.0,
                  vertical_horizontal_lines);
  cv::erode(~vertical_horizontal_lines, vertical_horizontal_lines,
            cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2)),
            cv::Point(-1, -1), 3);
  cv::threshold(vertical_horizontal_lines, vertical_horizontal_lines, 128, 255,
                cv::THRESH_BINARY | cv::THRESH_OTSU);

  // Bitwise operations
  cv::Mat bitxor, bitnot;
  cv::bitwise_xor(gray_image, vertical_horizontal_lines, bitxor);
  cv::bitwise_not(bitxor, bitnot);

  ////
  // Find contours
  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i> hierarchy;
  cv::findContours(vertical_horizontal_lines, contours, hierarchy,
                   cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

  // Get bounding boxes for each contour
  std::vector<cv::Rect> boundingBoxes;
  for (size_t i = 0; i < contours.size(); i++) {
    boundingBoxes.push_back(cv::boundingRect(contours[i]));
  }

  // Sort contours and bounding boxes by the y-coordinate of the bounding box
  std::vector<int> indices(contours.size());
  std::iota(indices.begin(), indices.end(), 0);

  std::sort(indices.begin(), indices.end(),
            [&boundingBoxes](int lhs, int rhs) -> bool {
              return boundingBoxes[lhs].y < boundingBoxes[rhs].y;
            });

  std::vector<std::vector<cv::Point>> sortedContours(contours.size());
  std::vector<cv::Rect> sortedBoundingBoxes(boundingBoxes.size());

  for (size_t i = 0; i < indices.size(); i++) {
    sortedContours[i] = contours[indices[i]];
    sortedBoundingBoxes[i] = boundingBoxes[indices[i]];
  }

  contours = sortedContours;
  boundingBoxes = sortedBoundingBoxes;
  ////

  std::vector<cv::Rect> boxes;
  for (size_t i = 0; i < contours.size(); i++) {
    cv::Rect rect = cv::boundingRect(contours[i]);
    if (rect.width < 1000 && rect.height < 500) {
      boxes.push_back(rect);
    }
  }

  return boxes;
}

Table TableDetector::Recognize(cv::Mat image) {
  std::vector<cv::Rect> cells = DetectCells(image);

  size_t table_width;
  for (size_t i = 1; i < cells.size(); i++) {
    if (abs(cells[i].y - cells[i - 1].y) > 5) {
      table_width = i;
      break;
    }
  }

  size_t table_height = cells.size() / table_width;

  std::cout << "table_width: " << table_width << std::endl;
  std::cout << "table_height: " << table_height << std::endl;

  Table tab(table_width, table_height);
  return tab;
}

}  // namespace table_recognizer::client::image_processing
