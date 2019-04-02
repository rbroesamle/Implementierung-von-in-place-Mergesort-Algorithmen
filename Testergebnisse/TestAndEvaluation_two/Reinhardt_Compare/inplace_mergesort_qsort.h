//
// Created by jonas on 02.01.2019.
//
template <typename Iterator, typename Compare>
void in_place_mergesort(Iterator begin, Iterator fin, Compare comp);

template <typename Iterator, typename Compare>
void rec_reinhardt_left_gap(Iterator start_gap, Iterator start_list, Iterator end_list, Compare comp);

template <typename Iterator, typename Compare>
void rec_reinhardt_right_gap(Iterator start_gap, Iterator start_list, Iterator end_list, Compare comp);