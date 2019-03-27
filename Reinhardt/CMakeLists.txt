cmake_minimum_required(VERSION 3.12)
project(Reinhardt)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -Winline -Werror")

add_executable(Reinhardt reinhardt_gapsort.cpp reinhardt_gapsort.h reinhardt_extrasort.cpp reinhardt_extrasort.h reinhardt_merge.cpp reinhardt_merge.h vectormain.cpp inplace_mergesort_ring.cpp inplace_mergesort_qsel.h iterator_ring.h reinhardt_gapsort_ring.cpp reinhardt_merge_ring.cpp reinhardt_gapsort_ring.h reinhardt_merge_ring.h inplace_mergesort_qsel.cpp quickselect_step.cpp)