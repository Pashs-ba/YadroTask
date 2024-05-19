#pragma once

#include <variant>
#include "../manager/Manager.h"
namespace Parser {
  std::variant<Manager, std::string> parse_manager_config(const std::string& table_count_str,
                                                          const std::string& times,
                                                          const std::string& cost_of_hour_str) noexcept;
  std::optional<std::unique_ptr<EventBase>> parse_event(const std::string& event) noexcept;

};
