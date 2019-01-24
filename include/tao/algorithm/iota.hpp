//! \file tao/algorithm/iota.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016-2019
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_ALGORITHM_IOTA_HPP_
#define TAO_ALGORITHM_SHIFT_HPP_

// #include <algorithm>
// #include <iterator>
// #include <utility>
// #include <iostream>
#include <random>


#include <tao/algorithm/concepts.hpp>
// #include <tao/algorithm/copy.hpp>
#include <tao/algorithm/iterator.hpp>
// #include <tao/algorithm/swap.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao { namespace algorithm {


// -----------------------------------------------------------------
// shift_right_by_one
// -----------------------------------------------------------------

template <ForwardIterator I> 
    requires(Writable<I>)
// DistanceType<I> iota(I f, I l, DistanceType<I> start = DistanceType<I>(0), DistanceType<I> step = DistanceType<I>(1)) {
DistanceType<I> iota(I f, I l, DistanceType<I> start, DistanceType<I> step) {
    //precondition: writable_bounded_range(f, l)
    using T = ValueType<I>;
    while (f != l) {
        *f = T(start);
        start += step;
        ++f;
    }
    return start;
}

template <ForwardIterator I> 
    requires(Writable<I>)
inline
DistanceType<I> iota(I f, I l) {
    using T = ValueType<I>;
    return iota(f, l, T(0), T(1));
}

template <RandomAccessIterator I>
    requires(Writable<I>)
void random_iota(I f, I l) {
    iota(f, l);
    // std::random_shuffle(f, l);
    std::random_device rd;
    std::mt19937 g(rd());
 
    std::shuffle(f, l, g);    
}

template <BidirectionalIterator I>
    requires(Writable<I>)
void reverse_iota(I f, I l) {
    iota(f, l);
    std::reverse(f, l);
}


// //Complexity: 
// //      Runtime:
// //          Amortized: O(n)
// //          Exact:     2 * n - 1 assigments (move or copy)
// //      Space:
// //          O(1)
// template <ForwardIterator I>
//     requires(Mutable<I>)
// void shift_right_by_one(I f, I l, std::forward_iterator_tag) {
//     //precondition: mutable_bounded_range(f, l)
//     if (f == l) return;

//     ValueType<I> a = std::move(*f++);
//     ValueType<I> b;
//     while (f != l) {
//         shift_three(b, *f++, a);
//         if (f == l) return;
//         shift_three(a, *f++, b);
//     }
// }



// template <Iterator I>
// inline
// I successor(I x) { return ++x; }

// template <BidirectionalIterator I>
// inline
// I predecessor(I x) { return --x; }

template <RandomAccessIterator I, Integral N>
inline
I successor(I x, N n, std::random_access_iterator_tag) { 
    return x + n;
}

template <Iterator I, Integral N>
inline
I successor(I x, N n, std::input_iterator_tag) { 
    while (n != N(0)) {
        ++x;
        --n;
    }
    return x;
}

template <Iterator I, Integral N>
inline
I successor(I x, N n) {
    typedef typename std::iterator_traits<I>::iterator_category C;
    return successor(x, n, C());
}

template <BidirectionalIterator I>
void hill(I first, I last) {
    I middle = successor(first, std::distance(first, last)/2);
    tao::algorithm::iota(first, middle);
    tao::algorithm::reverse_iota(middle, last);
}

template <BidirectionalIterator I>
void valley(I first, I last) {
    I middle = successor(first, std::distance(first, last)/2);
    tao::algorithm::reverse_iota(first, middle);
    tao::algorithm::iota(middle, last);
}


}} /*tao::algorithm*/

#endif /*TAO_ALGORITHM_IOTA_HPP_*/


#ifdef DOCTEST_LIBRARY_INCLUDED

#include <tao/benchmark/instrumented.hpp>

using namespace std;
using namespace tao::algorithm;

TEST_CASE("[shift] testing shift_right_by_one 0 elements random access") {
    using T = int;
    vector<T> a;
    shift_right_by_one(begin(a), end(a));
    CHECK(a == vector<T>());
}

#endif /*DOCTEST_LIBRARY_INCLUDED*/
