#include <charconv>
#include <string>
#include "TimeConverter.h"
#include "../NumParser.h"
namespace utils::TimeConverter {

std::optional<uint32_t> toMinutes(const std::string_view& sv) noexcept {
  if (sv.size() != 5 || sv[2] != ':') {
    return std::nullopt;
  }
  auto first = utils::NumParser::from_chars<uint32_t>(sv.data(), sv.data() + 2);
  auto second = utils::NumParser::from_chars<uint32_t>(sv.data() + 3, sv.data() + sv.size());
  if (!first.has_value() || !second.has_value() || first.value() > 23 || second.value() > 59) {
    return std::nullopt;
  }
  return first.value() * 60 + second.value();
}

std::string toTime(const uint32_t& minutes) noexcept {
  auto hours = minutes / 60;
  auto minutes_ = minutes % 60;
  auto hours_str = hours < 10 ? '0' + std::to_string(hours) : std::to_string(hours);
  auto minutes_str = minutes_ < 10 ? '0' + std::to_string(minutes_) : std::to_string(minutes_);
  return hours_str + ':' + minutes_str;
}
}