//
// Created by jonas on 02.01.2019.
//
#include "iterator_ring.h"
#include "inplace_mergesort_qsel.h"
#include "reinhardt_gapsort_ring.cpp"

template <typename Iterator>
void in_place_mergesort(Iterator begin, Iterator fin){
    RAI<Iterator>::initialize(begin, fin, 0);
    RAI<std::reverse_iterator<Iterator>>::initialize(std::make_reverse_iterator(fin), std::make_reverse_iterator(begin), RAI<Iterator>::size - RAI<Iterator>::shift);
    unsigned int size = fin - begin;
    if(size < 128){
        small_insertion_sort_swap(begin, fin, begin, true);
        return;
    }
    mergesort_in(begin + size / 5 + 1, fin);
    rec_reinhardt_left_gap(begin, begin + (size / 5 + 1), fin);
}

template <typename Iterator>
void rec_reinhardt_left_gap(Iterator start_gap, Iterator start_list, Iterator end_list){
    unsigned int size = start_list - start_gap;
    //für unsortierte Liste < Konstante dann füge einzeln in die lange bereits sortierte Liste ein (O(n))
    if(size < 8){
        //TODO: gleich ganzer Block shiften
        for(Iterator now = start_list - 1; now != start_gap - 1; now--){
            auto temp = RAI<Iterator>::star(now);
            int size_list = (end_list - now) - 1;
            int pos = binSearch(now, now + 1, size_list - 1);
            pos = pos == -1 ? size_list : pos;
            Iterator i;
            for(i = now; i != now + pos; i++){
                *RAI<Iterator>::get(i) = RAI<Iterator>::star(i+1);
            }
            *RAI<Iterator>::get(i) = temp;
        }
        //finaler Shift
        Iterator start_short = RAI<Iterator>::get(start_gap);
        Iterator smallest = RAI<Iterator>::get(start_gap);
        for(Iterator i = start_gap; i != end_list; i++){
            if(smallest == end_list){
                if(i < start_short){
                    smallest = start_short;
                }
                else{
                    break;
                }
            }
            if(i == start_short){
                start_short = smallest;
            }
            std::swap(*i, *smallest);
            smallest++;
        }
    }
    else{
        unsigned int size_unsorted = start_list - start_gap;
        unsigned int size_new_gap = size_unsorted - ((2* size_unsorted) / 3);
        mergesort_in(start_gap + size_new_gap, start_list);
        /*
        Iterator start = start_gap;
        for(Iterator i = start_gap + size_new_gap; i != end_list; i++){
            std::swap(*start, *i);
            start ++;
        }
         */
        //RAI<Iterator>::shift = (RAI<Iterator>::shift + size_new_gap) % RAI<Iterator>::size;
        //RAI<std::reverse_iterator<Iterator>>::shift = RAI<Iterator>::size - RAI<Iterator>::shift;
        RAI<Iterator>::set_shift((RAI<Iterator>::shift + size_new_gap) % RAI<Iterator>::size);
        RAI<std::reverse_iterator<Iterator>>::set_shift(RAI<Iterator>::size - RAI<Iterator>::shift);

        Iterator start_long = start_gap + (size_unsorted - size_new_gap);
        std::reverse_iterator<Iterator> start_merge(end_list);
        std::reverse_iterator<Iterator> start_second(end_list - size_new_gap);
        std::reverse_iterator<Iterator> end_second(start_long);
        std::reverse_iterator<Iterator> end_first(start_gap);

        asym_merge_gap_right(end_second, end_first, start_second, end_second, start_merge,-1);
        rec_reinhardt_left_gap(start_gap, start_gap + size_new_gap, end_list);

    }
}
