cmake_minimum_required(VERSION 3.12)
project(Code)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
add_executable(Code main.cpp huang_langston_merge.h wrapper.h mergesort.cpp mergesort.h bufferMerge.h chen.h)