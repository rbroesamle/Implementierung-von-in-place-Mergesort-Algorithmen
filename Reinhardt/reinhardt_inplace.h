//
// Created by jonas on 22.12.2018.
//
template <typename Iterator>
void sym_merge_gap_left(Iterator start_one, Iterator end_one, Iterator start_two, Iterator end_two, Iterator merge);

template <typename Iterator>
void sym_merge_gap_right(Iterator start_one, Iterator end_one, Iterator start_two, Iterator end_two, Iterator merge);

template <typename Iterator>
void asym_merge_gap_right(Iterator start_one, Iterator end_one, Iterator start_two, Iterator end_two, Iterator merge);

template <typename Iterator>
void asym_merge_gap_left(Iterator start_one, Iterator end_one, Iterator start_two, Iterator end_two, Iterator merge);

template <typename Iterator>
void in_place_mergesort(Iterator begin, Iterator fin);

template <typename Iterator>
void rec_reinhardt_left_gap(Iterator start_gap, Iterator start_list, Iterator end_list);



//für k = 0 (d.h. two enthält nur ein Element) ist diese Funktion nicht optimal/ nicht gedacht!
template<typename Iterator>
int binSearch(Iterator pos_one, Iterator pos_two, int k){

    auto elem_one = *pos_one;
    if(*(pos_two + k) <= elem_one){
        //Ganzer Block der zweiten Liste ist kleiner, dann wird -1 zurückgegeben
        return -1;
    }
    auto elem_two = pos_two;

    do{
        k = k / 2;
        if(*(elem_two + k) <= elem_one){
            //Suche in der rechten Teilhälfte weiter nach Einfügeposition
            elem_two = elem_two + (k + 1);
        }
        //ansonsten wird links weitergesucht
    } while(k > 0);
    //*elem_one muss also bei pos_two + returnwert eingefügt werden (=elem_two)
    return elem_two - pos_two;
}