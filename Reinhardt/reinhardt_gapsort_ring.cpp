#include "iterator_ring.h"
#include "reinhardt_gapsort_ring.h"
#include "reinhardt_merge_ring.cpp"
#include<algorithm>


/**
 * Rufe diese Prozedur im In-Place-Algorithmus auf
 * Sie verwendet swap statt Zuweisungen und als Gap einen Teil der unsortierten Liste (size/4 + 1 Elemente vor begin)
 */
template <typename Iterator>
void mergesort_in(Iterator begin, Iterator fin){
    unsigned int size = fin-begin;

    //sortiere mit Insertion Sort für die "kleinen Fälle"
    if(size < 128){
        small_insertion_sort_swap(begin, fin, begin, true);
        return;
    }

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

    recsort_swap(begin, first_end, (begin - (size / 4)) - 1, true);
    recsort_swap(first_end, second_end, (begin - (size / 4)) - 1, true);
    recsort_swap(second_end, third_end, (begin - (size / 4)) - 1, true);
    recsort_swap(third_end, fin, (begin - (size / 4)) - 1, true);

    reinhardt_special_swap(begin, first_end, second_end, third_end, fin, (begin - (size / 4)) - 1, begin);
}

/* Rufe diese Methode jeweils rekursiv mit invertiertem boolean i auf
 * Falls nur noch 2 oder 3 Elemente in v sind, dann rufe den small-sort auf
 * Merge dann die rekursiv bereits sortierten Teillisten
 * Falls i = true, dann merge von m in v; ansonsten merge von v in m
*/
template <typename Iterator>
void recsort_swap(Iterator begin_v, Iterator fin_v, Iterator begin_m, bool i){
    int size = fin_v - begin_v;
    int pivot = (size - 1) / 2 + 1;
    //TODO: Bedingung für smallsort bzw. gewünschten smallsort anpassen
    if(size > 50){
        recsort_swap(begin_v, begin_v + pivot, begin_m, !i);
        recsort_swap(begin_v + pivot, fin_v, begin_m + pivot, !i);
        if(i){
            merge_swap(begin_m, begin_m + size, begin_m + pivot, begin_v);
        } else {
            merge_swap(begin_v, fin_v, begin_v + pivot, begin_m);
        }
    } else {
        //small_sort_swap(begin_v, fin_v - 1, begin_m, i);
        small_insertion_sort_swap(begin_v, fin_v, begin_m, i);
    }
}

//merge die Teillisten sortiert vom ersten Vektor in den zweiten
template <typename Iterator>
void merge_swap (Iterator begin_v, Iterator fin_v, Iterator pivot, Iterator begin_m) {
    Iterator middle = pivot;
    while (begin_v != middle && pivot != fin_v){
        if (RAI<Iterator>::star(begin_v) <= RAI<Iterator>::star(pivot)){
            std::swap(*RAI<Iterator>::get(begin_m), *RAI<Iterator>::get(begin_v));
            begin_v++;
        }else{
            std::swap(*RAI<Iterator>::get(begin_m), *RAI<Iterator>::get(pivot));
            pivot++;
        }
        begin_m++;
    }

    while (begin_v != middle){
        std::swap(*RAI<Iterator>::get(begin_m), *RAI<Iterator>::get(begin_v));
        begin_v++;
        begin_m++;
    }
    while (pivot != fin_v){
        std::swap(*RAI<Iterator>::get(begin_m), *RAI<Iterator>::get(pivot));
        pivot++;
        begin_m++;
    }
}

/*
 * Diese Prozedur sortiert Listen der Länge 2 oder 3
 * Falls i = true, dann sortiere innerhalb von v
 * Ansonsten sortiere die Elemente von v in m
 */
//TODO: ändern auf shift
/*
template <typename Iterator>
void small_sort_swap (Iterator begin_v, Iterator fin_v, Iterator begin_m, bool i){
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
        Iterator middle_m = begin_m + 1;
        if (fin_v - begin_v == 1) {
            if (*begin_v > *fin_v){
                std::swap(*begin_m, *fin_v);
                std::swap(*middle_m, *begin_v);
            } else {
                std::swap(*begin_m, *begin_v);
                std::swap(*middle_m, *fin_v);
            }
        } else {
            Iterator fin_m = begin_m + 2;
            Iterator middle_v = begin_v + 1;
            if (*begin_v > *fin_v) {
                if (*middle_v > *begin_v){
                    // o < u < u+1
                    std::swap(*begin_m, *fin_v);
                    std::swap(*fin_m, *middle_v);
                    std::swap(*middle_m, *begin_v);
                } else {
                    if (*fin_v > *middle_v){
                        //u+1 < o < u
                        std::swap(*begin_m, *middle_v);
                        std::swap(*middle_m, *fin_v);
                        std::swap(*fin_m, *begin_v);
                    } else {
                        // o < u+1 < u
                        std::swap(*begin_m, *fin_v);
                        std::swap(*fin_m, *begin_v);
                        std::swap(*middle_m, *middle_v);
                    }
                }
            } else {
                // u < o
                if (*middle_v > *fin_v){
                    // u < o < u+1
                    std::swap(*begin_m, *begin_v);
                    std::swap(*middle_m, *fin_v);
                    std::swap(*fin_m, *middle_v);
                } else {
                    if (*begin_v > *middle_v){
                        // u+1 < u < o
                        std::swap(*fin_m, *fin_v);
                        std::swap(*begin_m, *middle_v);
                        std::swap(*middle_m, *begin_v);
                    } else {
                        // u < u+1 < o nur kopieren
                        std::swap(*begin_m, *begin_v);
                        std::swap(*middle_m, *middle_v);
                        std::swap(*fin_m, *fin_v);
                    }
                }
            }
        }
    }
}
 */
template <typename Iterator>
void small_insertion_sort_swap (Iterator begin_v, Iterator fin_v, Iterator begin_m, bool i){
    if (i) {
        // Wenn i gesetzt ist sortiere innerhalb von v
        for(auto it_i = begin_v + 1; it_i != fin_v; it_i++){
            auto temp = RAI<Iterator>::star(it_i);
            Iterator it_j;
            for (it_j = it_i; it_j != begin_v; it_j--) {
                if (RAI<Iterator>::star(it_j-1) > temp) {
                    *RAI<Iterator>::get(it_j) = RAI<Iterator>::star(it_j -1);
                } else {
                    break;
                }
            }
            *RAI<Iterator>::get(it_j) = temp;
        }
    } else {
        // Wenn i nicht gesetzt ist sortiere nach m
        std::swap(*RAI<Iterator>::get(begin_m), *RAI<Iterator>::get(begin_v));
        for(auto it_i = begin_v + 1; it_i != fin_v; it_i++){
            Iterator it_j;
            auto temp = RAI<Iterator>::star(begin_m + (it_i - begin_v));
            for (it_j = begin_m + (it_i - begin_v); it_j != begin_m; it_j--) {
                if (RAI<Iterator>::star(it_j-1) > RAI<Iterator>::star(it_i)) {
                    *RAI<Iterator>::get(it_j) = RAI<Iterator>::star(it_j - 1);
                } else {
                    break;
                }
            }
            *RAI<Iterator>::get(it_j) = RAI<Iterator>::star(it_i);
            *RAI<Iterator>::get(it_i) = temp;
        }
    }
}


template <typename Iterator>
void reinhardt_special_swap(Iterator begin, Iterator second_begin, Iterator third_begin, Iterator fourth_begin, Iterator end,
                       Iterator extra_begin, Iterator extra_end){
    Iterator act_first = begin;
    Iterator act_second = second_begin;

    //merge die ersten size/4 Elemente in den Extravektor
    Iterator act_in = begin;
    Iterator act_extra;
    for(act_extra = extra_begin; act_extra != extra_end - 1; act_extra ++){
        if (RAI<Iterator>::star(act_first) > RAI<Iterator>::star(act_second)) {
            std::swap(*RAI<Iterator>::get(act_extra), *RAI<Iterator>::get(act_second));
            act_second++;
        } else {
            std::swap(*RAI<Iterator>::get(act_extra), *RAI<Iterator>::get(act_first));
            act_first++;
        }
    }

    //merge noch genau ein Element in den Extravektor
    if(act_first == second_begin){
        //Falls erste Viertelliste schon leer
        std::swap(*RAI<Iterator>::get(act_extra), *RAI<Iterator>::get(act_second));
        act_second ++;

        while(act_second != third_begin){
            std::swap(*RAI<Iterator>::get(act_in), *RAI<Iterator>::get(act_second));
            act_second ++;
            act_in ++;
        }
    }
    else if(act_second == third_begin){
        //Falls zweite Viertelliste schon leer
        std::swap(*RAI<Iterator>::get(act_extra), *RAI<Iterator>::get(act_first));
        act_first ++;

        while(act_first != second_begin){
            std::swap(*RAI<Iterator>::get(act_in), *RAI<Iterator>::get(act_first));
            act_first ++;
            act_in ++;
        }
    }
    else{
        //Falls beide Listen noch nicht leer
        if (RAI<Iterator>::star(act_first) > RAI<Iterator>::star(act_second)) {
            std::swap(*RAI<Iterator>::get(act_extra), *RAI<Iterator>::get(act_second));
            act_second++;
        } else {
            std::swap(*RAI<Iterator>::get(act_extra), *RAI<Iterator>::get(act_first));
            act_first++;
        }

        merge_reinhardt_swap(act_first, second_begin, act_second, third_begin, act_in);

    }

    Iterator erster_merge_end = begin + ((third_begin - begin) - (extra_end - extra_begin));

    //merge die beiden hinteren Viertellisten zur hinteren Halbliste
    merge_reinhardt_swap(third_begin, fourth_begin, fourth_begin, end, erster_merge_end);

    Iterator zweiter_merge_end = end - (extra_end - extra_begin);
    Iterator now_one = erster_merge_end - 1;
    Iterator now_one_later = extra_end - 1;
    Iterator now_two = zweiter_merge_end - 1;
    Iterator to = end - 1;
    //merge die beiden Teillisten nach rechts, bis nicht mehr möglich
    //in dieser While-Schleife, bis ExtraArray erreicht
    while(now_two != erster_merge_end - 1 && now_one != begin - 1){

        if (RAI<Iterator>::star(now_one) > RAI<Iterator>::star(now_two)) {
            std::swap(*RAI<Iterator>::get(to), *RAI<Iterator>::get(now_one));
            now_one--;
        } else {
            std::swap(*RAI<Iterator>::get(to), *RAI<Iterator>::get(now_two));
            now_two --;
        }
        to --;
    }
    if(now_two == erster_merge_end - 1){
        while(now_one != begin - 1){
            std::swap(*RAI<Iterator>::get(to), *RAI<Iterator>::get(now_one));
            to --;
            now_one --;
        }
    }
    while(to != now_two && now_two != erster_merge_end - 1){

        if (RAI<Iterator>::star(now_one_later) > RAI<Iterator>::star(now_two)) {
            std::swap(*RAI<Iterator>::get(to), *RAI<Iterator>::get(now_one_later));
            now_one_later--;
        } else {
            std::swap(*RAI<Iterator>::get(to), *RAI<Iterator>::get(now_two));
            now_two --;
        }
        to --;
    }

    if(now_two == erster_merge_end - 1){
        //zurückkopieren der ersten Liste
        while(now_one_later != extra_begin - 1){
            std::swap(*RAI<Iterator>::get(to), *RAI<Iterator>::get(now_one_later));
            to --;
            now_one_later --;
        }
    }
    else{
        //merge nun von der anderen Seite (siehe Paper Fig. 2)
        merge_reinhardt_swap(extra_begin, now_one_later + 1, erster_merge_end, now_two + 1, begin);
    }

}

template <typename Iterator>
void merge_reinhardt_swap(Iterator start_one, Iterator end_one, Iterator start_two, Iterator end_two, Iterator start_merge){
    while (start_one != end_one && start_two != end_two) {
        if (RAI<Iterator>::star(start_one) > RAI<Iterator>::star(start_two)) {
            std::swap(*RAI<Iterator>::get(start_merge), *RAI<Iterator>::get(start_two));
            start_two++;
        } else {
            std::swap(*RAI<Iterator>::get(start_merge), *RAI<Iterator>::get(start_one));
            start_one++;
        }
        start_merge++;
    }

    if (start_one != end_one) {
        //Merge rest of block1 into vector
        while (start_one != end_one) {
            std::swap(*RAI<Iterator>::get(start_merge), *RAI<Iterator>::get(start_one));
            start_one++;
            start_merge++;
        }
    } else if (start_two != end_two) {
        //Merge rest of block2 into vector
        while (start_two != end_two) {
            std::swap(*RAI<Iterator>::get(start_merge), *RAI<Iterator>::get(start_two));
            start_two++;
            start_merge++;
        }
    }
}
