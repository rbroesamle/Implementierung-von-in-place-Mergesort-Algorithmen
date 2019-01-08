//
// Created by jonas on 02.01.2019.
//

#include "inplace_mergesort.h"
#include "inplace_merge.cpp"
#include "reinhardt_swap.cpp"

template <typename Iterator>
void in_place_mergesort(Iterator begin, Iterator fin){
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
        //alternativ zur binären Suche die lineare Suche:
        /*
        for(Iterator now = start_list - 1; now != start_gap - 1; now--){
            auto temp = *now;
            for(Iterator comp = now; comp != end_list - 1; comp++){
                if(*(comp + 1) < temp){
                    *comp = *(comp + 1);
                } else{
                    *comp = temp;
                    break;
                }
            }
        }
         */
        for(Iterator now = start_list - 1; now != start_gap - 1; now--){
            auto temp = *now;
            int size_list = (end_list - now) - 1;
            int pos = binSearch(now, now + 1, size_list - 1);
            pos = pos == -1 ? size_list : pos;
            Iterator i;
            for(i = now; i != now + pos; i++){
                *i = *(i+1);
            }
            *i = temp;
        }
    }
    else{
        unsigned int size_unsorted = start_list - start_gap;
        unsigned int size_new_gap = size_unsorted - ((2* size_unsorted) / 3);
        mergesort_in(start_gap + size_new_gap, start_list);
        Iterator start = start_gap;
        for(Iterator i = start_gap + size_new_gap; i != end_list; i++){
            std::swap(*start, *i);
            start ++;
        }
        Iterator start_long = start_gap + (size_unsorted - size_new_gap);
        std::reverse_iterator<Iterator> start_merge(end_list);
        std::reverse_iterator<Iterator> start_second(end_list - size_new_gap);
        std::reverse_iterator<Iterator> end_second(start_long);
        std::reverse_iterator<Iterator> end_first(start_gap);

        asym_merge_gap_right(end_second, end_first, start_second, end_second, start_merge,-1);
        rec_reinhardt_left_gap(start_gap, start_gap + size_new_gap, end_list);

    }
}

