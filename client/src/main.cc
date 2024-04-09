#include "client/inc/application.h"

namespace ld = table_recognizer::client::line_detector;
namespace UI = table_recognizer::client::UI;
namespace utils = table_recognizer::utils;

namespace application = table_recognizer::client::application;

int main() {
  std::unique_ptr<UI::UI_base> ui = std::make_unique<UI::ConsoleUI>();

  application::Application app(std::move(ui));

  cv::Mat inputted_image = app.GetImage();
  cv::Mat detected_edges_on_image;
  std::vector<utils::Line> lines_on_image =
      app.GetLinesFromImage(inputted_image, detected_edges_on_image);
  app.ShowLinesOnImage(detected_edges_on_image, lines_on_image);

  return 0;
}
