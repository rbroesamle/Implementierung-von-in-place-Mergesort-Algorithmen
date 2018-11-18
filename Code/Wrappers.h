#pragma once

#include <vector>
//Die algorithm und utility includes sind zur Einbindung von std::swap
#include <algorithm>
#include <utility>
//TODO: Das ist bisher nur ein Grundgerüst. Wenn wichtige Funktionen fehlen, nachträglich implementieren.
template<typename T>
class ArrayWrapper
{
public:
	template<typename T>
	class BasetypeWrapper
	{
	public:
		//constructors
		BasetypeWrapper() {}
		BasetypeWrapper(T xx) : x(xx) {}
		//copy constructor
		BasetypeWrapper(const BasetypeWrapper& orig) : x(orig.x) {}
		//move constructor
		BasetypeWrapper(BasetypeWrapper&& orig) {
			std::swap(x, orig.x);
		}
		~BasetypeWrapper() {}

		// copy operator 
		BasetypeWrapper& operator= (BasetypeWrapper const& other) {
			if (this != &other) {
				Vec3 tmp(other);
				std::swap(x, tmp.x);
			}
			return *this;
		}

		// move operator
		BasetypeWrapper& operator= (BasetypeWrapper&& other) {
			if (this != &other) {
				std::swap(x, other.x);
			}
			return *this;
		}

		//compare operators
		bool operator== (const int y) {
			c++;
			return (x == y);
		}

		bool operator!= (const int y) {
			c++;
			return (x != y);
		}

		bool operator<= (const int y) {
			c++;
			return (x <= y);
		}

		bool operator>= (const int y) {
			c++;
			return (x >= y);
		}

		bool operator< (const int y) {
			c++;
			return (x < y);
		}

		bool operator> (const int y) {
			c++;
			return (x > y);
		}

	private:
		T x;
	};
	// default constructor
	ArrayWrapper() {
		v = new std::vector;
		c = 0;
	}

	//copy constructor
	ArrayWrapper(const ArrayWrapper& orig) : v(orig.v) {}
	//move constructor
	ArrayWrapper(ArrayWrapper&& orig) {
		std::swap(v, orig.v);
	}
	//some other constructors
	//TODO: eventuell weitere implementieren, für arrays etc.
	ArrayWrapper(std::vector<T> orig) : v(orig) {}

	//default destructor
	~ArrayWrapper() {
		delete v;
	}
	
	std::vector<T>::Iterator end() {
		return v.end();
	}

	std::vector<T>::Iterator begin() {
		return v.begin();
	}

	//subscript operator
	T& operator[] (const int index) {
		return v[index];
	}

	//return the size of the container
	int size() {
		return v.size();
	}

	//returns comparison count 
	static int get_c() {
		return c;
	}

	//reset comparison count
	static void reset_c() {
		c = 0;
	}
private:
	std::vector<BasetypeWrapper<T>> v;
	static int c;
};