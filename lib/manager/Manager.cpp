//
// Created by pashs on 17.05.2024.
//

#include "Manager.h"
std::optional<std::unique_ptr<EventBase>>
Manager::submit(const std::unique_ptr<EventBase>& event) noexcept {
  return event->submit(context_);
}
