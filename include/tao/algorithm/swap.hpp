//! \file tao/algorithm/swap.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016-2019
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_ALGORITHM_SWAP_HPP_
#define TAO_ALGORITHM_SWAP_HPP_

#include <utility>

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao { namespace algorithm {

template <Semiregular T, Semiregular U>        //TODO(fernando): is Semiregular OK?
    requires(Same<T, U>)
inline
void shift_three(T& a, T& b, U&& c) noexcept {
    a = std::move(b);
    b = std::move(c);
}

template <ForwardIterator I1, ForwardIterator I2>
    requires(Mutable<I1> && Mutable<I1>)
I2 swap_ranges(I1 f1, I1 l1, I2 f2) {
    //precondition: mutable_bounded_range(f1, l1)
    //           && mutable_counted_range(f2, distance(f1, l1))

    while (f1 != l1) {
        std::iter_swap(f1, f2);
        ++f1;
        ++f2;
    }
    return f2;
}

template <ForwardIterator I1, ForwardIterator I2>
    requires(Mutable<I1> && Mutable<I1>)
std::pair<I1, I2> swap_ranges(I1 f1, I1 l1, I2 f2, I2 l2) {
    //precondition: mutable_bounded_range(f1, l1)
    //           && mutable_bounded_range(f2, l2)

    while (f1 != l1 && f2 != l2) {
        std::iter_swap(f1, f2);
        ++f1;
        ++f2;
    }
    return {f1, f2};
}

template <ForwardIterator I1, ForwardIterator I2>
    requires(Mutable<I1> && Mutable<I1>)
std::pair<I1, I2> swap_ranges_n(I1 f1, DistanceType<I1> n, I2 f2) {
    //precondition: mutable_counted_range(f1, n)
    //           && mutable_counted_range(f2, n)

    while (n > DistanceType<I1>(0)) {
        std::iter_swap(f1, f2);
        ++f1;
        ++f2;
        --n;
    }
    return {f1, f2};
}

}} /*tao::algorithm*/

#endif /*TAO_ALGORITHM_SWAP_HPP_*/

#ifdef DOCTEST_LIBRARY_INCLUDED

#include <iterator>
#include <iostream>
#include <tao/benchmark/instrumented.hpp>

using namespace std;
using namespace tao::algorithm;


TEST_CASE("[shift_three] testing shift_three") {
    int a = 1;
    int b = 2;
    int c = 3;

    shift_three(a, b, c);

    CHECK(a == 2);
    CHECK(b == 3);
    CHECK(c == 3);
}

TEST_CASE("[shift_three] testing shift_three const last") {
    int a = 1;
    int b = 2;
    int const c = 3;

    shift_three(a, b, c);

    CHECK(a == 2);
    CHECK(b == 3);
    CHECK(c == 3);
}

TEST_CASE("[shift_three] testing shift_three instrumented") {
    using T = instrumented<int>;

    T a = 1;
    T b = 2;
    T c = 3;

    instrumented<int>::initialize(0);
    shift_three(a, b, c);
    
    double* count_p = instrumented<int>::counts;
    CHECK(count_p[instrumented_base::copy_assignment] == 0);
    CHECK(count_p[instrumented_base::move_assignment] == 2);
}

TEST_CASE("[shift_three] testing shift_three instrumented const last") {
    using T = instrumented<int>;

    T a = 1;
    T b = 2;
    T const c = 3;

    instrumented<int>::initialize(0);
    shift_three(a, b, c);
    
    double* count_p = instrumented<int>::counts;
    CHECK(count_p[instrumented_base::copy_assignment] == 1);
    CHECK(count_p[instrumented_base::move_assignment] == 1);
}

#endif /*DOCTEST_LIBRARY_INCLUDED*/
