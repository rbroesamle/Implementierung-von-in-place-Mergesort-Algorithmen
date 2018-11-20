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
	template<typename B>
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
				BasetypeWrapper tmp(other);
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

		//compare operators for Type B
		bool operator== (const B y) {
			c++;
			return (x == y);
		}

		bool operator!= (const B y) {
			c++;
			return (x != y);
		}

		bool operator<= (const B y) {
			c++;
			return (x <= y);
		}

		bool operator>= (const B y) {
			c++;
			return (x >= y);
		}

		bool operator< (const B y) {
			c++;
			return (x < y);
		}

		bool operator> (const B y) {
			c++;
			return (x > y);
		}

		//compare operators for other Wrapper

		bool operator== (const BasetypeWrapper<B> y) {
			c++;
			return (x == y.x);
		}

		bool operator!= (const BasetypeWrapper<B> y) {
			c++;
			return (x != y.x);
		}

		bool operator<= (const BasetypeWrapper<B> y) {
			c++;
			return (x <= y.x);
		}

		bool operator>= (const BasetypeWrapper<B> y) {
			c++;
			return (x >= y.x);
		}

		bool operator< (const BasetypeWrapper<B> y) {
			c++;
			return (x < y.x);
		}

		bool operator> (const BasetypeWrapper<B> y) {
			c++;
			return (x > y.x);
		}

		//gibt Wert zurück
		B get_value() {
			return x;
		}

	private:
		//Value

		B x;

	};
	// default constructor
	ArrayWrapper() {}

	//copy constructor
	ArrayWrapper(const ArrayWrapper& orig) : v(orig.v) {
		std::vector<BasetypeWrapper<T>> temp = orig.v;
		std::swap(v, temp);
	}
	//move constructor
	ArrayWrapper(ArrayWrapper&& orig) {
		std::swap(v, orig.v);
	}
	//some other constructors
	//TODO: eventuell weitere implementieren, für arrays etc.
	ArrayWrapper(std::vector<BasetypeWrapper<T>> orig) : v(orig) {}

	ArrayWrapper(std::vector<T> orig) {
		v = std::vector<BasetypeWrapper<T>>
		for (int i = 0; i < orig.size(); i++) {
			v.push_back(orig[i]);
		}
	}

	//destructor
	~ArrayWrapper() {}

	// copy operator 
	ArrayWrapper<T>& operator= (ArrayWrapper<T> const& other) {
		if (this != &other) {
			ArrayWrapper<T> tmp(other);
			std::swap(x, tmp.x);
		}
		return *this;
	}

	// move operator
	ArrayWrapper<T>& operator= (ArrayWrapper<T>&& other) {
		if (this != &other) {
			std::swap(x, other.x);
		}
		return *this;
	}
	
	typename std::vector<BasetypeWrapper<T>>::iterator end() {
		return v.end();
	}

	typename std::vector<BasetypeWrapper<T>>::iterator begin() {
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

	//push operation
	void push_back(T value) {
		v.push_back(BasetypeWrapper<T>(value));
	}

private:
	std::vector<BasetypeWrapper<T>> v;
	static int c;
};