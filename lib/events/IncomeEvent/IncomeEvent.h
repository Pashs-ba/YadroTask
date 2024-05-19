#pragma once

#include "../EventBase/EventBase.h"

class IncomeEvent : public EventBase {
 public:
  IncomeEvent(std::string_view time, std::string client_)
      : EventBase{time},
        client_{std::move(client_)} {};

  std::optional<std::unique_ptr<EventBase>>
  submit(utils::data::Context& context) const noexcept override;
 protected:
  std::string client_;

  void
  print(std::ostream& ostream) const noexcept override;
};
