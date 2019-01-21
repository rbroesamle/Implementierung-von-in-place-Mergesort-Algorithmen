//
// Created by jonas on 15.01.2019.
//
#include <iterator>
#include "inplace_merge.cpp"
#include "reinhardt_swap.cpp"

/*
 * Performs the second Iteration as described in the paper
 * returns the "new" start_gap
 */
template<typename Iterator>
Iterator second_iteratorion(Iterator start_gap, Iterator start_list, Iterator end_list){
    //pivot wird nachher mitgemergt
    Iterator pivot = start_list + (((end_list - start_list) - 1) / 2);
    auto pivot_value = *pivot;

    std::reverse_iterator<Iterator> act(start_list);
    std::reverse_iterator<Iterator> last(start_gap + 1);
    //gap_middle wird später auf jeden Fall noch zur gap gehören
    std::reverse_iterator<Iterator> gap_middle(start_gap + ((start_list - start_gap - 1) / 2));

    /*
    while(act <= last && act != gap_middle){
        if(*act > pivot_value){
            std::swap(*act, *last);
            last --;
        } else{
            act ++;
        }
    }
     */
    while(true){
        while(*act <= pivot_value && act <= last && act != gap_middle){
            act ++;
        }
        if(act >= last || act == gap_middle){
            break;
        }
        while(*last > pivot_value){
            last --;
        }
        std::swap(*act, *last);
    }


    Iterator new_start_short = act.base();
    mergesort_in(new_start_short, start_list);
    asym_merge_gap_left(new_start_short, start_list, start_list, pivot + 1);
    return (pivot + 1) - (new_start_short - start_gap);
}

