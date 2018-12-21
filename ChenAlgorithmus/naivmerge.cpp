//
// Created by jonas on 02.11.2018.
//
#include "naivmerge.h"

template<typename Iterator>
void mergesort(Iterator start, Iterator end) {
    int x0 = 0;
    int yn = end - start - 1;
    for (int k = 1; k < (end - start); k *= 2) {
        int y0 = (end - start) / 2;
        y0 += k - (y0 % k);
        merge(start, end, x0, y0, yn, k);
    }
}

template<typename Iterator>
void merge(Iterator start, Iterator end, int x0, int y0, int yn, int k) {
    //1
    int f = (y0 - x0) % k;
    //2
    int x;
    if (f == 0) {
        x = y0 - 2 * k;
    } else {
        x = y0 - k - f;
    }
    //3
    auto t = *(start + x);
    *(start + x) = *(start + x0);
    //4
    int z = x0;
    int y = y0;
    int b1 = x + 1;
    int b2 = y0 - k;
    //5
    while ((y - z) > (2 * k)) {
        //6, 7
        if ((*(start + x) <= *(start + y)) || y > yn) {
            //8
            *(start + z) = *(start + x);
            *(start + x) = *(start + b1);
            x += 1;
            //9
            if (((x - x0) % k) == f) {
                //10
                if (z < (x - k)) {
                    b2 = x - k;
                }
                //11
                x = findNextXBlock(start, end, x0, z, y, k, f, b1, b2);
            }
            //12
        } else {
            //13
            *(start + z) = *(start + y);
            *(start + y) = *(start + b1);
            y += 1;
            //14
            if (((y - y0) % k) == 0) {
                b2 = y - k;
            }
        }
        //15
        z += 1;
        *(start + b1) = *(start + z);
        //16
        if (z == x) {
            x = b1;
        }
        //17
        if (z == b2) {
            b2 = -1;
        }
        //18
        b1 += 1;
        //19
        if (((b1 - x0) % k) == f) {
            //20
            if (b2 == -1) {
                b1 = b1 - k;
            } else {
                b1 = b2;
            }
        }
        //21
    }
    //22
    *(start + z) = t;
    //23
    mergeBandY(start, end, z, y, yn);
}

template<typename Iterator>
int findNextXBlock(Iterator start, Iterator end, int x0, int z, int y, int k, int f, int b1, int b2) {
    int x;
    //
    typename std::iterator_traits<Iterator>::value_type min1;
    typename std::iterator_traits<Iterator>::value_type min2;
    bool areMinsSet = false;
    int temp = (z - x0 - f) / k;
    int m = temp * k + f + x0;
    //
    if (m <= z) {
        m += k;
    }
    //
    //find from m, the start of the block adjacent to the right of z
    int j;
    int i = m;
    //
    while (i + k <= y) {
        //
        if (i != b1 && i != b2) {
            //
            if (i < b1 && b1 < i + k) {
                j = m - 1;
            } else {
                j = i + k - 1;
            }
            //
            if ((*(start + i) <= min1 && *(start + j) <= min2) || !areMinsSet) {
                x = i;
                min1 = *(start + i);
                min2 = *(start + j);
                areMinsSet = true;
            }
        }
        //
        i += k;
    }
    //
    return x;
}

template<typename Iterator>
void mergeBandY(Iterator start, Iterator end, int _z, int _y, int _yn) {
    int z = _z;
    int y = _y;
    int yn = _yn;
    //
    while (z < y && y <= yn) {
        //
        int j = z;
        for (int i = z + 1; i < y; i++) {
            if (*(start + j) > *(start + i)) {
                j = i;
            }
        }
        //
        if (*(start + j) <= *(start + y)) {
            swap(start, end, z, j);
            //
        } else {
            swap(start, end, z, y);
            y += 1;
        }
        //
        z += 1;
        //
    }
    //
    if (z < y) {
        std::sort((start + z), (start + yn));
        //FIXME should be heapsort here...
    }
}

template<typename Iterator>
void swap(Iterator start, Iterator end, int a, int b) {
    if (a == b) {
        return;
    }
    auto temp = *(start + a);
    *(start + a) = *(start + b);
    *(start + b) = temp;
}