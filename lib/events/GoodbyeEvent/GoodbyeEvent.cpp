//
// Created by pashs on 17.05.2024.
//

#include "GoodbyeEvent.h"
std::optional<std::unique_ptr<EventBase>> GoodbyeEvent::submit(utils::data::Context& context) const noexcept {
  return std::nullopt;
}
void GoodbyeEvent::print(std::ostream& ostream) const noexcept {
    ostream << time_ << " 11 " << client_;
}
