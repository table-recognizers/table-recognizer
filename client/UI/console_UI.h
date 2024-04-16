#ifndef TABLE_RECOGNIZER_CLIENT_CONSOLE_UI_H_
#define TABLE_RECOGNIZER_CLIENT_CONSOLE_UI_H_

#include "client/UI/UI_base.h"
#include "client/UI/console_input.h"

namespace table_recognizer::client::UI {

class ConsoleUI : public UI_base {
  std::string PickPathToImage() override;
};

}  // namespace table_recognizer::client::UI

#endif  // TABLE_RECOGNIZER_CLIENT_CONSOLE_UI_H_
