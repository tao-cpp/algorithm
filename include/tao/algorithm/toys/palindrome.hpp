//! \file tao/algorithm/toys/palindrome.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016-2018
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_ALGORITHM_TOYS_PALINDROME_HPP_
#define TAO_ALGORITHM_TOYS_PALINDROME_HPP_

// #include <algorithm>
// #include <functional>
// #include <iterator>
// #include <utility>

#include <iostream>

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao { namespace algorithm {

template <BidirectionalIterator I>
	requires(Readable<I>)
bool palindrome_n(I f, I l, DistanceType<I> n) {
    //precondition: readable_bounded_range(f, l) &&
    //              distance(f, l) == n

    using N = DistanceType<I>;
    n = half_nonnegative(n);
    while (n-- > N(0)) {
        if (*f++ != *--l) return false;
    }
    return true;
}

template <BidirectionalIterator I>
	requires(Readable<I>)
bool palindrome(I f, I l, std::bidirectional_iterator_tag) {
    //precondition: readable_bounded_range(f, l)
    while (f != l && f != --l) {
        if (*f++ != *l) return false;
    } 
}
template <RandomAccessIterator I>
	requires(Readable<I>)
inline
bool palindrome(I f, I l, std::random_access_iterator_tag) {
    //precondition: readable_bounded_range(f, l)
    return palindrome_n(f, l, l - f);
}

template <BidirectionalIterator I>
	requires(Readable<I>)
inline
bool palindrome(I f, I l) {
    //precondition: readable_bounded_range(f, l)
    return palindrome(f, l, IteratorCategory<I>{});
}

//Complexity:
//  Time:   floor(n / 2) equality comparisons
//  Space:  floor(n / 2) recursive calls

template <ForwardIterator I>
	requires(Readable<I>)
std::pair<bool, I> palindrome_recursive(I f, DistanceType<I> n) {
    //precondition: readable_weak_range(f, n)

    if (zero(n)) return {true, f};
    if (one(n))  return {true, ++f};

    auto r = palindrome_recursive(std::next(f), n - 2);

    if ( ! r.first) return r;
    if (*f != *r.second) return {false, r.second};

    return {true, ++r.second};
}


}} /*tao::algorithm*/

#endif /*TAO_ALGORITHM_TOYS_PALINDROME_HPP_*/


#ifdef DOCTEST_LIBRARY_INCLUDED

#include <iterator>
#include <forward_list>
// #include <list>
// #include <vector>
#include <tao/benchmark/instrumented.hpp>

using namespace std;
using namespace tao::algorithm;

TEST_CASE("[palindrome_recursive] palindrome_recursive empty range forward") {
    using T = int;
    forward_list<T> a;
    auto n = distance(begin(a), end(a));
    auto x = palindrome_recursive(begin(a), n);

    CHECK(x.first);
    // CHECK(a == vector<T>());
}

TEST_CASE("[palindrome_recursive] palindrome_recursive 1 element forward") {
    using T = int;
    forward_list<T> a = {0};
    auto n = distance(begin(a), end(a));
    auto x = palindrome_recursive(begin(a), n);

    CHECK(x.first);
}

TEST_CASE("[palindrome_recursive] palindrome_recursive 2 elements forward") {
    using T = int;
    forward_list<T> a = {0, 0};
    auto n = distance(begin(a), end(a));
    auto x = palindrome_recursive(begin(a), n);

    CHECK(x.first);
}

TEST_CASE("[palindrome_recursive] palindrome_recursive 2 elements forward, non palindrome") {
    using T = int;
    forward_list<T> a = {0, 1};
    auto n = distance(begin(a), end(a));
    auto x = palindrome_recursive(begin(a), n);

    CHECK( ! x.first);
}

TEST_CASE("[palindrome_recursive] palindrome_recursive 8 elements forward") {
    using T = int;
    forward_list<T> a = {0, 1, 2, 3, 3, 2, 1, 0};
    auto n = distance(begin(a), end(a));
    auto x = palindrome_recursive(begin(a), n);

    CHECK(x.first);
}

TEST_CASE("[palindrome_recursive] palindrome_recursive 9 elements forward") {
    using T = int;
    forward_list<T> a = {0, 1, 2, 3, 4, 3, 2, 1, 0};
    auto n = distance(begin(a), end(a));
    auto x = palindrome_recursive(begin(a), n);

    CHECK(x.first);
}

TEST_CASE("[palindrome_recursive] palindrome_recursive 9 elements forward") {
    using T = int;
    forward_list<T> a = {0, 1, 2, 3, 4, 3, 2, 1, 0};
    auto n = distance(begin(a), end(a));
    auto x = palindrome_recursive(begin(a), n);

    CHECK(x.first);
}

TEST_CASE("[palindrome_recursive] palindrome_recursive many elements forward") {
    using T = int;
    vector<T> a(1000000, 0);
    auto n = distance(begin(a), end(a));
    auto x = palindrome_recursive(begin(a), n);

    CHECK(x.first);
}


TEST_CASE("[palindrome_recursive] palindrome_recursive 9 elements forward, instrumented") {
    using T = instrumented<int>;
    forward_list<T> a = {0, 1, 2, 3, 4, 3, 2, 1, 0};
    auto n = distance(begin(a), end(a));
    instrumented<int>::initialize(0);
    size_t calls = 0;
    auto x = palindrome_recursive(begin(a), n);
    CHECK(x.first);

    double* count_p = instrumented<int>::counts;
    CHECK(count_p[instrumented_base::equality] == n >> 1);

    // std::cout << "equalities: " << count_p[instrumented_base::equality] << std::endl;
    // double* count_p = instrumented<int>::counts;
    // for (size_t i = 0; i < instrumented_base::number_ops; ++i) {
    //     std::cout << instrumented_base::counter_names[i] << ": " 
    //                 << count_p[i] 
    //                 << std::endl;
    // }
    // CHECK(false);
}

#endif /*DOCTEST_LIBRARY_INCLUDED*/
