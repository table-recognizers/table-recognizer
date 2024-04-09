#include "client/inc/application.h"

namespace table_recognizer::client::application {

namespace ld = table_recognizer::client::line_detector;
namespace ui = table_recognizer::client::UI;
namespace table = table_recognizer::client::table;

cv::Mat Application::GetImage() {
  std::string path_to_image = UI_->PickPathToImage();
  cv::Mat image = cv::imread(path_to_image);
  return image;
}

std::vector<ld::Line> Application::GetLinesFromImage(const cv::Mat image,
                                                     cv::Mat& detected_edges) {
  std::vector<ld::Line> lines = ld::DetectLines(image, detected_edges);
  return lines;
}

void Application::ShowLinesOnImage(const cv::Mat image,
                                   const std::vector<ld::Line> lines) {
  cv::Mat image_with_lines(image);
  cv::cvtColor(image_with_lines, image_with_lines, cv::COLOR_GRAY2BGR);
  int r = 255, g = 0, b = 0;
  for (auto line : lines) {
    cv::line(image_with_lines, line.start, line.end, cv::Scalar(b, g, r), cv::LINE_4);
    g = (g + 10) % 255;
  }
  std::cout << "Found lines: " << lines.size() << std::endl;
  cv::namedWindow("Lines On Image", cv::WindowFlags::WINDOW_GUI_EXPANDED);
  cv::imshow("Lines On Image", image_with_lines);

  if (cv::waitKey(0) >= 0) return;
}

Application::Application(std::unique_ptr<ui::UI_base> UI)
    : UI_(std::move(UI)) {}

}  // namespace table_recognizer::client::application
