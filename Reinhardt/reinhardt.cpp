#include "reinhardt.h"

//starte den rekursiven Mergesort
template <typename Iterator>
void mergesort(Iterator begin, Iterator fin){
    unsigned int size = fin-begin;
    Iterator first_end;
    Iterator second_end;
    Iterator third_end;

    int quarter = size/4;
    first_end = begin + quarter;

    switch(size % 4){
        case 2:
            second_end = first_end + quarter;
            third_end = second_end + (quarter + 1);
            break;
        case 3:
            second_end = first_end + (quarter + 1);
            third_end = second_end + (quarter + 1);
            break;
        default:
            //case 0 oder 1 Rest
            second_end = first_end + quarter;
            third_end = second_end + quarter;
            break;
    }

    std::vector<typename std::iterator_traits<Iterator>::value_type> merge_vector(size / 4 + 1);
    recsort(begin, first_end, merge_vector.begin(), true);
    recsort(first_end, second_end, merge_vector.begin(), true);
    recsort(second_end, third_end, merge_vector.begin(), true);
    recsort(third_end, fin, merge_vector.begin(), true);

    reinhardt_special(begin, first_end, second_end, third_end, fin, merge_vector.begin(), merge_vector.end());
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


template <typename Iterator,typename VecIterator>
void reinhardt_special(Iterator begin, Iterator second_begin, Iterator third_begin, Iterator fourth_begin, Iterator end,
                       VecIterator extra_begin, VecIterator extra_end){
    Iterator act_first = begin;
    Iterator act_second = second_begin;

    //merge die ersten size/4 Elemente in den Extravektor
    Iterator act_in = begin;
    VecIterator act_extra;
    for(act_extra = extra_begin; act_extra != extra_end - 1; act_extra ++){
        if (*act_first > *act_second) {
            *act_extra = *act_second;
            act_second++;
        } else {
            *act_extra = *act_first;
            act_first++;
        }
    }

    //merge noch genau ein Element in den Extravektor
    if(act_first == second_begin){
        //Falls erste Viertelliste schon leer
        *act_extra = *act_second;
        act_second ++;

        while(act_second != third_begin){
            *act_in = *act_second;
            act_second ++;
            act_in ++;
        }
    }
    else if(act_second == third_begin){
        //Falls zweite Viertelliste schon leer
        *act_extra = *act_first;
        act_first ++;

        while(act_first != second_begin){
            *act_in = *act_first;
            act_first ++;
            act_in ++;
        }
    }
    else{
        //Falls beide Listen noch nicht leer
        if (*act_first > *act_second) {
            *act_extra = *act_second;
            act_second++;
        } else {
            *act_extra = *act_first;
            act_first++;
        }

        merge_reinhardt(act_first, second_begin, act_second, third_begin, act_in);

    }

    Iterator erster_merge_end = begin + ((third_begin - begin) - (extra_end - extra_begin));

    //merge die beiden hinteren Viertellisten zur hinteren Halbliste
    merge_reinhardt(third_begin, fourth_begin, fourth_begin, end, erster_merge_end);

    Iterator zweiter_merge_end = end - (extra_end - extra_begin);

    Iterator now_one = erster_merge_end - 1;
    VecIterator now_one_later = extra_end - 1;
    Iterator now_two = zweiter_merge_end - 1;
    Iterator to = end - 1;
    //merge die beiden Teillisten nach rechts, bis nicht mehr möglich
    //in dieser While-Schleife, bis ExtraArray erreicht
    while(now_two != erster_merge_end && now_one != begin - 1){

        if (*now_one > *now_two) {
            *to = *now_one;
            now_one--;
        } else {
            *to = *now_two;
            now_two --;
        }
        to --;
    }
    if(now_two == erster_merge_end){
        while(now_one != begin - 1){
            *to = *now_one;
            to --;
            now_one --;
        }
    }


    //TODO: letzter Vergleich evtl. nicht nötig (bei "längeren" Listen)
    //TODO: fälle der while schleife nach verlassen behandeln
    while(to != now_two && now_two != erster_merge_end  && now_one_later != extra_begin - 1){

        if (*now_one_later > *now_two) {
            *to = *now_one_later;
            now_one_later--;
        } else {
            *to = *now_two;
            now_two --;
        }
        to --;
    }

    /*
    for(auto i = extra_begin; i!= extra_end; i++){
        std::cout << *i << ",";
    }
    std::cout << std::endl;
    for(auto i = begin; i!= zweiter_merge_end; i++){
        std::cout << *i << ",";
    }
     */

}

template <typename Iterator>
void merge_reinhardt(Iterator start_one, Iterator end_one, Iterator start_two, Iterator end_two, Iterator start_merge){
    while (start_one != end_one && start_two != end_two) {
        if (*start_one > *start_two) {
            *start_merge = *start_two;
            start_two++;
        } else {
            *start_merge = *start_one;
            start_one++;
        }
        start_merge++;
    }

    if (start_one != end_one) {
        //Merge rest of block1 into vector
        while (start_one != end_one) {
            *start_merge = *start_one;
            start_one++;
            start_merge++;
        }
    } else if (start_two != end_two) {
        //Merge rest of block2 into vector
        while (start_two != end_two) {
            *start_merge = *start_two;
            start_two++;
            start_merge++;
        }
    }
}