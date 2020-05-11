//! \file tao/algorithm/for_each.hpp
// Tao.Algorithm
//
// Copyright (c) 2016-2020 Fernando Pelliccioni.
//
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TAO_ALGORITHM_FOR_EACH_HPP_
#define TAO_ALGORITHM_FOR_EACH_HPP_

#include <algorithm>
#include <iterator>
#include <utility>

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao { namespace algorithm {

//Complexity: 
//      Runtime:
//          Amortized: O(n)
//          Exact:     ???
//      Space:
//          O(???)
template <Iterator I, Procedure Proc>
    requires(Readable<I> && Procedure<Proc> && Arity<Proc> == 1 &&
        ValueType<I> == InputType<Proc, 0>)
Proc for_each(I f, I l, Proc proc) {
    // precondition: readable_bounded_range(f, l)
    while (f != l) {
        proc(*f);
        ++f;
    }
    return proc;
}


//Note: for_each_n was added in C++17

//Complexity: 
//      Runtime:
//          Amortized: O(n)
//          Exact:     ???
//      Space:
//          O(???)
template <Iterator I, Procedure Proc>
    requires(Readable<I> && Procedure<Proc> && Arity<Proc> == 1 &&
        ValueType<I> == InputType<Proc, 0>)
std::pair<Proc, I> for_each_n(I f, DistanceType<I> n, Proc proc) {
    // precondition: readable_weak_range(f, n)
    while (n != 0) {
        --n;
        proc(*f);
        ++f;
    }
    return {proc, f};
}


}} /*tao::algorithm*/

#endif /*TAO_ALGORITHM_FOR_EACH_HPP_*/
