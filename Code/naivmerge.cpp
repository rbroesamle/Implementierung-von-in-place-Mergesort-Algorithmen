//
// Created by jonas on 02.11.2018.
//
#include<array>
#include<vector>
#include <iostream>

template<class Iterator,class Compare>
int merge(Iterator startfirst, Iterator endfirst, Iterator startsec, Iterator endsec, Iterator startgoal,Compare compare){
    auto ifir = startfirst;
    auto isec = startsec;
    int act = 0;
    while(true){
        if(ifir == endfirst) {
            while (isec != endsec) {
                *(startgoal + act) = *isec;
                isec++;
                act++;
            }
            break;
        }
        if(isec == endsec) {
            while (ifir != endfirst) {
                *(startgoal + act) = *ifir;
                ifir++;
                act++;
            }
            break;
        }
        if(compare(*ifir,*isec)){
            *(startgoal + act) = *ifir;
            ifir ++;
            act ++;
        }
        else{
            *(startgoal + act) = *isec;
            isec ++;
            act ++;
        }
    }
    return 0;
}

//Annahme: Anzahl Elemente ist Zweierpotenz
template<class Iterator, class Compare>
int mergesort(Iterator first, Iterator last, Compare compare){
    std::vector<int> goal(first,last);
    int block = 1;
    while(first + block != last){
        int* erste = first;
        int* zweite = first + block;
        int* ziel = &goal[0];
        while(true){
            merge(erste, zweite, zweite, zweite+block, ziel, compare);
            erste = zweite + block;
            if(erste == last){
                break;
            }
            zweite = erste + block;
            ziel = ziel + 2*block;
        }

        block = block * 2;
        auto g = goal.begin();
        for(auto i= first; i!=last; i++){
            *i = *g;
            g ++;
        }
    }
    return 0;
}

