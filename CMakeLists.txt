# CMakeLists.txt
cmake_minimum_required(VERSION 2.8)

project(lilypad C CXX)

# Version
set(lilypad_VERSION_MAJOR 0)
set(lilypad_VERSION_MINOR 1)
set(lilypad_VERSION_PATCH 0)
set(lilypad_VERSION_TWEAK 0)
set(LILYPAD_VERSION_STRING "${lilypad_VERSION_MAJOR}.${lilypad_VERSION_MINOR}.${lilypad_VERSION_PATCH}.${lilypad_VERSION_TWEAK}")

# Check MPI
find_package(MPI REQUIRED)
include_directories(${MPI_CXX_INCLUDE_PATH})

# Check BLAS/LAPACK
find_package(LAPACK REQUIRED)
# Intel MKL is assumed
include_directories($ENV{MKLINCLUDE})

# BLACS/ScaLAPACK LIB
# TODO: Automatic detection & validation
set(SCALAPACK_LIBRARIES "-lmkl_scalapack_lp64;-lmkl_blacs_intelmpi_lp64" CACHE STRING "ScaLAPACK Libraries")

# Check OpenMP
find_package(OpenMP REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

# for C++11
# TODO: Validation
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
include_directories(${CMAKE_SOURCE_DIR}/include)

# information
message(STATUS "configuration info")
message(STATUS "CXX:       ${CMAKE_CXX_COMPILER}")
message(STATUS "CXXFLAGS:  ${CMAKE_CXX_FLAGS}")
message(STATUS "LDFLAGS:   ${CMAKE_EXE_LINKER_FLAGS}")
message(STATUS "LIBRARIES: ${SCALAPACK_LIBRARIES};${MPI_CXX_LIBRARIES};${LAPACK_LIBRARIES}")

# for Git information
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)

# get configuration date
string(TIMESTAMP CONFIG_DATE)

# apply them to src/auxiliary/info.cpp.in
configure_file("${CMAKE_SOURCE_DIR}/src/misc/info.cpp.in"
    "${CMAKE_BINARY_DIR}/src/misc/info.cpp" @ONLY)

add_subdirectory(src)
link_libraries(lilypad)
add_subdirectory(bin)
