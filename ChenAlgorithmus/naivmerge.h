#pragma once
#include<array>
#include<vector>
#include <iostream>

/// <summary>
/// Merges two lists
/// </summary>
/// <param name="startFirst">Iterator to the start of the first list</param>
/// <param name="endFirst">Iterator to the end of the first list</param>
template<typename Iterator>
void mergesort(Iterator start, Iterator end);

template<typename Iterator>
void merge(Iterator start, Iterator end, int x0, int y0, int yn, int k);

template<typename Iterator>
int findNextXBlock(Iterator start, Iterator end, int x0, int z, int y, int k, int f, int b1, int b2);

template<typename Iterator>
void mergeBandY(Iterator start, Iterator end, int z, int y, int yn);

template<typename Iterator>
void swap(Iterator start, Iterator end, int a, int b);

template<typename Iterator>
void insertLastElement(Iterator start, Iterator end);