//
// Created by Patrick on 27.11.2018.
//

#include "rec_mergesort_reference.h"

//starte den rekursiven Mergesort
template<typename T>
void mergesort(std::vector<T> &v) {
    unsigned int size = v.size();
    std::vector<T> merge_vector;
    merge_vector.reserve(size);
    recsort(v, merge_vector, 0, v.size() - 1, true);
}

/* Rufe diese Methode jeweils rekursiv mit invertiertem boolean i auf
 * Falls nur noch 2 oder 3 Elemente in v sind, dann rufe den small-sort auf
 * Merge dann die rekursiv bereits sortierten Teillisten
 * Falls i = true, dann merge von m in v; ansonsten merge von v in m
*/
template<typename T>
void recsort(std::vector<T> &v, std::vector<T> &m, int u, int o, bool i){
    int pivot = (o-u)/2;
    if (o - u > 2) {
        recsort(v, m, u, u + pivot, !i);
        recsort(v, m, u + pivot + 1, o, !i);
        if (i) {
            merge(m, v, u, o, u + pivot);
        } else {
            merge(v, m, u, o, u + pivot);
        }
    } else {
        small_sort(v, m, u, o, i);
    }
}

//merge die Teillisten sortiert vom ersten Vektor in den zweiten
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

/*
 * Diese Prozedur sortiert Listen der Länge 2 oder 3
 * Falls i = true, dann sortiere innerhalb von v
 * Ansonsten sortiere die Elemente von v in m
 */
template <typename T>
void small_sort (std::vector<T> &v, std::vector<T> &m, int u, int o, bool i){
    if (i){
        //sort in v
        if (o - u == 1) {
            if (v[u] > v[o]){
                T temp = v[u];
                v[u] = v[o];
                v[o] = temp;
            }
        } else {
            if (v[u] > v[o]) {
                if (v[u + 1] > v[u]){
                    // o < u < u+1
                    T temp = v[u];
                    v[u] = v[o];
                    v[o] = v[u+1];
                    v[u+1] = temp;
                } else {
                    if (v[o] > v[u+1]){
                        //u+1 < o < u
                        T temp = v[u];
                        v[u] = v[u+1];
                        v[u+1] = v[o];
                        v[o] = temp;
                    } else {
                        // o < u+1 < u
                        T temp = v[u];
                        v[u] = v[o];
                        v[o] = temp;
                    }
                }
            } else {
                // u < o
                if (v[u+1] > v[o]){
                    // u < o < u+1
                    T temp = v[u+1];
                    v[u+1] = v[o];
                    v[o] = temp;
                } else {
                    if (v[u] > v[u+1]){
                        // u+1 < u < o
                        T temp = v[u];
                        v[u] = v[u+1];
                        v[u+1] = temp;
                    }
                }
            }
        }
    } else {
        //sort and write to m
        if (o - u == 1) {
            if (v[u] > v[o]){
                m[u] = v[o];
                m[o] = v[u];
            } else {
                m[u] = v[u];
                m[o] = v[o];
            }
        } else {
            if (v[u] > v[o]) {
                if (v[u + 1] > v[u]){
                    // o < u < u+1
                    m[u] = v[o];
                    m[o] = v[u+1];
                    m[u+1] = v[u];
                } else {
                    if (v[o] > v[u+1]){
                        //u+1 < o < u
                        m[u] = v[u+1];
                        m[u+1] = v[o];
                        m[o] = v[u];
                    } else {
                        // o < u+1 < u
                        m[u] = v[o];
                        m[o] = v[u];
                        m[u+1] = v[u+1];
                    }
                }
            } else {
                // u < o
                if (v[u+1] > v[o]){
                    // u < o < u+1
                    m[u] = v[u];
                    m[u+1] = v[o];
                    m[o] = v[u+1];
                } else {
                    if (v[u] > v[u+1]){
                        // u+1 < u < o
                        m[o] = v[o];
                        m[u] = v[u+1];
                        m[u+1] = v[u];
                    } else {
                        // u < u+1 < o nur kopieren
                        m[u] = v[u];
                        m[u+1] = v[u+1];
                        m[o] = v[o];
                    }
                }
            }
        }
    }
}