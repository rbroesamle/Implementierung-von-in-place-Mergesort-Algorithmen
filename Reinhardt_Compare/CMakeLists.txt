cmake_minimum_required(VERSION 3.12)
project(Reinhardt)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -Winline -Werror")

add_executable(Reinhardt reinhardt_gapsort.cpp reinhardt_gapsort.h reinhardt_merge.cpp reinhardt_merge.h vectormain.cpp inplace_mergesort_qsel.h inplace_mergesort_qsel.cpp quick_steps.cpp inplace_mergesort_qsort.cpp inplace_mergesort_qsort.h)