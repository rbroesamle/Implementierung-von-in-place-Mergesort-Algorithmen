//
// Created by jonas on 02.11.2018.
//
#include<array>
#include<vector>
#include <iostream>

template<class Iterator, class Compare>
void merge(Iterator startFirst, Iterator endFirst, Iterator startSecond, Iterator endSecond, Compare compare) {
    auto iFirst = startFirst;
    auto iSecond = startSecond;
    int *startExtra = new int[endSecond - startFirst + 1];
    auto iExtra = startExtra;

    while (true) {
        if (iFirst == endFirst) {
            while (iSecond != endSecond) {
                *iExtra = *iSecond;
                iExtra++;
                iSecond++;
            }
            break;
        }
        if (iSecond == endSecond) {
            while (iFirst != endFirst) {
                *iExtra = *iFirst;
                iExtra++;
                iFirst++;
            }
            break;
        }
        if (compare(*iFirst, *iSecond)) {
            *iExtra = *iFirst;
            iExtra++;
            iFirst++;
        } else {
            *iExtra = *iSecond;
            iExtra++;
            iSecond++;
        }
    }

    //Copy merged array to original positions
    int *iOrig = startFirst;
    iExtra = startExtra;
    while (iOrig != endSecond) {
        *iOrig = *iExtra;
        iExtra++;
        iOrig++;
    }
    delete(startExtra);
}

template<class Iterator, class Compare>
void mergesort(Iterator startIndex, Iterator endIndex, Compare compare) {
    int blockSize = 1;
    while (startIndex + blockSize < endIndex) {
        //merge all blocks with size blockSize
        int *startIndexBlock1 = startIndex;
        int *endIndexBlock1 = startIndexBlock1 + blockSize;
        int *startIndexBlock2 = endIndexBlock1;
        int *endIndexBlock2 = (startIndexBlock2 + blockSize) > endIndex
                              ? endIndex
                              : (startIndexBlock2 + blockSize);
        while (true) {
            merge(startIndexBlock1, endIndexBlock1, startIndexBlock2, endIndexBlock2, compare);
            if (endIndexBlock2 + blockSize >= endIndex) {
                break;
            }
            startIndexBlock1 = endIndexBlock2;
            endIndexBlock1 = startIndexBlock1 + blockSize;
            startIndexBlock2 = endIndexBlock1;
            endIndexBlock2 = (startIndexBlock2 + blockSize) > endIndex
                             ? endIndex
                             : (startIndexBlock2 + blockSize);
        }
        blockSize *= 2;
    }
}