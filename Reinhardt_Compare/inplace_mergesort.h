//
// Created by jonas on 02.01.2019.
//
#include "Compare.h"
template <typename Iterator, typename Compare>
void in_place_mergesort(Iterator begin, Iterator fin, Compare compare);

template <typename Iterator>
void rec_reinhardt_left_gap(Iterator start_gap, Iterator start_list, Iterator end_list);
