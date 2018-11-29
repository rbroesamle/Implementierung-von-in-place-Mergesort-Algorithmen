//
// Created by Patrick on 27.11.2018.
//

#include "vectormerge.h"

template<typename T>
void mergesort(std::vector<T> &v) {
    unsigned int size = v.size();
    std::vector<T> merge_vector = v;
    recsort(merge_vector, v, 0, v.size() - 1);
}

template<typename T>
void recsort(std::vector<T> &v, std::vector<T> &m, int u, int o){
    int pivot = (o-u)/2;
    if (u != o) {
        recsort(m, v, u, u + pivot);
        recsort(m, v, u + pivot + 1, o);
        merge(v, m, u, o, u + pivot);
    }
}

template<typename T>
void merge (std::vector<T> &v, std::vector<T> &m, int u_1, int o_2, int o_1) {
    int u_2 = o_1 + 1;
    int counter = u_1;
    while (u_1 <= o_1 && u_2 <= o_2) {
        if (v[u_1] <= v[u_2]) {
            m[counter] = v[u_1];
            counter++;
            u_1++;
        } else {
            m[counter] = v[u_2];
            counter++;
            u_2++;
        }
    }
    while (u_1 <= o_1) {
        m[counter] = v[u_1];
        u_1++;
        counter++;
    }
    while (u_2 <= o_2) {
        m[counter] = v[u_2];
        u_2++;
        counter++;
    }
}