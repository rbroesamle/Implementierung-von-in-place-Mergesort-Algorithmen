//
// Created by Patrick on 29.11.2018.
//
#include <algorithm>
#include <utility>

template<typename T>
class BasetypeWrapper
{
private:
    //Value
    T x;
    static unsigned long long c;
    static unsigned long long m;

public:
    //constructors
    BasetypeWrapper() {}
    BasetypeWrapper(T xx) : x(xx) {}
    //copy constructor
    BasetypeWrapper(const BasetypeWrapper& orig) : x(orig.x) {
    }
    //move constructor
    BasetypeWrapper(BasetypeWrapper&& orig) {
        std::swap(x, orig.x);
    }
    //destructor
    ~BasetypeWrapper() {}

    // copy operator
    BasetypeWrapper& operator= (BasetypeWrapper const& other) {
        if (this != &other) {
            BasetypeWrapper tmp(other);
            std::swap(x, tmp.x);
        }
        m++;
        return *this;
    }

    // move operator
    BasetypeWrapper& operator= (BasetypeWrapper&& other) {
        if (this != &other) {
            std::swap(x, other.x);
        }
        m++;
        return *this;
    }

    //compare operators for Type T
    bool operator== (const T &y) const {
        c++;
        return (x == y);
    }

    bool operator!= (const T &y) const {
        c++;
        return (x != y);
    }

    bool operator<= (const T &y) const {
        c++;
        return (x <= y);
    }

    bool operator>= (const T &y) const {
        c++;
        return (x >= y);
    }

    bool operator< (const T &y) const {
        c++;
        return (x < y);
    }

    bool operator> (const T &y) const {
        c++;
        return (x > y);
    }

    //compare operators for other Wrapper.

    bool operator== (const BasetypeWrapper<T> &y) const {
        c++;
        return (x == y.x);
    }

    bool operator!= (const BasetypeWrapper<T> &y) const {
        c++;
        return (x != y.x);
    }

    bool operator<= (const BasetypeWrapper<T> &y) const {
        c++;
        return (x <= y.x);
    }

    bool operator>= (const BasetypeWrapper<T> &y) const {
        c++;
        return (x >= y.x);
    }

    bool operator< (const BasetypeWrapper<T> &y) const {
        c++;
        return (x < y.x);
    }

    bool operator> (const BasetypeWrapper<T> &y) const {
        c++;
        return (x > y.x);
    }

    static bool compare(BasetypeWrapper<T> x, BasetypeWrapper<T> y){
        return x < y;
    }

    //returns actual value
    T get_value() {
        return x;
    }

    //returns comparison count
    static unsigned long long get_c() {
        return c;
    }

    //reset comparison count
    static void reset_c() {
        c = 0;
    }

    //returns move count
    static unsigned long long get_m() {
        return m;
    }

    //reset move count
    static void reset_m() {
        m = 0;
    }
};

template <typename T>
unsigned long long BasetypeWrapper<T>::c = 0;
template <typename T>
unsigned long long BasetypeWrapper<T>::m = 0;