cmake_minimum_required(VERSION 3.12)
project(Reinhardt)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

add_executable(Reinhardt reinhardt_swap.cpp reinhardt_swap.h reinhardt.cpp reinhardt.h inplace_merge.cpp inplace_merge.h vectormain.cpp RAI_wrapper.h inplace_mergesort.cpp inplace_mergesort.h )