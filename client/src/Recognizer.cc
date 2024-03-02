#include "client/inc/Recognizer.h"

namespace table_recognizer::client {

// namespace Table = table_recognizer::client::Table;

void Recognizer::Capture() {
  std::cout << "Captured" << std::endl;
  std::cout << "" << std::endl;
}  // namespace table_recognizer::client::Table

Table Recognizer::Recognize() {
  std::cout << "Some picture was recognized" << std::endl;
  Table new_table;
  return new_table;
}

}  // namespace table_recognizer::client
