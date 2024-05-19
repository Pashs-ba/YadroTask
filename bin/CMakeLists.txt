add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE utils events manager parser)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})