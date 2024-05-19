#pragma once
#include<optional>
#include "../events/EventBase/EventBase.h"

class Manager {
 public:
  Manager(
      uint32_t table_count,
      uint32_t cost_of_hour,
      uint32_t start_time,
      uint32_t end_time,
      std::string start_time_str,
      std::string end_time_str) : context_{start_time,
                                           end_time,
                                           cost_of_hour,
                                           std::vector<utils::data::Table>{table_count}},
                                  start_time_{std::move(start_time_str)},
                                  end_time_{std::move(end_time_str)} {};

  std::optional<std::unique_ptr<EventBase>>
  submit(const std::unique_ptr<EventBase>& event) noexcept;

  std::vector<std::unique_ptr<EventBase>>
  end_day() noexcept;

  [[nodiscard]] const std::string& get_start_time() const noexcept;
  [[nodiscard]] const std::string& get_end_time() const noexcept;
  [[nodiscard]] const std::vector<utils::data::Table>& get_tables() const noexcept;
 private:
  std::string start_time_;
  std::string end_time_;
  utils::data::Context context_;

};
