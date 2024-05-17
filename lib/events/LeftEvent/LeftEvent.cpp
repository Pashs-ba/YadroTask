#include "LeftEvent.h"
#include "../ErrorEvent/ErrorEvent.h"
#include "../../utils/time_converter/TimeConverter.h"
#include "../QueueNextEvent/QueueNextEvent.h"
std::optional<std::unique_ptr<EventBase>> LeftEvent::submit(utils::data::Context& context) const noexcept {
  if (!context.current_users.contains(client_)) {
    return std::make_unique<ErrorEvent>(time_, "ClientUnknown");
  }
  if (!context.queue.empty()) {
    auto next_client = context.queue.front();
    context.queue.pop();
    context.current_users[next_client] = context.current_users[client_];
    context.current_users.erase(client_);
    return std::make_unique<QueueNextEvent>(time_,
                                            next_client,
                                            context.current_users[next_client]);
  } else {
    auto& table = context.tables[context.current_users[client_]];
    table.busy = false;
    table.busy_time_total +=
        utils::TimeConverter::toMinutes(time_).value() - table.busy_from;
    return std::nullopt;
  }
}

void LeftEvent::print(std::ostream& ostream) const noexcept {
  ostream << time_ << " 4 " << client_;
}
