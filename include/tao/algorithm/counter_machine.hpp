//! \file tao/algorithm/counter_machine.hpp
// Tao.Algorithm
//
// Copyright (c) 2016-2020 Fernando Pelliccioni.
//
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TAO_ALGORITHM_COUNTER_MACHINE_HPP
#define TAO_ALGORITHM_COUNTER_MACHINE_HPP

// #include <iterator>

#include <tao/algorithm/binary_counter/add_to_counter.hpp>
#include <tao/algorithm/concepts.hpp>
// #include <tao/algorithm/integers.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao { namespace algorithm {

template <Semiregular T, BinaryOperation Op, std::size_t Size = 64>
//  requires Op is associative //TODO
    requires(Domain<Op> == T) //TODO...
struct counter_machine {
    counter_machine(Op op, T const& e)
        : op(op), e(e), l(f)
    {}

    counter_machine(counter_machine const&) = delete;
    counter_machine& operator=(counter_machine const&) = delete;
    
    //Move Constructor and Move Assignment Operator are deleted too
    //See http://stackoverflow.com/questions/37092864/should-i-delete-the-move-constructor-and-the-move-assignment-of-a-smart-pointer/38820178#38820178
    // and http://talesofcpp.fusionfenix.com/post-24/episode-eleven-to-kill-a-move-constructor

    void add(T x) {
        // precondition: must not be called more than 2^Size - 1 times
        x = add_to_counter(f, l, op, x, e);
        if (x != e) {
            *l = x;
            ++l;
        }
    }

    const Op op;
    const T e;
    T f[Size];
    T* l;
};

}} /*tao::algorithm*/

#endif /*TAO_ALGORITHM_COUNTER_MACHINE_HPP*/

