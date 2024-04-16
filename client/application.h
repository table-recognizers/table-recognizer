#ifndef TABLE_RECOGNIZER_CLIENT_APPLICATION_H_
#define TABLE_RECOGNIZER_CLIENT_APPLICATION_H_

#include <memory>
#include <opencv2/opencv.hpp>

#include "client/UI/UI_base.h"
#include "client/UI/console_UI.h"
#include "client/image_processing/line_detector.h"
#include "client/image_processing/table.h"
#include "httplib.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace table_recognizer::client::application {

namespace ld = table_recognizer::client::line_detector;
namespace ui = table_recognizer::client::UI;
namespace table = table_recognizer::client::table;
namespace utils = table_recognizer::utils;

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 8080

class Application {
 public:
  std::unique_ptr<table_recognizer::client::UI::UI_base> UI_;

  cv::Mat GetImage();
  std::vector<utils::Line> GetLinesFromImage(const cv::Mat image,
                                             cv::Mat& detected_edges);
  void ShowLinesOnImage(const cv::Mat image,
                        const std::vector<utils::Line> lines);
  httplib::Result TrySendLinesToServer(std::vector<utils::Line> lines);
  Application(std::unique_ptr<ui::UI_base> UI);
};

}  // namespace table_recognizer::client::application

#endif  // TABLE_RECOGNIZER_CLIENT_APPLICATION_H_
