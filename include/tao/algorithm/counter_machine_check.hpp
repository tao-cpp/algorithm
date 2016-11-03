//! \file tao/algorithm/counter_machine_check.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_ALGORITHM_COUNTER_MACHINE_CHECK_HPP
#define TAO_ALGORITHM_COUNTER_MACHINE_CHECK_HPP

// #include <iterator>

#include <tao/algorithm/add_to_counter.hpp>
#include <tao/algorithm/concepts.hpp>
// #include <tao/algorithm/integers.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao { namespace algorithm {

template <Semiregular T, BinaryOperation Op, BinaryOperation OpNoCheck, std::size_t Size = 64>
//  requires Op is associative //TODO
//  requires OpNoCheck is associative //TODO
    requires(Domain<Op> == T && Domain<Op> == Domain<OpNoCheck>) //TODO...
struct counter_machine_check {
    counter_machine_check(Op op, OpNoCheck op_nocheck, T const& e)
        : op(op), op_nocheck(op_nocheck), e(e), l(f)
    {}

    counter_machine_check(counter_machine_check const&) = delete;
    counter_machine_check& operator=(counter_machine_check const&) = delete;
    
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

    void add_to(T x, T* to) {
        // precondition: TODO
        x = add_to_counter(to, l, op_nocheck, x, e);
        if (x != e) {
            *l = x;
            ++l;
        }
    }

    Op op;
    const OpNoCheck op_nocheck;
    const T e;
    T f[Size];
    T* l;
};

}} /*tao::algorithm*/

#endif /*TAO_ALGORITHM_COUNTER_MACHINE_CHECK_HPP*/

