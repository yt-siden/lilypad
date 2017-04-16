# CMakeLists.txt
cmake_minimum_required(VERSION 2.8)

project(lilypad C CXX)

# Version
set(lilypad_VERSION_MAJOR 0)
set(lilypad_VERSION_MINOR 1)
set(lilypad_VERSION_PATCH 0)
set(lilypad_VERSION_TWEAK 0)

# Check MPI
find_package(MPI REQUIRED)
include_directories(${MPI_CXX_INCLUDE_PATH})

# Check BLAS/LAPACK
find_package(LAPACK REQUIRED)
# Intel MKL is assumed
include_directories($ENV{MKLINCLUDE})

# BLACS/ScaLAPACK LIB
# TODO: Automatic detection
# set(ScaLAPACK_LIB mkl_scalapack_lp64 mkl_blacs_intelmpi_lp64)

# Check OpenMP
find_package(OpenMP REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

# for C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
include_directories(${CMAKE_SOURCE_DIR}/include)

# information
message(MESSAGE, "configuration info")
message(MESSAGE, "CXX:       ${CMAKE_CXX_COMPILER}")
message(MESSAGE, "CXXFLAGS:  ${CMAKE_CXX_FLAGS}")
message(MESSAGE, "LDFLAGS:   ${CMAKE_EXE_LINKER_FLAGS}")
message(MESSAGE, "LIBRARIES: ${ScaLAPACK_LIB};${MPI_CXX_LIBRARIES};${LAPACK_LIBRARIES}")

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
add_subdirectory(testing)
add_subdirectory(example)

