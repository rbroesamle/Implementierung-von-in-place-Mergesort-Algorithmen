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
    Iterator end_merge = pivot + 1;
    Iterator size_short = start_list - new_start_short;

    //besser für später um einen shift zu verhindern: nur kurze und lange Liste tauschen
    Iterator start_long = start_list;
    Iterator smallest = start_list;
    for(Iterator i = new_start_short; i != end_merge; i++){
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

    //anschließend aufsteigend mergen, zweite Liste fängt bei Start erster Liste vor dem Tausch an
    Iterator start_one = end_merge - size_short;
    asym_merge_gap_left(start_one, end_merge, new_start_short, start_one, start_gap, -1);
    return end_merge - (start_list - start_gap);
}

