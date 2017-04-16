cmake_minimum_required(VERSION 2.8)

set(SRC_MISC
    ${CMAKE_BINARY_DIR}/src/misc/info.cpp
)

add_library(lilypad SHARED
    ${SRC_MISC}
)

target_link_libraries(lilypad
    ${SCALAPACK_LIBRARIES}
    ${MPI_CXX_LIBRARIES}
    ${LAPACK_LIBRARIES}
)
