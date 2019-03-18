//
// Created by jonas on 22.12.2018.
//
template <typename Iterator, typename Compare>
void sym_merge_gap_left(Iterator start_one, Iterator end_one, Iterator start_two, Iterator end_two, Iterator merge, Compare comp);

template <typename Iterator, typename Compare>
void sym_merge_gap_right(Iterator start_one, Iterator end_one, Iterator start_two, Iterator end_two, Iterator merge, Compare comp);

template <typename Iterator, typename Compare>
void asym_merge_gap_right(Iterator start_one, Iterator end_one, Iterator start_two, Iterator end_two, Iterator merge, int k_inp, Compare comp);

template <typename Iterator, typename Compare>
void asym_merge_gap_left(Iterator start_one, Iterator end_one, Iterator start_two, Iterator end_two, Iterator merge, int k_inp, Compare comp);

//die Funktion macht eine binäre Suche, um die Einfügeposition von one zu finden (Listen aufsteigender Reihenfolge)
//für k = 0 (d.h. two enthält nur ein Element) ist diese Funktion nicht optimal/ nicht gedacht!
template <typename Iterator, typename Compare>
int binSearch(Iterator pos_one, Iterator pos_two, int k, Compare comp){

    auto elem_one = *pos_one;
    if(!comp(elem_one, *(pos_two + k))){
        //Ganzer Block der zweiten Liste ist kleiner, dann wird -1 zurückgegeben
        return -1;
    }
    auto elem_two = pos_two;

    do{
        k = k / 2;
        if(!comp(elem_one, *(elem_two + k))){
            //Suche in der rechten Teilhälfte weiter nach Einfügeposition
            elem_two = elem_two + (k + 1);
        }
        //ansonsten wird links weitergesucht
    } while(k > 0);
    //*elem_one muss also bei pos_two + returnwert eingefügt werden (=elem_two)
    return elem_two - pos_two;
}
//die Funktion macht eine binäre Suche, um die Einfügeposition von one zu finden (Listen absteigend mit Revese-Iteratoren)
//für k = 0 (d.h. two enthält nur ein Element) ist diese Funktion nicht optimal/ nicht gedacht!
template <typename Iterator, typename Compare>
int binSearch_inverted(Iterator pos_one, Iterator pos_two, int k, Compare comp){

    auto elem_one = *pos_one;
    if(!comp(*(pos_two + k), elem_one)){
        //Ganzer Block der zweiten Liste ist kleiner, dann wird -1 zurückgegeben
        return -1;
    }
    auto elem_two = pos_two;

    do{
        k = k / 2;
        if(!comp(*(elem_two + k), elem_one)){
            //Suche in der linken Teilhälfte weiter nach Einfügeposition
            elem_two = elem_two + (k + 1);
        }
        //ansonsten wird rechts weitergesucht
    } while(k > 0);
    //*elem_one muss also bei pos_two + returnwert eingefügt werden (=elem_two)
    return elem_two - pos_two;
}
