cmake_minimum_required(VERSION 3.12)
project(Reinhardt)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

add_executable(Reinhardt reinhardt.cpp reinhardt.h reinhardt_inplace.cpp reinhardt_inplace.h vectormain.cpp RAI_wrapper.h)