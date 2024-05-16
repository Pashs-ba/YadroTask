//
// Created by pashs on 16.05.2024.
//

#include "IncomeEvent.h"
std::optional<std::unique_ptr<EventBase>>
IncomeEvent::submit(utils::data::Context& context) const noexcept {
  return std::nullopt;
}
