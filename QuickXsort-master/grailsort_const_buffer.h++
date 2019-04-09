#pragma once
/********* Grail sorting *********************************/
/*                                                       */
/* (c) 2013 by Andrey Astrelin                           */
/*                                                       */
/*                                                       */
/* Stable sorting that works in O(N*log(N)) worst time   */
/* and uses O(1) extra memory                            */
/*                                                       */
/* Define SORT_TYPE and SORT_CMP                         */
/* and then call GrailSort() function                    */
/*                                                       */
/* For sorting with fixed external buffer (512 items)    */
/* use GrailSortWithBuffer()                             */
/*                                                       */
/* For sorting with dynamic external buffer (O(sqrt(N)) items) */
/* use GrailSortWithDynBuffer()                          */
/*                                                       */
/* Also classic in-place merge sort is implemented       */
/* under the name of RecStableSort()                     */
/*                                                       */
/*********************************************************/

#include "grailsort.h++"

namespace grailsort_const_buffer {

 

    template<typename iter, typename Compare>
    void sort(iter begin, iter end, Compare less) {
        using t = typename std::iterator_traits<iter>::value_type;
        typedef typename std::iterator_traits<iter>::difference_type index;
        index n = end - begin;
        grailsort::inplace_merger<t>::GrailSortWithBuffer(&(*begin), n);
    }

    template<typename T>
    void sort(std::vector<T> &v) {
        typename std::vector<T>::iterator begin = v.begin();
        typename std::vector<T>::iterator end = v.end();
        grailsort_const_buffer::sort(begin, end, std::less<T>());

    }

}
