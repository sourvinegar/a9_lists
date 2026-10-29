cmake_minimum_required(VERSION 3.10)
# Set the C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# used internally by CMake to identify your project
project(a9_lists)
# Include the directory headers are located
include_directories(${CMAKE_SOURCE_DIR}/include)
# Add the main executable
add_executable(my_test tests/test_linked_list.cpp)