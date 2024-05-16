#pragma once

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <string_view>
#include "lib/utils/data/Table.h"
#include "lib/utils/data/Context.h"

class Processor {
 public:
  Processor(
      uint32_t table_count,
      uint32_t cost_of_hour,
      uint32_t start_time,
      uint32_t end_time) : context_(start_time,
                                    end_time,
                                    cost_of_hour,
                                    std::vector<data::Table>(table_count)) {};
  template<typename T>
  inline auto submit(const T& event) noexcept {
    return event.submit(context_);
  }
 private:
  data::Context context_;
};

