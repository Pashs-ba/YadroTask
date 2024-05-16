add_library(events EventBase.h EventBase.cpp
        IncomeEvent.cpp
        IncomeEvent.h)
target_link_libraries(events PRIVATE utils)