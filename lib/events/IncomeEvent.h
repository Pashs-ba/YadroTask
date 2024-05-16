#pragma once

#include "EventBase.h"

class IncomeEvent: public EventBase{
 public:
  std::optional<std::unique_ptr<EventBase>>
  submit(utils::data::Context &context) const noexcept override;
 protected:
  void print(std::ostream &ostream) const override{};
};
