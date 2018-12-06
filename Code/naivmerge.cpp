//
// Created by jonas on 02.11.2018.
//
#include "naivmerge.h"

template<typename T>
void merge(std::__1::__wrap_iter<T *> startBlock1From, std::__1::__wrap_iter<T *> endBlock1From,
           std::__1::__wrap_iter<T *> startBlock2From, std::__1::__wrap_iter<T *> endBlock2From,
           std::__1::__wrap_iter<T *> startTo, std::__1::__wrap_iter<T *> endTo) {
    //Iterators
    typename std::__1::__wrap_iter<T *> iteratorBlock1 = startBlock1From;
    typename std::__1::__wrap_iter<T *> iteratorBlock2 = startBlock2From;
    typename std::__1::__wrap_iter<T *> iteratorTo = startTo;

    //Elements to compare
    T a = *iteratorBlock1;
    T b = *iteratorBlock2;

    //While there are unmerged elements in block1 and block2
    while (iteratorBlock1 < endBlock1From && iteratorBlock2 < endBlock2From) {
        if (a > b) {
            //copy b into extra vector
            *iteratorTo = b;
            iteratorBlock2++;
            //update b
            b = *iteratorBlock2;
        } else {
            //copy a into extra vector
            *iteratorTo = a;
            iteratorBlock1++;
            //update a
            a = *iteratorBlock1;
        }
        iteratorTo++;
    }

    if (iteratorBlock1 < endBlock1From) {
        //Merge rest of block1 into vector
        while (iteratorBlock1 < endBlock1From) {
            *iteratorTo = *iteratorBlock1;
            iteratorBlock1++;
            iteratorTo++;
        }
    } else if (iteratorBlock2 < endBlock2From) {
        //Merge rest of block2 into vector
        while (iteratorBlock2 < endBlock2From) {
            *iteratorTo = *iteratorBlock2;
            iteratorBlock2++;
            iteratorTo++;
        }
    }
}

template<typename T>
void mergesort(typename std::__1::__wrap_iter<T *> start, typename std::__1::__wrap_iter<T *> end) {
    //Iterators for the new vector
    typename std::vector<T> newVector(end - start);
    typename std::vector<T>::iterator newStart = newVector.begin();
    typename std::vector<T>::iterator newEnd = newVector.end();
    //Outer Variables
    bool copyFromOrigToNew = true;
    int blockSize = 1;

    //Merge until the last 2 blockSizes
    while (blockSize * 4 < end - start) {
        //Variables for original vector
        auto startBlock1Orig = start;
        auto endBlock1Orig = startBlock1Orig + blockSize;
        auto startBlock2Orig = endBlock1Orig;
        auto endBlock2Orig = startBlock2Orig + blockSize;

        //Variables for new vector
        auto startBlock1New = newStart;
        auto endBlock1New = startBlock1New + blockSize;
        auto startBlock2New = endBlock1New;
        auto endBlock2New = startBlock2New + blockSize;

        //Continue until there are less than 2 unmerged blocks left.
        while (endBlock2Orig <= end) {
            if (copyFromOrigToNew) {
                merge(startBlock1Orig, endBlock1Orig,
                      startBlock2Orig, endBlock2Orig,
                      startBlock1New, endBlock2New);
            } else {
                merge(startBlock1New, endBlock1New,
                      startBlock2New, endBlock2New,
                      startBlock1Orig, endBlock2Orig);
            }

            //Randfälle abdecken
            if (endBlock2Orig + 2 * blockSize <= end) {
                //Es passen noch 2 ganze Blöcke in den ungemergten Bereich
                startBlock1Orig = endBlock2Orig;
                endBlock1Orig = startBlock1Orig + blockSize;
                startBlock2Orig = endBlock1Orig;
                endBlock2Orig = startBlock2Orig + blockSize;

                startBlock1New = endBlock2New;
                endBlock1New = startBlock1New + blockSize;
                startBlock2New = endBlock1New;
                endBlock2New = startBlock2New + blockSize;
            } else if (endBlock2Orig + blockSize <= end) {
                //Es passt nur noch 1 ganzer Block in den ungemergten Bereich
                if (copyFromOrigToNew) {
                    merge(endBlock2Orig, endBlock2Orig + blockSize,
                          endBlock2Orig + blockSize, end,
                          endBlock2New, newEnd);
                } else {
                    merge(endBlock2New, endBlock2New + blockSize,
                          endBlock2New + blockSize, newEnd,
                          endBlock2Orig, end);
                }
                break;
            } else {
                //Es passt kein ganzer Block in den ungemergten Bereich
                //Kopiere letzten Block in anderes Array/Vektor.
                if (copyFromOrigToNew) {
                    merge(endBlock2Orig, end,
                          end, end,
                          endBlock2New, newEnd);
                } else {
                    merge(endBlock2New, newEnd,
                          newEnd, newEnd,
                          endBlock2Orig, end);
                }
                break;
            }
        }

        //Adjust outer variables
        blockSize *= 2;
        copyFromOrigToNew = !copyFromOrigToNew;
    }
    //Merge the last 2 blockSizes
    if (copyFromOrigToNew) {
        //Merge normally

        //Step 1:
        merge(start, start + blockSize,
              start + blockSize, start + 2 * blockSize,
              newStart, newStart + 2 * blockSize);
        if (start + 3 * blockSize >= end) {
            //Es passt kein ganzer Block in den "ungemergten" Bereich
            merge(start + 2 * blockSize, end,
                  end, end,
                  newStart + 2 * blockSize, newEnd);
        } else {
            //Es passt noch 1 ganzer Block in den "ungemergten" Bereich
            merge(start + 2 * blockSize, start + 3 * blockSize,
                  start + 3 * blockSize, end,
                  newStart + 2 * blockSize, newEnd);
        }

        //Step 2:
        blockSize *= 2;
        merge(newStart, newStart + blockSize,
              newStart + blockSize, newEnd,
              start, end);
    } else {
        //Merge so, dass ein zurückkopieren nicht nötig ist.

        //Step 1:
        merge(newStart, newStart + blockSize,
              newStart + blockSize, newStart + 2 * blockSize,
              end - 2 * blockSize, end);
        unsigned long blockLength = newEnd - (newStart + 2 * blockSize);
        if (newStart + 3 * blockSize >= newEnd) {
            //Es passt kein ganzer Block in den "ungemergten" Bereich
            merge(newStart + 2 * blockSize, newEnd,
                  newEnd, newEnd,
                  newStart, newStart + blockLength);
        } else {
            //Es passt noch 1 ganzer Block in den "ungemergten" Bereich
            merge(newStart + 2 * blockSize, newStart + 3 * blockSize,
                  newStart + 3 * blockSize, newEnd,
                  newStart, newStart + blockLength);
        }

        //Step 2:
        blockSize *= 2;
        merge(newStart, newStart + blockLength,
              end - blockSize, end,
              start, end);
    }
}