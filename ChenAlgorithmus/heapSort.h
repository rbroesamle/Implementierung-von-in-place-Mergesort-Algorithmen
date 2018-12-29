//
// Created by Patrick on 29.12.2018.
//
#include <utility>

// finds the leaf of the path the next element will sink in;
template <typename Iterator>
int leaf_search(Iterator root, int m, int i){
    int j = i;
    while (2 * j < m) {
        if (root[2 * j] < root[(2 * j) - 1]) j *= 2; else j = (2 * j) + 1;
    }
    if (2 * j == m) j = m;
    return j;
}

//find the position along the path given by leaf to which *s will sink in;
template <typename Iterator>
int bottom_up_search(Iterator root, int i, int leaf){
    while(root[leaf-1] < root[i-1]) leaf /= 2;
    return leaf;
}

//let the element at position i sink in to the specified position
template <typename Iterator>
void interchange(Iterator root, int i, int position){
    typename std::iterator_traits<Iterator>::value_type x = root[position-1];
    root[position-1] = root[i-1];
    while(i < position){
        position /= 2;
        std::swap(root[position-1], x);
    }
}

//bottom-up reheap
template <typename Iterator>
void bottom_up_reheap(Iterator root, int m, int i){
    int leaf = leaf_search(root, m, i);
    int position = bottom_up_search(root, i, leaf);
    interchange(root, i, position);
}

//heapsort to use in the mergeBandY step (and maybe for small subarrays)
template <typename Iterator>
void heapSort(Iterator s, Iterator e){
    int n = e - s;
    for (int i = n / 2; i > 0; i--){
        bottom_up_reheap(s, n, i);
    }
    for (int i = n; i > 1; i--){
        std::swap(*s, s[i-1]);
        if (i != 2) bottom_up_reheap(s, i-1, 1);
    }
}
