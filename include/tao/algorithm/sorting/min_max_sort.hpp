//! \file tao/algorithm/sorting/min_max_sort.hpp
// Tao.Algorithm
//
// Copyright (c) 2016-2020 Fernando Pelliccioni.
//
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

// C++ Standard used: C++17

#ifndef TAO_ALGORITHM_SORTING_MIN_MAX_SORT_HPP_
#define TAO_ALGORITHM_SORTING_MIN_MAX_SORT_HPP_

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/type_attributes.hpp>
#include <tao/algorithm/iterator.hpp>
#include <tao/algorithm/rotate.hpp>

namespace tao { namespace algorithm {

template <BidirectionalIterator I, StrictWeakOrdering R>
    requires(Mutable<I> && Domain<R, ValueType<I>>)
void min_max_sort(I f, I l, R r) {
    //precondition: mutable_bounded_range(f, l)

    using std::swap;
    while (f != l) {
        auto p = tao::algorithm::min_max_element(f, l, r);
        --l;
        swap(*f, *p.first);
        swap(*l, *p.second);
        
        if (f == l) return;
        ++f;
    }
}

}} /*tao::algorithm*/

#include <tao/algorithm/concepts_undef.hpp>

#endif /*TAO_ALGORITHM_SORTING_MIN_MAX_SORT_HPP_*/

#ifdef DOCTEST_LIBRARY_INCLUDED

#include <tao/benchmark/instrumented.hpp>

TEST_CASE("[min_max_sort] testing min_max_sort 6 elements random access sorted") {
    using T = int;
    vector<T> a = {1, 2, 3, 4, 5, 6};
    min_max_sort(begin(a), end(a), std::less<>());
    CHECK(a == vector<T>{1, 2, 3, 4, 5, 6});
}

#endif /*DOCTEST_LIBRARY_INCLUDED*/
