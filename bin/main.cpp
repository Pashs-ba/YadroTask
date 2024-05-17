#include <iostream>
#include "lib/events/IncomeEvent/IncomeEvent.h"
#include "lib/utils/time_converter/TimeConverter.h"
#include "lib/manager/Manager.h"
#include "lib/events/SitEvent/SitEvent.h"
#include "lib/events/LeftEvent/LeftEvent.h"
#include "lib/events/WaitEvent/WaitEvent.h"

int main() {
  Manager manager{
      1,
      1,
      utils::TimeConverter::toMinutes("09:30").value(),
      utils::TimeConverter::toMinutes("21:30").value()
  };
  manager.submit(
      std::make_unique<IncomeEvent>(
          "09:40",
          std::string_view("pashs.ba")));
  manager.submit(
      std::make_unique<SitEvent>(
          "09:50",
          std::string_view("pashs.ba"),
          0));
  manager.submit(
      std::make_unique<IncomeEvent>(
          "09:50",
          std::string_view("pashs.ba2")));
  manager.submit(
      std::make_unique<WaitEvent>(
          "09:50",
          std::string_view("pashs.ba2")));
  std::optional<std::unique_ptr<EventBase>> result = manager.submit(
      std::make_unique<LeftEvent>(
          "11:40",
          std::string_view("pashs.ba")));
  std::optional<std::unique_ptr<EventBase>> result2 = manager.submit(
      std::make_unique<LeftEvent>(
          "11:50",
          std::string_view("pashs.ba2")));
  if (result.has_value()) {
    std::cout << *(result.value());
  } else {
    std::cout << "Nothing!";
  }

  return 0;
}
