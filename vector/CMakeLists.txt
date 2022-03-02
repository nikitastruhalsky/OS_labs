cmake_minimum_required(VERSION 3.21)
project(vector)

set(CMAKE_CXX_STANDARD 14)

add_library(Number
        ../number1/cmake-build-debug/libnumber1.a
        ../number1/library.cpp)

add_library(vector SHARED library.cpp)

target_link_libraries(vector PUBLIC Number)
