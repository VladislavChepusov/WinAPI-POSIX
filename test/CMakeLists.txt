cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 11)

project(my_test)

add_subdirectory(gtest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(my_test client.c client.h test.cpp)
target_link_libraries(my_test gtest gtest_main)
target_link_libraries(my_test pthread)
