//
// Created by jonas on 15.01.2019.
//
#include <iterator>
#include "inplace_merge.cpp"
#include "reinhardt_swap.cpp"
//#include "wrapper.h"
/*
 * Performs the second Iteration as described in the paper
 * returns the "new" start_gap
 */
template<typename Iterator>
Iterator second_iteratorion(Iterator start_gap, Iterator start_list, Iterator end_list){
    //pivot wird nachher mitgemergt
    int size_sorted = end_list - start_list;
    int size_unsorted = start_list - start_gap;
    if(size_sorted < size_unsorted){
        std::cout << "warnung! size_sorted < size_unsorted !!" << std::endl;
        std::cout << "Evtl. falsches Ergebnis !!" << std::endl;
        std::cout << "evtl. noch implementieren sodass es trotzdem funktioniert" << std::endl;
    }
    int size_new_gap = size_unsorted - ((2* size_unsorted) / 3);
    Iterator start_new_gap = start_list - size_new_gap;
    //TODO: space??
    std::nth_element(start_gap, start_new_gap, start_list);
    //TODO: evtl. gap als erstes um shifts später zu vermeiden
    mergesort_in_gap_right(start_gap, start_new_gap);
    Iterator end_merge = std::upper_bound(start_list, end_list, *(start_new_gap - 1));
    //Bisher haben wir: neu sortierte Liste <-> gap <-> start_list bis end_list
    //tausche nun sodass: gap <-> start_list bis pivot <-> neu sortierte Liste <-> pivot + 1 bis end_list

    Iterator start_long = start_new_gap;
    Iterator smallest = start_new_gap;

    for(Iterator i = start_gap; i != end_merge; i++){
        if(smallest == end_merge){
            if(i < start_long){
                smallest = start_long;
            }
            else{
                break;
            }
        }
        if(i == start_long){
            start_long = smallest;
        }
        std::swap(*i, *smallest);
        smallest++;
    }
    int size_new_list = size_unsorted - size_new_gap;
    Iterator start_one = end_merge - size_new_list;
    Iterator start_two = start_list - size_new_list;
    asym_merge_gap_left(start_one, end_merge, start_two, start_one, start_gap, -1);
    return end_merge - size_new_gap;
}

