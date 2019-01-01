//
// Created by jonas on 22.12.2018.
//
#include "reinhardt_inplace.h"
#include<iterator>
#include<math.h>
//#include "RAI_wrapper.h"

//template<typename Iterator>
//RAI_wrapper<Iterator> wrap;

//todo: bei mergesort mit Reinhardt stets beachten: swappen statt nur zuweisen (-> reinhardt.cpp hierfür abändern!)
//todo: dabei stets in-place-Extraspeicher als gap statt neuen Speicherbereich (-> reinhardt.cpp hierfür abändern!)
template <typename Iterator>
void in_place_mergesort(Iterator begin, Iterator fin){
    //wrap<Iterator> = RAI_wrapper<Iterator>(begin, fin - 1);
    //todo: mergesort mit Reinhardt der hinteren 0.8n Elemente mit Gap vordere 0.2n Elemente
    //todo: rec_reinhardt_left_gap aufrufen
}

template <typename Iterator>
void rec_reinhardt_left_gap(Iterator start_gap, Iterator start_list, Iterator end_list){
    unsigned int size = start_list - start_gap;
    //für unsortierte Liste < Konstante dann füge einzeln in die lange bereits sortierte Liste ein (O(n))
    if(size < 4){
        //todo: hier evtl. zuerst binäre Suche statt wie hier "lineares Einfügen", um Vergleiche einzusparen
        for(Iterator now = start_list - 1; now != start_gap - 1; now--){
            Iterator next = now + 1;
            Iterator temp;
            while(next != end_list && *next < *now){
                *temp = *now;
                *now = *next;
                *next = *temp;
                now = next;
                next = now + 1;
            }
        }
    }
    else{
        //todo: mergesort mit Reinhardt der hinteren 2/3 von der unsortierten Liste und verwende die vorderen 1/3 als gap
        //todo: (nun die beiden sortierten Teillisten einmal nach links shiften, um gap nach rechts zu bekommen)
        //todo: hierzu logischen Ringspeicher!! Idee: iterator+x als (iterator+x) - size falls drüber (+/- überladen) um die shifts zu vermeiden
        //todo: anschließend sortierte Listen absteigend mergen (später asymmetrisch, anfangs sym_merge_gap_right verwenden)
        //todo: danach rec_reinhardt_left_gap wieder rekursiv aufrufen
    }
}



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
        temp = *merge;
        if (*act_two < *act_one) {
            *merge = *act_two;
            *act_two = temp;
            act_two++;
        } else {
            *merge = *act_one;
            *act_one = temp;
            act_one++;
        }
        merge++;
    }
    //falls zweite Liste leer
    if (act_two == end_two) {
        while (act_one != end_one) {
            temp = *merge;
            *merge = *act_one;
            *act_one = temp;
            act_one++;
            merge++;
        }
    //falls erste Liste leer
    } else if (act_one == end_one) {
        if(merge != act_two) {
            while (act_two != end_two) {
                temp = *merge;
                *merge = *act_two;
                *act_two = temp;
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
        temp = *merge;
        if (*act_one < *act_two) {
            *merge = *act_two;
            *act_two = temp;
            act_two++;
        } else {
            *merge = *act_one;
            *act_one = temp;
            act_one++;
        }
        merge++;
    }
    //falls zweite Liste leer
    if (act_two == end_two) {
        while (act_one != end_one) {
            temp = *merge;
            *merge = *act_one;
            *act_one = temp;
            act_one++;
            merge++;
        }
    //falls erste Liste leer
    } else if (act_one == end_one) {
        if(merge != act_two) {
            while (act_two != end_two) {
                temp = *merge;
                *merge = *act_two;
                *act_two = temp;
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

template <typename Iterator>
void asym_merge_gap_left(Iterator start_one, Iterator end_one, Iterator start_two, Iterator end_two, Iterator merge){
    int size_short = end_one - start_one;
    int size_long = end_two - start_two;

    int teiler = size_long / size_short;
    //suche nächstliegende Zweierpotenz po <= teiler
    int po = 1;
    while(po * 2 <= teiler){
        po = po * 2;
    }
    // bei gleicher Distanz wird aufgerundet (-> gleicht evtl. Abschneiden bei Berechnung von teiler wieder aus)
    int k;
    int k_down = po;
    int k_up = 2 * po;
    teiler - k_down < k_up - teiler ? k = k_down : k = k_up;

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
                temp = *merge;
               *merge = *(act_two + i);
               *(act_two + i) = temp;
               merge ++;
            }
            act_two = act_two + (k + 1);
        }
        else{
            // act_one an passender Stelle "einfügen"
            for(int i = 0; i < pos; i++){
                temp = *merge;
                *merge = *(act_two + i);
                *(act_two + i) = temp;
                merge ++;
            }
            temp = *merge;
            *merge = *act_one;
            *act_one = temp;
            merge ++;
            act_one ++;
            act_two = act_two + pos;
        }
    }
    //falls erste Liste leer
    if (act_one == end_one) {
        if(merge != act_two) {
            while (act_two != end_two) {
                temp = *merge;
                *merge = *act_two;
                *act_two = temp;
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
        asym_merge_gap_right(new_start_one, new_end_one, new_start_two, new_end_two, new_merge);
    }
}

template <typename Iterator>
void asym_merge_gap_right(Iterator start_one, Iterator end_one, Iterator start_two, Iterator end_two, Iterator merge){
    int size_short = end_one - start_one;
    int size_long = end_two - start_two;

    int teiler = size_long / size_short;
    //suche nächstliegende Zweierpotenz po <= teiler
    int po = 1;
    while(po * 2 <= teiler){
        po = po * 2;
    }
    // bei gleicher Distanz wird aufgerundet (-> gleicht evtl. Abschneiden bei Berechnung von teiler wieder aus)
    int k;
    int k_down = po;
    int k_up = 2 * po;
    teiler - k_down < k_up - teiler ? k = k_down : k = k_up;

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
        int pos = binSearch(act_one, act_two, k);
        if(pos == -1){
            // ganzer Block von two kopieren
            for(int i = 0; i <= k; i ++){
                temp = *merge;
                *merge = *(act_two + i);
                *(act_two + i) = temp;
                merge ++;
            }
            act_two = act_two + (k + 1);
        }
        else{
            // act_one an passender Stelle "einfügen"
            for(int i = 0; i < pos; i++){
                temp = *merge;
                *merge = *(act_two + i);
                *(act_two + i) = temp;
                merge ++;
            }
            temp = *merge;
            *merge = *act_one;
            *act_one = temp;
            merge ++;
            act_one ++;
            act_two = act_two + pos;
        }
    }
    //falls erste Liste leer
    if (act_one == end_one) {
        if(merge != act_two) {
            while (act_two != end_two) {
                temp = *merge;
                *merge = *act_two;
                *act_two = temp;
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
        asym_merge_gap_left(new_start_one, new_end_one, new_start_two, new_end_two, new_merge);
    }
}