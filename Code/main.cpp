#pragma once
//
// Created by jonas on 02.11.2018.
//
#include<array>
#include<vector>
#include <iostream>
#include "naivmerge.cpp"

static int z = 0;

bool comp(int i, int j) {
    z++;
    return (i < j);
}


int main() {

    std::vector<int> myarr = {80, 16, 77, 34, 65, 345, 2, 15, 4, 47, 64, 117, 11, 14, 96, 33, 109, 42};
    std::vector<int>::iterator start = myarr.begin();
    std::vector<int>::iterator end = myarr.end();
    std::cout << "\nDas Array vor der Sortierung: " << "\n";
    for (auto it = myarr.begin(); it != myarr.end(); it++) {
        std::cout << *it;
        std::cout << " ";
    }

    mergesort(start, end);

    std::cout << "\nDas Array nach der Sortierung: " << "\n";
    for (auto it = myarr.begin(); it != myarr.end(); it++) {
        std::cout << *it;
        std::cout << " ";
    }

/*
    std::vector<int> myvec = { 80, 16, 77, 34, 65, 345, 2, 15, 4, 47, 64, 117, 11, 14, 96, 33, 109, 42 };
    ArrayWrapper<int> wrapvec(myvec);
    std::sort(wrapvec.begin(),wrapvec.end());
    for(auto i=wrapvec.begin();i!= wrapvec.end();i++){
        std::cout << (*i).get_value() << "\n";
    }
    */

    /*

    std::vector<ArrayWrapper<int>::BasetypeWrapper<int>>(v);
    v.push_back(2);
    v[0] = ArrayWrapper<int>::BasetypeWrapper<int>(5);
    std::cout << v[0].get_value();
    ArrayWrapper<int> arr(v);
    arr.push_back(3);
    arr.push_back(7);
    arr[0] = 7;
    for(auto i= arr.begin(); i != arr.end(); i++){
        std::cout << (*i).get_value();
    }
    ArrayWrapper<int> nextarr(myarr);
    nextarr[0] = 1;
    nextarr.push_back(3);
    nextarr[0] = 4;
    for(auto i= nextarr.begin(); i != nextarr.end(); i++){
        std::cout << (*i).get_value();
        std::cout << "  ";
    }

    ArrayWrapper<int> nextarr(myarr);
    mergesort(nextarr.begin(),nextarr.end());
    for(auto i= nextarr.begin(); i != nextarr.end(); i++){
        std::cout << (*i).get_value();
        std::cout << "  ";
    }
    */
    return 0;
}
