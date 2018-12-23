#pragma once
//
// Created by jonas on 02.11.2018.
//
#include<array>
#include<vector>
#include <iostream>
#include "naivmerge.cpp"

int main() {

    std::vector<int> myarr = {80, 16, 77, 34, 65, 345, 2, 15, 4, 47, 64, 117, 11, 14, 96, 33, 109, 42};
    auto start = myarr.begin();
    auto end = myarr.end();
    std::cout << "\nDas Array vor der Sortierung: " << "\n";
    for (int &it : myarr) {
        std::cout << it;
        std::cout << " ";
    }

    mergesort<std::vector<int>::iterator>(start, end);

    std::cout << "\nDas Array nach der Sortierung: " << "\n";
    for (int &it : myarr) {
        std::cout << it;
        std::cout << " ";
    }
    return 0;
}
