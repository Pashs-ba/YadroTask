#include<optional>
#include<string>
#include<memory>
#include "../events/EventBase/EventBase.h"
#include "../utils/NumParser.h"
#include "../events/SitEvent/SitEvent.h"
#include "../events/IncomeEvent/IncomeEvent.h"
#include "Parser.h"
#include "../events/LeftEvent/LeftEvent.h"
#include "../events/WaitEvent/WaitEvent.h"

std::optional<std::string_view>
Parser::inner::parse_name(std::string_view body) noexcept {
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

template<typename T>
std::optional<std::unique_ptr<EventBase>> standard_parse(std::string_view time,
                                                         std::string_view body) noexcept {
  auto name = Parser::inner::parse_name(body);
  if (!name.has_value()) {
    return std::nullopt;
  }
  if (body.size() != name->size()) {
    return std::nullopt;
  }
  return std::make_unique<T>(time, name.value());
}

std::optional<std::unique_ptr<EventBase>>
Parser::inner::parse_income(std::string_view time,
                            std::string_view body) noexcept {
  return standard_parse<IncomeEvent>(time, body);
}

std::optional<std::unique_ptr<EventBase>>
Parser::inner::parse_leave(std::string_view time,
                           std::string_view body) noexcept {
  return standard_parse<LeftEvent>(time, body);
}

std::optional<std::unique_ptr<EventBase>>
Parser::inner::parse_wait(std::string_view time,
                          std::string_view body) noexcept {
  return standard_parse<WaitEvent>(time, body);
}

std::optional<std::unique_ptr<EventBase>>
Parser::inner::parse_sit(std::string_view time,
                         std::string_view body) noexcept {
  auto name = parse_name(body);
  if (!name.has_value()) {
    return std::nullopt;
  }
  auto whitespace = body.find(' ');
  if (whitespace == std::string::npos) {
    return std::nullopt;
  }
  auto table = utils::NumParser::from_chars<uint32_t>(
      body.data() + whitespace + 1,
      body.data() + body.size());
  if (!table.has_value()) {
    return std::nullopt;
  }
  return std::make_unique<SitEvent>(time, name.value(), table.value());
}

