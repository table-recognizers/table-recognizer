#include "client/inc/table.h"

namespace table_recognizer::client::table {

Table::Table(size_t width, size_t height) : width_(width), height_(height) {
  table_ = std::vector<std::vector<std::string>>(
      width, std::vector<std::string>(height));
}

size_t Table::getWidth() { return width_; }

size_t Table::getHeight() { return height_; }

std::string Table::getCell(size_t x, size_t y) { return table_[x][y]; }

void Table::setCell(size_t x, size_t y, std::string data) {
  table_[y][x] = data;
}

}  // namespace table_recognizer::client::table
