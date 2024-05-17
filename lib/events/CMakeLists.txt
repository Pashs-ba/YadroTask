add_library(events EventBase/EventBase.h EventBase/EventBase.cpp
        IncomeEvent/IncomeEvent.cpp
        IncomeEvent/IncomeEvent.h
        ErrorEvent/ErrorEvent.cpp
        ErrorEvent/ErrorEvent.h
        SitEvent/SitEvent.cpp
        SitEvent/SitEvent.h
        WaitEvent/WaitEvent.cpp
        WaitEvent/WaitEvent.h
        GoodbyeEvent/GoodbyeEvent.cpp
        GoodbyeEvent/GoodbyeEvent.h)
target_link_libraries(events PRIVATE utils)