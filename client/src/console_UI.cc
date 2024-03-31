#include "client/inc/console_UI.h"

namespace table_recognizer::client::UI {

namespace console_input = table_recognizer::client::console_input;

std::string ConsoleUI::PickPathToImage() {
  std::string inputted_string =
      console_input::ReadString("Enter a path to an image: ");
  return inputted_string;
}

}  // namespace table_recognizer::client::UI
