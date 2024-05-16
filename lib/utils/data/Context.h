#pragma once
#include<vector>
#include<unordered_map>
#include<string_view>
#include "Table.h"

namespace data {
struct Context {
  const uint32_t start_time;
  const uint32_t end_time;
  const uint32_t cost_of_hour;
  std::vector<Table> tables;
  std::unordered_map<std::string_view, int> current_users;
};
}
