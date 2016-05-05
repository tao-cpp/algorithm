// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// #include <tao/algorithm.hpp>
#include <tao/algorithm/statistics.hpp>
#include <iterator>

#include <forward_list>
#include <list>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;
using namespace tao::algorithm;

TEST_CASE("mean_forward", "mean on ForwardIterator's") {
    forward_list<int> c = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    REQUIRE(mean_c(c) == 5.5);
}

TEST_CASE("mean_bidirectional", "mean on BidirectionalIterator's") {
    list<int> c = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    REQUIRE(mean_c(c) == 5.5);
}
