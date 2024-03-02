#include <iostream>

#include "client/inc/Recognizer.h"
#include "client/inc/Saver.h"

namespace client = table_recognizer::client;

int main() {
  client::Recognizer recognizer;
  recognizer.Capture();
  client::Table recognized_table = recognizer.Recognize();

  client::Saver saver;
  saver.Save(recognized_table);

  return 0;
}
