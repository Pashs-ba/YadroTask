#pragma once
#include<iostream>
#include <optional>

namespace utils::TimeConverter{
std::optional<uint32_t> toMinutes(const std::string_view& sv) noexcept;
std::string toTime(const uint32_t& minutes) noexcept;
}



