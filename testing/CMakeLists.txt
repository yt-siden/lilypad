cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(testing_info testing_info.cpp)
target_link_libraries(testing_info
    lilypad
)
