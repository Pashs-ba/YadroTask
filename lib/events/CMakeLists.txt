add_library(events EventBase/EventBase.h EventBase/EventBase.cpp
        IncomeEvent/IncomeEvent.cpp
        IncomeEvent/IncomeEvent.h
        ErrorEvent/ErrorEvent.cpp
        ErrorEvent/ErrorEvent.h)
target_link_libraries(events PRIVATE utils)