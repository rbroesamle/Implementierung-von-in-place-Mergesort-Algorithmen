//
// Created by Patrick on 09.02.2019.
//
#include <cmath>
#include <algorithm>
#include "bufferMerge.h"

namespace huang_langston_merge{
    template <typename Iterator, typename Compare>
    void mergesort(Iterator s, Iterator e, Compare comp);

    /*
     * swaps two blocks of equal size
     */
    template <typename Iterator, typename Compare>
    void swap_blocks(Iterator block_1, Iterator block_2, int blockSize, Compare comp){
        for (int i = 0; i < blockSize; i++){
            std::swap(block_1[i], block_2[i]);
        }
    }

    /*
     * merges two series until the first one is exhausted
     * returns the leftmost unmerged element
     */
    template <typename Iterator, typename Compare>
    Iterator merge_with_buffer(Iterator buffer, Iterator first_series, Iterator second_series, Compare comp){
        Iterator first = first_series, second = second_series;
        while(first != second_series){
            if (comp(*second, *first)){
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
    template <typename Iterator, typename Compare>
    Iterator find_series(Iterator s, Iterator e, int blockSize, Compare comp){
        //int block_count = static_cast<int>(std::round(static_cast<float>((e-s)) / static_cast<float>(blockSize)));
        int block_count = (e-s) / blockSize;
        for (int i = 1; i < block_count; i++){
            int head_distance = i * blockSize;
            if (comp(s[head_distance], s[head_distance - 1])) return s + head_distance;
        }
        return e;
    }


    /*
     * sorts the blocks, so that their tails are in nondecreasing order
     */
    template <typename Iterator, typename Compare>
    void sort_blocks(Iterator s, Iterator e, int blockSize, Compare comp){
        int tail_distance = blockSize - 1;
        //int block_count = static_cast<int>(std::round(static_cast<float>((e-s)) / static_cast<float>(blockSize)));
        int block_count = (e-s) / blockSize;
        Iterator max_head = s + ((block_count - 1) * blockSize);
        for (Iterator current =  s; current != max_head; current += blockSize){
            Iterator min = current;
            for (Iterator other = min + blockSize; other != e ; other += blockSize){
                if (comp(other[tail_distance], min[tail_distance])) min = other;
            }
            if (min != current) swap_blocks(min, current, blockSize);
        }
    }


    /*
     * places the sqrt(e-s) largest elements at the begin of the list, followed by the remainders of
     * the sublists
     */
    template <typename Iterator, typename Compare>
    void extract_buffer(Iterator s, Iterator m, Iterator e, int blockSize, Compare comp){
        int list_1_shifts = 1, list_2_shifts = 1;
        for(int i = 0; i < blockSize; i++){
            if(comp(*(e-list_2_shifts), *(m-list_1_shifts))) list_1_shifts++; else list_2_shifts++;
        }
        list_1_shifts--, list_2_shifts--;
        std::rotate(m, e - list_2_shifts,e);
        std::rotate(s, (m - list_1_shifts),m+list_2_shifts);
    }

    /*
     * basic merge procedure for two sublist of length (m-s) + (e-m) = n
     * each list must contain an integral multiple of sqrt(n)
     * Edit: At this point, the buffer has already been extracted
     */
    template <typename Iterator, typename Compare>
    void basic_inplace_merge(Iterator s, Iterator e, int blockSize, Compare comp){
        sort_blocks(s+blockSize, e, blockSize, comp);
        Iterator second_series = find_series(s + blockSize, e, blockSize, comp);
        Iterator first_series = merge_with_buffer(s, s+blockSize, second_series, comp);
        second_series = find_series(second_series, e, blockSize, comp);
        while (second_series != e){
            first_series = merge_with_buffer(first_series - blockSize, first_series, second_series, comp);
            second_series = find_series(second_series, e, blockSize, comp);
        }
        std::rotate(first_series - blockSize, first_series,e);
        //TODO: replace std::sort (possibly by recursive mergesort call)
        //chen_sort::mergesort_chen(e-blockSize, e);
        //std::sort(e - blockSize, e);
        huang_langston_merge::mergesort(e - blockSize, e, comp);
    }


    /*
     * merges F and G using the Buffer and puts H in its final position
     */
    template <typename Iterator, typename Compare>
    void mergeFandG(Iterator f_start, Iterator f_end, Iterator g_start, Iterator g_end, Iterator buffer, Compare comp){
        int t_1 = g_start - buffer;
        Iterator s = f_start, b = buffer;
        while(f_start != f_end && g_start != g_end){
            if (comp(*g_start, *f_start)) {
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
        swap_blocks(s, b, t_1, comp);
    }

    /*
     * binary search for the position in list [s...e] to insert *element
     * if the whole list is smaller than element, e is returned
     */
    template <typename Iterator, typename Compare>
    Iterator binary_search(Iterator s, Iterator e, Iterator element, Compare comp){
        Iterator pos;
        while(e-s > 1){
            pos = s + ((e-s)/2);
            if (comp(*pos, *element)) s = pos + 1; else {
                e = pos;
                if (!comp(*element, *pos)) return pos;
            }
        }
        if (comp(*s, *element)) return e; else return s;
    }

    /*
     * merges a large sorted list with a far smaller list
     * since this uses rotations, the smaller list must begin at m, with m being the position of the last element of
     * the larger sublist +1
     */
    template <typename Iterator, typename Compare>
    void block_merge_backward(Iterator s, Iterator m, Iterator e, Compare comp){
        for (int rightListSize = (e - m); rightListSize > 0; rightListSize--){
            Iterator insert_pos = binary_search(s, m, m + (rightListSize-1), comp);
            std::rotate(insert_pos, m, e);
            m = insert_pos; e = insert_pos + (rightListSize-1);
        }
    }

    /*
     * merge D and C using A and B as Buffer
     */
    template <typename Iterator, typename Compare>
    void mergeCandD(Iterator c_first, Iterator c_last, Iterator d_first, Iterator d_last, Iterator e, Compare comp){
        e--; c_first--; d_first--;
        while(d_last != d_first && c_last != c_first){
            if(comp(*d_last, *c_last)){
                std::swap(*e, *c_last);
                c_last--;
            } else {
                std::swap(*e, *d_last);
                d_last--;
            }
            e--;
        }

        while(d_last != d_first){
            std::swap(*e, *d_last);
            d_last--; e--;
        }

        while(c_last != c_first){
            std::swap(*e, *c_last);
            c_last--; e--;
        }
    }



    /*
     * merge procedure doing some preparations and then calling the basic algorithm
     * each sublist must have at least sqrt(n) elements
     */
    template <typename Iterator, typename Compare>
    void merge(Iterator s, Iterator m, Iterator e, Compare comp) {
        int blockSize = std::sqrt(e - s);
        int s_1 = 1, s_2 = 1;
        for (int i = 0; i < blockSize; i++) {
            if (comp(*(e - s_2), *(m - s_1))) s_1++; else s_2++;
        }
        s_1--, s_2--;
        int d = ((e - m) - s_2) % blockSize;
        // if both lists are integral multiples of the blocksize, just use the basic merging scheme
        if (d == 0 && ((m - s) - s_1) % blockSize == 0) {
            std::rotate(m, e - s_2, e);
            std::rotate(s, (m - s_1), m + s_2);
            basic_inplace_merge(s, e, blockSize, comp);
            return;
        }
        //TODO merge b and c using the buffer instead
        mergeCandD(m - (s_1 + s_2), m - (s_1 + 1), e - (s_2 + d), e-(s_2+1), e);
        //swap_blocks(m - (s_1 + s_2), e - s_2, s_2);
        //chen_sort::mergesort_chen(e - (s_2 + d), e);
        //std::sort(e - (s_2 + d), e);
        //huang_langston_merge::mergesort(e - (s_2 + d), e);
        int t_1 = (m - s) % blockSize;
        if (t_1 != 0) mergeFandG(s, s + t_1, m, m + blockSize, m - t_1, comp);
        swap_blocks(s + t_1, m - blockSize, blockSize, comp);
        Iterator block_e = e - (s_2 + d);
        if(e-block_e == blockSize){
            basic_inplace_merge(s+t_1, e, blockSize, comp);
        } else {
            if (e-block_e > blockSize) {
                // rotate the largest block-sized part of block E in correct block-position and merge ignoring the rest of E. merge the rest later
                std::rotate(block_e, e - blockSize, e);
                basic_inplace_merge(s + t_1, block_e + blockSize, blockSize, comp);
                block_merge_backward(s+t_1, block_e + blockSize, e, comp);
                //std::sort(s, e);
            } else {
                basic_inplace_merge(s+t_1, block_e, blockSize, comp);
                block_merge_backward(s+t_1, block_e, e, comp);
                //std::sort(s, e);
            }
        }
    }


template <typename Iterator, typename Compare>
    void mergesort(Iterator s, Iterator e, Compare comp){
        int size = e - s;
        int pivot = (size - 1) / 2;
        if(size > 50){
            bufferMerge::mergesort(s, s+pivot, s+pivot, comp);
            huang_langston_merge::mergesort(s + pivot, e, comp);
            huang_langston_merge::merge(s, s + pivot, e, comp);
        } else {
            bufferMerge::small_insertion_sort(s, e, e, comp);
            //chen_sort::mergesort_chen(s, e);
        }
    }
}