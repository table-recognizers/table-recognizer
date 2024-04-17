#ifndef TABLE_RECOGNIZER_CLIENT_CONSOLE_INPUT_H_
#define TABLE_RECOGNIZER_CLIENT_CONSOLE_INPUT_H_

#include <iostream>
#include <string>

namespace table_recognizer::client::UI {

std::string ReadString(const std::string& prompt);

}  // namespace table_recognizer::client::UI

#endif  // TABLE_RECOGNIZER_CLIENT_CONSOLE_INPUT_H_
