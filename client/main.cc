#include "client/application.h"

namespace ld = table_recognizer::client::line_detector;
namespace cliUI = table_recognizer::client::UI;
namespace utils = table_recognizer::utils;

namespace application = table_recognizer::client::application;

int main() {
  std::unique_ptr<cliUI::UI_base> ui = std::make_unique<cliUI::ConsoleUI>();

  application::Application app(std::move(ui));

  cv::Mat inputted_image = app.GetImage();
  cv::Mat detected_edges_on_image;
  std::vector<utils::Line> lines_on_image =
      app.GetLinesFromImage(inputted_image, detected_edges_on_image);
  httplib::Result result = app.TrySendLinesToServer(lines_on_image);
  if (result && result->status == 200) {
    std::cout << "Data sent successfully to the server" << std::endl;
  } else {
    std::cout << "Failed to send data to the server" << std::endl;
  }
  app.ShowLinesOnImage(detected_edges_on_image, lines_on_image);

  return 0;
}
