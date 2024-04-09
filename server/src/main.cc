#include <iostream>
#include <vector>

#include "httplib.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "utils/inc/line.h"

namespace utils = table_recognizer::utils;

int main() {
  httplib::Server server;

  server.Post("/lines",
              [](const httplib::Request &req, httplib::Response &res) {
                // Вывод полученных данных в виде JSON
                std::cout << "Received JSON: " << req.body << std::endl;

                // Преобразование JSON обратно в вектор Line
                rapidjson::Document d;
                d.Parse(req.body.c_str());

                std::vector<utils::Line> lines;
                for (auto &line : d.GetArray()) {
                  utils::Line l;
                  l.start.x = line["start"][0].GetInt();
                  l.start.y = line["start"][1].GetInt();
                  l.end.x = line["end"][0].GetInt();
                  l.end.y = line["end"][1].GetInt();
                  lines.push_back(l);
                }

                // Вывод преобразованных данных
                std::cout << "Converted back to vector<Line>: " << std::endl;
                for (const auto &line : lines) {
                  std::cout << "Start: (" << line.start.x << ", "
                            << line.start.y << "), End: (" << line.end.x << ", "
                            << line.end.y << ")" << std::endl;
                }

                res.set_content("Data received and processed", "text/plain");
              });

  server.listen("127.0.0.1", 8080);

  return 0;
}
