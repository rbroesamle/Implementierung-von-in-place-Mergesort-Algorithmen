//
// Created by jonas on 07.12.2018.
//

#include "vectormergeIter.h"

template <typename Iterator, typename T>
void mergesort(Iterator begin, Iterator fin){
    std::vector<T> merge_vector;
    merge_vector.reserve(fin - begin);
    recsort<Iterator,T>(begin, fin, merge_vector.begin(), true);
}

template <typename Iterator, typename T>
void recsort(Iterator begin_v, Iterator fin_v, Iterator begin_m, bool i){
    int size = fin_v - begin_v;
    int pivot = size / 2;
    if(fin_v - begin_v > 3){
        recsort<Iterator,T>(begin_v, begin_v + pivot, begin_m, !i);
        recsort<Iterator,T>(begin_v + pivot, fin_v, begin_m + pivot, !i);
        if(i){
            merge<Iterator,T>(begin_m, begin_m + size, begin_m + pivot, begin_v);
        } else {
            merge<Iterator,T>(begin_v, fin_v, begin_v + pivot, begin_m);
        }
    } else {
        small_sort<Iterator,T>(begin_v, fin_v - 1, begin_m, i);
    }
}

template <typename Iterator, typename T>
void merge (Iterator begin_v, Iterator fin_v, Iterator pivot, Iterator begin_m) {
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

template <typename Iterator, typename T>
void small_sort (Iterator begin_v, Iterator fin_v, Iterator begin_m, bool i){
    if (i){
        //sort in v
        if (fin_v - begin_v == 1) {
            if (*begin_v > *fin_v){
                T temp = *begin_v;
                *begin_v = *fin_v;
                *fin_v = temp;
            }
        } else {
            Iterator m = begin_v + 1;
            if (*begin_v > *fin_v) {
                if (*m > *begin_v){
                    // o < u < u+1
                    T temp = *begin_v;
                    *begin_v = *fin_v;
                    *fin_v = *m;
                    *m = temp;
                } else {
                    if (*fin_v > *m){
                        //u+1 < o < u
                        T temp = *begin_v;
                        *begin_v = *m;
                        *m = *fin_v;
                        *fin_v = temp;
                    } else {
                        // o < u+1 < u
                        T temp = *begin_v;
                        *begin_v = *fin_v;
                        *fin_v = temp;
                    }
                }
            } else {
                // u < o
                if (*m > *fin_v){
                    // u < o < u+1
                    T temp = *m;
                    *m = *fin_v;
                    *fin_v = temp;
                } else {
                    if (*begin_v > *m){
                        // u+1 < u < o
                        T temp = *begin_v;
                        *begin_v = *m;
                        *m = temp;
                    }
                }
            }
        }
    } else {
        //sort and write to m
        Iterator middle_m = begin_m + 1;
        if (fin_v - begin_v == 1) {
            if (*begin_v > *fin_v){
                *begin_m = *fin_v;
                *middle_m = *begin_v;
            } else {
                *begin_m = *begin_v;
                *middle_m = *fin_v;
            }
        } else {
            Iterator fin_m = begin_m + 2;
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