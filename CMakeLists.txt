cmake_minimum_required(VERSION 3.21)
project(bfbuffer_lib)


set(CMAKE_CXX_STANDARD 14)

add_library(bfbuffer_lib
        src/main/private/buffer.cpp
        src/main/public/buffer.hpp)

add_executable(bfbuffer_tests
        src/test/buffer_test.cpp)
target_include_directories(bfbuffer_tests PUBLIC
        src/main)
target_link_libraries(bfbuffer_tests
        friendly_buffer)
