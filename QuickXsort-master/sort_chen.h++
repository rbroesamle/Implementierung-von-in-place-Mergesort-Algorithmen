#include "../TestAndEvaluation/chen.h"
namespace sort_chen{
	template<typename Iter, typename Comp>
	void sort(Iter begin, Iter fin, Comp comp){
	    chen::mergesort_chen(begin, fin, comp);
	}
}