//
// Created by Patrick on 23.12.2018.
//
#include <iterator>
#include <cmath>
#include <algorithm>


//finds the minimum in range *s to *e-1
template<typename Iterator>
Iterator find_minimum(Iterator s, Iterator e) {
    Iterator min = s;
    for (Iterator it = s; it != e; it++){
        if (*it < *min) {
            min = it;
        }
    }
    return min;
}

template<typename Iterator>
Iterator findNextXBlock(Iterator x_0, Iterator z, Iterator y, int k, int f, Iterator b_1, Iterator b_2) {
    Iterator x; //return Iterator
    typename std::iterator_traits<Iterator>::value_type min_1, min_2;
    int t = ((z - x_0) - f)/k;
    Iterator m = x_0 + (f + (k * t));
    if (!(z<m)) m = m + k;
    Iterator i = m; Iterator j;
    bool minNotSet = true; // is false, when  min_1/2 are set. maybe come up with a more elegant solution
    while ((i + k) <= y) {
        if (i != b_1 && i != b_2) {
            if (i < b_1 && b_1 < i+k) j = m - 1; else j = i + (k - 1);
            // check if min1/2 are set. It should work just like infinity in pseudo-code
            if (minNotSet || (!(min_1 < *i) && !(min_2 < *j))) {
                x = i; min_1 = *i; min_2 = *j;
                minNotSet = false;
            }
        }
        i = i + k;
    }
    return x;
}


//TODO: Implement the improvements suggested in the paper
template<typename Iterator>
void mergeBandY(Iterator z, Iterator y, Iterator y_n) {
    Iterator j; typename std::iterator_traits<Iterator>::value_type t;
    while (z <= y && y < y_n) {
        j = find_minimum(z, y);
        if (!(*y < *j)) {
            t = *z; *z = *j; *j = t;
        } else {
            t = *z; *z = *y; *y = t;
            y++;
        }
        z++;
    }
    //TODO: implement heapsort instead
    if (z < y) std::sort(z, y_n);
}


template<typename Iterator>
void merge(Iterator x_0, Iterator y_0, Iterator y_n, int k) {
    // Initialization. (line 1-4 in pseudo-code)
    int f = (y_0 - x_0) % k;
    Iterator x;
    if (f == 0) x = y_0 - (2 * k); else x = (y_0 - (k+f));
    if (x < x_0) x = x_0; //optional line to make the merge step work with y_0 - x_0 < 2k as mentioned in the paper
    typename std::iterator_traits<Iterator>::value_type t = *x; *x = *x_0;
    Iterator z = x_0, y = y_0, b_1 = x + 1, b_2 = y_0 - k;
    // line 5
    while (y - z > 2 * k) {
        // line 6 -14
        if (!(*y < *x) || y_n == y) {
            *z = *x; *x = *b_1; x++;
            if ((x - x_0) % k == f) {
                if (z < x - k) b_2 = x-k;
                x = findNextXBlock(x_0, z, y, k, f, b_1, b_2);
            }
        } else {
            *z = *y; *y = *b_1; y++;
            if ((y - y_0) % k == 0) b_2 = y - k;
        }
        // line 15
        z ++; *b_1 = *z;
        if (z == x) x = b_1;
        if (z == b_2) b_2 = y_n; // Use end-Iterator to replace "-1"
        b_1++;
        if ((b_1 - x_0) % k == f) {
            if (b_2 == y_n) b_1 = b_1 - k; else b_1 = b_2;
        }
    }
    //copy temp back, merge B and Y
    *z = t;
    mergeBandY(z, y, y_n);
}


template<typename Iterator>
void smallInsertionSort(Iterator s, Iterator e) {
    typename std::iterator_traits<Iterator>::value_type temp;
    for(auto it_i = s + 1; it_i != e; it_i++) {
        temp = *it_i;
        Iterator it_j;
        for (it_j = it_i; it_j != s; it_j--) {
            if (*(it_j - 1) > temp) {
                *it_j = *(it_j - 1);
            } else {
                break;
            }
        }
        *it_j = temp;
    }
}


template<typename Iterator>
void mergesort_chen(Iterator s, Iterator e) {
    // FIXME: k stattdesse als Parameter übergeben
    int k = 100;
    int size = e - s;
    int pivot = (size - 1) / 2 + 1;
    // size > 50
    if(size > 50){
        mergesort_chen(s, s + pivot);
        mergesort_chen(s + pivot, e);
        merge(s, s + pivot, e, k);
    } else {
        smallInsertionSort(s, e);
    }
}