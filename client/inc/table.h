#ifndef TABLE_RECOGNIZER_CLIENT_TABLE_H_
#define TABLE_RECOGNIZER_CLIENT_TABLE_H_

#include <iomanip>
#include <vector>

namespace table_recognizer::client::table {

class Table {
  std::vector<std::vector<std::string>> table_;
  size_t height_;
  size_t width_;

 public:
  Table(size_t width, size_t height);

  size_t getWidth();
  size_t getHeight();
  std::string getCell(size_t x, size_t y);
  void setCell(size_t x, size_t y, std::string data);
};

}  // namespace table_recognizer::client::table

#endif  // TABLE_RECOGNIZER_CLIENT_TABLE_H_
