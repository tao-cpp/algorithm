//! \file tao/benchmark/instrumented.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016-2018
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_ALGORITHM_BENCHMARK_INSTRUMENTED_HPP_
#define TAO_ALGORITHM_BENCHMARK_INSTRUMENTED_HPP_

#include <cstddef>
#include <utility>

struct instrumented_base {
    enum operations {
        n, default_constructor, construction, copy_ctor, copy_assignment, move_ctor, move_assignment, destructor, equality, comparison//, swaps
    };
    static size_t const  number_ops = 10;
    static double counts[number_ops];
    static char const* counter_names[number_ops];
    static void initialize(size_t);
};


template <typename T> 
// T is Semiregular or Regular or TotallyOrdered
struct instrumented : instrumented_base {
    using value_type = T;
    T value;

    instrumented() { ++counts[default_constructor]; }

    // Conversions from T and to T:
    // explicit 
    instrumented(T const& x) : value(x) { ++counts[construction]; }

    // Semiregular:
    instrumented(instrumented const& x) : value(x.value) {
        ++counts[copy_ctor];
    }

    instrumented(instrumented&& x) : value(std::move(x.value)) {
        ++counts[move_ctor];
    }

    ~instrumented() { ++counts[destructor]; }

    instrumented& operator=(instrumented const& x) {  
        ++counts[copy_assignment];
        value = x.value;
        return *this;
    }

    instrumented& operator=(instrumented&& x) {  
        ++counts[move_assignment];
        value = std::move(x.value);
        return *this;
    }

    // Regular
    friend
    bool operator==(instrumented const& x, instrumented const& y) {
        ++counts[equality];
        return x.value == y.value;
    }

    friend
    bool operator!=(instrumented const& x, instrumented const& y) {
        return !(x == y);
    }

    // TotallyOrdered
    friend
    bool operator<(instrumented const& x, instrumented const& y) { 
        ++counts[comparison];
        return x.value < y.value;
    }

    friend
    bool operator>(instrumented const& x, instrumented const& y) {
        return y < x;
    }

    friend
    bool operator<=(instrumented const& x, instrumented const& y) {
        return !(y < x);
    }
    
    friend
    bool operator>=(instrumented const& x, instrumented const& y) {
        return !(x < y);
    } 

    // friend 
    // void swap(instrumented& a, instrumented& b) {
    //     using std::swap; 
    //     ++counts[swaps];
    //     swap(a.value, b.value);
    // }

    //Convertion Operator
    operator T() const {
        return value;
    }
};

#endif /*TAO_ALGORITHM_BENCHMARK_INSTRUMENTED_HPP_*/
