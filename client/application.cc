#include "client/application.h"

namespace table_recognizer::client::application {

namespace ld = table_recognizer::client::line_detector;
namespace ui = table_recognizer::client::UI;
namespace table = table_recognizer::client::table;
namespace utils = table_recognizer::utils;

cv::Mat Application::GetImage() {
  std::string path_to_image = UI_->PickPathToImage();
  cv::Mat image = cv::imread(path_to_image);
  return image;
}

std::vector<utils::Line> Application::GetLinesFromImage(
    const cv::Mat image, cv::Mat& detected_edges) {
  std::vector<utils::Line> lines = ld::DetectLines(image, detected_edges);
  return lines;
}

void Application::ShowLinesOnImage(const cv::Mat image,
                                   const std::vector<utils::Line> lines) {
  cv::Mat image_with_lines(image);
  cv::cvtColor(image_with_lines, image_with_lines, cv::COLOR_GRAY2BGR);
  int r = 255, g = 0, b = 0;
  for (auto line : lines) {
    cv::line(image_with_lines, line.start, line.end, cv::Scalar(b, g, r),
             cv::LINE_4);
    g = (g + 10) % 255;
  }
  std::cout << "Found lines: " << lines.size() << std::endl;
  cv::namedWindow("Lines On Image", cv::WindowFlags::WINDOW_GUI_EXPANDED);
  cv::imshow("Lines On Image", image_with_lines);

  if (cv::waitKey(0) >= 0) return;
}

httplib::Result Application::TrySendLinesToServer(std::vector<utils::Line> lines) {
  rapidjson::Document d;
  d.SetArray();
  for (const auto& line : lines) {
    rapidjson::Value obj(rapidjson::kObjectType);
    rapidjson::Value start(rapidjson::kArrayType);
    start.PushBack(line.start.x, d.GetAllocator());
    start.PushBack(line.start.y, d.GetAllocator());
    obj.AddMember("start", start, d.GetAllocator());
    rapidjson::Value end(rapidjson::kArrayType);
    end.PushBack(line.end.x, d.GetAllocator());
    end.PushBack(line.end.y, d.GetAllocator());
    obj.AddMember("end", end, d.GetAllocator());
    d.PushBack(obj, d.GetAllocator());
  }
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  d.Accept(writer);

  httplib::Client client(SERVER_ADDRESS, SERVER_PORT);
  httplib::Headers headers = {{"Content-Type", "application/json"}};
  httplib::Result res =
      client.Post("/lines", headers, buffer.GetString(), "application/json");

  return res;
}

Application::Application(std::unique_ptr<ui::UI_base> UI)
    : UI_(std::move(UI)) {}

}  // namespace table_recognizer::client::application
