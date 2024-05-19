#pragma once
#include <charconv>
#include <optional>

namespace utils::NumParser {
template<typename T>
inline std::optional<T> from_chars(const char* start, const char* end) noexcept {
  T ans;
  auto result = std::from_chars(start, end, ans);
  if (result.ec == std::errc::invalid_argument || result.ptr != end) {
    return std::nullopt;
  }
  return ans;
}
}