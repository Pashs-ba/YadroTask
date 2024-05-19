#include "Table.h"

void utils::data::Table::free(uint32_t cost_of_hour, uint32_t current_time) noexcept {
  busy = false;
  busy_time_total +=
      current_time - busy_from;
  revenue += cost_of_hour *
      ((current_time - busy_from) / 60);
  if ((current_time - busy_from) % 60) {
    revenue += cost_of_hour;
  }
}
