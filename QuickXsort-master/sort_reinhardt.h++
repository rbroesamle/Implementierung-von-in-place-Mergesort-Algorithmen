#include "../TestAndEvaluation/Reinhardt_Compare/inplace_mergesort_qsel.cpp"
namespace sort_reinhardt{
	template<typename Iter, typename Comp>
	void sort(Iter begin, Iter fin, Comp comp){
	    in_place_mergesort(begin, fin, comp);
	}
}