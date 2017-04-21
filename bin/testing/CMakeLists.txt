cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(testing_info testing_info.cpp)
add_executable(testing_global testing_global.cpp)
add_executable(testing_args testing_args.cpp)
add_executable(testing_cholQR testing_cholQR.cpp)
add_executable(testing_type_traits testing_type_traits.cpp)
