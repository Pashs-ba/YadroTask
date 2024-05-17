#include <iostream>
#include "lib/processor/Processor.h"
#include "lib/events/IncomeEvent/IncomeEvent.h"

int main() {
  int type;
  Processor processor{
      1,
      1,
      1000,
      2000
  };
  auto result = processor.submit(std::make_unique<IncomeEvent>("123", std::string_view("some")));
  std::cout << *result;
  return 0;
}
