//
// Created by jonas on 15.01.2019.
//
#include <iterator>
#include "reinhardt_merge.cpp"
#include "reinhardt_gapsort.cpp"
/*
 * Performs a quickselect-step
 * returns the "new" start_gap
 */
template<typename Iterator>
Iterator second_iteratorion(Iterator start_gap, Iterator start_list, Iterator end_list){
    int size_unsorted = start_list - start_gap;
    int size_new_gap = size_unsorted - ((2* size_unsorted) / 3);
    Iterator start_new_list = start_gap + size_new_gap;
    int size_new_list = size_unsorted - size_new_gap;
    std::nth_element(std::reverse_iterator<Iterator>(start_list), std::reverse_iterator<Iterator>(start_new_list), std::reverse_iterator<Iterator>(start_gap));
    mergesort_in(start_new_list, start_list);
    Iterator end_merge = std::upper_bound(start_list, end_list, *(start_list - 1));

    //tausche die Listen, falls erste Liste kleiner als zweite Liste
    if(size_new_list < end_merge - start_list){
        Iterator start_long = start_list;
        Iterator smallest = start_list;

        for(Iterator i = start_new_list; i != end_merge; i++){
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
    } else{
        if(start_list == end_merge){
            Iterator swap = start_gap;
            for(Iterator i = start_new_list; i != start_list; i++){
                std::swap(*i, *swap);
                swap ++;
            }
        } else{
            asym_merge_gap_left(start_list, end_merge, start_new_list, start_list, start_gap, -1);
        }
        return end_merge - size_new_gap;
    }
    Iterator start_one = end_merge - size_new_list;
    Iterator start_two = start_list - size_new_list;
    asym_merge_gap_left(start_one, end_merge, start_two, start_one, start_gap, -1);
    return end_merge - size_new_gap;
}