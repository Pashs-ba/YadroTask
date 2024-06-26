#pragma once

#include "../EventBase/EventBase.h"
class LeftEvent : public EventBase {
 public:
  LeftEvent(std::string_view time, std::string client) :
      EventBase(time),
      client_(std::move(client)) {};

  std::optional<std::unique_ptr<EventBase>>
  submit(utils::data::Context& context) const noexcept override;
 protected:
  void
  print(std::ostream& ostream) const noexcept override;
 private:
  std::string client_;
};

