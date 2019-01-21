cmake_minimum_required(VERSION 3.12)
project(Reinhardt)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -Winline -Werror")

add_executable(Reinhardt reinhardt_swap.cpp reinhardt_swap.h reinhardt.cpp reinhardt.h inplace_merge.cpp inplace_merge.h vectormain.cpp inplace_mergesort.cpp inplace_mergesort.h RAI_shift.h reinhardt_swap_shift.cpp inplace_merge_shift.cpp reinhardt_swap_shift.h inplace_merge_shift.h inplace_mergesort_without_ring.cpp quicksort_step.cpp)