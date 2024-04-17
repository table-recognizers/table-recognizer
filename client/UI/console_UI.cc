#include "client/UI/console_UI.h"

namespace table_recognizer::client::UI {

std::string ConsoleUI::PickPathToImage() {
  std::string inputted_string = ReadString("Enter a path to an image: ");
  return inputted_string;
}

}  // namespace table_recognizer::client::UI
