#ifndef TABLE_RECOGNIZER_CLIENT_TABLE_H_
#define TABLE_RECOGNIZER_CLIENT_LINE_TABLE_H_

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>
#include <opencv2/opencv.hpp>

namespace table_recognizer::client::table {

class Table {
  std::string** table;
  int Height;
  int Width;

 public:
  Table(int NWidth, int NHeight);

  std::string get(int x, int y);
  void set(int x, int y, std::string data);
  int getMx();
  int getMy();
};

}  // namespace table_recognizer::client::table

#endif