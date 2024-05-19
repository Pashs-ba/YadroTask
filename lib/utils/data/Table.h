#pragma once

#include <cstdint>
namespace utils::data {
struct Table {
  bool busy = false;
  uint32_t busy_from = 0;
  uint32_t busy_time_total = 0;
  uint32_t revenue = 0;

  void free(uint32_t cost_of_hour, uint32_t current_time) noexcept;
};
}


