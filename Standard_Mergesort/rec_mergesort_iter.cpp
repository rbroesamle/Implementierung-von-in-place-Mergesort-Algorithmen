//
// Created by jonas on 07.12.2018.
//

#include "rec_mergesort_iter.h"

//starte den rekursiven Mergesort
template <typename Iterator>
void mergesort(Iterator begin, Iterator fin){
    std::vector<typename std::iterator_traits<Iterator>::value_type> merge_vector(fin-begin);
    recsort(begin, fin, merge_vector.begin(), true);
}

/* Rufe diese Methode jeweils rekursiv mit invertiertem boolean i auf
 * Falls nur noch 2 oder 3 Elemente in v sind, dann rufe den small-sort auf
 * Merge dann die rekursiv bereits sortierten Teillisten
 * Falls i = true, dann merge von m in v; ansonsten merge von v in m
*/
template <typename Iterator, typename VecIterator>
void recsort(Iterator begin_v, Iterator fin_v, VecIterator begin_m, bool i){
    int size = fin_v - begin_v;
    int pivot = (size - 1) / 2 + 1;
    //TODO: Bedingung für smallsort bzw. gewünschten smallsort anpassen
    if(size > 50){
        recsort(begin_v, begin_v + pivot, begin_m, !i);
        recsort(begin_v + pivot, fin_v, begin_m + pivot, !i);
        if(i){
            merge(begin_m, begin_m + size, begin_m + pivot, begin_v);
        } else {
            merge(begin_v, fin_v, begin_v + pivot, begin_m);
        }
    } else {
        //small_sort(begin_v, fin_v - 1, begin_m, i);
        small_insertion_sort(begin_v, fin_v, begin_m, i);
    }
}

//merge die Teillisten sortiert vom ersten Vektor in den zweiten
template <typename Iterator, typename VecIterator>
void merge (Iterator begin_v, Iterator fin_v, Iterator pivot, VecIterator begin_m) {
    Iterator middle = pivot;
    while (begin_v != middle && pivot != fin_v){
        if (*begin_v <= *pivot){
            *begin_m = *begin_v;
            begin_v++;
        }else{
            *begin_m = *pivot;
            pivot++;
        }
        begin_m++;
    }

    while (begin_v != middle){
        *begin_m = *begin_v;
        begin_v++;
        begin_m++;
    }
    while (pivot != fin_v){
        *begin_m = *pivot;
        pivot++;
        begin_m++;
    }
}

/*
 * Diese Prozedur sortiert Listen der Länge 2 oder 3
 * Falls i = true, dann sortiere innerhalb von v
 * Ansonsten sortiere die Elemente von v in m
 */
template <typename Iterator, typename VecIterator>
void small_sort (Iterator begin_v, Iterator fin_v, VecIterator begin_m, bool i){
    if (i){
        //sort in v
        if (fin_v - begin_v == 1) {
            if (*begin_v > *fin_v){
                auto temp = *begin_v;
                *begin_v = *fin_v;
                *fin_v = temp;
            }
        } else {
            Iterator m = begin_v + 1;
            if (*begin_v > *fin_v) {
                if (*m > *begin_v){
                    // o < u < u+1
                    auto temp = *begin_v;
                    *begin_v = *fin_v;
                    *fin_v = *m;
                    *m = temp;
                } else {
                    if (*fin_v > *m){
                        //u+1 < o < u
                        auto temp = *begin_v;
                        *begin_v = *m;
                        *m = *fin_v;
                        *fin_v = temp;
                    } else {
                        // o < u+1 < u
                        auto temp = *begin_v;
                        *begin_v = *fin_v;
                        *fin_v = temp;
                    }
                }
            } else {
                // u < o
                if (*m > *fin_v){
                    // u < o < u+1
                    auto temp = *m;
                    *m = *fin_v;
                    *fin_v = temp;
                } else {
                    if (*begin_v > *m){
                        // u+1 < u < o
                        auto temp = *begin_v;
                        *begin_v = *m;
                        *m = temp;
                    }
                }
            }
        }
    } else {
        //sort and write to m
        VecIterator middle_m = begin_m + 1;
        if (fin_v - begin_v == 1) {
            if (*begin_v > *fin_v){
                *begin_m = *fin_v;
                *middle_m = *begin_v;
            } else {
                *begin_m = *begin_v;
                *middle_m = *fin_v;
            }
        } else {
            VecIterator fin_m = begin_m + 2;
            Iterator middle_v = begin_v + 1;
            if (*begin_v > *fin_v) {
                if (*middle_v > *begin_v){
                    // o < u < u+1
                    *begin_m = *fin_v;
                    *fin_m = *middle_v;
                    *middle_m = *begin_v;
                } else {
                    if (*fin_v > *middle_v){
                        //u+1 < o < u
                        *begin_m = *middle_v;
                        *middle_m = *fin_v;
                        *fin_m = *begin_v;
                    } else {
                        // o < u+1 < u
                        *begin_m = *fin_v;
                        *fin_m = *begin_v;
                        *middle_m = *middle_v;
                    }
                }
            } else {
                // u < o
                if (*middle_v > *fin_v){
                    // u < o < u+1
                    *begin_m = *begin_v;
                    *middle_m = *fin_v;
                    *fin_m = *middle_v;
                } else {
                    if (*begin_v > *middle_v){
                        // u+1 < u < o
                        *fin_m = *fin_v;
                        *begin_m = *middle_v;
                        *middle_m = *begin_v;
                    } else {
                        // u < u+1 < o nur kopieren
                        *begin_m = *begin_v;
                        *middle_m = *middle_v;
                        *fin_m = *fin_v;
                    }
                }
            }
        }
    }
}
template <typename Iterator, typename VecIterator>
void small_insertion_sort (Iterator begin_v, Iterator fin_v, VecIterator begin_m, bool i){
    if (i) {
        // Wenn i gesetzt ist sortiere innerhalb von v
        for(auto it_i = begin_v + 1; it_i != fin_v; it_i++){
            auto temp = *it_i;
            Iterator it_j;
            for (it_j = it_i; it_j != begin_v; it_j--) {
                if (*(it_j-1) > temp) {
                    *it_j = *(it_j -1);
                } else {
                    break;
                }
            }
            *it_j = temp;
        }
    } else {
        // Wenn i nicht gesetzt ist sortiere nach m
        *begin_m = *begin_v;
        for(auto it_i = begin_v + 1; it_i != fin_v; it_i++){
            VecIterator it_j;
            for (it_j = begin_m + (it_i - begin_v); it_j != begin_m; it_j--) {
                if (*(it_j-1) > *it_i) {
                    *it_j = *(it_j -1);
                } else {
                    break;
                }
            }
            *it_j = *it_i;
        }
    }
}