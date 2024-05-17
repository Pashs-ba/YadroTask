#pragma once

#include "../EventBase/EventBase.h"
class SitEvent : public EventBase {
 public:
  SitEvent(const std::string_view& time,
           std::string_view client,
           int32_t table_id)
      : EventBase{time},
        client_{client},
        table_id_{table_id} {};

  std::optional<std::unique_ptr<EventBase>>
  submit(utils::data::Context& context) const noexcept override;
 protected:
  void print(std::ostream& ostream) const noexcept override;
 private:
  std::string_view client_;
  int32_t table_id_;
};

