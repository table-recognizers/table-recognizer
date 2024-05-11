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
  table_detector.Recognize(inputted_image);
  auto detected_cells = table_detector.DetectCells(inputted_image);
  for (auto cell : detected_cells) {
    cv::rectangle(inputted_image, cell, cv::Scalar(0, 255, 0), 2);
  }

  cv::namedWindow("Test", cv::WINDOW_GUI_EXPANDED);
  cv::imshow("Test", inputted_image);

  cv::waitKey(0);

  return 0;
}
