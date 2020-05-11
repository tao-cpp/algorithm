//! \file tao/algorithm/binary_counter/add_to_counter.hpp
// Tao.Algorithm
//
// Copyright (c) 2016-2020 Fernando Pelliccioni.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TAO_ALGORITHM_BINARY_COUNTER_ADD_TO_COUNTER_HPP_
#define TAO_ALGORITHM_BINARY_COUNTER_ADD_TO_COUNTER_HPP_

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao::algorithm {

// TODO: requires associativity on Op? 
template <ForwardIterator I, BinaryOperation Op>
    requires(Mutable<I> && ValueType<I> == Domain<Op>) 
ValueType<I> add_to_counter_nonzeroes(I f, I l, Op op, ValueType<I> x, ValueType<I> const& z) {
    // precondition: x != z
    while (f != l) {
        if (*f == z) {
            *f = x;
            return z;
        }
        x = op(*f, x);
        *f = z;
        ++f;
    }
    return x;
}

template <ForwardIterator I, BinaryOperation Op>
    requires(Mutable<I> && ValueType<I> == Domain<Op>) 
ValueType<I> add_to_counter(I f, I l, Op op, ValueType<I> x, ValueType<I> const& z) {
    if (x == z) return z;
    return add_to_counter_nonzeroes(f, l, op, x, z);
}

// TODO: requires associativity on Op? 
template <ForwardIterator I, BinaryOperation Op>
    requires(Mutable<I> && ValueType<I> == Domain<Op>) 
void add_to_counter_unguarded_nonzeroes(I f, Op op, ValueType<I> x, ValueType<I> const& z) {
    // precondition: x != z
    while (true) {
        if (*f == z) {
            *f = x;
            return;
        }
        x = op(*f, x);
        *f = z;
        ++f;
    }
}

template <ForwardIterator I, BinaryOperation Op>
    requires(Mutable<I> && ValueType<I> == Domain<Op>) 
void add_to_counter_unguarded(I f, Op op, ValueType<I> x, ValueType<I> const& z) {
    if (x == z) return;
    add_to_counter_unguarded_nonzeroes(f, op, x, z);
}

} // namespace tao::algorithm

#include <tao/algorithm/concepts_undef.hpp>
#endif /* TAO_ALGORITHM_BINARY_COUNTER_ADD_TO_COUNTER_HPP_ */

