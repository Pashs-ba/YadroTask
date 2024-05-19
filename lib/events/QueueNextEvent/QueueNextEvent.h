#pragma once

#include "../EventBase/EventBase.h"
class QueueNextEvent : public EventBase {
 public:
  QueueNextEvent(std::string_view time,
                 std::string client,
                 int32_t table_id) :
      EventBase(time),
      table_id_(table_id),
      client_(std::move(client)) {};

  std::optional<std::unique_ptr<EventBase>>
  submit(utils::data::Context& context) const noexcept override;
 protected:
  void
  print(std::ostream& ostream) const noexcept override;
 private:
  int32_t table_id_;
  std::string client_;
};
