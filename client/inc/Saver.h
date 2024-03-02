#ifndef TABLE_RECOGNIZER_CLIENT_SAVER_H
#define TABLE_RECOGNIZER_CLIENT_SAVER_H

#include <iostream>
#include "client/inc/Table.h"

namespace table_recognizer::client {

class Saver {
 public:
  void Save(Table table);
};

}  // namespace table_recognizer::client

#endif  // TABLE_RECOGNIZER_CLIENT_SAVER_H
