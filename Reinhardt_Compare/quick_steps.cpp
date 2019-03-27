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
template<typename Iterator, typename Compare>
Iterator second_iteratorion(Iterator start_gap, Iterator start_list, Iterator end_list, Compare comp){
    int size_unsorted = start_list - start_gap;
    int size_new_gap = size_unsorted - ((2* size_unsorted) / 3);
    Iterator start_new_list = start_gap + size_new_gap;
    int size_new_list = size_unsorted - size_new_gap;
    std::nth_element(std::reverse_iterator<Iterator>(start_list), std::reverse_iterator<Iterator>(start_new_list), std::reverse_iterator<Iterator>(start_gap), comp);
    mergesort_in(start_new_list, start_list, comp);
    Iterator end_merge = std::upper_bound(start_list, end_list, *(start_list - 1), comp);

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
            asym_merge_gap_left(start_list, end_merge, start_new_list, start_list, start_gap, -1, comp);
        }
        return end_merge - size_new_gap;
    }
    Iterator start_one = end_merge - size_new_list;
    Iterator start_two = start_list - size_new_list;
    asym_merge_gap_left(start_one, end_merge, start_two, start_one, start_gap, -1, comp);
    return end_merge - size_new_gap;
}

/*
 * Performs a Quicksort-iteration as described in the paper
 * Call this procedure if the gap is on the left side of the list
 */
template<typename Iterator, typename Compare>
void third_iteratorion_left_side(Iterator start_gap, Iterator start_list, Iterator end_list, Compare comp){

    Iterator pivot = start_list + (((end_list - start_list) - 1) / 2);
    auto pivot_value = *pivot;

    std::reverse_iterator<Iterator> act(start_list);
    std::reverse_iterator<Iterator> last(start_gap + 1);

    //mache eine Quicksort-Iteration
    while(true){
        while(!comp(pivot_value, *act) && act <= last){
            act ++;
        }
        while(comp(pivot_value, *last) && act < last){
            last --;
        }
        if(act >= last){
            break;
        }
        std::swap(*act, *last);
    }

    //act.base() zeigt auf das erste der kleineren Elemente
    Iterator new_start_short = act.base();
    int size_small = start_list - new_start_short;
    int size_big = new_start_short - start_gap;
    int size_unsorted = start_list - start_gap;
    int size_min_gap = size_unsorted - ((2* size_unsorted) / 3);
    Iterator end_merge = pivot + 1;

    if(new_start_short == start_gap){
        rec_reinhardt_left_gap(start_gap, start_list, end_merge, comp);
        return;
    }

    if (start_list == new_start_short){
        Iterator s_g = start_gap;
        for(Iterator s_l = start_list; s_l != end_merge; s_l++){
            std::swap(*s_l,*s_g);
            s_g ++;
        }
        rec_reinhardt_left_gap(s_g, end_merge, end_list, comp);
        return;
    }

    //sortiere kleine oder große Elemente, je nach Gapgröße und Größe der Partitionen
    if((size_small > size_big && size_min_gap <= size_big) || size_min_gap > size_small){
        //nun die kleinen Elemente sortieren
        mergesort_in(new_start_short, start_list, comp);

        //hier nur kurze und lange Liste tauschen
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
        Iterator start_one = end_merge - size_small;
        asym_merge_gap_left(start_one, end_merge, new_start_short, start_one, start_gap, -1, comp);
        rec_reinhardt_left_gap(end_merge - size_big, end_merge, end_list, comp);
        return;
    }

    //die großen Elemente sortieren
    mergesort_in_gap_right(start_gap, new_start_short, comp);

    //erstmal neue Liste und gap mit vorderem Teil der langen Liste swappen
    Iterator start_long = start_list;
    Iterator smallest = start_list;
    for(Iterator i = start_gap; i != end_merge; i++) {
        if (smallest == end_merge) {
            if (i < start_long) {
                smallest = start_long;
            } else {
                break;
            }
        }
        if (i == start_long) {
            start_long = smallest;
        }
        std::swap(*i, *smallest);
        smallest++;
    }
    //nun gap und hinterer Teil der langen Liste swappen
    Iterator gap_swap = end_merge - size_small;
    for(Iterator i = end_merge; i != end_list; i++) {
        std::swap(*i, *gap_swap);
        gap_swap++;
    }
    //anschließend absteigend mergen
    Iterator one_end = end_merge - size_unsorted;
    std::reverse_iterator<Iterator> start_two(gap_swap);
    std::reverse_iterator<Iterator> start_one(one_end + size_big);
    std::reverse_iterator<Iterator> end_one(one_end);
    std::reverse_iterator<Iterator> start_merge(end_list);
    asym_merge_gap_right(start_one, end_one, start_two, start_one, start_merge, -1, comp);
    rec_reinhardt_right_gap(std::reverse_iterator<Iterator>(one_end + size_small), std::reverse_iterator<Iterator>(one_end), std::reverse_iterator<Iterator>(start_gap), comp);
}






/*
 * Call this procedure with reverse iterators (gap on the right side of the list)
 * It has the same effect as the procedure above
 */
template<typename Iterator, typename Compare>
void third_iteratorion_right_side(Iterator start_gap, Iterator start_list, Iterator end_list, Compare comp) {

    Iterator pivot = start_list + (((end_list - start_list) - 1) / 2);
    auto pivot_value = *pivot;

    auto act = start_list.base();
    auto last = (start_gap + 1).base();

    //mache eine Quicksort-Iteration
    while(true){
        while(comp(pivot_value, *act) && act <= last){
            act ++;
        }
        while(!comp(pivot_value, *last) && act < last){
            last --;
        }
        if(act >= last){
            break;
        }
        std::swap(*act, *last);
    }

    //new_start_big zeigt auf das erste der größeren Elemente
    Iterator new_start_big(act);
    int size_big = start_list - new_start_big;
    int size_small = new_start_big - start_gap;
    int size_unsorted = start_list - start_gap;
    int size_min_gap = size_unsorted - ((2* size_unsorted) / 3);
    Iterator end_merge = pivot + 1;

    if(new_start_big == start_gap){
        rec_reinhardt_right_gap(start_gap, start_list, end_merge, comp);
        return;
    }

    if (start_list == new_start_big){
        Iterator s_g = start_gap;
        for(Iterator s_l = start_list; s_l != end_merge; s_l++){
            std::swap(*s_l,*s_g);
            s_g ++;
        }
        rec_reinhardt_right_gap(s_g, end_merge, end_list, comp);
        return;
    }

    //sortiere kleine oder große Elemente, je nach Gapgröße und Größe der Partitionen
    if((size_big > size_small && size_min_gap <= size_small) || size_min_gap > size_big){
        //nun die großen Elemente sortieren
        mergesort_in_gap_right(start_list.base(), new_start_big.base(), comp);

        //hier nur kurze und lange Liste tauschen
        Iterator start_long = start_list;
        Iterator smallest = start_list;
        for(Iterator i = new_start_big; i != end_merge; i++){
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

        //anschließend absteigend mergen
        Iterator start_one = end_merge - size_big;
        asym_merge_gap_right(start_one, end_merge, new_start_big, start_one, start_gap, -1, comp);
        rec_reinhardt_right_gap(end_merge - size_small, end_merge, end_list, comp);
        return;
    }

    //die kleinen Elemente sortieren
    mergesort_in(new_start_big.base(), start_gap.base(), comp);

    //erstmal neue Liste und gap mit vorderem Teil der langen Liste swappen
    Iterator start_long = start_list;
    Iterator smallest = start_list;
    for(Iterator i = start_gap; i != end_merge; i++) {
        if (smallest == end_merge) {
            if (i < start_long) {
                smallest = start_long;
            } else {
                break;
            }
        }
        if (i == start_long) {
            start_long = smallest;
        }
        std::swap(*i, *smallest);
        smallest++;
    }
    //nun gap und hinterer Teil der langen Liste swappen
    Iterator gap_swap = end_merge - size_big;
    for(Iterator i = end_merge; i != end_list; i++) {
        std::swap(*i, *gap_swap);
        gap_swap++;
    }
    //anschließend aufsteigend mergen
    Iterator one_end = end_merge - size_unsorted;
    auto start_two = gap_swap.base();
    auto start_one = (one_end + size_small).base();
    auto end_one = one_end.base();
    auto start_merge = end_list.base();
    asym_merge_gap_left(start_one, end_one, start_two, start_one, start_merge, -1, comp);
    rec_reinhardt_left_gap((one_end + size_big).base(), one_end.base(), start_gap.base(), comp);
}
