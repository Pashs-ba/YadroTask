//
// Created by pashs on 17.05.2024.
//

#include "WaitEvent.h"
#include "../ErrorEvent/ErrorEvent.h"
#include "../GoodbyeEvent/GoodbyeEvent.h"
std::optional<std::unique_ptr<EventBase>>
WaitEvent::submit(utils::data::Context& context) const noexcept {
  if (!context.current_users.contains(client_)) { // not specified in task but seems like a good idea
    return std::make_unique<ErrorEvent>(time_, "ClientUnknown");
  }
  if (std::all_of(context.tables.begin(),
                  context.tables.end(),
                  [](auto& table) {
                    return !table.busy;
                  })) {
    return std::make_unique<ErrorEvent>(time_, "ICanWaitNoLonger!");
  }
  if (context.queue.size() > context.tables.size()) {
    return std::make_unique<GoodbyeEvent>(time_, client_);
  }
  context.queue.push(client_);
  return std::nullopt;
}
void
WaitEvent::print(std::ostream& ostream) const noexcept {
  ostream << time_ << " 3 " << client_;
}
