//
// Created by jonas on 02.01.2019.
//

#include "inplace_mergesort.h"
#include "inplace_merge.cpp"
#include "reinhardt_swap.cpp"

//#include "RAI_wrapper.h"

//template<typename Iterator>
//RAI_wrapper<Iterator> wrap;

template <typename Iterator>
void in_place_mergesort(Iterator begin, Iterator fin){
    //wrap<Iterator> = RAI_wrapper<Iterator>(begin, fin - 1);
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
        //todo: hier zuerst binäre Suche statt wie hier "lineares Einfügen", um Vergleiche einzusparen
        for(Iterator now = start_list - 1; now != start_gap - 1; now--){
            Iterator next = now + 1;
            while(next != end_list && *next < *now){
                std::swap(*now, *next);
                now = next;
                next = now + 1;
            }
        }
    }
    else{
        unsigned int size_unsorted = start_list - start_gap;
        unsigned int size_new_gap = size_unsorted - ((2* size_unsorted) / 3);
        mergesort_in(start_gap + size_new_gap, start_list);
        //todo: logischer ringspeicher statt shift! iterator+x als (iterator+x) - size falls drüber (+/- überladen) um die shifts zu vermeiden
        Iterator start = start_gap;
        for(Iterator i = start_gap + size_new_gap; i != end_list; i++){
            std::swap(*start, *i);
            start ++;
        }
        //todo: asymmetrisch mergen!
        Iterator start_long = start_gap + (size_unsorted - size_new_gap);
        std::reverse_iterator<Iterator> start_merge(end_list);
        std::reverse_iterator<Iterator> start_second(end_list - size_new_gap);
        std::reverse_iterator<Iterator> end_second(start_long);
        std::reverse_iterator<Iterator> end_first(start_gap);

        asym_merge_gap_right(end_second, end_first, start_second, end_second, start_merge,-1);
        rec_reinhardt_left_gap(start_gap, start_gap + size_new_gap, end_list);

    }
}
