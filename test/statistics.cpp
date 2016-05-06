// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// #include <tao/algorithm.hpp>
#include <tao/algorithm/statistics.hpp>
// #include <iterator>
#include <forward_list>
#include <list>
#include <vector>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;
using namespace tao::algorithm;

TEST_CASE("mean_forward", "mean on ForwardIterator's") {
    forward_list<int> c = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    
    // std::forward_list doesn't have size() member function, so doesn't meet the requirements of Container concept.
    // We can't use mean_c
    // REQUIRE(mean_c(c) == 5.5);

    REQUIRE(mean(begin(c), end(c)) == 5.5);
}

TEST_CASE("mean_bidirectional", "mean on BidirectionalIterator's") {
    list<int> c = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    REQUIRE(mean_c(c) == 5.5);
}

TEST_CASE("mean_random_access", "mean on RandomAccessIterator's") {
    vector<int> c = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    REQUIRE(mean_c(c) == 5.5);
}


TEST_CASE("median", "median") {
    vector<int> c1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    REQUIRE(median_c(c1) == 5.5);

    vector<int> c2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    REQUIRE(median_c(c2) == 5);

    vector<int> c3 = { 2, 1, 5, 4, 3, 7, 9, 8, 6 };
    REQUIRE(median_c(c3) == 5);

    vector<double> c4 = { 1, 2, 3, 4, 5.5, 6, 7, 8, 9, 10 };
    REQUIRE(median_c(c4) == 5.75);
}


TEST_CASE("sample variance", "sample variance") {
    // vector<int> c1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    // REQUIRE(sample_variance_n(c1) == 5.5);

    // vector<int> c2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    // REQUIRE(sample_variance_n(c2) == 5);

    // vector<int> c3 = { 2, 1, 5, 4, 3, 7, 9, 8, 6 };
    // REQUIRE(sample_variance_n(c3) == 5);

    vector<double> c4 = { 1, 2, 3, 4, 5.5, 6, 7, 8, 9, 10 };
    REQUIRE(sample_variance_n(c4) == 9.13611);
    REQUIRE(equal_epsilon(sample_variance_n(c4), 9.13611));

}

TEST_CASE("population variance", "population variance") {
    // vector<int> c1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    // REQUIRE(sample_variance_n(c1) == 5.5);

    // vector<int> c2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    // REQUIRE(sample_variance_n(c2) == 5);

    // vector<int> c3 = { 2, 1, 5, 4, 3, 7, 9, 8, 6 };
    // REQUIRE(sample_variance_n(c3) == 5);

    vector<double> c4 = { 1, 2, 3, 4, 5.5, 6, 7, 8, 9, 10 };
    REQUIRE(sample_variance_n(c4) == 8.2225);
    REQUIRE(equal_epsilon(sample_variance_n(c4), 8.2225));

}



// TEST_CASE("population variance", "population variance") {
//     vector<int> c1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
//     REQUIRE(median_c(c1) == 5.5);

//     vector<int> c2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//     REQUIRE(median_c(c2) == 5);

//     vector<int> c3 = { 2, 1, 5, 4, 3, 7, 9, 8, 6 };
//     REQUIRE(median_c(c3) == 5);

//     vector<double> c4 = { 1, 2, 3, 4, 5.5, 6, 7, 8, 9, 10 };
//     REQUIRE(median_c(c4) == 5.75);
// }