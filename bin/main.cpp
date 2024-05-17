#include <iostream>
#include "lib/events/IncomeEvent/IncomeEvent.h"
#include "lib/utils/time_converter/TimeConverter.h"
#include "lib/manager/Manager.h"

int main() {
  Manager manager{
      1,
      1,
      utils::TimeConverter::toMinutes("09:30").value(),
      utils::TimeConverter::toMinutes("21:30").value()
  };
  std::optional<std::unique_ptr<EventBase>> result = manager.submit(
      std::make_unique<IncomeEvent>(
          "09:40",
          std::string_view("pashs.ba")));
  if (result.has_value()) {
    std::cout << *(result.value());
  }else{
    std::cout<<"Nothing!";
  }
  return 0;
}
