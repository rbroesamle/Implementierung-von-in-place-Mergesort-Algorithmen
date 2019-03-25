//
// Created by Patrick on 18.03.2019.
//
#pragma once

#include <functional>
#include <array>
#include <random>


template<int size, bool expensive_compare, int MIN_NUMBER, int MAX_NUMBER>
class Big_Type
{
private:
    //Value
    std::array<int, size> x;

public:
    //constructors
    Big_Type() {}
    Big_Type(std::array<int, size> xx) : x(xx) {}
    //copy constructor
    Big_Type(const Big_Type& orig) : x(orig.x) {
    }
    //move constructor
    Big_Type(Big_Type&& orig) {
        std::swap(x, orig.x);
    }
    Big_Type(const int& trash){
        auto rand = std::bind(std::uniform_int_distribution<int>(MIN_NUMBER,MAX_NUMBER), std::mt19937(trash + 1));
        for(auto it = x.begin(); it != x.end(); it++) {
            *it = rand();
        }
    }

    //destructor
    ~Big_Type() {}

    // copy operator
    Big_Type& operator= (Big_Type const& other) {
        if (this != &other) {
            Big_Type tmp(other);
            std::swap(x, tmp.x);
        }
        return *this;
    }

    // move operator
    Big_Type& operator= (Big_Type&& other) {
        if (this != &other) {
            std::swap(x, other.x);
        }
        return *this;
    }

    bool operator!= (const Big_Type &y) const {
        if (!expensive_compare) return (this->x[0] != y.x[0]);
        long sum_x = 0;
        long sum_y = 0;
        for(typename std::array<int, size>::const_iterator it = x.begin(); it != x.end();++it) {
            sum_x += *it;
        }
        for(auto it = y.x.begin(); it != y.x.end(); it++) {
            sum_y += *it;
        }
        sum_x /= size;
        sum_y /= size;
        return (sum_x != sum_y);
    }

    // < operator
    bool operator< (const Big_Type &y) const {
        if (!expensive_compare) return (this->x[0] < y.x[0]);
        long sum_x = 0;
        long sum_y = 0;
        for(auto it = x.begin(); it != x.end(); it++) {
            sum_x += *it;
        }
        for(auto it = y.x.begin(); it != y.x.end(); it++) {
            sum_y += *it;
        }
        sum_x /= size;
        sum_y /= size;
        return (sum_x < sum_y);
    }
};

template<typename T>
class Ptr_Type
{
private:
    //Value
    T *ptr;

public:
    //constructors
    Ptr_Type() {}

    //copy constructor
    Ptr_Type(const Ptr_Type& orig) : ptr(orig.ptr) {
    }

    Ptr_Type(const int& trash){
        ptr = new T(trash);
    }

    //destructor
    ~Ptr_Type() {}

    // copy operator
    Ptr_Type& operator= (Ptr_Type const& other) {
        if (this != &other) {
            Ptr_Type tmp(other);
            std::swap(ptr, tmp.ptr);
        }
        return *this;
    }

    // move operator
    Ptr_Type& operator= (Ptr_Type&& other) {
        if (this != &other) {
            std::swap(ptr, other.ptr);
        }
        return *this;
    }

    bool operator!= (const Ptr_Type &y) const {
        return *ptr != *(y.ptr);
    }

    // < operator
    bool operator< (const Ptr_Type &y) const {
        return *ptr < *(y.ptr);
    }
};
