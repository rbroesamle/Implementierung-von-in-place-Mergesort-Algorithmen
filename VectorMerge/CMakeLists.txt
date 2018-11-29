cmake_minimum_required(VERSION 3.12)
project(VectorMerge)

set(CMAKE_CXX_STANDARD 14)

add_executable(VectorMerge vectormain.cpp vectormerge.cpp vectormerge.h wrapper.h)