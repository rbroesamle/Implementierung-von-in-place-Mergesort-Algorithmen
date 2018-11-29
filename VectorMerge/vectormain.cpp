//
// Created by Patrick on 29.11.2018.
//

#include "vectormerge.cpp"
#include <iostream>
#include "wrapper.h"

int main (){
    std::vector<BasetypeWrapper<int>> v = {6, 3, 5445, 344, 45, 272, 1973, 3297439, 838, 5769, 98, 1, 85830};
    BasetypeWrapper<int>::reset_m();
    mergesort(v);
    for (std::vector<BasetypeWrapper<int>>::iterator it = v.begin() ; it != v.end(); ++it) {
        std::cout << ' ' << it->get_value();
    }
    //std::vector<BasetypeWrapper<int>> merge_vector = std::vector<BasetypeWrapper<int>>(v);
    std::cout << std::endl << BasetypeWrapper<int>::get_c() << std::endl;
    std::cout << std::endl << BasetypeWrapper<int>::get_m() << std::endl;
    return 0;
}