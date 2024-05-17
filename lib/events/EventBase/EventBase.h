#pragma once
#include<ostream>
#include<optional>
#include "../../utils/data/Context.h"

class EventBase {
 public:
  virtual std::optional<std::unique_ptr<EventBase>>
  submit(utils::data::Context& context) const noexcept = 0;

  friend std::ostream&
  operator<<(std::ostream& stream, const EventBase& event);

  virtual ~EventBase() = default;
 protected:
  std::string_view time_;

  explicit EventBase(const std::string_view& time) :
      time_{time} {};

  virtual void
  print(std::ostream& ostream) const noexcept = 0;
};
