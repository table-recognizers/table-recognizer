#include "client/inc/table.h"

namespace table_recognizer::client::table {

Table::Table(int NWidth, int NHeight) {
  Width = NWidth;
  Height = NHeight;
  table = new std::string*[Width];
  for (int i = 0; i < Width; i++) {
    table[i] = new std::string[Height];
  }
}

int Table::getMx() { 

return Width; 
}

int Table::getMy() { 

return Height; 
}

void Table::set(int x, int y, std::string data) { 

table[x][y] = data; 
}

std::string Table::get(int x, int y) { 

return table[x][y]; 
}

}  // namespace table_recognizer::client::table