#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <functional> // std::less
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <cmath>
//#include "quick_merge.h++"

namespace in_situ_merge {

	template <class iter, class Compare>
	inline iter median(const iter a, iter b, iter c, Compare less) {
		if (less(*b, *a))
			if (less(*c, *b))
				return b;
			else if (less(*c, *a))
				return c;
			else
				return a;
		else if (less(*c, *a))
			return a;
		else if (less(*c, *b))
			return c;
		else
			return b;
	}

	template<typename iter, typename Compare>
	void unguarded_linear_insert(iter last, Compare less) {
		using t = typename std::iterator_traits<iter>::value_type;
		t val = std::move(*last);
		iter next = last;
		--next;
		while (less(*next, val)) {
			*last = std::move(*next);
			last = next;
			--next;
		}
		*last = std::move(val);
	}

	template<typename iter, typename Compare>
	void insertion_sort(iter first, iter last, Compare less) {
		using t = typename std::iterator_traits<iter>::value_type;
		if (first == last) return;
		for (iter i = first + 1; i != last; ++i) {
			if (less(*first, *i)) {
				t	val = std::move(*i);
				std::move_backward(first, i, i + 1);
				*first = std::move(val);
			}
			else
				unguarded_linear_insert(i, less);
		}
	}

	template <class iter, class t, class Compare>
	iter unguarded_partition(iter first, iter last, t& pivot, Compare less) {
		while (true) {
			while (less(pivot, *first))
				++first;
			--last;
			while (less(*last, pivot))
				--last;
			if (!(first < last))
				return first;
			std::iter_swap(first, last);
			++first;
		}
	}

	template <class iter, class Compare>
	void nth_element(iter first, iter nth, iter last, Compare less) {
		using t = typename std::iterator_traits<iter>::value_type;
		while (last - first > 3) {
			iter i = in_situ_merge::median(first, (first + (last - first) / 2), (last - 1), less);
			t p = std::move(*i);
			iter cut = in_situ_merge::unguarded_partition(first, last, p, less);
			if (cut <= nth)
				first = cut;
			else
				last = cut;
		}
		in_situ_merge::insertion_sort(first, last, less);
	}


	template <class iter, class index, class Compare>
	void two_passes(iter a, index n, Compare less) {
		using t = typename std::iterator_traits<iter>::value_type;
		index rest = n & 3;
		iter boundary = a + n - rest;
		for (iter s = a; s < boundary; s += 4) {
			iter u = s;
			iter v = s + 1;
			iter x = s + 2;
			iter y = s + 3;
			bool c = less(*v, *u);
			iter z = u;
			u = c ? v : u;
			v = c ? z : v;
			c = less(*y, *x);
			z = x;
			x = c ? y : x;
			y = c ? z : y;
			c = less(*x, *u);
			z = u;
			u = c ? x : u;
			x = c ? z : x;
			c = less(*y, *v);
			z = v;
			v = c ? y : v;
			y = c ? z : y;
			c = less(*v, *x);
			z = x;
			x = c ? v : x;
			v = c ? z : v;
			t e1 = std::move(*u);
			t e2 = std::move(*x);
			t e3 = std::move(*v);
			t e4 = std::move(*y);
			*s = std::move(e1);
			*(s + 1) = std::move(e2);
			*(s + 2) = std::move(e3);
			*(s + 3) = std::move(e4);
		}
		std::sort(boundary, boundary + rest);
	}

	template <class iter, class index, class Compare>
	iter remaining_passes(iter a, iter b, index n, Compare less) {
		index size = 4;
		while (size < n) {
			iter p = a;
			iter o = b;
			iter r = a + n;
			iter t1 ;
			while (p + size < r) {
				t1 = p + size;
				iter t2 = (t1 + size < r) ? t1 + size : r;
				iter q = t1;
				iter z ;
				//	t x;
				while (p < t1 && q < t2) {
					if (less(*q, *p)) {
						z = q;
						++q;
					}
					else {
						z = p;
						++p;
					}
					std::iter_swap(z, o++);
				}
				while (p < t1) {
					std::iter_swap(p++, o++);
				}
				while (q < t2) {
					std::iter_swap(q++, o++);
				}
				p = t2;
			}
			while (p < r) {
				std::iter_swap(p++, o++);
			}
			size = size << 1;
			std::swap(a, b);
		}
		return a;
	}

	template <class iter, class Compare>
	void mergesort(iter p, iter r, iter t, Compare less) {
		using index = typename std::iterator_traits<iter>::difference_type;
		index const n = r - p;
		two_passes(p, n, less);
		iter q = remaining_passes(p, t, n, less);
		if (q != t) {
			while (p != r) {
				std::iter_swap(p++, t++);
			}
		}
	}

	template <class iter, class Compare>
	void sort(iter first, iter beyond, Compare less) {
		using index = typename std::iterator_traits<iter>::difference_type;
		iter r = beyond;
		iter p = first;
		index n = r - p;
		index threshold = n / ilogb(2 + n);
		while (n > threshold) {
			iter q_1 = p + n / 2;
			iter q_2 = r - n / 2;
			in_situ_merge::nth_element(p, q_1, r, less);
			mergesort(p, q_1, q_2, less);
			r = q_1;
			n = r - p;
		}
		std::sort(p, r);
	}
	template<typename T>
	void sort(std::vector<T> &v) {
		typename std::vector<T>::iterator begin = v.begin();
		typename std::vector<T>::iterator end = v.end();
		in_situ_merge::sort(begin, end, std::less<T>());
		// quicksort::qsort(begin, end, &quicksort::lomuto_optimized_partition);
	}
}
