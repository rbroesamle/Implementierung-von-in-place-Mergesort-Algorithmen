#include <vector>
#include <iostream>

template <typename Iterator, typename Compare>
void mergesort_in(Iterator begin, Iterator fin, Compare comp);

template <typename Iterator, typename Compare>
void mergesort_in_gap_right(Iterator begin, Iterator fin, Compare comp);

template <typename Iterator, typename VecIterator, typename Compare>
void recsort_swap(Iterator begin_v, Iterator fin_v, VecIterator begin_m, bool i, Compare comp);

template <typename Iterator, typename VecIterator, typename Compare>
void merge_swap (Iterator begin_v, Iterator fin_v, Iterator pivot, VecIterator begin_m, Compare comp);

template <typename Iterator, typename VecIterator, typename Compare>
void small_sort_swap (Iterator begin_v, Iterator fin_v, VecIterator begin_m, bool i, Compare comp);

// Insertionsort als Ersatz für den Smallsort um auch größere Blöcke ohne weiteres Aufspalten sortieren zu können.
template <typename Iterator, typename VecIterator, typename Compare>
void small_insertion_sort_swap (Iterator begin_v, Iterator fin_v, VecIterator begin_m, bool i, Compare comp);

template <typename Iterator,typename VecIterator, typename Compare>
void reinhardt_special_swap(Iterator begin, Iterator second_begin, Iterator third_begin, Iterator fourth_begin, Iterator end,
                       VecIterator extra_begin, VecIterator extra_end, Compare comp);

template <typename Iterator,typename VecIterator, typename Compare>
void merge_reinhardt_swap(VecIterator start_one, VecIterator end_one, Iterator start_two, Iterator end_two, Iterator start_merge, Compare comp);
