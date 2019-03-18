cmake_minimum_required(VERSION 3.12)
project(TestAndEvaluation)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -Winline -Werror")

add_executable(TestAndEvaluation main.cpp main.h wrapper.h huang_langston_merge.h chen.h bufferMerge.h)