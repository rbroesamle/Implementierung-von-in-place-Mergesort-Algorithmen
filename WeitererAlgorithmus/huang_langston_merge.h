//
// Created by Patrick on 09.02.2019.
//
#include <cmath>
#include <algorithm>
#include "bufferMerge.h"

namespace huang_langston_merge{

    template <typename Iterator>
    void mergesort(Iterator s, Iterator e);

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
    Iterator merge_with_buffer(Iterator buffer, Iterator first_series, Iterator second_series, Iterator e){
        Iterator first = first_series, second = second_series;
        while(first != second_series && second != e){
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
        //TODO :blocksize beachten
        int block_count = ((e-s)+(blockSize-1)) / blockSize;
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
     * merges F and G using the Buffer and puts H in its final position
     */
    template<typename Iterator>
    void mergeFandG(Iterator f_start, Iterator f_end, Iterator g_start, Iterator g_end, Iterator buffer){
        int t_1 = g_start - buffer;
        Iterator s = f_start, b = buffer;
        while(f_start != f_end && g_start != g_end){
            if (*g_start < *f_start) {
                std::swap(*g_start, *buffer);
                g_start++;
            }else{
                std::swap(*f_start, *buffer);
                f_start++;
            }
            buffer++;
        }
        while(f_start!=f_end){
            std::swap(*f_start, *buffer); f_start++; buffer++;
        }
        while(g_start!=g_end){
            std::swap(*g_start, *buffer); g_start++; buffer++;
        }
        swap_blocks(s, b, t_1);
    }


    /*
     * places the sqrt(e-s) largest elements at the begin of the list, followed by the remainders of
     * the sublists
     * the case that the sublists do not meet the size requirements is handled here
     */
    template<typename Iterator>
    Iterator extract_buffer(Iterator s, Iterator m, Iterator e, int blockSize, Iterator &block_e){
        int s_1 = 1, s_2 = 1;
        for(int i = 0; i < blockSize; i++){
            if(*(e-s_2) < *(m-s_1)) s_1++; else s_2++;
        }
        s_1--, s_2--;
        int d = ((e-m) - s_2) % blockSize;
        if (d == 0 && ((m- s) - s_1)%blockSize == 0) {
            std::rotate(m, e - s_2, e);
            std::rotate(s, (m - s_1), m + s_2);
            block_e = e;
            return s;
        }
        swap_blocks(m -(s_1 + s_2), e - s_2, s_2);
        //TODO merge b and c using the buffer instead
        huang_langston_merge::mergesort(e - (s_2+d), e);
        int t_1 = (m - s) % blockSize;
        if (t_1 != 0) mergeFandG(s, s+t_1, m, m+blockSize, m-t_1);
        swap_blocks(s + t_1, m-blockSize, blockSize);
        block_e = e - (s_2+d);
        return s+t_1;
    }

    /*
     * basic merge procedure for two sublist of length (m-s) + (e-m) = n
     * each list must contain an integral multiple of sqrt(n)
     */
    template<typename Iterator>
    void inplace_merge(Iterator s, Iterator m, Iterator e){
        int blockSize = static_cast<int>(std::round(std::sqrt(e-s)));
        Iterator block_e = e;
        s = extract_buffer(s, m, e, blockSize, block_e);
        //changed e to block_e in some calls
        sort_blocks(s+blockSize, block_e, blockSize);
        Iterator second_series = find_series(s + blockSize, e, blockSize);
        Iterator first_series = merge_with_buffer(s, s+blockSize, second_series, e);
        second_series = find_series(second_series, e, blockSize);
        while (second_series != e){
            first_series = merge_with_buffer(first_series - blockSize, first_series, second_series, e);
            second_series = find_series(second_series, e, blockSize);
        }
        //TODO check if std::rotate is inplace
        std::rotate(first_series - blockSize, first_series,e);
        //TODO: replace std::sort (possibly by recursive mergesort call)
        huang_langston_merge::mergesort(e-(3*blockSize), e);
        //std::sort(e - blockSize, e);
        //std::sort(e - (2* blockSize), e - blockSize);
        //huang_langston_merge::mergesort(e - blockSize, e);
        //huang_langston_merge::mergesort(e - (2* blockSize), e - blockSize);
    }

    /*
     * standard recursive merge procedure, using normal mergesort with the rest of the list as internal buffer for
     * each left sublist and in-place merge when no buffer is available
     */
    template <typename Iterator>
    void mergesort(Iterator s, Iterator e){
        int size = e - s;
        int pivot = (size - 1) / 2;
        if(size > 50){
            bufferMerge::mergesort(s, s+pivot, s+pivot);
            huang_langston_merge::mergesort(s + pivot, e);
            huang_langston_merge::inplace_merge(s, s + pivot, e);
        } else {
            if (size > 1) {
                bufferMerge::small_insertion_sort(s, e, e);
            }
        }
    }
}
