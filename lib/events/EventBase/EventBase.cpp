//
// Created by pashs on 16.05.2024.
//

#include "EventBase.h"
std::ostream& operator<<(std::ostream& stream, const EventBase& event) {
  event.print(stream);
  return stream;
}
