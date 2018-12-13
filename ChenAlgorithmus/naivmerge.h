#pragma once
#include<array>
#include<vector>
#include <iostream>

/// <summary>
/// Merges two lists
/// </summary>
/// <param name="startFirst">Iterator to the start of the first list</param>
/// <param name="endFirst">Iterator to the end of the first list</param>
/// <param name="startSecond">Iterator to the start of the second list</param>
/// <param name="endSecond">Iterator to the end of the second list</param>

template<typename Iterator>
void mergesort(Iterator start, Iterator end);

