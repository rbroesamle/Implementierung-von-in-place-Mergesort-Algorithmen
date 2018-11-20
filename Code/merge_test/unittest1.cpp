#include "stdafx.h"
#include "CppUnitTest.h"
#include "../naivmerge.h"
#include <random>
#include <vector>
#include <limits>
#include <algorithm>
#include "../Wrappers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace merge_test
{	
	static int c = 0;
	TEST_CLASS(UnitTest1)
	{
	public:
		bool compare (int x, int y) { c++; return (x < y); }

		TEST_METHOD(TestMethod1)
		{
			// nehme 1000 Listen zufälliger Länge (mit Grenze int_max/100000) und sortiere sie.
			// Überprüfung durch Vegleich mit durch Algorithmus der STL sortierter Liste.
			// Gebe außerdem die Anzahl der Vergleiche aus.
			int min = std::numeric_limits<int>::min();
			int max = std::numeric_limits<int>::max();
			std::random_device rd;
			std::mt19937 rng(rd());
			std::uniform_int_distribution<int> uni(min, max); 
			for (int i = 0; i < 1000; i++) {
				//ArrayWrapper<int>::reset_c();
				int length = uni(rng) / 100000;
				length = std::abs(length) + 1;
				ArrayWrapper<int> v;
				std::vector<int> u;
				for (int j = 0; j <= length; j++) {
					int t = uni(rng);
					v.push_back(t);
					u.push_back(t);
				}
				mergesort<std::vector<ArrayWrapper<int>::BasetypeWrapper<int>>::iterator>(v.begin(), v.end());
				std::sort(u.begin(), u.end());
				for (int j = 0; j <= length; j++) {
					ArrayWrapper<int>::BasetypeWrapper<int> a = u[j];
					Assert::AreEqual(a.get_value(), u[j]);
				}
				//int c = ArrayWrapper<int>::get_c();
				//std::cout << "Anzahl Vergleiche" << c << std::endl;
			}
		}
	};
}