#pragma once
//
// Created by jonas on 02.11.2018.
//
#include<array>
#include <iostream>
#include "naivmerge.cpp"


static int z = 0;
bool comp (int i,int j) { z++; return (i<j); }


int main(){
	/*
    std::array<int,18> myarr = { 80, 16, 77, 34, 65, 345, 2, 15, 4, 47, 64, 117, 11, 14, 96, 33, 109, 42 };
    mergesort(myarr.begin(),myarr.end());
    std::cout << "Vergleiche: ";
    std::cout << z;
    std::cout << "   ";

    std::cout << " das array nach der Sortierung: ";
    for(auto it=myarr.begin(); it != myarr.end(); it++){
        std::cout << *it;
        std::cout << " ";
    }
	*/
    return 0;
}
