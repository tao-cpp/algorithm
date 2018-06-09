//! \file tao/algorithm/copy.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016-2018
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

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


template <Integer N>
bool count_down(N& n) {
    //precondition: n >= 0
    if (zero(n)) return false;
    --n;        //n = predecessor(n);
    return true;
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
