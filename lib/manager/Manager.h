#pragma once
#include<optional>
#include "../events/EventBase/EventBase.h"

class Manager {
 public:
  Manager(
      int32_t table_count,
      uint32_t cost_of_hour,
      uint32_t start_time,
      uint32_t end_time) : context_{start_time,
                                    end_time,
                                    cost_of_hour,
                                    std::vector<utils::data::Table>(table_count)} {};
  std::optional<std::unique_ptr<EventBase>>
  submit(const std::unique_ptr<EventBase>& event) noexcept;
 private:
  utils::data::Context context_;

};
