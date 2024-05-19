#pragma once

#include "../EventBase/EventBase.h"
class GoodbyeEvent: public EventBase{
  public:
  GoodbyeEvent(const std::string_view& time, std::string client)
      : EventBase{time},
        client_{std::move(client)} {};

  std::optional<std::unique_ptr<EventBase>>
  submit(utils::data::Context& context) const noexcept override;
 protected:
  std::string client_;

  void
  print(std::ostream& ostream) const noexcept override;
};

