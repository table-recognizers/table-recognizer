#include "OpenXLSX/OpenXLSX.hpp"
#include "client/application.h"
#include "client/image_processing/table_detector.h"

namespace imgp = table_recognizer::client::image_processing;
namespace cliUI = table_recognizer::client::UI;
namespace utils = table_recognizer::utils;

namespace application = table_recognizer::client::application;

int main() {
  std::unique_ptr<cliUI::UI_base> ui = std::make_unique<cliUI::ConsoleUI>();

  application::Application app(std::move(ui));

  cv::Mat inputted_image = app.GetImage();
  imgp::TableDetector table_detector;
  auto table = table_detector.Recognize(inputted_image);
  OpenXLSX::XLDocument doc;
  doc.create("./Demo01.xlsx");
  auto wks = doc.workbook().worksheet("Sheet1");
  for (size_t y = 0; y < table.getHeight(); y++) {
    for (size_t x = 0; x < table.getWidth(); x++) {
      wks.cell(x + 1, y + 1).value() = table.getCell(x, y);
    }
  }
  doc.save();
  doc.close();

  auto detected_cells = table_detector.DetectCells(inputted_image);
  int green = 0.0;
  for (auto cell : detected_cells) {
    cv::rectangle(inputted_image, cell, cv::Scalar(0, green, 0), 2);
    green = (green + 10) % 255;
  }

  cv::namedWindow("Test", cv::WINDOW_GUI_EXPANDED);
  cv::imshow("Test", inputted_image);

  cv::waitKey(0);

  return 0;
}
