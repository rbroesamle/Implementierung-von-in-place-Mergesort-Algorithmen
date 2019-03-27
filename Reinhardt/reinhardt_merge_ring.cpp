//
// Created by jonas on 22.12.2018.
//
#include "iterator_ring.h"
#include "reinhardt_merge_ring.h"
#include<iterator>
#include<math.h>
/*
 * diese Prozedur mergt zwei Listen, two ist dabei die längere Liste
 * notwendig 1: gap <-> lange Liste = two <-> kurze Liste = one
 * notwendig 2: Länge(gap) >= Hälfte der Länge(kürzeren Liste)
 * Sie swapped dabei immer Elemente der "gap" mit Elementen der zu mergenden Listen
 */

template <typename Iterator>
void sym_merge_gap_left(Iterator start_one, Iterator end_one, Iterator start_two, Iterator end_two, Iterator merge){
    typename std::iterator_traits<Iterator>::value_type temp;
    Iterator act_one = start_one;
    Iterator act_two = start_two;

    //while beide Listen nichtleer und keine Kollision
    while (act_one != end_one && act_two != end_two && merge != act_two) {
        temp = RAI<Iterator>::star(merge);
        if (*RAI<Iterator>::get(act_two) < RAI<Iterator>::star(act_one)) {
            *RAI<Iterator>::get(merge) = RAI<Iterator>::star(act_two);
            *RAI<Iterator>::get(act_two) = temp;
            act_two++;
        } else {
            *RAI<Iterator>::get(merge) = RAI<Iterator>::star(act_one);
            *RAI<Iterator>::get(act_one) = temp;
            act_one++;
        }
        merge++;
    }
    //falls zweite Liste leer
    if (act_two == end_two) {
        while (act_one != end_one) {
            temp = RAI<Iterator>::star(merge);
            *RAI<Iterator>::get(merge) = RAI<Iterator>::star(act_one);
            *RAI<Iterator>::get(act_one) = temp;
            act_one++;
            merge++;
        }
    //falls erste Liste leer
    } else if (act_one == end_one) {
        if(merge != act_two) {
            while (act_two != end_two) {
                temp = RAI<Iterator>::star(merge);
                *RAI<Iterator>::get(merge) = RAI<Iterator>::star(act_two);
                *RAI<Iterator>::get(act_two) = temp;
                act_two++;
                merge++;
            }
        }
    }
    //falls Kollsion
    else{
            //nun im zweiten Durchlauf absteigend mergen
            std::reverse_iterator<Iterator> new_start_one(end_one);
            std::reverse_iterator<Iterator> new_end_one(act_one);
            std::reverse_iterator<Iterator> new_start_two(end_two);
            std::reverse_iterator<Iterator> new_end_two(act_two);
            std::reverse_iterator<Iterator> new_merge(end_two + (end_one - act_one));
        sym_merge_gap_right(new_start_one, new_end_one, new_start_two, new_end_two, new_merge);
    }
}

/*
 * diese Prozedur mergt zwei Listen, two ist dabei die längere Liste
 * notwendig 1: kurze Liste = one <-> lange Liste = two <-> gap
 * notwendig 2: Länge(gap) >= Hälfte der Länge(kürzeren Liste)
 * Es werden ReverseIteratoren von der Prozedur erwartet: std::reverse_iterator<Iter>(i) !!!
 * bei Reverse-Iteratoren den "Versatz" zu normalen Iteratoren bei der Initialisierung beachten
 */

template <typename Iterator>
void sym_merge_gap_right(Iterator start_one, Iterator end_one, Iterator start_two, Iterator end_two, Iterator merge){
    typename std::iterator_traits<Iterator>::value_type temp;
    Iterator act_one = start_one;
    Iterator act_two = start_two;

    //while beide Listen nichtleer und keine Kollision
    while (act_one != end_one && act_two != end_two && merge != act_two) {
        temp = RAI<Iterator>::star(merge);
        if (RAI<Iterator>::star(act_one) < RAI<Iterator>::star(act_two)) {
            *RAI<Iterator>::get(merge) = RAI<Iterator>::star(act_two);
            *RAI<Iterator>::get(act_two) = temp;
            act_two++;
        } else {
            *RAI<Iterator>::get(merge) = RAI<Iterator>::star(act_one);
            *RAI<Iterator>::get(act_one) = temp;
            act_one++;
        }
        merge++;
    }
    //falls zweite Liste leer
    if (act_two == end_two) {
        while (act_one != end_one) {
            temp = RAI<Iterator>::star(merge);
            *RAI<Iterator>::get(merge) = RAI<Iterator>::star(act_one);
            *RAI<Iterator>::get(act_one) = temp;
            act_one++;
            merge++;
        }
    //falls erste Liste leer
    } else if (act_one == end_one) {
        if(merge != act_two) {
            while (act_two != end_two) {
                temp = RAI<Iterator>::star(merge);
                *RAI<Iterator>::get(merge) = RAI<Iterator>::star(act_two);
                *RAI<Iterator>::get(act_two) = temp;
                act_two++;
                merge++;
            }
        }
    }
        //falls Kollsion
    else{
        //nun im zweiten Durchlauf aufsteigend mergen
        auto new_start_one = end_one.base();
        auto new_end_one = act_one.base();
        auto new_start_two = end_two.base();
        auto new_end_two = act_two.base();
        auto new_merge = end_two.base() - (end_one - act_one);
        sym_merge_gap_left(new_start_one, new_end_one, new_start_two, new_end_two, new_merge);
    }
}

/*
 * Zur Nutzung siehe sym_merge_gap_left
 * Diese Prozedur ist Vergleichs-effizienter bei Listen ungleicher Länge
 * k_inp ist das 2**k aus dem Paper (siehe 3.1)
 * k_inp <= 0: der Faktor wird von der Prozedur bestimmt, ansonsten wird der übergebene Wert übernommen
 * k_inp = 1 entspricht symmetrischem mergen
 */
template <typename Iterator>
void asym_merge_gap_left(Iterator start_one, Iterator end_one, Iterator start_two, Iterator end_two, Iterator merge, int k_inp){
    int k;
    if(k_inp <= 0){
        int size_short = end_one - start_one;
        int size_long = end_two - start_two;

        int teiler = size_long / size_short;
        //suche nächstliegende Zweierpotenz po <= teiler
        int po = 1;
        while(po * 2 <= teiler){
            po = po * 2;
        }
        // bei gleicher Distanz wird aufgerundet (-> gleicht evtl. Abschneiden bei Berechnung von teiler wieder aus)
        int k_down = po;
        int k_up = 2 * po;
        teiler - k_down < k_up - teiler ? k = k_down : k = k_up;
    } else{
        k = k_inp;
    }

    if(k == 1){
        sym_merge_gap_left(start_one, end_one, start_two, end_two, merge);
        return;
    }
    //k dekrementieren sodass act_iter + k stets auf k'tes Element nach act_iter zeigt
    k --;
    Iterator act_one = start_one;
    Iterator act_two = start_two;
    typename std::iterator_traits<Iterator>::value_type temp;

    //while kurze Liste nichtleer und keine Kollsion
    //Anmerkung: ein Platz für merge pro Schleifendurchlauf reicht stets aus
    while (act_one != end_one && merge != act_two) {
        if(act_two + k >= end_two){
            //k ist zu groß (zeigt über Ende der zweiten Liste)
            if(end_two - act_two < end_one - act_one || end_two - act_two < 20){
                //merge symmetrisch falls Listen nur noch ca gleich lang
                //oder wenn es sich asymmetrisch nicht mehr lohnt weil lange Liste nun kurz
                sym_merge_gap_left(act_one, end_one, act_two, end_two, merge);
                return;
            }
            else{
                //ansonsten falls sich asymmetrisch noch lohnt, dann verringere k
                while(act_two + k >= end_two){
                    k = k / 2;
                }
            }
        }
        int pos = binSearch(act_one, act_two, k);
        if(pos == -1){
            // ganzer Block von two kopieren
            for(int i = 0; i <= k; i ++){
                temp = RAI<Iterator>::star(merge);
               *RAI<Iterator>::get(merge) = RAI<Iterator>::star(act_two + i);
               *RAI<Iterator>::get(act_two + i) = temp;
               merge ++;
            }
            act_two = act_two + (k + 1);
        }
        else{
            // act_one an passender Stelle "einfügen"
            for(int i = 0; i < pos; i++){
                temp = RAI<Iterator>::star(merge);
                *RAI<Iterator>::get(merge) = RAI<Iterator>::star(act_two + i);
                *RAI<Iterator>::get(act_two + i) = temp;
                merge ++;
            }
            temp = RAI<Iterator>::star(merge);
            *RAI<Iterator>::get(merge) = RAI<Iterator>::star(act_one);
            *RAI<Iterator>::get(act_one) = temp;
            merge ++;
            act_one ++;
            act_two = act_two + pos;
        }
    }
    //falls erste Liste leer
    if (act_one == end_one) {
        if(merge != act_two) {
            while (act_two != end_two) {
                temp = RAI<Iterator>::star(merge);
                *RAI<Iterator>::get(merge) = RAI<Iterator>::star(act_two);
                *RAI<Iterator>::get(act_two) = temp;
                act_two++;
                merge++;
            }
        }
    }
    //falls Kollsion
    else{
        //nun im zweiten Durchlauf absteigend mergen
        std::reverse_iterator<Iterator> new_start_one(end_one);
        std::reverse_iterator<Iterator> new_end_one(act_one);
        std::reverse_iterator<Iterator> new_start_two(end_two);
        std::reverse_iterator<Iterator> new_end_two(act_two);
        std::reverse_iterator<Iterator> new_merge(end_two + (end_one - act_one));
        asym_merge_gap_right(new_start_one, new_end_one, new_start_two, new_end_two, new_merge, k+1);
    }
}

/*
 * Zur Nutzung siehe sym_merge_gap_right
 * Diese Prozedur ist Vergleichs-effizienter bei Listen ungleicher Länge
 * k_inp ist das 2**k aus dem Paper (siehe 3.1)
 * k_inp <= 0: der Faktor wird von der Prozedur bestimmt, ansonsten wird der übergebene Wert übernommen
 * k_inp = 1 entspricht symmetrischem mergen
 */
template <typename Iterator>
void asym_merge_gap_right(Iterator start_one, Iterator end_one, Iterator start_two, Iterator end_two, Iterator merge, int k_inp){
    int k;
    if(k_inp <= 0){
        int size_short = end_one - start_one;
        int size_long = end_two - start_two;

        int teiler = size_long / size_short;
        //suche nächstliegende Zweierpotenz po <= teiler
        int po = 1;
        while(po * 2 <= teiler){
            po = po * 2;
        }
        // bei gleicher Distanz wird aufgerundet (-> gleicht evtl. Abschneiden bei Berechnung von teiler wieder aus)
        int k_down = po;
        int k_up = 2 * po;
        teiler - k_down < k_up - teiler ? k = k_down : k = k_up;
    } else{
        k = k_inp;
    }

    if(k == 1){
        sym_merge_gap_right(start_one, end_one, start_two, end_two, merge);
        return;
    }
    //k dekrementieren sodass act_iter + k stets auf k'tes Element nach act_iter zeigt
    k --;
    Iterator act_one = start_one;
    Iterator act_two = start_two;
    typename std::iterator_traits<Iterator>::value_type temp;

    //while kurze Liste nichtleer und keine Kollsion
    //Anmerkung: ein Platz für merge pro Schleifendurchlauf reicht stets aus
    while (act_one != end_one && merge != act_two) {
        if(act_two + k >= end_two){
            //k ist zu groß (zeigt über Ende der zweiten Liste)
            if(end_two - act_two < end_one - act_one || end_two - act_two < 20){
                //merge symmetrisch falls Listen nur noch ca gleich lang
                //oder wenn es sich asymmetrisch nicht mehr lohnt weil lange Liste nun kurz
                sym_merge_gap_right(act_one, end_one, act_two, end_two, merge);
                return;
            }
            else{
                //ansonsten falls sich asymmetrisch noch lohnt, dann verringere k
                while(act_two + k >= end_two){
                    k = k / 2;
                }
            }
        }
        int pos = binSearch_inverted(act_one, act_two, k);
        if(pos == -1){
            // ganzer Block von two kopieren
            for(int i = 0; i <= k; i ++){
                temp = RAI<Iterator>::star(merge);
                *RAI<Iterator>::get(merge) = RAI<Iterator>::star(act_two + i);
                *RAI<Iterator>::get(act_two + i) = temp;
                merge ++;
            }
            act_two = act_two + (k + 1);
        }
        else{
            // act_one an passender Stelle "einfügen"
            for(int i = 0; i < pos; i++){
                temp = RAI<Iterator>::star(merge);
                *RAI<Iterator>::get(merge) = RAI<Iterator>::star(act_two + i);
                *RAI<Iterator>::get(act_two + i) = temp;
                merge ++;
            }
            temp = RAI<Iterator>::star(merge);
            *RAI<Iterator>::get(merge) = RAI<Iterator>::star(act_one);
            *RAI<Iterator>::get(act_one) = temp;
            merge ++;
            act_one ++;
            act_two = act_two + pos;
        }
    }
    //falls erste Liste leer
    if (act_one == end_one) {
        if(merge != act_two) {
            while (act_two != end_two) {
                temp = RAI<Iterator>::star(merge);
                *RAI<Iterator>::get(merge) = RAI<Iterator>::star(act_two);
                *RAI<Iterator>::get(act_two) = temp;
                act_two++;
                merge++;
            }
        }
    }
        //falls Kollsion
    else{
        //nun im zweiten Durchlauf aufsteigend mergen
        auto new_start_one = end_one.base();
        auto new_end_one = act_one.base();
        auto new_start_two = end_two.base();
        auto new_end_two = act_two.base();
        auto new_merge = end_two.base() - (end_one - act_one);
        asym_merge_gap_left(new_start_one, new_end_one, new_start_two, new_end_two, new_merge, k+1);
    }
}