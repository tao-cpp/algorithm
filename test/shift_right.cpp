// Tao.Algorithm
//
// Copyright Fernando Pelliccioni, 2016
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <tao/algorithm.hpp>
#include <iterator>

#include <forward_list>
#include <list>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;
using namespace tao::algorithm;

template <Iterator I, Integral N>
void check(I first, I last, N n, ValueType<I> const& expected_value) {
    auto m = shift_right(first, last, n);
    REQUIRE(*m == expected_value);
    REQUIRE(&*m == &*next(first, n));
}

TEST_CASE("shift_right_forward", "shift_right on ForwardIterator's") {

    forward_list<int> c = { 1, 2, 3, 4, 5, 6, 7, 8 };

    check(begin(c), end(c), 0, 1);
    check(begin(c), end(c), 1, 1);
    check(begin(c), end(c), 2, 1);
    check(begin(c), end(c), 3, 1);
    check(begin(c), end(c), 4, 1);
    check(begin(c), end(c), 5, 1);
    check(begin(c), end(c), 6, 1);
    check(begin(c), end(c), 7, 1);
    check(begin(c), end(c), 8, 1);



    // auto r = shift_right(begin(c), end(c), 0);
    // REQUIRE(*r == 1);
    // REQUIRE(&*r == &*begin(c));

    // r = shift_right(begin(c), end(c), 1);
    // REQUIRE(*r == 1);
    // REQUIRE(&*r == &*next(begin(c), 1));

    // r = shift_right(begin(c), end(c), 2);
    // REQUIRE(*r == 1);
    // REQUIRE(&*r == &*next(begin(c), 2));

    // r = shift_right(begin(c), end(c), 3);
    // REQUIRE(*r == 1);
    // REQUIRE(&*r == &*next(begin(c), 3));

    // r = shift_right(begin(c), end(c), 3);
    // REQUIRE(*r == 1);
    // REQUIRE(&*r == &*next(begin(c), 3));

    // r = shift_right(begin(c), end(c), 3);
    // REQUIRE(*r == 1);
    // REQUIRE(&*r == &*next(begin(c), 3));

    // r = shift_right(begin(c), end(c), 3);
    // REQUIRE(*r == 1);
    // REQUIRE(&*r == &*next(begin(c), 3));

    // r = shift_right(begin(c), end(c), 3);
    // REQUIRE(*r == 1);
    // REQUIRE(&*r == &*next(begin(c), 3));

    // r = shift_right(begin(c), end(c), 3);
    // REQUIRE(*r == 1);
    // REQUIRE(&*r == &*next(begin(c), 3));

    // r = shift_right(begin(c), end(c), 3);
    // REQUIRE(*r == 1);
    // REQUIRE(&*r == &*next(begin(c), 3));

    // CHECK(*r == 1);
}


TEST_CASE("shift_right_bidirectional", "shift_right on BidirectionalIterator's") {

    list<int> c = { 1, 2, 3, 4, 5, 6, 7, 8 };

    auto r = shift_right(begin(c), end(c), 3);

    REQUIRE(*r == 1);
    // CHECK(*r == 1);
}

