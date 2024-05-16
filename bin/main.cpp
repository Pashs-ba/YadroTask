#include <iostream>
#include "lib/utils/TimeConverter.h"


int main() {

    std::cout << utils::TimeConverter::toMinutes("23:59").value() << std::endl;
    return 0;
}
