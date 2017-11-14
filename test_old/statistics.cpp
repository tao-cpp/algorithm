// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


// #include <iterator>
#include <array>
#include <forward_list>
#include <list>
#include <vector>


#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// #include <tao/algorithm.hpp>
#include <tao/algorithm/statistics.hpp>

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
    vector<int> c1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    auto sv1 = sample_variance_n(begin(c1), tao::algorithm::size(c1));
    REQUIRE(sv1 == Approx(9.1667));
    // http://www.wolframalpha.com/input/?i=variance+%7B1,+2,+3,+4,+5,+6,+7,+8,+9,+10%7D

    vector<int> c2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto sv2 = sample_variance_n(begin(c2), tao::algorithm::size(c2));
    REQUIRE(sv2 == Approx(7.5000));
    // http://www.wolframalpha.com/input/?i=variance+%7B1,+2,+3,+4,+5,+6,+7,+8,+9%7D

    vector<double> c4 = { 1, 2, 3, 4, 5.5, 6, 7, 8, 9, 10 };
    auto sv4 = sample_variance_n(begin(c4), tao::algorithm::size(c4));
    REQUIRE(sv4 == Approx(9.13611));
    // http://www.wolframalpha.com/input/?i=variance+%7B1,+2,+3,+4,+5.5,+6,+7,+8,+9,+10%7D
}

TEST_CASE("population variance", "population variance") {
    vector<int> c1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    auto pv1 = population_variance_n(begin(c1), tao::algorithm::size(c1));
    REQUIRE(pv1 == Approx(8.2500));
    // http://www.wolframalpha.com/input/?i=variance+%7B1,+2,+3,+4,+5,+6,+7,+8,+9,+10%7D&rawformassumption=%7B%22C%22,+%22variance%22%7D+-%3E+%7B%22PopulationVariance%22%7D&rawformassumption=%7B%22MC%22,%22%22%7D-%3E%7B%22Formula%22%7D

    vector<int> c2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto pv2 = population_variance_n(begin(c2), tao::algorithm::size(c2));
    REQUIRE(pv2 == Approx(6.6667));
    // http://www.wolframalpha.com/input/?i=variance+%7B1,+2,+3,+4,+5,+6,+7,+8,+9%7D&rawformassumption=%7B%22C%22,+%22variance%22%7D+-%3E+%7B%22PopulationVariance%22%7D&rawformassumption=%7B%22MC%22,%22%22%7D-%3E%7B%22Formula%22%7D

    vector<double> c4 = { 1, 2, 3, 4, 5.5, 6, 7, 8, 9, 10 };
    auto pv4 = population_variance_n(begin(c4), tao::algorithm::size(c4));
    REQUIRE(pv4 == Approx(8.2225));
    // http://www.wolframalpha.com/input/?i=variance+%7B1,+2,+3,+4,+5.5,+6,+7,+8,+9,+10%7D&rawformassumption=%7B%22C%22,+%22variance%22%7D+-%3E+%7B%22PopulationVariance%22%7D&rawformassumption=%7B%22MC%22,%22%22%7D-%3E%7B%22Formula%22%7D
}

TEST_CASE("sample standard deviation", "sample standard deviation") {
    vector<int> c1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    auto ssd1 = sample_std_dev_n(begin(c1), tao::algorithm::size(c1));
    REQUIRE(ssd1 == Approx(3.02765035409749));
    // http://www.wolframalpha.com/input/?i=stddev+%7B1,+2,+3,+4,+5,+6,+7,+8,+9,+10%7D

    vector<int> c2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto ssd2 = sample_std_dev_n(begin(c2), tao::algorithm::size(c2));
    REQUIRE(ssd2 == Approx(2.7386));
    // http://www.wolframalpha.com/input/?i=stddev+%7B1,+2,+3,+4,+5,+6,+7,+8,+9%7D

    vector<double> c4 = { 1, 2, 3, 4, 5.5, 6, 7, 8, 9, 10 };
    auto ssd4 = sample_std_dev_n(begin(c4), tao::algorithm::size(c4));
    REQUIRE(ssd4 == Approx(3.0226));
    // http://www.wolframalpha.com/input/?i=stddev+%7B1,+2,+3,+4,+5.5,+6,+7,+8,+9,+10%7D
}

TEST_CASE("population standard deviation", "population standard deviation") {
    vector<int> c1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    auto psd1 = population_std_dev_n(begin(c1), tao::algorithm::size(c1));
    REQUIRE(psd1 == Approx(2.8723));
    // http://www.wolframalpha.com/input/?i=stddev+%7B1,+2,+3,+4,+5,+6,+7,+8,+9,+10%7D&rawformassumption=%7B%22C%22,+%22stddev%22%7D+-%3E+%7B%22PopulationStandardDeviation%22%7D&rawformassumption=%7B%22MC%22,%22%22%7D-%3E%7B%22Formula%22%7D

    vector<int> c2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto psd2 = population_std_dev_n(begin(c2), tao::algorithm::size(c2));
    REQUIRE(psd2 == Approx(2.5820));
    // http://www.wolframalpha.com/input/?i=stddev+%7B1,+2,+3,+4,+5,+6,+7,+8,+9%7D&rawformassumption=%7B%22C%22,+%22stddev%22%7D+-%3E+%7B%22PopulationStandardDeviation%22%7D&rawformassumption=%7B%22MC%22,%22%22%7D-%3E%7B%22Formula%22%7D

    vector<double> c4 = { 1, 2, 3, 4, 5.5, 6, 7, 8, 9, 10 };
    auto psd4 = population_std_dev_n(begin(c4), tao::algorithm::size(c4));
    REQUIRE(psd4 == Approx(2.86749));
    // http://www.wolframalpha.com/input/?i=stddev+%7B1,+2,+3,+4,+5.5,+6,+7,+8,+9,+10%7D&rawformassumption=%7B%22C%22,+%22stddev%22%7D+-%3E+%7B%22PopulationStandardDeviation%22%7D&rawformassumption=%7B%22MC%22,%22%22%7D-%3E%7B%22Formula%22%7D
}

TEST_CASE("get_statistics_mutate", "get_statistics_mutate") {
    vector<int> c1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    auto stats = get_statistics_mutate(c1);
    auto mean = get<0>(stats);
    auto ssd = get<1>(stats);
    auto median = get<2>(stats);

    REQUIRE(mean   == Approx(5.5));
    REQUIRE(ssd    == Approx(3.02765035409749));
    REQUIRE(median == Approx(5.5));

    //---------------------

    vector<int> c2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    stats = get_statistics_mutate(c2);
    mean = get<0>(stats);
    ssd = get<1>(stats);
    median = get<2>(stats);

    REQUIRE(mean   == Approx(5));
    REQUIRE(ssd    == Approx(2.7386));
    REQUIRE(median == Approx(5));

    //---------------------

    vector<double> c4 = { 1, 2, 3, 4, 5.5, 6, 7, 8, 9, 10 };
    stats = get_statistics_mutate(c4);
    mean = get<0>(stats);
    ssd = get<1>(stats);
    median = get<2>(stats);

    REQUIRE(mean   == Approx(5.55));
    REQUIRE(ssd    == Approx(3.0226));
    REQUIRE(median == Approx(5.75));
}


