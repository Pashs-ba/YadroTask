//
// Created by pashs on 17.05.2024.
//

#include "ErrorEvent.h"
std::optional<std::unique_ptr<EventBase>>
ErrorEvent::submit(utils::data::Context& context) const noexcept {
  return std::nullopt;
}

void
ErrorEvent::print(std::ostream& ostream) const noexcept {
  ostream << time_ << ' ' << 13 << ' ' << error_;
}

