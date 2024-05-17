#pragma once

#include "../EventBase/EventBase.h"
class WaitEvent : public EventBase {
 public:
  WaitEvent(const std::string_view& time, std::string_view client)
      : EventBase{time},
        client_{client} {};

  std::optional<std::unique_ptr<EventBase>>
  submit(utils::data::Context& context) const noexcept override;
 protected:
  std::string_view client_;

  void
  print(std::ostream& ostream) const noexcept override;
};