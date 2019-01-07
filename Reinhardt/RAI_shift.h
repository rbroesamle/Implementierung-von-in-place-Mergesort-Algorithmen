//
// Created by jonas on 06.01.2019.
//

template<typename Iterator>
class RAI {

    static Iterator begin;
    static Iterator fin;
    static unsigned int shift;
    static unsigned int size;

public:
    static void initialize(Iterator begin_i, Iterator fin_i, unsigned int shift_i){
        begin = begin_i;
        fin = fin_i;
        shift = shift_i;
        size = fin_i - begin_i;
    }

    /*
     * rufe diese Funktion immer auf, wenn der Wert des Iterators benötigt wird (Stern auf der rechten Seite)
     * D.h. insbesondere statt x = *i nun: x = star(i)
     */
    static auto star(Iterator i){
        return shift < fin - i ? *(i + shift) : *(i - (size - shift));
    }

    /*
     * rufe diese Funktion immer auf, wenn Stern auf der linken Seite auftaucht
     * D.h. insbesondere statt *i = x nun: *get(i) = x
     */
    static Iterator get(Iterator i){
        return shift < fin - i ? (i + shift) : (i - (size - shift));
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
