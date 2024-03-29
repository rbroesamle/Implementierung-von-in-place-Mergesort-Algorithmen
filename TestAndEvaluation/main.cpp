//
// Created by kai on 25.02.2019.
//

#include "main.h"
#include <time.h>
#include <random>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <limits>
#include <functional>


// create a random list with size elements and returning it
std::vector<BasetypeWrapper<gen_type>> createList(unsigned long long size, time_t seed){
    std::vector<BasetypeWrapper<gen_type>> test;
    auto rand = std::bind(std::uniform_int_distribution<int>(MIN_NUMBER,MAX_NUMBER), std::mt19937(seed));
    for(unsigned long long i=0; i < size; i++){
        test.emplace_back(gen_type(static_cast<int>(rand())));
    }

    return test;
}

// resets time, comparison and assignment arrays
void reset(){
    for(int i = 0; i < 4; i++){
        //
        timings[i] = std::vector<long long>();
        comparisons[i] = std::vector<long long>();
        assignments[i] = std::vector<long long>();
    }
}

// stores data in text files
void outputdata(std::array<unsigned long long, 3> standard, std::array<unsigned long long, 3> chen, std::array<unsigned long long, 3> reinhardt,
        std::array<unsigned long long, 3> other){
    if(!standard_out.is_open()){
        standard_out.open(STANDARD_OUTPUTFILE, std::ofstream::out | std::ofstream::app);
    }
    if(!chen_out.is_open()){
        chen_out.open(CHEN_OUTPUTFILE, std::ofstream::out | std::ofstream::app);
    }
    if(!reinhardt_out.is_open()){
        reinhardt_out.open(REINHARDT_OUTPUTFILE, std::ofstream::out | std::ofstream::app);
    }
    if(!other_out.is_open()){
        other_out.open(OTHER_OUTPUTFILE, std::ofstream::out | std::ofstream::app);
    }
    standard_out << current_elements_to_sort << ";" << standard[0] << ";" << standard[1] << ";" << standard[2] << std::endl;
    chen_out << current_elements_to_sort << ";" << chen[0] << ";" << chen[1] << ";" << chen[2] << std::endl;
    reinhardt_out << current_elements_to_sort << ";" << reinhardt[0] << ";" << reinhardt[1] << ";" << reinhardt[2] << std::endl;
    other_out << current_elements_to_sort << ";" << other[0] << ";" << other[1] << ";" << other[2] << std::endl;

}

void clear_files(){
    if(debug.is_open()){
        debug.close();
        debug.open(DEBUG_LOG, std::ofstream::out | std::ofstream::app);
    }else{
        debug.open(DEBUG_LOG, std::ofstream::out | std::ofstream::app);
    }
    if(!chen_out.is_open()){
        chen_out.open(CHEN_OUTPUTFILE, std::ofstream::out | std::ofstream::trunc);
    }
    if(!reinhardt_out.is_open()){
        reinhardt_out.open(REINHARDT_OUTPUTFILE, std::ofstream::out | std::ofstream::trunc);
    }
    if(!other_out.is_open()){
        other_out.open(OTHER_OUTPUTFILE, std::ofstream::out | std::ofstream::trunc);
    }
    if(!standard_out.is_open()){
        standard_out.open(STANDARD_OUTPUTFILE, std::ofstream::out | std::ofstream::trunc);
    }
}

std::array<unsigned long long, 3> compute_average(std::vector<long long> timings,
        std::vector<long long> comparisons, std::vector<long long> assignements){
    unsigned long long sum_t = 0L;
    unsigned long long sum_c = 0L;
    unsigned long long sum_a = 0L;
    if(DEBUGGING){
        if(timings.size() != comparisons.size() || comparisons.size() != assignements.size()){
            if(!debug.is_open()){
                debug.open(DEBUG_LOG);
            }
            debug << "Error: the sizes in compute_average don't match" << std::endl;
        } else if(timings.size() != current_REPETITIONS){
            if(!debug.is_open()){
                debug.open(DEBUG_LOG);
            }
            debug << "Error: seems like there is a problem with the value of current_REPETITIONS" << std::endl;
        }
    }

    for(int i = 0; i < current_REPETITIONS; i++){
        // should be big enough but we'll see
        if(DEBUGGING){
            if (sum_t + timings.at(i) < sum_t){
                if(!debug.is_open()){
                    debug.open(DEBUG_LOG);
                }
                debug << "Overflow detected: at time " << current_elements_to_sort << " Sum: " << sum_t << " + " << timings[i] << std::endl;
            }
            if (sum_c + timings.at(i) < sum_c){
                if(!debug.is_open()){
                    debug.open(DEBUG_LOG);
                }
                debug << "Overflow detected: at comparisions " << current_elements_to_sort << " Sum: " << sum_t << " + " << timings[i] << std::endl;
            }
            if (sum_a + timings.at(i) < sum_a){
                if(!debug.is_open()){
                    debug.open(DEBUG_LOG);
                }
                debug << "Overflow detected: at assignements " << current_elements_to_sort << " Sum: " << sum_t << " + " << timings[i] << std::endl;
            }
        }

        sum_t += timings.at(i);
        sum_c += comparisons.at(i);
        sum_a += assignements.at(i);
    }
    // after summing up divide by the number of current_REPETITIONS
    sum_t /= current_REPETITIONS;
    sum_c /= current_REPETITIONS;
    sum_a /= current_REPETITIONS;
    return {sum_t, sum_c, sum_a};
}


// check if the sorted list is correct return true if correct
bool check_sorted_list(std::array<std::vector<BasetypeWrapper<gen_type>>, 4> &lists){
    bool errorOccured = false;
    if(lists[0].size() != lists[1].size() || lists[0].size() != lists[2].size() || lists[0].size() != lists[3].size()){
        if (!debug.is_open()) {
            debug.open(DEBUG_LOG);
        }
        debug << "The list sizes in the compare function don`t match" << std::endl;

        std::cout << "The list sizes in the compare function don`t match" << std::endl;
        errorOccured  = true;
    }
    for(unsigned long long i = 0; i < lists[0].size(); i ++){
        if(lists[0].at(i).get_value() != lists[1].at(i).get_value()){
            if (DEBUGGING) {
                if (!debug.is_open()) {
                    debug.open(DEBUG_LOG);
                }
                debug << "Element " << i << " of Chen sorting at length " << current_elements_to_sort << " is wrong" << std::endl;
            }
            errorOccured = true;
        }
        if(lists[0].at(i).get_value() != lists[2].at(i).get_value()){
            if (DEBUGGING) {
                if (!debug.is_open()) {
                    debug.open(DEBUG_LOG);
                }
                debug << "Element " << i << " of Reinhardt sorting at length " << current_elements_to_sort
                          << " is wrong" << std::endl;
            }
            errorOccured = true;
        }
        if(lists[0].at(i).get_value() != lists[3].at(i).get_value()){
            if (DEBUGGING) {
                if (!debug.is_open()) {
                    debug.open(DEBUG_LOG);
                }
                debug << "Element " << i << " of Other sorting at length " << current_elements_to_sort
                          << " is wrong" << std::endl;
            }
            errorOccured = true;
        }
    }

    return !errorOccured;
}

int main(){
    if(DEBUGGING){
        debug.open (DEBUG_LOG);
    }

    clear_files();

    for(;current_elements_to_sort <= MAX_ELEMENTS_TO_SORT; current_elements_to_sort *= STEP_FACTOR){

        time_t seed_time;
        srand(time(&seed_time));
        if (DEBUGGING){
            std::string s = "\n Creating List of length " + std::to_string(current_elements_to_sort) + " (with seed: " +
                    std::to_string(seed_time) + ")\n";
            std::string s2 = "\n with " + std::to_string(current_REPETITIONS) + " Repetitions to be made";
            if (!debug.is_open()) {
                debug.open(DEBUG_LOG);
            }
            debug << s << s2 << std::endl;
            std::cout << s << s2 << std::endl;
        }




        for(int i = 0; i < current_REPETITIONS; i++) {
            //create int list
            std::array<std::vector<BasetypeWrapper<gen_type>>, 4> lists;
            lists[0] = createList(current_elements_to_sort, seed_time + i);
            if(MERGE_TEST){
                std::sort(lists[0].begin(), lists[0].begin()+((lists[0].end()-lists[0].begin())/2), BasetypeWrapper<gen_type>::compare);
                std::sort(lists[0].begin()+((lists[0].end()-lists[0].begin())/2), lists[0].end(), BasetypeWrapper<gen_type>::compare);
            }

            // create deep copies of the list
            lists[1] = lists[0];
            lists[2] = lists[0];
            if(MERGE_TEST){
                lists[2].resize(lists[0].size() + lists[0].size() / 4 + 1);
                std::rotate(lists[2].begin(), lists[2].begin() + lists[0].size(), lists[2].end());
            }
            lists[3] = lists[0];


            //TODO list sorting
            for(int j = 0; j < lists.size(); j++) {
                BasetypeWrapper<gen_type>::reset_c();
                BasetypeWrapper<gen_type>::reset_m();

                std::chrono::high_resolution_clock::time_point t1;
                std::chrono::high_resolution_clock::time_point t2;

                switch(j){
                    case 1:
                        if(MERGE_TEST){
                            t1 = std::chrono::high_resolution_clock::now();
                            chen::merge(lists[j].begin(),lists[j].begin()+((lists[j].end()-lists[j].begin())/2), lists[j].end(),
                                        static_cast<int>(std::sqrt(lists[j].end()-lists[j].begin())), 0, BasetypeWrapper<gen_type>::compare);
                        } else{
                            t1 = std::chrono::high_resolution_clock::now();
                            chen::mergesort_chen(lists[1].begin(), lists[1].end(), BasetypeWrapper<gen_type>::compare);
                        }
                        t2 = std::chrono::high_resolution_clock::now();
                        break;
                    case 2:
                        if(MERGE_TEST){
                            t1 = std::chrono::high_resolution_clock::now();
                            auto start_two = lists[2].begin() + lists[0].size() / 4 + 1;
                            auto start_one = start_two + lists[0].size() / 2;
                            sym_merge_gap_left(start_one, lists[2].end(), start_two, start_one, lists[2].begin(), BasetypeWrapper<gen_type>::compare);
                        } else{
                            t1 = std::chrono::high_resolution_clock::now();
                            in_place_mergesort(lists[2].begin(), lists[2].end(), BasetypeWrapper<gen_type>::compare);
                        }
                        t2 = std::chrono::high_resolution_clock::now();
                        if(MERGE_TEST){
                            lists[2].resize(lists[0].size());
                        }
                        break;
                    case 3:
                        if(MERGE_TEST){
                            t1 = std::chrono::high_resolution_clock::now();
                            huang_langston_merge::merge(lists[j].begin(),lists[j].begin()+((lists[j].end()-lists[j].begin())/2), lists[j].end(), BasetypeWrapper<gen_type>::compare);
                        } else{
                            t1 = std::chrono::high_resolution_clock::now();
                            huang_langston_merge::mergesort(lists[3].begin(), lists[3].end(), BasetypeWrapper<gen_type>::compare);
                        }
                        t2 = std::chrono::high_resolution_clock::now();
                        break;
                    default:
                        if(MERGE_TEST){
                            t1 = std::chrono::high_resolution_clock::now();
                            std::inplace_merge(lists[j].begin(),lists[j].begin()+((lists[j].end()-lists[j].begin())/2), lists[j].end(), BasetypeWrapper<gen_type>::compare);
                        } else{
                            t1 = std::chrono::high_resolution_clock::now();
                            std::stable_sort(lists[j].begin(), lists[j].end(), BasetypeWrapper<gen_type>::compare);
                        }
                        t2 = std::chrono::high_resolution_clock::now();

                }

                comparisons[j].emplace_back(BasetypeWrapper<gen_type>::get_c());
                assignments[j].emplace_back(BasetypeWrapper<gen_type>::get_m());
                timings[j].emplace_back(std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count());



            }



            // testing resulting lists
            bool valid = check_sorted_list(lists);
            if(!valid){
                std::cout << "Wrong order for size " << current_elements_to_sort << std::endl;
            }
        }

        std::array<unsigned long long, 3> standard = compute_average(timings[0], comparisons[0], assignments[0]);
        std::array<unsigned long long, 3> chen = compute_average(timings[1], comparisons[1], assignments[1]);
        std::array<unsigned long long, 3> reinhardt = compute_average(timings[2], comparisons[2], assignments[2]);
        std::array<unsigned long long, 3> other = compute_average(timings[3], comparisons[3], assignments[3]);

        outputdata(standard, chen, reinhardt, other);

        // compute the number of repetitions that should be made
        current_REPETITIONS *= (current_REPETITIONS * REPETITION_FACTOR >= MIN_REPETITIONS)? REPETITION_FACTOR: 1.f;
        reset();
    }



    if(DEBUGGING){
        if (debug.is_open()) {
            debug.close();
        }
    }

    return 0;
}