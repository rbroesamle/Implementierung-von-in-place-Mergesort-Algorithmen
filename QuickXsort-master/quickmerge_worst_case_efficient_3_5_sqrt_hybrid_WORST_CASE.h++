#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <random>
#include <ctime>
#include <cmath>
#include <assert.h>




#ifndef WORST_CASE_SIMULATION
#define WORST_CASE_SIMULATION
bool worst_case_simulation = false;
#endif // WORST_CASE_SIMULATION

#ifndef SQRT_HYBRID
#define SQRT_HYBRID
#endif // SQRT_HYBRID


#include "insertionsort.h"
#include "median_of_medians.h"
#include "partition_stl.h"
#include "smallsort.h"



#include "quickmerge_worst_case.h"

namespace quickmerge_worst_case_efficient_3_5_sqrt_hybrid_WORST_CASE {
    template<typename iter, typename Compare>
    void sort(iter begin, iter end, Compare less) {
        worst_case_simulation = true;
        quickmerge::sort_worst_case_efficient_3_5(begin, end, less);
        worst_case_simulation = false;
    }
    template<typename T>
    void sort(std::vector<T> &v) {
        typename std::vector<T>::iterator begin = v.begin();
        typename std::vector<T>::iterator end = v.end();
        worst_case_simulation = true;
        //   quicksort::qsort_blocked(begin,end);
        quickmerge::sort_worst_case_efficient_3_5(begin, end, std::less<T>());
        worst_case_simulation = false;
    }
}