add_library(parser Parser.h Parser.cpp)
target_link_libraries(parser PRIVATE utils manager events)