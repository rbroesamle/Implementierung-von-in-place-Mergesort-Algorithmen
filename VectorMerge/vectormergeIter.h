//
// Created by jonas on 07.12.2018.
//

#include <vector>
#include <iostream>
#include <iterator>

template <typename Iterator>
void mergesort(Iterator begin, Iterator fin);

template <typename Iterator>
void recsort(Iterator begin_v, Iterator fin_v, Iterator begin_m, bool i);

template <typename Iterator>
void merge (Iterator begin_v, Iterator fin_v, Iterator pivot, Iterator begin_m);

template <typename Iterator>
void small_sort (Iterator begin_v, Iterator fin_v, Iterator begin_m, bool i);

// Insertionsort als Ersatz für den Smallsort um auch größere Blöcke ohne weiteres Aufspalten sortieren zu können.
template <typename Iterator>
void small_insertion_sort (Iterator begin_v, Iterator fin_v, Iterator begin_m, bool i);