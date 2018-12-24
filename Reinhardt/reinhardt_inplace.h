//
// Created by jonas on 22.12.2018.
//
template <typename Iterator>
void sym_merge_gap_left(Iterator start_one, Iterator end_one, Iterator start_two, Iterator end_two, Iterator merge);

template <typename Iterator>
void sym_merge_gap_right(Iterator start_one, Iterator end_one, Iterator start_two, Iterator end_two, Iterator merge);

template <typename Iterator>
void asym_merge(Iterator start_one, Iterator end_one, Iterator start_two, Iterator end_two, Iterator merge, bool direction);

template <typename Iterator>
void in_place_mergesort(Iterator begin, Iterator fin);

template <typename Iterator>
void rec_reinhardt_left_gap(Iterator start_gap, Iterator start_list, Iterator end_list);