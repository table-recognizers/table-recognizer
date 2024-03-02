#ifndef TABLE_RECOGNIZER_CLIENT_RECOGNIZER_H
#define TABLE_RECOGNIZER_CLIENT_RECOGNIZER_H

#include <iostream>

#include "client/inc/Table.h"

namespace table_recognizer::client {

class Recognizer {
 public:
  void Capture();
  Table Recognize();
};

}  // namespace table_recognizer::client

#endif
