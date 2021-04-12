//! \file tao/algorithm/copy.hpp
// Tao.Algorithm
//
// Copyright (c) 2016-2021 Fernando Pelliccioni.
//
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TAO_ALGORITHM_COPY_HPP_
#define TAO_ALGORITHM_COPY_HPP_

#include <algorithm>
#include <iterator>
#include <utility>

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/integers.hpp>
#include <tao/algorithm/swap.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao { namespace algorithm {

template <Iterator I, Iterator O>
    requires(Readable<I> && Writable<O> && SameValueType<I, O>)
void copy_step(I& f, O& o) {
    //precondition: source(f) and sink(o) are defined
    *o++ = *f++;
}

template <Iterator I, Iterator O>
    requires(Readable<I> && Writable<O> && SameValueType<I, O>)
void move_step(I& f, O& o) {
    //precondition: source(f) and sink(o) are defined
    *o++ = std::move(*f++);
}

template <BidirectionalIterator I, BidirectionalIterator O>
    requires(Readable<I> && Writable<O> &&  ValueType<I> == ValueType<O>)
void copy_backward_step(I& l_i, O& l_o) {
    // precondition: source(predecessor(l_i)) and sink(predecessor(l_o)) are defined
    --l_i;
    --l_o;
    *l_o = *l_i;

    //l_i = predecessor(l_i);
    //l_o = predecessor(l_o);
    // sink(l_o) = source(l_i);
}

template <BidirectionalIterator I, BidirectionalIterator O>
    requires(Readable<I> && Writable<O> &&  ValueType<I> == ValueType<O>)
void move_backward_step(I& l_i, O& l_o) {
    // precondition: source(predecessor(l_i)) and sink(predecessor(l_o)) are defined
    --l_i;
    --l_o;
    *l_o = std::move(*l_i);
}

template <Integer N>
bool count_down(N& n) {
    //precondition: n >= 0
    if (zero(n)) return false;
    --n;        //n = predecessor(n);
    return true;
}

template <Iterator I, Iterator O>
    requires(Readable<I> && Writable<O> && SameValueType<I, O>)
O copy(I f, I l, O o) {
    //precondition: not_overlapped_forward(f, l, o, next(o, distance(f, l)))
    while (f != l) copy_step(f, o);
    return o;
}

template <Iterator I, Iterator O, Integer N>
    requires(Readable<I> && Writable<O> && SameValueType<I, O>)
std::pair<I, O> copy_n(I f, N n, O o) {
    //precondition: not_overlapped_forward(f, next(f, n), o, next(o, n))
    while (count_down(n)) copy_step(f, o);
    return {f, o};
}

template <Iterator I, Iterator O>
    requires(Readable<I> && Writable<O> && SameValueType<I, O>)
O move(I f, I l, O o) {
    //precondition: not_overlapped_forward(f, l, o, next(o, distance(f, l)))
    while (f != l) move_step(f, o);
    return o;
}

template <Iterator I, Iterator O, Integer N>
    requires(Readable<I> && Writable<O> && SameValueType<I, O>)
std::pair<I, O> move_n(I f, N n, O o) {
    //precondition: not_overlapped_forward(f, next(f, n), o, next(o, n))
    while (count_down(n)) move_step(f, o);
    return {f, o};
}


// -----------------------------------------------------------------
// copy_backward and copy_backward_n
// -----------------------------------------------------------------

//Complexity:
//      Runtime:
//          Amortized: O(n)
//          Exact:     ????
//      Space:
//          O(1)
template <BidirectionalIterator I, BidirectionalIterator O>
    requires(Readable<I> && Writable<O> && ValueType<I> == ValueType<O>)
O copy_backward(I f_i, I l_i, O l_o) {
    //precondition: not_overlapped_backward(f_i, l_i, l_o-(l_i-f_i), l_o)
    while (f_i != l_i) copy_backward_step(l_i, l_o);
    return l_o;
}

//Complexity:
//      Runtime:
//          Amortized: O(n)
//          Exact:     ????
//      Space:
//          O(1)
template <BidirectionalIterator I, BidirectionalIterator O>
    requires(Readable<I> && Writable<O> && ValueType<I> == ValueType<O>)
std::pair<I, O> copy_backward_n(I l_i, DistanceType<I> n, O l_o) {
    while (count_down(n)) copy_backward_step(l_i, l_o);
    return {l_i, l_o};
}

// -----------------------------------------------------------------
// move_backward and move_backward_n
// -----------------------------------------------------------------

//Complexity:
//      Runtime:
//          Amortized: O(n)
//          Exact:     ????
//      Space:
//          O(1)
template <BidirectionalIterator I, BidirectionalIterator O>
    requires(Readable<I> && Writable<O> && ValueType<I> == ValueType<O>)
O move_backward(I f_i, I l_i, O l_o) {
    //precondition: not_overlapped_backward(f_i, l_i, l_o-(l_i-f_i), l_o)
    while (f_i != l_i) move_backward_step(l_i, l_o);
    return l_o;
}

//Complexity:
//      Runtime:
//          Amortized: O(n)
//          Exact:     ????
//      Space:
//          O(1)
template <BidirectionalIterator I, BidirectionalIterator O>
    requires(Readable<I> && Writable<O> && ValueType<I> == ValueType<O>)
std::pair<I, O> move_backward_n(I l_i, DistanceType<I> n, O l_o) {
    while (count_down(n)) move_backward_step(l_i, l_o);
    return {l_i, l_o};
}


}} /*tao::algorithm*/

#endif /*TAO_ALGORITHM_COPY_HPP_*/


#ifdef DOCTEST_LIBRARY_INCLUDED

#include <iterator>
#include <forward_list>
#include <list>
#include <vector>

#include <tao/benchmark/instrumented.hpp>

using namespace std;
using namespace tao::algorithm;

// TEST_CASE("[shift] testing shift_right_by_one 0 elements random access") {
//     using T = int;
//     vector<T> a;
//     shift_right_by_one(begin(a), end(a));
//     CHECK(a == vector<T>());
// }

#endif /*DOCTEST_LIBRARY_INCLUDED*/
