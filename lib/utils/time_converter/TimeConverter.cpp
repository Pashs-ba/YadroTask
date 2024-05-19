#include <charconv>
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


}