//! \file tao/algorithm/partition/partition.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016-2019
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_ALGORITHM_PARTITION_PARTITION_HPP_
#define TAO_ALGORITHM_PARTITION_PARTITION_HPP_

// #include <utility>
#include <functional>   //std::not_fn(), C++17

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/integers.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao { namespace algorithm {

// template <ForwardIterator I, UnaryPredicate P>
//     requires(Mutable<I> && Domain<P, ValueType<I>>)
// I partition_semistable(I f, I l, P p) {
//     //precondition:  mutable_bounded_range(f, l)
//     //postcondition: 
//     //complexity:    

//     I i = std::find_if(f, l, p);
//     if (i == l) return i;

//     I j = successor(i);
//     while (true) {
//         j = std::find_if_not(j, l, p);
//         if (j == l) return i;
//         swap_step(i, j);
//     }
// }

template <ForwardIterator I, UnaryPredicate P>
    requires(Mutable<I> && Domain<P, ValueType<I>>)
I partition_semistable(I f, I l, P p) {
    //precondition:  mutable_bounded_range(f, l)
    //postcondition: 
    //complexity:    

    f = std::find_if(f, l, p);
    if (f == l) return f;

    I j = std::next(f);
    while (j == l) {
        if ( ! p(*j)) {
            std::iter_swap(f, j);
            ++f;
        }
        ++j;
    }
    return f;
}

}} /*tao::algorithm*/

#include <tao/algorithm/concepts_undef.hpp>

#endif /*TAO_ALGORITHM_PARTITION_PARTITION_HPP_*/

// #ifdef DOCTEST_LIBRARY_INCLUDED
// #include <forward_list>
// #include <list>
// #include <vector>

// #include <tao/benchmark/instrumented.hpp>

// using namespace tao::algorithm;
// using namespace std;

// TEST_CASE("[min_element] testing min_element selection algorithm, instrumented, random access") {
//     using T = instrumented<int>;
//     vector<T> a = {3, 6, 2, 1, 4, 5, 1, 6, 2, 3};

//     instrumented<int>::initialize(0);
//     auto m0 = tao::algorithm::min_element(begin(a), end(a), less<>());

//     double* count_p = instrumented<int>::counts;
//     CHECK(count_p[instrumented_base::comparison] == a.size() - 1);
// }

// #endif /*DOCTEST_LIBRARY_INCLUDED*/
