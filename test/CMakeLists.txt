# Basic CMake project
cmake_minimum_required(VERSION 3.10.2) # version that is currently installed in test env

# Set source files
set(AOI_SOURCES
    example.cpp)

# Set C++17 as the standard
set(CMAKE_CXX_STANDARD 17)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests ${AOI_SOURCES})
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread fruit)

