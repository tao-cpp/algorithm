// Tao.Algorithm
//
// Copyright Fernando Pelliccioni, 2016
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <tao/algorithm.hpp>
#include <iterator>
#include <list>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("first_test", "first test example") {

    list<int> c = { 1, 2, 3, 4, 5, 6, 7, 8 };

    auto r = tao::algorithm::shift_right(std::begin(c), std::end(c), 3);


    REQUIRE(*r == 1);
    // CHECK(*r == 1);
}
