// Tao.Algorithm
//
// Copyright (c) 2016-2021 Fernando Pelliccioni.
//
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <iterator>
#include <forward_list>
#include <list>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <tao/algorithm.hpp>

using namespace std;
using namespace tao::algorithm;

template <Iterator I, Integral N>
void check(I first, I last, N n, bool expected_empty, ValueType<I> const& expected_value) {
    auto m = shift_right(first, last, n);

    if (m == last) {
        REQUIRE(expected_empty);
    } else {
        REQUIRE(!expected_empty);
        REQUIRE((*m == expected_value));
        REQUIRE((&*m == &*next(first, n)));
    }
}

TEST_CASE("shift_right_forward", "shift_right on ForwardIterator's") {

    forward_list<int> c = { 1, 2, 3 };

    // For n < 0 or n > std::distance(first, last) it is a violation of the precondition of the function.
    // No need to check these cases

    SECTION( "for 0" ) {
        check(begin(c), end(c), 0, false, 1);
    }
    SECTION( "for 1" ) {
        check(begin(c), end(c), 1, false, 1);
    }
    SECTION( "for 2" ) {
        check(begin(c), end(c), 2, false, 1);
    }
    SECTION( "for 3" ) {
        check(begin(c), end(c), 3, true, 0);
    }

    // CHECK(*r == 1);
}

TEST_CASE("shift_right_bidirectional", "shift_right on BidirectionalIterator's") {

    list<int> c = { 1, 2, 3 };

    // For n < 0 or n > std::distance(first, last) it is a violation of the precondition of the function.
    // No need to check these cases

    SECTION( "for 0" ) {
        check(begin(c), end(c), 0, false, 1);
    }
    SECTION( "for 1" ) {
        check(begin(c), end(c), 1, false, 1);
    }
    SECTION( "for 2" ) {
        check(begin(c), end(c), 2, false, 1);
    }
    SECTION( "for 3" ) {
        check(begin(c), end(c), 3, true, 0);
    }

    // auto r = shift_right(begin(c), end(c), 3);
    // REQUIRE(*r == 1);
    // CHECK(*r == 1);
}

// #include <tao/algorithm/concepts_undef.hpp>
