add_library(manager Manager.h Manager.cpp)
target_link_libraries(manager PRIVATE utils events)