//! \file tao/algorithm/selection/max_element.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016-2018
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_ALGORITHM_SELECTION_MAX_ELEMENT_HPP_
#define TAO_ALGORITHM_SELECTION_MAX_ELEMENT_HPP_

#include <algorithm>
#include <iterator>
#include <utility>

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/integers.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao { namespace algorithm {

template <ForwardIterator I, StrictWeakOrdering R>
    requires(Readable<I> && Domain<R, ValueType<I>>)
I max_element(I f, I l, R r) {
    //precondition: readable_bounded_range(f, l)
    //postcondition: max_element(f, l, r) == stable_sort_copy(f, l, r)[distance(f, l) - 1]

    if (f == l) return l;
 
    I m = f++;
    while (f != l) {
        if ( ! r(*f, *m)) {
            m = f;
        }
        ++f;
    }
    return m;
}

template <ForwardIterator I, StrictWeakOrdering R>
    requires(Readable<I> && Domain<R, ValueType<I>>)
std::pair<I, DistanceType<I>> max_element_n(I f, DistanceType<I> n, R r) {
    //precondition: readable_counted_range(f, n)
    //postcondition: max_element_n(f, n, r) == stable_sort_copy_n(f, n, r)[n - 1]

    if (zero(n)) return {f, n};
 
    I m = f;
    auto m_n = n;
    step_n(f, n);

    while ( ! zero(n)) {
        if ( ! r(*f, *m)) {
            m = f;
            m_n = n;
        }
        step_n(f, n);
    }
    return {m, m_n};
}



}} /*tao::algorithm*/

#include <tao/algorithm/concepts_undef.hpp>

#endif /*TAO_ALGORITHM_SELECTION_MAX_ELEMENT_HPP_*/

#ifdef DOCTEST_LIBRARY_INCLUDED
    using namespace tao::algorithm;
    using namespace std;

TEST_CASE("[max_element] testing max_element selection algorithm, random access") {
    using T = int;
    vector<T> a = {3, 6, 2, 1, 4, 5, 6, 2, 3};
    auto m = tao::algorithm::max_element(begin(a), end(a), std::less<>());
    CHECK(m == next(begin(a), 6));
}

TEST_CASE("[max_element] testing max_element_n selection algorithm, random access") {
    using T = int;
    vector<T> a = {3, 6, 2, 1, 4, 5, 6, 2, 3};
    auto m = max_element_n(begin(a), a.size(), std::less<>());
    CHECK(std::get<0>(m) == next(begin(a), 6));
}

#endif /*DOCTEST_LIBRARY_INCLUDED*/
