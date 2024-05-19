#include "SitEvent.h"
#include "../ErrorEvent/ErrorEvent.h"
#include "../../utils/time_converter/TimeConverter.h"

std::optional<std::unique_ptr<EventBase>>
SitEvent::submit(utils::data::Context& context) const noexcept {
  int32_t table_index = table_id_-1;
  if (!context.current_users.contains(client_)) {
    return std::make_unique<ErrorEvent>(time_, "ClientDoesNotExist");
  }
  if (context.tables[table_index].busy) {
    return std::make_unique<ErrorEvent>(time_, "PlaceIsBusy");
  }
  auto current_time = utils::TimeConverter::toMinutes(time_).value();
  if (context.current_users[client_] != -1) {
    auto& prev_table = context.tables[context.current_users[client_]];
    prev_table.free(context.cost_of_hour, current_time);
  }
  context.tables[table_index].busy_from = current_time;
  context.tables[table_index].busy = true;
  context.current_users[client_] = table_index;
  return std::nullopt;
}

void SitEvent::print(std::ostream& ostream) const noexcept {
  ostream << time_ << ' ' << 2 << ' ' << client_ << ' ' << table_id_;
}
