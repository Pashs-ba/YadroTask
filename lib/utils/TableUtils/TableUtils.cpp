#include "TableUtils.h"

void utils::TableUtils::freeTable(utils::data::Table& table,
                                  uint32_t cost_of_hour,
                                  uint32_t current_time) noexcept {
  table.busy = false;
  table.busy_time_total +=
      current_time - table.busy_from;
  table.revenue += cost_of_hour *
      (current_time - table.busy_from) / 60;
  if ((current_time - table.busy_from) % 60) {
    table.revenue += cost_of_hour;
  }
}