//! \file tao/algorithm/toys/palindrome.hpp
// Tao.Algorithm
//
// Copyright (c) 2016-2020 Fernando Pelliccioni.
//
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TAO_ALGORITHM_TOYS_PALINDROME_HPP_
#define TAO_ALGORITHM_TOYS_PALINDROME_HPP_

// #include <algorithm>
// #include <functional>
// #include <iterator>
// #include <utility>

#include <iostream>

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/type_attributes.hpp>
#include <tao/algorithm/integers.hpp>
#include <tao/algorithm/iterator.hpp>

namespace tao { namespace algorithm {

template <BidirectionalIterator I, Relation R, UnaryPredicate P>
	requires(Readable<I> && Domain<R, ValueType<I>> && Domain<P, ValueType<I>>)
bool palindrome_n_filter(I f, I l, DistanceType<I> n, R r, P skip) {
    //precondition: readable_bounded_range(f, l) &&
    //              distance(f, l) == n

    while (true) {
        std::tie(f, n) = successor_while_n(f, n, skip);
        if (zero(n) || one(n)) break;
        std::tie(l, n) = predecessor_while_n(--l, n, skip);
        if (zero(n) || one(n)) break;

        if ( ! r(*f, *l)) return false;
        
        ++f;
        n -= 2;
    }
    return true;
}

template <BidirectionalIterator I, Relation R>
	requires(Readable<I> && Domain<R, ValueType<I>>)
bool palindrome_n(I f, I l, DistanceType<I> n, R r) {
    //precondition: readable_bounded_range(f, l) &&
    //              distance(f, l) == n

    using N = DistanceType<I>;
    n = half(n);
    while (n-- > N(0)) {
        if ( ! r(*f++, *--l)) return false;
    }
    return true;
}

template <BidirectionalIterator I>
	requires(Readable<I>)
inline
bool palindrome_n(I f, I l, DistanceType<I> n) {
    return palindrome_n(f, l, n, std::equal_to<>{});
}

template <BidirectionalIterator I, Relation R>
	requires(Readable<I> && Domain<R, ValueType<I>>)
bool palindrome(I f, I l, R r, std::bidirectional_iterator_tag) {
    //precondition: readable_bounded_range(f, l)
    while (f != l && f != --l) {
        if ( ! r(*f++, *l)) return false;
    }
    return true;
}

template <BidirectionalIterator I>
	requires(Readable<I>)
inline
bool palindrome(I f, I l, std::bidirectional_iterator_tag) {
    //precondition: readable_bounded_range(f, l)
    return palindrome(f, l,  std::equal_to<>{}, std::bidirectional_iterator_tag{});
}

template <RandomAccessIterator I, Relation R>
	requires(Readable<I> && Domain<R, ValueType<I>>)
inline
bool palindrome(I f, I l, R r, std::random_access_iterator_tag) {
    //precondition: readable_bounded_range(f, l)
    return palindrome_n(f, l, l - f, r);
}

template <RandomAccessIterator I>
	requires(Readable<I>)
inline
bool palindrome(I f, I l, std::random_access_iterator_tag) {
    //precondition: readable_bounded_range(f, l)
    return palindrome_n(f, l, l - f);
}

template <BidirectionalIterator I, Relation R>
	requires(Readable<I> && Domain<R, ValueType<I>>)
inline
bool palindrome(I f, I l, R r) {
    //precondition: readable_bounded_range(f, l)
    return palindrome(f, l, r, IteratorCategory<I>{});
}

template <BidirectionalIterator I>
	requires(Readable<I>)
inline
bool palindrome(I f, I l) {
    //precondition: readable_bounded_range(f, l)
    return palindrome(f, l, std::equal_to<>{}, IteratorCategory<I>{});
}

//Complexity:
//  Time:   floor(n / 2) equality comparisons
//  Space:  floor(n / 2) recursive calls
template <ForwardIterator I, Relation R>
	requires(Readable<I> && Domain<R, ValueType<I>>)
std::pair<bool, I> palindrome_recursive(I f, DistanceType<I> n, R r) {
    //precondition: readable_weak_range(f, n)

    if (zero(n)) return {true, f};
    if (one(n))  return {true, ++f};

    auto ret = palindrome_recursive(std::next(f), n - 2, r);

    if ( ! ret.first) return ret;
    if ( ! r(*f, *ret.second)) return {false, ret.second};

    return {true, ++ret.second};
}

template <ForwardIterator I>
	requires(Readable<I>)
inline
std::pair<bool, I> palindrome_recursive(I f, DistanceType<I> n) {
    //precondition: readable_weak_range(f, n)
    return palindrome_recursive(f, n, std::equal_to<>{});
}

}} /*tao::algorithm*/

#endif /*TAO_ALGORITHM_TOYS_PALINDROME_HPP_*/

#ifdef DOCTEST_LIBRARY_INCLUDED

#include <iterator>
#include <forward_list>
// #include <list>
#include <vector>
#include <string>
#include <tao/benchmark/instrumented.hpp>

using namespace std;
using namespace tao::algorithm;



struct skipper {
    bool operator()(char x) const {
        if (x == ' ') return true;
        if (x == '\'') return true;
        if (x == ',') return true;
        return false;
    }
};

struct equal_to_fake {
    bool operator()(char a, char b) const {
        if (a == 'x' && b == 'y') return true;
        if (b == 'x' && a == 'y') return true;
        return a == b;
    }
};

TEST_CASE("[palindrome_n_filter]") {
    using T = int;
    string a = "";
    auto n = distance(begin(a), end(a));
    auto x = palindrome_n_filter(begin(a), end(a), n, std::equal_to<>{}, skipper{});
    CHECK(x);
}

TEST_CASE("[palindrome_n_filter]") {
    using T = int;
    string a = " ";
    auto n = distance(begin(a), end(a));
    auto x = palindrome_n_filter(begin(a), end(a), n, std::equal_to<>{}, skipper{});
    CHECK(x);
}

TEST_CASE("[palindrome_n_filter]") {
    using T = int;
    string a = "  ";
    auto n = distance(begin(a), end(a));
    auto x = palindrome_n_filter(begin(a), end(a), n, std::equal_to<>{}, skipper{});
    CHECK(x);
}

TEST_CASE("[palindrome_n_filter]") {
    using T = int;
    string a = "   ";
    auto n = distance(begin(a), end(a));
    auto x = palindrome_n_filter(begin(a), end(a), n, std::equal_to<>{}, skipper{});
    CHECK(x);
}

TEST_CASE("[palindrome_n_filter]") {
    using T = int;
    string a = " x  ";
    auto n = distance(begin(a), end(a));
    auto x = palindrome_n_filter(begin(a), end(a), n, std::equal_to<>{}, skipper{});
    CHECK(x);
}

TEST_CASE("[palindrome_n_filter]") {
    using T = int;
    string a = " xy  ";
    auto n = distance(begin(a), end(a));
    auto x = palindrome_n_filter(begin(a), end(a), n, equal_to_fake{}, skipper{});
    CHECK(x);
}

TEST_CASE("[palindrome_n_filter]") {
    using T = int;
    string a = "x  ";
    auto n = distance(begin(a), end(a));
    auto x = palindrome_n_filter(begin(a), end(a), n, equal_to_fake{}, skipper{});
    CHECK(x);
}

TEST_CASE("[palindrome_n_filter]") {
    using T = int;
    string a = "  x";
    auto n = distance(begin(a), end(a));
    auto x = palindrome_n_filter(begin(a), end(a), n, equal_to_fake{}, skipper{});
    CHECK(x);
}

TEST_CASE("[palindrome_n_filter]") {
    using T = int;
    // string a = "Madam, I'm Adam";
    string a = "madam, i'm adam";
    auto n = distance(begin(a), end(a));
    auto x = palindrome_n_filter(begin(a), end(a), n, equal_to_fake{}, skipper{});
    CHECK(x);
}


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
