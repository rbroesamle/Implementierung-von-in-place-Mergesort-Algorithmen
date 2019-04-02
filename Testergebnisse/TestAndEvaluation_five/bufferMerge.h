//
// Created by Patrick on 03.01.2019.
//
#pragma once
#include <vector>
#include <iostream>
#include <iterator>

namespace bufferMerge {

    //merge die Teillisten sortiert vom ersten Vektor in den zweiten
    template <typename Iterator, typename VecIterator, typename Compare>
    void merge (Iterator begin_v, Iterator fin_v, Iterator pivot, VecIterator begin_m, Compare compare) {
        Iterator middle = pivot;
        while (begin_v != middle && pivot != fin_v){
            if (!compare(*pivot, *begin_v)){
                std::swap(*begin_m, *begin_v);
                begin_v++;
            }else{
                std::swap(*begin_m, *pivot);
                pivot++;
            }
            begin_m++;
        }

        while (begin_v != middle){
            std::swap(*begin_m, *begin_v);
            begin_v++;
            begin_m++;
        }
        while (pivot != fin_v){
            std::swap(*begin_m, *pivot);
            pivot++;
            begin_m++;
        }
    }

    //insertion sort for small lists
    template <typename Iterator, typename VecIterator, typename Compare>
    void small_insertion_sort (Iterator begin_v, Iterator fin_v, VecIterator begin_m, Compare compare) {
        // Wenn i gesetzt ist sortiere innerhalb von v
        for (auto it_i = begin_v + 1; it_i != fin_v; it_i++) {
            auto temp = *it_i;
            Iterator it_j;
            for (it_j = it_i; it_j != begin_v; it_j--) {
                if (compare(temp, *(it_j - 1))) {
                    *it_j = *(it_j - 1);
                } else {
                    break;
                }
            }
            *it_j = temp;
        }
    }

    /* Rufe diese Methode jeweils rekursiv mit invertiertem boolean i auf
    * Falls nur noch 2 oder 3 Elemente in v sind, dann rufe den small-sort auf
    * Merge dann die rekursiv bereits sortierten Teillisten
    * Falls i = true, dann merge von m in v; ansonsten merge von v in m
    */
    template <typename Iterator, typename VecIterator, typename Compare>
    void recsort(Iterator begin_v, Iterator fin_v, VecIterator begin_m, bool i, Compare compare){
        int size = fin_v - begin_v;
        int pivot = (size - 1) / 2 + 1;
        if(size > 60 || !i){
            recsort(begin_v, begin_v + pivot, begin_m, !i, compare);
            recsort(begin_v + pivot, fin_v, begin_m + pivot, !i, compare);
            if(i){
                bufferMerge::merge(begin_m, begin_m + size, begin_m + pivot, begin_v, compare);
            } else {
                bufferMerge::merge(begin_v, fin_v, begin_v + pivot, begin_m, compare);
            }
        } else {
            small_insertion_sort(begin_v, fin_v, begin_m, compare);
        }
    }

    //starte den rekursiven Mergesort
    template <typename Iterator, typename Compare>
    void mergesort(Iterator begin, Iterator fin, Iterator buffer, Compare compare){
        recsort(begin, fin, buffer, true, compare);
    }
}