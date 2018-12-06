//
// Created by Patrick on 27.11.2018.
//
#include <vector>
#include <iostream>

template<typename T>
void mergesort(std::vector<T> &v);

template<typename T>
void recsort(std::vector<T> &v, std::vector<T> &m, int u, int o);

template<typename T>
void merge (std::vector<T> &v, std::vector<T> &m, int u_1, int o_2, int o_1);

// sort function for 3 or less elements
template<typename T>
void small_sort(std::vector<T> &v, std::vector<T> &m, int u, int o, bool i);