//
// Created by jonas on 07.12.2018.
//
#include <vector>
#include <iostream>
#include <iterator>
//starte den rekursiven Mergesort

namespace vectormergeIter {

    template<typename Iterator, typename VecIterator, typename Comp>
    void merge(Iterator begin_v, Iterator fin_v, Iterator pivot, VecIterator begin_m, Comp comp) {
        Iterator middle = pivot;
        while (begin_v != middle && pivot != fin_v) {
            if (comp(*pivot, *begin_v)) {
                *begin_m = *pivot;
                pivot++;
            } else {
                *begin_m = *begin_v;
                begin_v++;
            }
            begin_m++;
        }

        while (begin_v != middle) {
            *begin_m = *begin_v;
            begin_v++;
            begin_m++;
        }
        while (pivot != fin_v) {
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
    template<typename Iterator, typename VecIterator, typename Comp>
    void small_sort(Iterator begin_v, Iterator fin_v, VecIterator begin_m, bool i, Comp comp) {
        if (i) {
            //sort in v
            if (fin_v - begin_v == 1) {
                if (comp(*fin_v, *begin_v)) {
                    auto temp = *begin_v;
                    *begin_v = *fin_v;
                    *fin_v = temp;
                }
            } else {
                Iterator m = begin_v + 1;
                if (comp(*fin_v, *begin_v)) {
                    if (comp(*begin_v, *m)) {
                        // o < u < u+1
                        auto temp = *begin_v;
                        *begin_v = *fin_v;
                        *fin_v = *m;
                        *m = temp;
                    } else {
                        if (comp(*m, *fin_v)) {
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
                    if (comp(*fin_v, *m)) {
                        // u < o < u+1
                        auto temp = *m;
                        *m = *fin_v;
                        *fin_v = temp;
                    } else {
                        if (comp(*m, *begin_v)) {
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
                if (comp(*fin_v, *begin_v)) {
                    *begin_m = *fin_v;
                    *middle_m = *begin_v;
                } else {
                    *begin_m = *begin_v;
                    *middle_m = *fin_v;
                }
            } else {
                VecIterator fin_m = begin_m + 2;
                Iterator middle_v = begin_v + 1;
                if (comp(*fin_v, *begin_v)) {
                    if (comp(*begin_v, *middle_v)) {
                        // o < u < u+1
                        *begin_m = *fin_v;
                        *fin_m = *middle_v;
                        *middle_m = *begin_v;
                    } else {
                        if (comp(*middle_v, *fin_v)) {
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
                    if (comp(*fin_v, *middle_v)) {
                        // u < o < u+1
                        *begin_m = *begin_v;
                        *middle_m = *fin_v;
                        *fin_m = *middle_v;
                    } else {
                        if (comp(*middle_v, *begin_v)) {
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

    template<typename Iterator, typename VecIterator, typename Comp>
    void small_insertion_sort(Iterator begin_v, Iterator fin_v, VecIterator begin_m, bool i, Comp comp) {
        if (i) {
            // Wenn i gesetzt ist sortiere innerhalb von v
            for (auto it_i = begin_v + 1; it_i != fin_v; it_i++) {
                auto temp = *it_i;
                Iterator it_j;
                for (it_j = it_i; it_j != begin_v; it_j--) {
                    if (comp(temp,*(it_j - 1))) {
                        *it_j = *(it_j - 1);
                    } else {
                        break;
                    }
                }
                *it_j = temp;
            }
        } else {
            // Wenn i nicht gesetzt ist sortiere nach m
            *begin_m = *begin_v;
            for (auto it_i = begin_v + 1; it_i != fin_v; it_i++) {
                VecIterator it_j;
                for (it_j = begin_m + (it_i - begin_v); it_j != begin_m; it_j--) {
                    if (comp(*it_i,*(it_j - 1))) {
                        *it_j = *(it_j - 1);
                    } else {
                        break;
                    }
                }
                *it_j = *it_i;
            }
        }
    }

    /* Rufe diese Methode jeweils rekursiv mit invertiertem boolean i auf
     * Falls nur noch 2 oder 3 Elemente in v sind, dann rufe den small-sort auf
    * Merge dann die rekursiv bereits sortierten Teillisten
    * Falls i = true, dann merge von m in v; ansonsten merge von v in m
    */
    template<typename Iterator, typename VecIterator, typename Comp>
    void recsort(Iterator begin_v, Iterator fin_v, VecIterator begin_m, bool i, Comp comp) {
        int size = fin_v - begin_v;
        int pivot = (size - 1) / 2 + 1;
        //TODO: Bedingung für smallsort bzw. gewünschten smallsort anpassen
        if (size > 3) {
            vectormergeIter::recsort(begin_v, begin_v + pivot, begin_m, !i, comp);
            vectormergeIter::recsort(begin_v + pivot, fin_v, begin_m + pivot, !i, comp);
            if (i) {
                vectormergeIter::merge(begin_m, begin_m + size, begin_m + pivot, begin_v, comp);
            } else {
                vectormergeIter::merge(begin_v, fin_v, begin_v + pivot, begin_m, comp);
            }
        } else {
            vectormergeIter::small_sort(begin_v, fin_v - 1, begin_m, i, comp);
            //vectormergeIter::small_insertion_sort(begin_v, fin_v, begin_m, i, comp);
        }
    }

    //merge die Teillisten sortiert vom ersten Vektor in den zweiten
    template<typename Iterator, typename Comp>
    void sort(Iterator begin, Iterator fin, Comp comp) {
        std::vector<typename std::iterator_traits<Iterator>::value_type> merge_vector(fin - begin);
        vectormergeIter::recsort(begin, fin, merge_vector.begin(), true, comp);
    }

}