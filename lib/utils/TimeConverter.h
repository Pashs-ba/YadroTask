#pragma once
#include<iostream>
#include <optional>

namespace utils::TimeConverter{
std::optional<uint32_t> toMinutes(const std::string& ss) noexcept;
}



