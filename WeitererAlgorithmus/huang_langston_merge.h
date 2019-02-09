//
// Created by Patrick on 09.02.2019.
//
#include <cmath>
#include <algorithm>

namespace huang_langston_merge{
    /*
     * swaps two blocks of equal size
     */
    template<typename Iterator>
    void swap_blocks(Iterator block_1, Iterator block_2, int blockSize){
        for (int i = 0; i < blockSize; i++){
            std::swap(block_1[i], block_2[i]);
        }
    }

    /*
     * merges two series until the first one is exhausted
     * returns the leftmost unmerged element
     */
    template<typename Iterator>
    Iterator merge_with_buffer(Iterator buffer, Iterator first_series, Iterator second_series){
        Iterator first = first_series, second = second_series;
        while(first != second_series){
            if (*second < *first){
                std::swap(*second, *buffer);
                second++;
            } else {
                std::swap(*first, *buffer);
                first++;
            }
            buffer++;
        }
        return second;
    }

    /*
     * returns an iterator to the start of the second series with s being the start of the first one
     */
    template<typename Iterator>
    Iterator find_series(Iterator s, Iterator e, int blockSize){
        //int block_count = static_cast<int>(std::round(static_cast<float>((e-s)) / static_cast<float>(blockSize)));
        int block_count = (e-s) / blockSize;
        for (int i = 1; i < block_count; i++){
            int head_distance = i * blockSize;
            if (s[head_distance] < s[head_distance - 1]) return s + head_distance;
        }
        return e;
    }


    /*
     * sorts the blocks, so that their tails are in nondecreasing order
     */
    template<typename Iterator>
    void sort_blocks(Iterator s, Iterator e, int blockSize){
        int tail_distance = blockSize - 1;
        //int block_count = static_cast<int>(std::round(static_cast<float>((e-s)) / static_cast<float>(blockSize)));
        int block_count = (e-s) / blockSize;
        Iterator max_head = s + ((block_count - 1) * blockSize);
        for (Iterator current =  s; current != max_head; current += blockSize){
            Iterator min = current;
            for (Iterator other = min + blockSize; other != e ; other += blockSize){
                if (other[tail_distance] < min[tail_distance]) min = other;
            }
            if (min != current) swap_blocks(min, current, blockSize);
        }
    }


    /*
     * places the sqrt(e-s) largest elements at the begin of the list, followed by the remainders of
     * the sublists
     */
    template<typename Iterator>
    void extract_buffer(Iterator s, Iterator m, Iterator e, int blockSize){
        int list_1_shifts = 1, list_2_shifts = 1;
        for(int i = 0; i < blockSize; i++){
            if(*(e-list_2_shifts) < *(m-list_1_shifts)) list_1_shifts++; else list_2_shifts++;
        }
        list_1_shifts--, list_2_shifts--;
        std::rotate(m, e - list_2_shifts,e);
        std::rotate(s, (m - list_1_shifts),m+list_2_shifts);
    }

    /*
     * basic merge procedure for two sublist of length (m-s) + (e-m) = n
     * each list must contain an integral multiple of sqrt(n)
     */
    template<typename Iterator>
    void basic_inplace_merge(Iterator s, Iterator m, Iterator e){
        int blockSize = static_cast<int>(std::round(std::sqrt(e-s)));
        extract_buffer(s, m, e, blockSize);
        //TODO: now check if sublist remainders are integral multiples of the blocksize

        sort_blocks(s+blockSize, e, blockSize);
        Iterator second_series = find_series(s + blockSize, e, blockSize);
        Iterator first_series = merge_with_buffer(s, s+blockSize, second_series);
        second_series = find_series(second_series, e, blockSize);
        while (second_series != e){
            first_series = merge_with_buffer(first_series - blockSize, first_series, second_series);
            second_series = find_series(second_series, e, blockSize);
        }
        std::rotate(first_series - blockSize, first_series,e);
        //TODO: replace std::sort (possibly by recursive mergesort call)
        std::sort(e - blockSize, e);
    }
}
