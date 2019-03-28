cmake_minimum_required(VERSION 3.12)
project(Standard_Mergesort)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

add_executable(Standard_Mergesort vectormain.cpp rec_mergesort_reference.cpp rec_mergesort_reference.h wrapper.h iterative_mergesort.cpp iterative_mergesort.h)