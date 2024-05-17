//
// Created by pashs on 16.05.2024.
//

#include "IncomeEvent.h"
#include "../ErrorEvent/ErrorEvent.h"
#include "../../utils/time_converter/TimeConverter.h"
std::optional<std::unique_ptr<EventBase>>
IncomeEvent::submit(utils::data::Context& context) const noexcept {
  if (context.current_users.contains(client_)) {
    return std::make_unique<ErrorEvent>(time_, "YouShallNotPass");
  }
  auto current_minutes = utils::TimeConverter::toMinutes(time_);
  if (!current_minutes.has_value()) {
    return std::nullopt;
  }

  if (current_minutes < context.start_time || current_minutes > context.end_time) {
    return std::make_unique<ErrorEvent>(time_, "NotOpenYet");
  }
  context.current_users[client_] = -1;
  return std::nullopt;
}
