#include "../TestAndEvaluation/huang_langston_merge.h"
namespace sort_huang{
	template<typename Iter, typename Comp>
	void sort(Iter begin, Iter fin, Comp comp){
	    huang_langston_merge::mergesort(begin, fin, comp);
	}
}