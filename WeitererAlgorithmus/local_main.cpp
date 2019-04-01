//
// Created by Patrick on 29.12.2018.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include"huang_langston_merge.h"

int main(){
    //std::vector<int> banane = {2, 2, 2, 4, 4, 5, 5, 6, 7, 8, 8, 12, 13, 15, 16,     1, 1, 1, 2, 2, 3, 3, 5, 7, 7, 8, 9, 9, 11, 12};
    //std::vector<int> banane = {23,342, 32, 244, 24,5 ,5, 57,8 ,6,686,8 , 86,6868 ,68, 32235, 23525,5325,523345,5356,5768,856586,586585,324,3543, 244, 24325, 271328944, 3,4,56,7,7,75,4474,8,3543,534,5,3,6,2335,34,4,5,7,99,9,776,45454344,5,435,5,8,8,877,9,4535,54,755699876,3,43335};
    std::vector<int> banane = {1, 2, 3, 4, 5, 7, 8, 9, 10, 11, 12, 12, 14, 15, 16, 17, 18, 19, 20, 1, 2, 3, 4, 5, 6};
    std::vector<int> b = {15};
    std::cout << "unsortiert:" << std::endl;
    for (std::vector<int>::iterator it = banane.begin(); it != banane.end(); it++){
        std::cout << *it << " ; ";
    }
    std::cout << std::endl << *(banane.end() - 3) << std::endl;
    huang_langston_merge::block_merge_backward(banane.begin(), banane.end()-6, banane.end());
    //huang_langston_merge::extract_buffer(banane.begin(), banane.begin() + 9, banane.end(), 4);
    //huang_langston_merge::inplace_merge(banane.begin(), banane.begin() + 15, banane.end());
    //huang_langston_merge::mergesort(banane.begin(), banane.end());
    //huang_langston_merge::sort_blocks(banane.begin(), banane.end(), 4);
    //std::vector<int>::iterator it = huang_langston_merge::find_series(banane.begin()+5, banane.end(), 5);
    //huang_langston_merge::merge_with_buffer(banane.begin(), banane.begin() + 5, banane.begin() + 15);
    std::cout << std::endl;
    std::cout << "sortiert mit chen:" << std::endl;
    for (std::vector<int>::iterator it = banane.begin(); it != banane.end(); it++){
        std::cout << *it << " ; ";
    }
    std::cout << std::endl;
    return 0;
}