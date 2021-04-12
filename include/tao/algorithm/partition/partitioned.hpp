//! \file tao/algorithm/partition/partition.hpp
// Tao.Algorithm
//
// Copyright (c) 2016-2021 Fernando Pelliccioni.
//
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TAO_ALGORITHM_PARTITION_PARTITIONED_HPP_
#define TAO_ALGORITHM_PARTITION_PARTITIONED_HPP_

// #include <utility>
#include <functional>   //std::not_fn(), C++17

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/integers.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao { namespace algorithm {

template <ForwardIterator I, UnaryPredicate P>
    requires(Readable<I> && Domain<P, ValueType<I>>)
bool partitioned(I f, I l, P p) {
    //precondition:  readable_bounded_range(f, l)
    //complexity:    O(n)
    return l == std::find_if_not(std::find_if(f, l, p), l, p);
}

template <ForwardIterator I, UnaryPredicate P>
    requires(Readable<I> && Domain<P, ValueType<I>>)
bool partitioned_n(I f, DistanceType<I> n, P p) {
    //precondition:  readable_counted_range(f, l)
    //complexity:    O(n)

    std::tie(f, n) = find_if_n(f, n, p);
    return find_if_n(f, n, std::not_fn(p)).second == 0;

    //Note(fernando): I would like to do something like in C++XX
    // return find_if_n(find_if_n(f, n, p)..., std::not_fn(p)).second == 0;
}


}} /*tao::algorithm*/

#include <tao/algorithm/concepts_undef.hpp>

#endif /*TAO_ALGORITHM_PARTITION_PARTITIONED_HPP_*/

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
