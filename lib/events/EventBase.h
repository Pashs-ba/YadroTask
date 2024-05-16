#pragma once
#include<ostream>
#include<optional>
#include "../utils/data/Context.h"

class EventBase {
 public:
  virtual std::optional<std::unique_ptr<EventBase>>
  submit(utils::data::Context& context) const noexcept = 0;

  friend std::ostream&
  operator<<(std::ostream& stream, const EventBase& event);
 protected:
  virtual void
  print(std::ostream& ostream) const = 0;
};
