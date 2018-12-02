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
    static int c;
    static int m;

public:
    //constructors
    BasetypeWrapper() {}
    BasetypeWrapper(T xx) : x(xx) {}
    //copy constructor
    BasetypeWrapper(const BasetypeWrapper& orig) : x(orig.x) {
        m++;
    }
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
        m++;
        return *this;
    }

    //compare operators for Type T
    bool operator== (const T y) {
        c++;
        return (x == y);
    }

    bool operator!= (const T y) {
        c++;
        return (x != y);
    }

    bool operator<= (const T y) {
        c++;
        return (x <= y);
    }

    bool operator>= (const T y) {
        c++;
        return (x >= y);
    }

    bool operator< (const T y) {
        c++;
        return (x < y);
    }

    bool operator> (const T y) {
        c++;
        return (x > y);
    }

    //compare operators for other Wrapper

    bool operator== (const BasetypeWrapper<T> y) {
        c++;
        return (x == y.x);
    }

    bool operator!= (const BasetypeWrapper<T> y) {
        c++;
        return (x != y.x);
    }

    bool operator<= (const BasetypeWrapper<T> y) {
        c++;
        return (x <= y.x);
    }

    bool operator>= (const BasetypeWrapper<T> y) {
        c++;
        return (x >= y.x);
    }

    bool operator< (const BasetypeWrapper<T> y) {
        c++;
        return (x < y.x);
    }

    bool operator> (const BasetypeWrapper<T> y) {
        c++;
        return (x > y.x);
    }

    //returns actual value
    T get_value() {
        return x;
    }

    //returns comparison count
    static int get_c() {
        return c;
    }

    //reset comparison count
    static void reset_c() {
        c = 0;
    }

    //returns move count
    static int get_m() {
        return m;
    }

    //reset move count
    static void reset_m() {
        m = 0;
    }
};

template <typename T>
int BasetypeWrapper<T>::c = 0;
template <typename T>
int BasetypeWrapper<T>::m = 0;