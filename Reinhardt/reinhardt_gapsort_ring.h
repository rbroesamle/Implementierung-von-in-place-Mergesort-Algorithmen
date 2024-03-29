#include <vector>
#include <iostream>

template <typename Iterator>
void mergesort_in(Iterator begin, Iterator fin);

template <typename Iterator>
void recsort_swap(Iterator begin_v, Iterator fin_v, Iterator begin_m, bool i);

template <typename Iterator>
void merge_swap (Iterator begin_v, Iterator fin_v, Iterator pivot, Iterator begin_m);

template <typename Iterator>
void small_sort_swap (Iterator begin_v, Iterator fin_v, Iterator begin_m, bool i);

// Insertionsort als Ersatz für den Smallsort um auch größere Blöcke ohne weiteres Aufspalten sortieren zu können.
template <typename Iterator>
void small_insertion_sort_swap (Iterator begin_v, Iterator fin_v, Iterator begin_m, bool i);

template <typename Iterator>
void reinhardt_special_swap(Iterator begin, Iterator second_begin, Iterator third_begin, Iterator fourth_begin, Iterator end,
                       Iterator extra_begin, Iterator extra_end);

template <typename Iterator>
void merge_reinhardt_swap(Iterator start_one, Iterator end_one, Iterator start_two, Iterator end_two, Iterator start_merge);
