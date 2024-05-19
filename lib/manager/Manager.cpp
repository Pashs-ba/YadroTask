//
// Created by pashs on 17.05.2024.
//

#include "Manager.h"
#include "../events/GoodbyeEvent/GoodbyeEvent.h"
std::optional<std::unique_ptr<EventBase>>
Manager::submit(const std::unique_ptr<EventBase>& event) noexcept {
  return event->submit(context_);
}

std::vector<std::unique_ptr<EventBase>> Manager::end_day() noexcept {
  std::vector<std::string_view> names;
  names.reserve(context_.current_users.size());
  for (auto& table : context_.current_users) {
    names.push_back(table.first);
    context_.tables[table.second].free(context_.cost_of_hour, context_.end_time);
  }
  std::sort(names.begin(), names.end());
  std::vector<std::unique_ptr<EventBase>> events;
  events.reserve(names.size());
  for (auto& name : names) {
    events.push_back(std::make_unique<GoodbyeEvent>(end_time_, std::string(name)));
  }
  return events;
}
const std::string& Manager::get_start_time() const noexcept {
  return start_time_;
}
const std::string& Manager::get_end_time() const noexcept {
  return end_time_;
}
const std::vector<utils::data::Table>& Manager::get_tables() const noexcept {
  return context_.tables;
}
