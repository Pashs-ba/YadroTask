//
// Created by pashs on 17.05.2024.
//

#include "QueueNextEvent.h"
std::optional<std::unique_ptr<EventBase>> QueueNextEvent::submit(utils::data::Context& context) const noexcept {
  return std::nullopt;
}
void QueueNextEvent::print(std::ostream& ostream) const noexcept {
  ostream << time_ << " 12 " << client_ << " " << table_id_ + 1;
}
