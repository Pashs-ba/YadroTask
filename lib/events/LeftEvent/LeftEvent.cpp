#include "LeftEvent.h"
#include "../ErrorEvent/ErrorEvent.h"
#include "../../utils/time_converter/TimeConverter.h"
#include "../QueueNextEvent/QueueNextEvent.h"

std::optional<std::unique_ptr<EventBase>> LeftEvent::submit(utils::data::Context& context) const noexcept {
  if (!context.current_users.contains(client_)) {
    return std::make_unique<ErrorEvent>(time_, "ClientUnknown");
  }
  auto table_id = context.current_users[client_];
  context.current_users.erase(client_);
  if (table_id == -1) {
    return std::nullopt;
  }
  auto& table = context.tables[table_id];
  auto current_time = utils::TimeConverter::toMinutes(time_).value();

  table.free(context.cost_of_hour, current_time);

  if (!context.queue.empty()) {
    auto next_client = context.queue.front();
    context.queue.pop();
    context.current_users[next_client] = table_id;
    table.busy_from = current_time;
    table.busy = true;
    return std::make_unique<QueueNextEvent>(time_,
                                            next_client,
                                            context.current_users[next_client]);
  } else {
    table.busy = false;
    return std::nullopt;
  }

}

void LeftEvent::print(std::ostream& ostream) const noexcept {
  ostream << time_ << " 4 " << client_;
}
