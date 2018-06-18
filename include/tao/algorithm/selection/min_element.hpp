//! \file tao/algorithm/selection/min_element.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016-2018
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_ALGORITHM_SELECTION_MIN_ELEMENT_HPP_
#define TAO_ALGORITHM_SELECTION_MIN_ELEMENT_HPP_

// #include <algorithm>
// #include <iterator>
#include <utility>

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/integers.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao { namespace algorithm {

// Bounded ranges
// -------------------------------------------------------

template <ForwardIterator I, StrictWeakOrdering R>
    requires(Readable<I> && Domain<R, ValueType<I>>)
I min_element(I f, I l, R r) {
    //precondition:  readable_bounded_range(f, l)
    //postcondition: f != l && *min_element(f, l, r) == stable_sort_copy(f, l, r)[0]
    //complexity:    distance(f, l) - 1 comparisons

    if (f == l) return l;
 
    I m = f++;
    while (f != l) {
        if (r(*f, *m)) {
            m = f;
        }
        ++f;
    }
    return m;
}

template <ForwardIterator I>
    requires(Readable<I> && TotallyOrdered<ValueType<I>>)
inline
I min_element(I f, I l) {
    //same specs as min_element<I, R>
    return tao::algorithm::min_element(f, l, std::less<>());
}

template <Iterator I, StrictWeakOrdering R>
    requires(Readable<I> && Domain<R, ValueType<I>>)
ValueType<I> min_value_nonempty(I f, I l, R r) {
    //precondition:     f != l && readable_bounded_range(f, l)
    //postcondition:    min_value_nonempty(f, l, r) == stable_sort_copy(f, l, r)[0]
    //complexity:       distance(f, l) - 1 comparisons
    //                  1 copy construction, distance(f, l) - 1 copy assignments (worst case)

    using T = ValueType<I>;
    T val = *f++;
    while (f != l) {
        if (r(*f, val)) {
            val = *f;
        }
        ++f;
    }
    return val;
}

template <Iterator I>
    requires(Readable<I> && TotallyOrdered<ValueType<I>>)
inline
ValueType<I> min_value_nonempty(I f, I l) {
    //same specs as min_value_nonempty<I, R>
    return tao::algorithm::min_value_nonempty(f, l, std::less<>());
}

template <Iterator I, StrictWeakOrdering R>
    requires(Readable<I> && Domain<R, ValueType<I>>)
inline
ValueType<I> min_value(I f, I l, R r) {
    //precondition:     readable_bounded_range(f, l)
    //postcondition:    f != l && min_value(f, l, r) == stable_sort_copy(f, l, r)[0]
    //complexity:       distance(f, l) - 1 comparisons
    //                  1 copy construction, distance(f, l) - 1 copy assignments (worst case)

    using T = ValueType<I>;
    if (f == l) return supremum<T>; //supremum(r)
    return tao::algorithm::min_value_nonempty(f, l, r);
}

template <Iterator I>
    requires(Readable<I> && TotallyOrdered<ValueType<I>>)
inline
ValueType<I> min_value(I f, I l) {
    //same specs as min_value<I, R>
    return tao::algorithm::min_value(f, l, std::less<>());
}

// Counted ranges
// -------------------------------------------------------

template <ForwardIterator I, StrictWeakOrdering R>
    requires(Readable<I> && Domain<R, ValueType<I>>)
std::pair<I, DistanceType<I>> min_element_n(I f, DistanceType<I> n, R r) {
    //precondition:  readable_counted_range(f, n)
    //postcondition: n != 0 && *min_element_n(f, n, r) == stable_sort_copy_n(f, n, r)[0]
    //complexity:    n - 1 comparisons

    if (zero(n)) return {f, n};
 
    I m = f;
    auto m_n = n;
    step_n(f, n);

    while ( ! zero(n)) {
        if (r(*f, *m)) {
            m = f;
            m_n = n;
        }
        step_n(f, n);
    }
    return {m, m_n};
}

template <ForwardIterator I>
    requires(Readable<I> && TotallyOrdered<ValueType<I>>)
inline
std::pair<I, DistanceType<I>> min_element_n(I f, DistanceType<I> n) {
    //same specs as min_element<I, R>
    return tao::algorithm::min_element_n(f, n, std::less<>());
}

template <Iterator I, StrictWeakOrdering R>
    requires(Readable<I> && Domain<R, ValueType<I>>)
ValueType<I> min_value_nonempty_n(I f, DistanceType<I> n, R r) {
    //precondition:     n != 0 && readable_counted_range(f, n)
    //postcondition:    min_value_nonempty_n(f, n, r) == stable_sort_copy_n(f, n, r)[0]
    //complexity:       n - 1 comparisons
    //                  1 copy construction, n - 1 copy assignments (worst case)

    using T = ValueType<I>;
    T val = *f++;
    --n;
    while ( ! zero(n)) {
        if (r(*f, val)) {
            val = *f;
        }
        ++f;
        --n;
    }
    return val;
}

template <Iterator I>
    requires(Readable<I> && TotallyOrdered<ValueType<I>>)
inline
ValueType<I> min_value_nonempty_n(I f, DistanceType<I> n) {
    //same specs as min_value_nonempty_n<I, R>
    return tao::algorithm::min_value_nonempty_n(f, n, std::less<>());
}

template <Iterator I, StrictWeakOrdering R>
    requires(Readable<I> && Domain<R, ValueType<I>>)
inline
ValueType<I> min_value_n(I f, DistanceType<I> n, R r) {
    //precondition:     readable_counted_range(f, n)
    //postcondition:    n != 0 && min_value_n(f, n, r) == stable_sort_copy_n(f, n, r)[0]
    //complexity:       n - 1 comparisons
    //                  1 copy construction, n - 1 copy assignments (worst case)

    using T = ValueType<I>;
    if (zero(n)) return supremum<T>; //supremum(r)
    return tao::algorithm::min_value_nonempty_n(f, n, r);
}

template <Iterator I>
    requires(Readable<I> && TotallyOrdered<ValueType<I>>)
inline
ValueType<I> min_value_n(I f, DistanceType<I> n) {
    //same specs as min_value_n<I, R>
    return tao::algorithm::min_value_n(f, n, std::less<>());
}


}} /*tao::algorithm*/

#include <tao/algorithm/concepts_undef.hpp>

#endif /*TAO_ALGORITHM_SELECTION_MIN_ELEMENT_HPP_*/

#ifdef DOCTEST_LIBRARY_INCLUDED
    using namespace tao::algorithm;
    using namespace std;

TEST_CASE("[min_element] testing min_element selection algorithm, random access") {
    using T = int;
    vector<T> a = {3, 6, 2, 1, 4, 5, 1, 6, 2, 3};
    auto m = tao::algorithm::min_element(begin(a), end(a), std::less<>());
    CHECK(m == next(begin(a), 3));
}

TEST_CASE("[min_element] testing min_element selection algorithm, random access, default relation") {
    using T = int;
    vector<T> a = {3, 6, 2, 1, 4, 5, 1, 6, 2, 3};
    auto m = tao::algorithm::min_element(begin(a), end(a));
    CHECK(m == next(begin(a), 3));
}

TEST_CASE("[min_element] testing min_element_n selection algorithm, random access") {
    using T = int;
    vector<T> a = {3, 6, 2, 1, 4, 5, 1, 6, 2, 3};
    auto m = min_element_n(begin(a), a.size(), std::less<>());
    CHECK(std::get<0>(m) == next(begin(a), 3));
}

TEST_CASE("[min_element] testing min_element_n selection algorithm, random access, default relation") {
    using T = int;
    vector<T> a = {3, 6, 2, 1, 4, 5, 1, 6, 2, 3};
    auto m = min_element_n(begin(a), a.size());
    CHECK(std::get<0>(m) == next(begin(a), 3));
}

#endif /*DOCTEST_LIBRARY_INCLUDED*/
