#include "SitEvent.h"
#include "../ErrorEvent/ErrorEvent.h"
#include "../../utils/time_converter/TimeConverter.h"

std::optional<std::unique_ptr<EventBase>>
SitEvent::submit(utils::data::Context& context) const noexcept {
  if (!context.current_users.contains(client_)) {
    return std::make_unique<ErrorEvent>(time_, "ClientDoesNotExist");
  }
  if (context.tables[table_id_].busy) {
    return std::make_unique<ErrorEvent>(time_, "PlaceIsBusy");
  }
  if (context.current_users[client_] != -1) {
    auto& prev_table = context.tables[context.current_users[client_]];
    prev_table.busy = false;
    prev_table.busy_time_total +=
        utils::TimeConverter::toMinutes(time_).value() - prev_table.busy_from;
  }
  context.tables[table_id_].busy = true;
  context.tables[table_id_].busy_from = utils::TimeConverter::toMinutes(time_).value();
  context.current_users[client_] = table_id_;
  return std::nullopt;
}

void SitEvent::print(std::ostream& ostream) const noexcept {
  ostream << time_ << ' ' << 2 << ' ' << client_ << ' ' << table_id_;
}
