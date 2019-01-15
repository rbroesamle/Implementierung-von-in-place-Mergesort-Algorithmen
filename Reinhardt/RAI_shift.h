//
// Created by jonas on 06.01.2019.
//
#pragma once
template<typename Iterator>
class RAI {
    static Iterator begin;
    static Iterator fin;
public:
    static unsigned int shift;
    static unsigned int size;

    static Iterator fin_minus_shift;
    static void set_shift(unsigned int shift_i){
        shift = shift_i;
        fin_minus_shift = fin - shift;
    }

    static void initialize(Iterator begin_i, Iterator fin_i, unsigned int shift_i){
        begin = begin_i;
        fin = fin_i;
        shift = shift_i;
        size = fin_i - begin_i;
        fin_minus_shift = fin - shift;
    }

    /*
     * rufe diese Funktion immer auf, wenn der Wert des Iterators benötigt wird (Stern auf der rechten Seite)
     * D.h. insbesondere statt x = *i nun: x = star(i)
     */
    inline static auto star(Iterator i){
        //return shift < fin - i ? *(i + shift) : *(i - (size - shift));
        return i < fin_minus_shift ? *(i + shift) : *(i - (size - shift));
    }

    /*
     * rufe diese Funktion immer auf, wenn Stern auf der linken Seite auftaucht
     * D.h. insbesondere statt *i = x nun: *get(i) = x
     */
    inline static Iterator get(Iterator i){
        //return shift < fin - i ? (i + shift) : (i - (size - shift));
        return i < fin_minus_shift ? (i + shift) : (i - (size - shift));
    }
};

template <typename Iterator>
Iterator RAI<Iterator>::begin;
template <typename Iterator>
Iterator RAI<Iterator>::fin;
template <typename Iterator>
unsigned int RAI<Iterator>::shift;
template <typename Iterator>
unsigned int RAI<Iterator>::size;
template <typename Iterator>
Iterator RAI<Iterator>::fin_minus_shift;
