#include <iostream>
#include <opencv2/opencv.hpp>

#include "client/inc/console_UI.h"
#include "client/inc/line_detector.h"

namespace ld = table_recognizer::client::line_detector;
namespace UI = table_recognizer::client::UI;

int main() {
  std::unique_ptr<UI::UI_base> ui = std::make_unique<UI::ConsoleUI>();

  std::string path_to_image = ui->PickPathToImage();
  cv::Mat image = cv::imread(path_to_image);

  cv::Mat detected_edges;
  std::vector<ld::Line> lines = ld::DetectLines(image, detected_edges);
  cv::cvtColor(detected_edges, detected_edges, cv::COLOR_GRAY2BGR);
  int r = 255, g = 0, b = 0;
  for (auto line : lines) {
    cv::line(detected_edges, line.start, line.end, cv::Scalar(b, g, r),
             cv::LINE_4);
    g = (g + 10) % 255;
  }
  std::cout << "Found lines: " << lines.size() << std::endl;
  cv::namedWindow("edges", cv::WindowFlags::WINDOW_GUI_EXPANDED);
  cv::imshow("edges", detected_edges);

  if (cv::waitKey(0) >= 0) return 0;

  return 0;
}
