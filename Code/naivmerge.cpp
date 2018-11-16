//
// Created by jonas on 02.11.2018.
//
#include<array>
#include<vector>
#include <iostream>

template<class Iterator, class Compare>
void merge(Iterator startFirst, Iterator endFirst, Iterator startSecond, Iterator endSecond, Iterator startExtra, Compare compare) {
    auto iFirst = startFirst;
    auto iSecond = startSecond;
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
}

template<class Iterator, class Compare>
void mergesort(Iterator start, Iterator end, Compare compare) {
    Iterator startIndex = start;
    Iterator endIndex = end;
    int blockSize = 1;
    while (startIndex + blockSize < endIndex) {

        int *startExtra = new int[endIndex - startIndex + 1];
        auto iExtra = startExtra;

        //merge all blocks with size blockSize
        int *startIndexBlock1 = startIndex;
        int *endIndexBlock1 = startIndexBlock1 + blockSize;
        int *startIndexBlock2 = endIndexBlock1;
        int *endIndexBlock2 = (startIndexBlock2 + blockSize) > endIndex
                              ? endIndex
                              : (startIndexBlock2 + blockSize);
        while (true) {
            merge(startIndexBlock1, endIndexBlock1, startIndexBlock2, endIndexBlock2, iExtra, compare);
            if (endIndexBlock2 + blockSize >= endIndex) {
                for(auto addEnd = endIndexBlock2; addEnd != endIndex; addEnd ++){
                    *(startExtra + (addEnd - startIndex)) = *addEnd;
                }
                break;
            }
            startIndexBlock1 = endIndexBlock2;
            endIndexBlock1 = startIndexBlock1 + blockSize;
            startIndexBlock2 = endIndexBlock1;
            endIndexBlock2 = (startIndexBlock2 + blockSize) > endIndex
                             ? endIndex
                             : (startIndexBlock2 + blockSize);
            iExtra = startExtra + (startIndexBlock1 - startIndex);
        }
        blockSize *= 2;

        endIndex = startExtra + (endIndex - startIndex);
        delete(startIndex);
        startIndex = startExtra;
    }
    auto copBack = start;
    for(auto i = startIndex; i != endIndex; i ++){
        *copBack = *i;
        copBack ++;
    }

}