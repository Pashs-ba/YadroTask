add_library(events EventBase.h EventBase.cpp)
target_link_libraries(events PRIVATE utils)