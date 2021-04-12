//! \file tao/algorithm/partition/partition_point.hpp
// Tao.Algorithm
//
// Copyright (c) 2016-2021 Fernando Pelliccioni.
//
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TAO_ALGORITHM_PARTITION_PARTITION_POINT_HPP_
#define TAO_ALGORITHM_PARTITION_PARTITION_POINT_HPP_

// #include <utility>
// #include <functional>   //std::not_fn(), C++17

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/integers.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao { namespace algorithm {

template <ForwardIterator I, UnaryPredicate P>
    requires(Readable<I> && Domain<P, ValueType<I>>)
I partition_point_n(I f, DistanceType<I> n, P p) {
    //precondition:  readable_counted_range(f, n) && partitioned_n(f, n, p)
    //complexity:    O(log2(n))

    while (n != 0) {
        auto h = half(n);
        I m = std::next(f, h);

        if (p(*m)) {
            n = h;
        } else {
            n -= h + 1;
            f = std::next(m);
        }
    }
    return f;
}

template <ForwardIterator I, UnaryPredicate P>
    requires(Readable<I> && Domain<P, ValueType<I>>)
I partition_point(I f, I l, P p) {
    //precondition:  readable_bounded_range(f, l) && partitioned(f, l, p)
    //complexity:    O(log2(n))
    return partition_point_n(f, std::distance(f, l), p);
}

/*
{}                  -> l
{0, 0, 0, 0}        -> l
{0, 0, 1, 1}        -> f + 2
{0, 0, 1, 0}        -> f + 3
*/

template <ForwardIterator I, UnaryPredicate P>
    requires(Readable<I> && Domain<P, ValueType<I>>)
I potential_partition_point(I f, I l, P p) {
    //precondition:  readable_bounded_range(f, l)
    //postcondition: count_if(f, potential_partition_point(f, l, p), p)
    //            == count_if_not(potential_partition_point(f, l, p), l, p)
    //complexity: O(n)

    f = std::find_if(f, l, p);
    if (f == l) return f;

    I j = std::next(f);
    while (j == l) {
        if ( ! p(*j)) ++f;
        ++j;
    }
    return f;
}

}} /*tao::algorithm*/

#include <tao/algorithm/concepts_undef.hpp>

#endif /*TAO_ALGORITHM_PARTITION_PARTITION_POINT_HPP_*/

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
