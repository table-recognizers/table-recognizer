#include "client/image_processing/table_detector.h"

namespace table_recognizer::client::image_processing {

RectsTable::RectsTable(std::unique_ptr<std::vector<cv::Rect>> rects,
                       size_t width)
    : rects_(std::move(rects)),
      width_(width),
      height_(rects_->size() / width) {}

size_t RectsTable::GetWidth() const { return width_; }

size_t RectsTable::GetHeight() const { return height_; }

cv::Rect RectsTable::GetCell(size_t x, size_t y) const {
  return rects_->at(y * width_ + x);
}

cv::Rect RectsTable::GetCell(size_t i) const { return rects_->at(i); }

RectsTable::Iterator::Iterator(const std::vector<cv::Rect> *rects, size_t index)
    : rects_(rects), index_(index) {}

cv::Rect RectsTable::Iterator::operator*() const { return (*rects_)[index_]; }

RectsTable::Iterator &RectsTable::Iterator::operator++() {
  ++index_;
  return *this;
}

bool RectsTable::Iterator::operator!=(const Iterator &other) const {
  return index_ != other.index_;
}

RectsTable::Iterator RectsTable::begin() const {
  return Iterator(rects_.get(), 0);
}

RectsTable::Iterator RectsTable::end() const {
  return Iterator(rects_.get(), rects_->size());
}

RectsTable TableDetector::DetectCells(const cv::Mat input_image) const {
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

  auto boxes = std::make_unique<std::vector<cv::Rect>>();
  for (size_t i = 0; i < contours.size(); i++) {
    cv::Rect rect = cv::boundingRect(contours[i]);
    if (rect.width < 1000 && rect.height < 500) {
      boxes->push_back(rect);
    }
  }

  size_t table_width;
  for (size_t i = 1; i < boxes->size(); i++) {
    if (abs(boxes->at(i).y - boxes->at(i - 1).y) > 5) {
      table_width = i;
      break;
    }
  }

  for (size_t i = 0; i < boxes->size() / table_width; i++) {
    std::sort(boxes->begin() + (i * table_width),
              boxes->begin() + (i * table_width + table_width),
              [](cv::Rect left, cv::Rect right) { return left.x < right.x; });
  }

  RectsTable coordsOfCellsTable(std::move(boxes), table_width);

  return coordsOfCellsTable;
}

Table TableDetector::Recognize(cv::Mat image) {
  RectsTable coordsOfCells = DetectCells(image);

  std::cout << "table_width: " << coordsOfCells.GetWidth() << std::endl;
  std::cout << "table_height: " << coordsOfCells.GetHeight() << std::endl;

  tesseract::TessBaseAPI *tesseract = new tesseract::TessBaseAPI();

#ifdef TESSDATA_PATH
  const char *tessdata_path = TESSDATA_PATH;
#endif

  if (tesseract->Init(tessdata_path, "rus")) {
    fprintf(stderr, "Cound not initialize tesseract.\n");
    exit(1);
  }

  for (size_t x = 0; x < coordsOfCells.GetWidth(); x++) {
    for (size_t y = 0; y < coordsOfCells.GetHeight(); y++) {
      cv::Mat cell_image = image(coordsOfCells.GetCell(x, y));
      cv::cvtColor(cell_image, cell_image, cv::COLOR_BGR2GRAY);
      auto pix_cell_image = mat8ToPix(cell_image);
      tesseract->SetImage(pix_cell_image);
      char *chars_text = tesseract->GetUTF8Text();
      std::string text(chars_text);

      std::cout << x << "." << y << "\"" << chars_text << "\"" << std::endl;

      delete[] chars_text;
      pixDestroy(&pix_cell_image);
    }
  }

  tesseract->End();

  Table tab(coordsOfCells.GetWidth(), coordsOfCells.GetHeight());
  return tab;
}

PIX *TableDetector::mat8ToPix(cv::Mat &mat8) {
  PIX *pixd = pixCreate(mat8.size().width, mat8.size().height, 8);
  for (int y = 0; y < mat8.rows; y++) {
    for (int x = 0; x < mat8.cols; x++) {
      pixSetPixel(pixd, x, y, (l_uint32)mat8.at<uchar>(y, x));
    }
  }
  return pixd;
}

}  // namespace table_recognizer::client::image_processing
