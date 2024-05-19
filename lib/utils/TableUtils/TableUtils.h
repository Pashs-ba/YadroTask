#pragma once

#include "../data/Table.h"
namespace utils::TableUtils {
void freeTable(utils::data::Table& table, uint32_t cost_of_hour, uint32_t current_time) noexcept;
}