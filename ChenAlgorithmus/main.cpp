//
// Created by Patrick on 29.11.2018.
//

//#include "chen.h"
#include <chrono>
#include <iostream>
#include "wrapper.h"
#include <random>
#include "naivmerge.cpp"
#include "chen.h"

/*
 * Testmethode, die auf einer Kopie eines Vektors der Größe size sortiert
 * Falls stdSort = true, dann verwendet sie zur Sortierung die C++-Standardsortiermethode
 * Sie verursacht eine Konsolenausgabe, falls die Sortierung nicht stimmt
 * Sie gibt außerdem die Anzahl an Vergleichen, Zuweisungen und die verbrauchte Zeit bei der Sortierung auf der Konsole aus
 * Rückgabewert ist die verbrauchte Zeit bei der Sortierung
 * Der Reset des Vergleichs- und Zuweisungszählers erfolgt direkt am Anfang der Methode
 *
 */
std::vector<long> times;
std::vector<int> comps;
std::vector<int> assis;

std::vector<long> std_times;
std::vector<int> std_comps;
std::vector<int> std_assis;

long testSort(std::vector<BasetypeWrapper<int>> test, int size, bool stdSort) {
    std::vector<BasetypeWrapper<int>> copy;
    if (!stdSort) {
        copy = test;
        std::sort(copy.begin(), copy.end());
    }
    BasetypeWrapper<int>::reset_c();
    BasetypeWrapper<int>::reset_m();
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    //stdSort? std::stable_sort(test.begin(), test.end()): mergesort(test);
    stdSort ? std::stable_sort(test.begin(), test.end()) : mergesort_chen(test.begin(), test.end());
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    int c = BasetypeWrapper<int>::get_c();
    int m = BasetypeWrapper<int>::get_m();
    auto mikro = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    float milli = float(mikro) / 1000;
    float seconds = float(mikro) / 1000000;

    stdSort ? std_comps.push_back(c) : comps.push_back(c);
    stdSort ? std_assis.push_back(m) : assis.push_back(m);
    stdSort ? std_times.push_back(mikro) : times.push_back(mikro);

    std::cout << "Anzahl an Vergleichen:" << std::endl << c << std::endl;
    std::cout << "Anzahl an Zuweisungen:" << std::endl << m << std::endl;
    std::cout << "Dauer der Sortierung:" << std::endl;
    std::cout << seconds << " sekunden" << std::endl;
    std::cout << milli << " millisekunden" << std::endl;
    std::cout << mikro << " mikrosekunden" << std::endl;
    std::cout << std::endl;
    std::cout << " -----------------------------------" << std::endl;
    std::cout << std::endl;

    bool success = true;
    if (!stdSort) {
        auto testIt = test.begin();
        for (auto sortIt = copy.begin(); sortIt != copy.end(); sortIt++) {
            if (*sortIt != *testIt) {
                std::cout << "------> Sortierung inkorrekt!!! <------" << std::endl;
                success = false;
            }
            testIt++;
        }
        if (testIt != test.end()) {
            std::cout << "------> Sortierung inkorrekt!!! <------" << std::endl;
            success = false;
        }
        if (success) {
            std::cout << "------> Sortierreihenfolge stimmt <------" << std::endl;
        }
    }

    return static_cast<long>(mikro);
}

/*
 * Die Methode ruft obige Testmethode mit einem geshuffelten Vektor der Größe size mit paarweise verschiedenen Elementen auf
 * Rückgabewert ist die verbrauchte Zeit bei der Sortierung
 * Falls stdSort = true, dann erfolgt zusätzlich ein Vergleich des Mergesorts mit der C++-Standardsortmethode
 * In diesem Fall ist der Rückgabewert die Zeit bei der Standardsortierung
 * und Vergleichs-/Zuweisungszähler beziehen sich auf die Standardsortierung (ansonsten jeweils auf den Mergesort)
 */
long testDifferElem(int size, bool stdSort) {
    std::vector<BasetypeWrapper<int>> test;
    for (int i = 0; i < size; i++) {
        test.push_back(i);
    }
    std::srand(time(0));
    std::random_shuffle(test.begin(), test.end());
    long mikro = testSort(test, size, false);
    if (stdSort) {
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
long testRandNum(int size, int u, int o, bool stdSort) {
    // TODO: evtl bessere Verteilung implementieren
    std::vector<BasetypeWrapper<int>> test;
    std::srand(time(0));
    for (int i = 0; i < size; i++) {
        test.push_back(static_cast<int>(std::rand() * 1.0 / RAND_MAX * (o - u + 1) + u));
        //test.push_back(uni(rng));
    }
    long mikro = testSort(test, size, false);
    if (stdSort) {
        std::cout << std::endl;
        std::cout << "Vergleich mit C++ - Standardsort:" << std::endl;
        std::cout << std::endl;
        mikro = testSort(test, size, true);
    }
    return mikro;
}

int main() {
    //Anzahl Wiederholungen
    int anz = 1;
    //Größe der zu sortierenden Listen
    int size = 30000000;
    int u = 0;
    int o = 10000;

    for (int durch = 0; durch < anz; durch++) {
        //testRandNum(size, u, o, true);
        testDifferElem(size, true);
    }

    int comp_sum = 0;
    int assi_sum = 0;
    long time_sum = 0;
    int std_comp_sum = 0;
    int std_assi_sum = 0;
    long std_time_sum = 0;

    for (int i = 0; i < anz; i++) {
        comp_sum += comps[i];
        assi_sum += assis[i];
        time_sum += times[i];

        std_comp_sum += std_comps[i];
        std_assi_sum += std_assis[i];
        std_time_sum += std_times[i];
    }

    std::cout << "Vergleichsschnitt:" << std::endl << comp_sum / anz << std::endl;
    std::cout << "Zuweisungsschnitt:" << std::endl << assi_sum / anz << std::endl;
    std::cout << "Zeitschnitt:" << std::endl << time_sum / anz << std::endl;

    std::cout << "Vergleichsschnitt std-Sort:" << std::endl << std_comp_sum / anz << std::endl;
    std::cout << "Zuweisungsschnitt std-Sort:" << std::endl << std_assi_sum / anz << std::endl;
    std::cout << "Zeitschnitt std-Sort:" << std::endl << std_time_sum / anz << std::endl;
    return 0;
}
