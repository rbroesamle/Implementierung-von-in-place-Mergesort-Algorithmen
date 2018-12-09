//
// Created by Patrick on 29.11.2018.
//

#include "vectormerge.cpp"
#include <iostream>
#include "wrapper.h"
#include <time.h>
#include <algorithm>
#include <random>
#include "vectormergeIter.cpp"

/*
 * Testmethode, die auf einer Kopie eines Vektors der Größe size sortiert
 * Falls stdSort = true, dann verwendet sie zur Sortierung die C++-Standardsortiermethode
 * Sie verursacht eine Konsolenausgabe, falls die Sortierung nicht stimmt
 * Sie gibt außerdem die Anzahl an Vergleichen, Zuweisungen und die verbrauchte Zeit bei der Sortierung auf der Konsole aus
 * Rückgabewert ist die verbrauchte Zeit bei der Sortierung
 * Der Reset des Vergleichs- und Zuweisungszählers erfolgt direkt am Anfang der Methode
 *
 */
long testSort(std::vector<BasetypeWrapper<int>> test, int size, bool stdSort){
    std::vector<BasetypeWrapper<int>> copy;
    if(!stdSort){
        copy = test;
        std::sort(copy.begin(), copy.end());
    }
    BasetypeWrapper<int>::reset_c();
    BasetypeWrapper<int>::reset_m();
    timeval start, end;
    mingw_gettimeofday(&start, 0);
    //stdSort? std::sort(test.begin(), test.end()): mergesort(test);
    stdSort? std::sort(test.begin(), test.end()): mergesort<std::vector<BasetypeWrapper<int>>::iterator, BasetypeWrapper<int>>(test.begin(),test.end());
    mingw_gettimeofday(&end,0);
    std::cout << "Anzahl an Vergleichen:" << std::endl;
    std::cout << BasetypeWrapper<int>::get_c() << std::endl;
    std::cout << "Anzahl an Zuweisungen:" << std::endl;
    std::cout << BasetypeWrapper<int>::get_m() << std::endl;
    std::cout << "Dauer der Sortierung:" << std::endl;
    long mikro = (end.tv_sec - start.tv_sec)* 1000000 + end.tv_usec - start.tv_usec;
    std::cout << double(mikro)/1000000 << " sekunden" << std::endl;
    std::cout << double(mikro)/1000 << " millisekunden" << std::endl;
    std::cout << mikro  << " mikrosekunden" << std::endl;
    std::cout << std::endl;
    std::cout << " -----------------------------------" << std::endl;
    std::cout << std::endl;

    bool success = true;
    if(!stdSort){
        auto testIt = test.begin();
        for(auto sortIt = copy.begin(); sortIt != copy.end(); sortIt++){
            if(*sortIt != *testIt){
                std::cout << "------> Sortierung inkorrekt!!! <------" << std::endl;
                success = false;
            }
            testIt++;
        }
        if(testIt != test.end()){
            std::cout << "------> Sortierung inkorrekt!!! <------" << std::endl;
            success = false;
        }
        if(success){
            std::cout << "------> Sortierreihenfolge stimmt <------" << std::endl;
        }
    }

    return mikro;
}

/*
 * Die Methode ruft obige Testmethode mit einem geshuffelten Vektor der Größe size mit paarweise verschiedenen Elementen auf
 * Rückgabewert ist die verbrauchte Zeit bei der Sortierung
 * Falls stdSort = true, dann erfolgt zusätzlich ein Vergleich des Mergesorts mit der C++-Standardsortmethode
 * In diesem Fall ist der Rückgabewert die Zeit bei der Standardsortierung
 * und Vergleichs-/Zuweisungszähler beziehen sich auf die Standardsortierung (ansonsten jeweils auf den Mergesort)
 */
long testDifferElem(int size, bool stdSort){
    std::vector<BasetypeWrapper<int>> test;
    for(int i=0; i < size; i++){
        test.push_back(i);
    }
    std::random_shuffle(test.begin(), test.end());
    long mikro = testSort(test, size, false);
    if(stdSort){
        std::cout << std::endl;
        std::cout << " -------- Vergleich mit C++ - Standardsort: --------" << std::endl;
        std::cout << std::endl;
        mikro = testSort(test, size, true);
    }
    return mikro;
}
/*
 * Die Methode ruft obige Testmethode mit einem Vektor mit size Zufallselementen zwischen u und o auf
 * Rückgabewert ist die verbrauchte Zeit bei der Sortierung
 * Falls stdSort = true, dann erfolgt zusätzlich ein Vergleich des Mergesorts mit der C++-Standardsortmethode
 * In diesem Fall ist der Rückgabewert die Zeit bei der Standardsortierung
 * und Vergleichs-/Zuweisungszähler beziehen sich auf die Standardsortierung (ansonsten jeweils auf den Mergesort)
 */
long testRandNum(int size, int u, int o, bool stdSort){
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(u, o);
    std::vector<BasetypeWrapper<int>> test;
    for(int i=0; i < size; i++){
        test.push_back(uni(rng));
    }
    long mikro = testSort(test, size, false);
    if(stdSort){
        std::cout << std::endl;
        std::cout << "Vergleich mit C++ - Standardsort:" << std::endl;
        std::cout << std::endl;
        mikro = testSort(test, size, true);
    }
    return mikro;
}

int main (){
    testRandNum(500000, 0, 10000, true);
    testDifferElem(500000, true);
    return 0;
}