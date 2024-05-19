#include <charconv>
#include<string_view>
#include "Parser.h"
#include "../utils/time_converter/TimeConverter.h"
#include "../utils/NumParser.h"
#include "../events/IncomeEvent/IncomeEvent.h"

std::optional<std::string_view>
parse_name(std::string_view body) noexcept {
  auto whitespace = body.find(' ');
  if (whitespace == std::string::npos) {
    whitespace = body.size();
  }
  std::string_view name{body.data(), whitespace};
  if (name.empty()) {
    return std::nullopt;
  }
  if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyz"
                             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                             "0123456789_-") != std::string::npos) {
    return std::nullopt;
  }
  return name;

}

std::optional<std::unique_ptr<EventBase>>
parse_income(std::string_view time,
             std::string_view body) {
  auto name = parse_name(body);
  if (!name.has_value()) {
    return std::nullopt;
  }
  if (body.size() != name->size()) {
    return std::nullopt;
  }
  return std::make_unique<IncomeEvent>(time, name.value());
}

std::variant<Manager, std::string>
Parser::parse_manager_config(const std::string& table_count_str,
                             const std::string& times,
                             const std::string& cost_of_hour_str) noexcept {
  auto table_count = utils::NumParser::from_chars<uint32_t>(
      table_count_str.data(),
      table_count_str.data() + table_count_str.size());
  if (!table_count.has_value()) {
    return table_count_str;
  }
  auto cost_of_hour = utils::NumParser::from_chars<uint32_t>(
      cost_of_hour_str.data(),
      cost_of_hour_str.data() + cost_of_hour_str.size());
  if (!cost_of_hour.has_value()) {
    return cost_of_hour_str;
  }
  auto first_whitespace = times.find(' ');
  auto time_open = utils::TimeConverter::toMinutes(
      std::string_view{times.data(),
                       first_whitespace});
  auto time_close = utils::TimeConverter::toMinutes(
      std::string_view{times.data() + first_whitespace + 1,
                       times.size() - first_whitespace - 1});
  if (!time_open.has_value() || !time_close.has_value()) {
    return times;
  }
  if (time_open.value() >= time_close.value()) { // not saied in the task
    return times;
  }
  return Manager{table_count.value(),
                 cost_of_hour.value(),
                 time_open.value(),
                 time_close.value()};
}

std::optional<std::unique_ptr<EventBase>>
Parser::parse_event(const std::string& event) noexcept {
  auto first_whitespace = event.find(' ');
  if (first_whitespace == std::string::npos) {
    return std::nullopt;
  }
  auto time = utils::TimeConverter::toMinutes(
      std::string_view{event.data(),
                       first_whitespace});
  if (!time.has_value()) {
    return std::nullopt;
  }
  auto second_whitespace = event.find(' ', first_whitespace + 1);
  if (second_whitespace == std::string::npos) {
    return std::nullopt;
  }
  auto id_task = utils::NumParser::from_chars<uint32_t>(
      event.data() + first_whitespace + 1,
      event.data() + second_whitespace);
  if (!id_task.has_value()) {
    return std::nullopt;
  }
  switch (id_task.value()) {
    case 1:
      return parse_income(std::string_view{event.data(),
                                           first_whitespace},
                          std::string_view{event.data() + second_whitespace + 1,
                                           event.size() - second_whitespace - 1});
    default:return std::nullopt;
  }
}

