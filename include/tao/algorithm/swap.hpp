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
