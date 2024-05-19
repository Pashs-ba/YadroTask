#include "LeftEvent.h"
#include "../ErrorEvent/ErrorEvent.h"
#include "../../utils/time_converter/TimeConverter.h"
#include "../QueueNextEvent/QueueNextEvent.h"
#include "../../utils/TableUtils/TableUtils.h"
std::optional<std::unique_ptr<EventBase>> LeftEvent::submit(utils::data::Context& context) const noexcept {
  if (!context.current_users.contains(client_)) {
    return std::make_unique<ErrorEvent>(time_, "ClientUnknown");
  }
  auto& table = context.tables[context.current_users[client_]];
  auto current_time = utils::TimeConverter::toMinutes(time_).value();
  utils::TableUtils::freeTable(table, context.cost_of_hour, current_time);
  if (!context.queue.empty()) {
    auto next_client = context.queue.front();
    context.queue.pop();
    context.current_users[next_client] = context.current_users[client_];
    context.current_users.erase(client_);
    table.busy_from = current_time;
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
