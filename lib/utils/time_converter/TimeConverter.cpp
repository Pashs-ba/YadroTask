#include <charconv>
#include "TimeConverter.h"
namespace utils::TimeConverter {
inline std::optional<uint32_t> from_chars(const char* start, const char* end) noexcept {
  uint32_t ans;
  auto result = std::from_chars(start, end, ans);
  if (result.ec == std::errc::invalid_argument) {
    return std::nullopt;
  }
  return ans;
}

std::optional<uint32_t> toMinutes(const std::string& ss) noexcept {
  std::string_view sv = ss;
  if (sv.size() != 5 || sv[2] != ':') {
    return std::nullopt;
  }
  auto first = from_chars(sv.data(), sv.data() + 2);
  auto second = from_chars(sv.data() + 3, sv.data() + sv.size());
  if (!first.has_value() || !second.has_value() || first.value() > 23 || second.value() > 59) {
    return std::nullopt;
  }
  return first.value() * 60 + second.value();
}


}