//
// Created by jonas on 02.01.2019.
//

#include "inplace_mergesort.h"
#include "quicksort_step.cpp"
#include "vector"
#include "iterator"
#include "Compare.h"

//TODO: hier angeben die wievielte Iteration den Quicksort-step verwenden soll ( >= 1 )
static const unsigned int qstep = 1;
static unsigned int qstep_counter;
template <typename Iterator, typename Compare>
void in_place_mergesort(Iterator begin, Iterator fin, Compare compare){
    comp = compare;
    qstep_counter = 1;
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
        /* alternativ: Insertion Sort getrennt für die Elemente:
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
         */
        small_insertion_sort_swap(start_gap,start_list,start_gap, true);
        Iterator start_unsorted = start_gap;
        Iterator start_sorted = start_unsorted + size;
        std::vector<typename std::iterator_traits<Iterator>::value_type> extra(size);
        for(int i = 0; i != size; i++){
            extra[i] = *(start_gap + i);
        }
        for(int act = 0; act != size; act ++){
            int size_sorted = end_list - start_sorted;
            int pos;
            if(size_sorted == 0){
                for(int elem = act; elem != size; elem ++){
                    *start_unsorted = extra[elem];
                    start_unsorted ++;
                }
                break;
            }
            if(size_sorted == 1){
                pos = extra[act] < *start_sorted ? 0 : 1;
            }
            else{
                pos = std::lower_bound(start_sorted, end_list, extra[act]) - start_sorted;
            }
            Iterator insert_pos = start_sorted + pos;
            while(start_sorted != insert_pos){
                *start_unsorted = *start_sorted;
                start_unsorted ++;
                start_sorted ++;
            }
            *start_unsorted = extra[act];
            start_unsorted ++;
        }

    }
    else{
        if(qstep == qstep_counter){
            qstep_counter = 1;
            Iterator new_start_gap = second_iteratorion(start_gap, start_list, end_list);
            int size_unsorted = start_list - start_gap;
            int size_new_gap = size_unsorted - ((2* size_unsorted) / 3);
            rec_reinhardt_left_gap(new_start_gap, new_start_gap + size_new_gap, end_list);
            return;
        }
        qstep_counter ++;
        unsigned int size_unsorted = start_list - start_gap;
        unsigned int size_new_gap = size_unsorted - ((2* size_unsorted) / 3);
        Iterator end_new_sort = start_list - size_new_gap;
        mergesort_in_gap_right(start_gap, end_new_sort);
        Iterator start = end_new_sort;
        for(Iterator i = start_list; i != end_list; i++){
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

