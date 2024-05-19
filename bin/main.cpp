#include <iostream>
#include <string>
#include "lib/parser/Parser.h"
int main() {

  auto result = Parser::parse_manager_config("10",
                                             "10:20 11:40",
                                             "100");
  if (std::holds_alternative<Manager>(result)) {
    std::cout << "Manager parsed\n";
  } else {
    std::cout << std::get<std::string>(result) << '\n';
    return 1;
  }
  auto manager = std::get<Manager>(result);
  std::string event_str;
  std::getline(std::cin, event_str);
  auto event = Parser::parse_event(event_str);
  if (!event.has_value()) {
    std::cout << event_str << '\n';
    return 1;
  }
  std::cout << *(event.value()) << '\n';
  auto event_res = manager.submit(event.value());
  if (event_res.has_value()) {
    std::cout << *(event_res.value()) << '\n';
  }
  return 0;
}
