//
// Created by kai on 26.02.2019.
//

#pragma once
#include <array>
#include <vector>

#include "Reinhardt_Compare/inplace_mergesort_qsel.cpp"
#include "huang_langston_merge.h"
#include "chen.h"
#include <iostream>
#include <fstream>
#include "structs.h"
#include "wrapper.h"



// enables debugging messeges and  logs stuff
const bool DEBUGGING = false;
const bool MERGE_TEST = false;

std::ofstream debug;

//number of REPETITIONS done for every list length
const int START_REPETITIONS = 10000;
int current_REPETITIONS = START_REPETITIONS;
const unsigned int MIN_REPETITIONS = 1; // default 1 shouldn't be lower than 1, else undefined behavior
// take the repetitions of times the factor
const float REPETITION_FACTOR = 0.1f; // default 1 doesn't change the number of repetitions
// if you only want to make half as many steps in the next list length change it to 0.5f


//control the length of list that are created and tested
const unsigned long long MIN_ELEMENTS_TO_SORT = 1000;
const unsigned long long MAX_ELEMENTS_TO_SORT = 10000000;

unsigned long long current_elements_to_sort = MIN_ELEMENTS_TO_SORT;

// factor used to compute the next tested length
const int STEP_FACTOR = 10;

//the range from which the random numbers are generated
const int MIN_NUMBER = std::numeric_limits<int>::min();
const int MAX_NUMBER = std::numeric_limits<int>::max();

// set the type to be tested
typedef Big_Type<30, true, MIN_NUMBER, MAX_NUMBER> gen_type;
//typedef int gen_type;

// 0 := stdSort; 1 := Chen; 2 := Reinhardt; 3 := weitererAlgo
std::array<std::vector<long long>, 4> timings;
std::array<std::vector<long long>, 4> comparisons;
std::array<std::vector<long long>, 4> assignments;

// output streams
std::ofstream standard_out;
std::ofstream chen_out;
std::ofstream reinhardt_out;
std::ofstream other_out;

// Files the output is stored to
std::string STANDARD_OUTPUTFILE = "standard.csv";
std::string CHEN_OUTPUTFILE = "chen.csv";
std::string REINHARDT_OUTPUTFILE = "reinhardt.csv";
std::string OTHER_OUTPUTFILE = "other.csv";

std::string DEBUG_LOG = "debug.log";


template <class T>
std::vector<BasetypeWrapper<T>> createList(unsigned long long size, time_t seed);

void reset();

void outputdata();

template <class T>
void check_sorted_list(std::array<BasetypeWrapper<T>, 4> &lists);

