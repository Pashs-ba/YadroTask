#include <iostream>
#include <string>
#include <fstream>
#include "lib/parser/Parser.h"

int main(int32_t argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " input_file" << std::endl;
    return 1;
  }
  std::fstream file{argv[1]};
  if (!file.is_open()) {
    std::cerr << "Can't open file " << argv[1] << std::endl;
    return 1;
  }
  std::string table_count_str;
  std::string times;
  std::string cost_of_hour_str;
  std::getline(file, table_count_str);
  std::getline(file, times);
  std::getline(file, cost_of_hour_str);
  auto manager_parse_result = Parser::parse_manager_config(
      table_count_str,
      times,
      cost_of_hour_str);
  if (std::holds_alternative<std::string>(manager_parse_result)) {
    std::cout << std::get<std::string>(manager_parse_result) << '\n';
    return 1;
  }
  Manager manager = std::get<Manager>(manager_parse_result);
  while (!file.eof()) {
    std::string event;
    std::getline(file, event);
    auto event_parse_result = Parser::parse_event(event);
    if (!event_parse_result.has_value()) {
      std::cout << event << '\n';
      return 1;
    }
    std::cout << *(event_parse_result.value()) << '\n';
    auto result = manager.submit(event_parse_result.value());
    if (result.has_value()) {
      std::cout << *(result.value()) << '\n';
    }
  }
  return 0;
}
