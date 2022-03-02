cmake_minimum_required(VERSION 3.21)
project(testing)

set(CMAKE_CXX_STANDARD 14)

add_library(Number
        ../number1/cmake-build-debug/libnumber1.a
        ../number1/library.cpp)

add_library(vector
        ../vector/cmake-build-debug/libvector.so
        ../vector/library.cpp)

add_executable(testing main.cpp)

target_link_libraries(testing PUBLIC Number vector)
