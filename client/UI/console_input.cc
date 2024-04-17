#include "client/UI/console_input.h"

namespace table_recognizer::client::UI {

std::string ReadString(const std::string& prompt = "") {
  std::cout << prompt;
  std::string input;
  std::getline(std::cin, input);
  return input;
}

}  // namespace table_recognizer::client::UI
