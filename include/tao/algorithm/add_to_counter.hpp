//! \file tao/algorithm/add_to_counter.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_ALGORITHM_ADD_TO_COUNTER_MACHINE_HPP
#define TAO_ALGORITHM_ADD_TO_COUNTER_MACHINE_HPP

// #include <iterator>

#include <tao/algorithm/concepts.hpp>
// #include <tao/algorithm/integers.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao { namespace algorithm {

template <ForwardIterator I, BinaryOperation Op>
//  TODO: requires Op is associative
    requires(Mutable<I> && ValueType<I> == Domain<Op>) 
ValueType<I> add_to_counter(I f, I l, Op op, ValueType<I> x, ValueType<I> const& e) {
    // precondition: x != e
    while (f != l) {
        if (*f == e) {
            *f = x;
            return e;
        }
        x = op(*f, x);
        *f = e;
        ++f;
    }
    return x;
}

}} /*tao::algorithm*/

#endif /*TAO_ALGORITHM_ADD_TO_COUNTER_MACHINE_HPP*/

