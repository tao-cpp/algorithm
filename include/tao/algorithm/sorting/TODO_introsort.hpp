//! \file tao/algorithm/sorting/merge_sort.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016-2019
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// C++ Standard used: C++17

#ifndef TAO_ALGORITHM_SORTING_MERGE_SORT_HPP_
#define TAO_ALGORITHM_SORTING_MERGE_SORT_HPP_

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/type_attributes.hpp>
#include <tao/algorithm/iterator.hpp>
#include <tao/algorithm/rotate_one.hpp>

namespace tao { namespace algorithm {

}} /*tao::algorithm*/

#include <tao/algorithm/concepts_undef.hpp>

#endif /*TAO_ALGORITHM_SORTING_MERGE_SORT_HPP_*/

#ifdef DOCTEST_LIBRARY_INCLUDED

#include <tao/benchmark/instrumented.hpp>

TEST_CASE("[merge_sort] testing merge_sort_binary 6 elements random access sorted") {
    using T = int;
    vector<T> a = {1, 2, 3, 4, 5, 6};
    merge_sort_binary(begin(a), end(a), std::less<>());
    CHECK(a == vector<T>{1, 2, 3, 4, 5, 6});
}

TEST_CASE("[merge_sort] testing merge_sort_binary 6 elements random access reverse") {
    using T = int;
    vector<T> a = {6, 5, 4, 3, 2, 1};
    merge_sort_binary(begin(a), end(a), std::less<>());
    CHECK(a == vector<T>{1, 2, 3, 4, 5, 6});
}

TEST_CASE("[merge_sort] testing merge_sort_binary 6 elements random access random") {
    using T = int;
    vector<T> a = {3, 6, 2, 1, 4, 5};
    merge_sort_binary(begin(a), end(a), std::less<>());
    CHECK(a == vector<T>{1, 2, 3, 4, 5, 6});
}

TEST_CASE("[merge_sort] testing merge_sort_binary_n 6 elements random access sorted") {
    using T = int;
    vector<T> a = {1, 2, 3, 4, 5, 6};
    merge_sort_binary_n(begin(a), a.size(), std::less<>());
    CHECK(a == vector<T>{1, 2, 3, 4, 5, 6});
}

TEST_CASE("[merge_sort] testing merge_sort_binary_n 6 elements random access reverse") {
    using T = int;
    vector<T> a = {6, 5, 4, 3, 2, 1};
    merge_sort_binary_n(begin(a), a.size(), std::less<>());
    CHECK(a == vector<T>{1, 2, 3, 4, 5, 6});
}

TEST_CASE("[merge_sort] testing merge_sort_binary_n 6 elements random access random") {
    using T = int;
    vector<T> a = {3, 6, 2, 1, 4, 5};
    merge_sort_binary_n(begin(a), a.size(), std::less<>());
    CHECK(a == vector<T>{1, 2, 3, 4, 5, 6});
}

TEST_CASE("[merge_sort] testing merge_sort_binary instrumented random access") {
    using T = instrumented<int>;
    vector<T> a = {1, 2, 3, 4, 5, 6};

    instrumented<int>::initialize(0);
    merge_sort_binary(begin(a), end(a), std::less<>());

    double* count_p = instrumented<int>::counts;
    CHECK(count_p[instrumented_base::comparison] <= std::pow(a.size(), 2)); //insertion sort worst case
}

TEST_CASE("[merge_sort] testing merge_sort_binary instrumented bidirectional") {
    using T = instrumented<int>;
    list<T> a = {1, 2, 3, 4, 5, 6};

    instrumented<int>::initialize(0);
    merge_sort_binary(begin(a), end(a), std::less<>());

    double* count_p = instrumented<int>::counts;
    CHECK(count_p[instrumented_base::comparison] <= std::pow(a.size(), 2)); //insertion sort worst case
}

TEST_CASE("[merge_sort] testing merge_sort_binary instrumented forward") {
    using T = instrumented<int>;
    forward_list<T> a = {1, 2, 3, 4, 5, 6};
    auto n = distance(begin(a), end(a));

    instrumented<int>::initialize(0);
    merge_sort_binary(begin(a), end(a), std::less<>());

    double* count_p = instrumented<int>::counts;
    CHECK(count_p[instrumented_base::comparison] <= std::pow(n, 2)); //insertion sort worst case
}


// using random_eng_t = random_int_generator<int32_t>;
// random_eng_t eng;
// auto data_random_access = random_container_creator<std::vector>(array_size, eng);


#endif /*DOCTEST_LIBRARY_INCLUDED*/
