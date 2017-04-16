cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/util)
add_subdirectory(util)
link_libraries(lilypad_exec_util)

add_subdirectory(testing)
add_subdirectory(example)
