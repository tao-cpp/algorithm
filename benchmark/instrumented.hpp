//! \file tao/benchmark/instrumented.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2017
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_ALGORITHM_BENCHMARK_INSTRUMENTED_HPP_
#define TAO_ALGORITHM_BENCHMARK_INSTRUMENTED_HPP_

#include <cstddef>

struct instrumented_base {
    enum operations {
        n, copy, assignment, destructor, default_constructor, equality, comparison, construction
    };
    static size_t const  number_ops = 8;
    static double counts[number_ops];
    static char const* counter_names[number_ops];
    static void initialize(size_t);
};


template <typename T> 
// T is Semiregular or Regular or TotallyOrdered
struct instrumented : instrumented_base {
    using value_type = T;
    T value;

    // Conversions from T and to T:
    explicit 
    instrumented(T const& x) : value(x) { ++counts[construction]; }

    // Semiregular:
    instrumented(instrumented const& x) : value(x.value) {
        ++counts[copy];
    }

    instrumented() { ++counts[default_constructor]; }
    ~instrumented() { ++counts[destructor]; }

    instrumented& operator=(instrumented const& x) {  
        ++counts[assignment];
        value = x.value;
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
};

#endif /*TAO_ALGORITHM_BENCHMARK_INSTRUMENTED_HPP_*/
