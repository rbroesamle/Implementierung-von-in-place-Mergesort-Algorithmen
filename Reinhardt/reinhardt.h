//
// Created by jonas on 21.12.2018.
//

#include <vector>
#include <iostream>

template <typename Iterator>
void mergesort(Iterator begin, Iterator fin);

template <typename Iterator, typename VecIterator>
void recsort(Iterator begin_v, Iterator fin_v, VecIterator begin_m, bool i);

template <typename Iterator, typename VecIterator>
void merge (Iterator begin_v, Iterator fin_v, Iterator pivot, VecIterator begin_m);

template <typename Iterator, typename VecIterator>
void small_sort (Iterator begin_v, Iterator fin_v, VecIterator begin_m, bool i);

// Insertionsort als Ersatz für den Smallsort um auch größere Blöcke ohne weiteres Aufspalten sortieren zu können.
template <typename Iterator, typename VecIterator>
void small_insertion_sort (Iterator begin_v, Iterator fin_v, VecIterator begin_m, bool i);

template <typename Iterator,typename VecIterator>
void reinhardt_special(Iterator begin, Iterator second_begin, Iterator third_begin, Iterator fourth_begin, Iterator end,
        VecIterator extra_begin, VecIterator extra_end);

template <typename Iterator>
void merge_reinhardt(Iterator start_one, Iterator end_one, Iterator start_two, Iterator end_two, Iterator start_merge);