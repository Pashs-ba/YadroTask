#pragma once
#include<vector>
#include<unordered_map>
#include<string_view>
#include<queue>
#include "Table.h"

namespace utils::data {
struct Context {
  const uint32_t start_time;
  const uint32_t end_time;
  const uint32_t cost_of_hour;
  std::vector<Table> tables;
  std::unordered_map<std::string_view, int32_t> current_users;
  std::queue<std::string_view> queue;
};
}
