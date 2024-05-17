#pragma once

#include "../EventBase/EventBase.h"

class ErrorEvent : public EventBase {
 public:
  ErrorEvent(const std::string_view& time, std::string error) :
      EventBase{time},
      error_{std::move(error)} {}

  std::optional<std::unique_ptr<EventBase>>
  submit(utils::data::Context& context) const noexcept override;
 protected:
  void
  print(std::ostream& ostream) const noexcept override;
 private:
  std::string error_;
};

