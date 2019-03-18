//
// Created by Patrick on 23.12.2018.
//
#pragma once
#include <iterator>
#include <cmath>
#include <algorithm>
#include "bufferMerge.h"

namespace chen {
    template<typename Iterator, typename Compare>
    void mergesort_chen(Iterator s, Iterator e, Compare compare);

    //finds the minimum in range *s to *e-1
    template<typename Iterator, typename Compare>
    Iterator find_minimum(Iterator s, Iterator e, Compare compare) {
        Iterator min = s;
        for (Iterator it = s; it != e; it++) {
            if (compare(*it, *min)) {
                min = it;
            }
        }
        return min;
    }

    template<typename Iterator, typename Compare>
    Iterator
    findNextXBlock(Iterator x_0, Iterator z, Iterator y, int k, int f, Iterator b_1, Iterator b_2, Compare compare) {
        Iterator x; //return Iterator
        typename std::iterator_traits<Iterator>::value_type min_1, min_2;
        int t = ((z - x_0) - f) / k;
        Iterator m = x_0 + (f + (k * t));
        if (!(z < m)) m = m + k;
        Iterator i = m;
        Iterator j;
        bool minNotSet = true; // is false, when  min_1/2 are set. maybe come up with a more elegant solution
        while ((i + k) <= y) {
            if (i != b_1 && i != b_2) {
                if (i < b_1 && b_1 < i + k) j = m - 1; else j = i + (k - 1);
                // check if min1/2 are set. It should work just like infinity in pseudo-code
                if (minNotSet || (!compare(min_1, *i) && !compare(min_2, *j))) {
                    x = i;
                    min_1 = *i;
                    min_2 = *j;
                    minNotSet = false;
                }
            }
            i = i + k;
        }
        return x;
    }


    template<typename Iterator, typename Compare>
    void mergeBandY(Iterator z, Iterator y, Iterator y_n, Compare compare) {
        Iterator j;
        typename std::iterator_traits<Iterator>::value_type t;
        while (z <= y && y < y_n) {
            j = find_minimum(z, y, compare);
            if (!compare(*y, *j)) {
                t = *z;
                *z = *j;
                *j = t;
            } else {
                t = *z;
                *z = *y;
                *y = t;
                y++;
            }
            z++;
        }
        if (z < y) mergesort_chen(z, y_n, compare);
    }


    template<typename Iterator, typename Compare>
    void merge(Iterator x_0, Iterator y_0, Iterator y_n, int k, int recursionDepth, Compare compare) {
        // Initialization. (line 1-4 in pseudo-code)
        int f = (y_0 - x_0) % k;
        Iterator x;
        if (f == 0) x = y_0 - (2 * k); else x = (y_0 - (k + f));
        if (x < x_0) x = x_0; //optional line to make the merge step work with y_0 - x_0 < 2k as mentioned in the paper
        typename std::iterator_traits<Iterator>::value_type t = *x;
        *x = *x_0;
        Iterator z = x_0, y = y_0, b_1 = x + 1, b_2 = y_0 - k;
        // line 5
        while (y - z > 2 * k) {
            // line 6 -14
            if (!compare(*y, *x) || y_n == y) {
                *z = *x;
                *x = *b_1;
                x++;
                if ((x - x_0) % k == f) {
                    if (z < x - k) b_2 = x - k;
                    x = findNextXBlock(x_0, z, y, k, f, b_1, b_2, compare);
                }
            } else {
                *z = *y;
                *y = *b_1;
                y++;
                if ((y - y_0) % k == 0) b_2 = y - k;
            }
            // line 15
            z++;
            *b_1 = *z;
            if (z == x) x = b_1;
            if (z == b_2) b_2 = y_n; // Use end-Iterator to replace "-1"
            b_1++;
            if ((b_1 - x_0) % k == f) {
                if (b_2 == y_n) b_1 = b_1 - k; else b_1 = b_2;
            }
        }
        //copy temp back, merge B and Y
        *z = t;
        if (recursionDepth > 1) mergeBandY(z, y, y_n, compare);
        else {
            mergesort_chen(z, y, compare);
            merge(z, y, y_n, static_cast<int>(std::sqrt(k)), recursionDepth + 1, compare);
        }
    }


    template<typename Iterator, typename Compare>
    void mergesort_chen(Iterator s, Iterator e, Compare compare) {
        int size = e - s;
        int k = static_cast<int>(std::sqrt(size));
        int pivot = (size - 1) / 2;
        if (size > 50) {
            bufferMerge::mergesort(s, s + pivot, s + pivot, compare);
            mergesort_chen(s + pivot, e, compare);
            merge(s, s + pivot, e, k, 0, compare);
        } else {
            bufferMerge::small_insertion_sort(s, e, e, compare);
        }
    }
}