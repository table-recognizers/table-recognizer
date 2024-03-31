#ifndef TABLE_RECOGNIZER_CLIENT_UI_H_
#define TABLE_RECOGNIZER_CLIENT_UI_H_

#include <string>

namespace table_recognizer::client::UI {

class UI_base {
 public:
  virtual ~UI_base() = default;
  virtual std::string PickPathToImage() = 0;
};

}  // namespace table_recognizer::client::UI

#endif  // #define TABLE_RECOGNIZER_CLIENT_UI_H_
