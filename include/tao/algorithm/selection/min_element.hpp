//! \file tao/algorithm/selection/min_element.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016-2018
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_ALGORITHM_SELECTION_MIN_ELEMENT_HPP_
#define TAO_ALGORITHM_SELECTION_MIN_ELEMENT_HPP_

#include <algorithm>
#include <iterator>
#include <utility>

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/integers.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao { namespace algorithm {

template <ForwardIterator I, StrictWeakOrdering R>
    requires(Domain<R, ValueType<I>)
I min_element(I f, I l, R r) {
    //precondition: readable_bounded_range(f, l)
    //postcondition: min_element(f, l, r) == stable_sort_copy(f, l, r)[0]

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

template <ForwardIterator I, StrictWeakOrdering R>
    requires(Domain<R, ValueType<I>)
std::pair<I, DistanceType<I>> min_element_n(I f, DistanceType<I> n, R r) {
    //precondition:  readable_counted_range(f, n)
    //postcondition: min_element_n(f, n, r) == stable_sort_copy_n(f, n, r)[0]

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

template <ForwardIterator I, StrictWeakOrdering R>
    requires(Domain<R, ValueType<I>)
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
    requires(Domain<R, ValueType<I>)
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



// --------------------------------------------

template <ForwardIterator I>
using min_max_ret_elem = std::pair<I, DistanceType<I>>;

template <ForwardIterator I>
using min_max_ret = std::pair<min_max_ret_elem<I>, min_max_ret_elem<I>>;

template <ForwardIterator I>
ValueType<I> const& operator*(min_max_ret_elem<I> const& p) {
    return *p.first;
}

template <StrictWeakOrdering R>
struct min_max {
    R r;

    template <Regular T> 
        requires(Domain<R, T>)
    T const& min(T const& x, T const& y) const {
        if (r(y, x)) return y;
        return x;
    }

    template <Regular T> 
        requires(Domain<R, T>)
    T const& max(T const& x, T const& y) const {
        if (r(y, x)) return x;
        return y;
    }

    template <Regular T>
        requires(Domain<R, T>)
    std::pair<T, T> construct(T const& x, T const& y) const {
        if (r(y, x)) return {y, x};
        return {x, y};
    }   

    template <Regular T>
        requires(Domain<R, T>)
    std::pair<T, T> combine(std::pair<T, T> const& x, pair<T, T> const& y) const {
        return { min(x.first, y.first), max(x.second, y.second) };
    }
}; 


template <StrictWeakOrdering R>
struct compare_dereference {
    R r;

    template <Iterator I>
        requires(Domain<R, ValueType<I>>)
    bool operator()(I const& x, I const& y) const {
        return r(*x, *y);
    }
};


template <ForwardIterator I, StrictWeakOrdering R>
    requires(Domain<R, ValueType<I>)
std::pair<I, I> min_max_element_even_length(I f, I l, R r) {
    // precondition:  distance(f, l) % 2 == 0 &&
    //                readable_bounded_range(f, l)
    // postcondition: result.first == stable_sort_copy(f, l, r)[0] &&
    //                result.second == stable_sort_copy(f, l, r)[distance(f, l) - 1]
    if (f == l) return {l, l};

    I prev = f;
    min_max<compare_dereference<R>> op{r};
    pair<I, I> result = op.construct(prev, ++f);
    while (++f != l) {
        prev = f;
        result = op.combine(result, op.construct(prev, ++f));
    }
    return result;
}

template <ForwardIterator I, StrictWeakOrdering R>
    requires(Domain<R, ValueType<I>)
pair<I, I> min_max_element_n_basis(I f, DistanceType<I> n, R r) {
    //precondition: readable_counted_range(f, n)
    //postcondition: result.first == stable_sort_copy_n(f, n, r)[0] &&
    //               result.second == stable_sort_copy_n(f, n, r)[n - 1]

    if (zero(n)) return {f, f};
    if (one(n)) return {f, f};

    auto m = 2 * half(n);

    min_max<compare_dereference<R>> op{r};

    I prev = f;
    ++f;
    pair<I, I> result = op.construct(prev, f);
    ++f;
    DistanceType<I> i = 2;

    while (i != m) {
        prev = f;
        ++i; ++f;
        result = op.combine(result, op.construct(prev, f));
        ++i; ++f;
    }

    if (i != n) {
        return op.combine(result, {f, f});
    }

    return result;
}

template <ForwardIterator I, StrictWeakOrdering R>
    requires(Domain<R, ValueType<I>)
std::pair<I, I> min_max_element(I f, I l, R r, std::forward_iterator_tag) {
    //precondition: readable_bounded_range(f, l)
    //postcondition: result.first == stable_sort_copy(f, l, r)[0] &&
    //               result.second == stable_sort_copy(f, l, r)[distance(f, l) - 1]

    I prev = f;
    if (f == l || ++f == l) return {prev, prev};

    min_max<compare_dereference<R>> op{r};
    pair<I, I> result = op.construct(prev, f);
    while (++f != l) {
        prev = f;
        if (++f == l) return op.combine(result, {prev, prev});
    
        result = op.combine(result, op.construct(prev, f));
    }
    return result;
}

template <RandomAccessIterator I, StrictWeakOrdering R>
    requires(Domain<R, ValueType<I>)
std::pair<I, I> min_max_element(I f, I l, R r, std::random_access_iterator_tag) {
    //precondition: readable_bounded_range(f, l)
    //postcondition: result.first == stable_sort_copy(f, l, r)[0] &&
    //               result.second == stable_sort_copy(f, l, r)[distance(f, l) - 1]

    auto n = std::distance(f, l);
    return min_max_element_n_basis(f, n, r);
}

template <ForwardIterator I, StrictWeakOrdering R>
    requires(Domain<R, ValueType<I>)
inline
auto min_max_element(I f, I l, R r) {
    //precondition:  readable_bounded_range(f, l)
    //postcondition: result.first == stable_sort_copy(f, l, r)[0] &&
    //               result.second == stable_sort_copy(f, l, r)[distance(f, l) - 1]

    return min_max_element(f, l, r, IteratorCategory<I>{});
}


template <ForwardIterator I, StrictWeakOrdering R>
    requires(Domain<R, ValueType<I>)
min_max_ret<I> min_max_element_n(I f, DistanceType<I> n, R r) {
    //precondition: readable_counted_range(f, n)
    //postcondition: result.first == stable_sort_copy_n(f, n, r)[0] &&
    //               result.second == stable_sort_copy_n(f, n, r)[n - 1]

    if (zero(n)) return {{f, n}, {f, n}};
    if (one(n)) return {{f, n}, {f, n}};

    min_max<compare_dereference<R>> op{r};

    min_max_ret_elem<I> prev{f, n}; //I prev = f;
    ++f;
    auto result = op.construct(prev, min_max_ret_elem<I>{f, n - 1});
    ++f;
    DistanceType<I> i = 2;

    auto m = 2 * half(n);
    while (i != m) {
        prev = min_max_ret_elem<I>{f, n - i};
        ++i; ++f;
        result = op.combine(result, op.construct(prev, min_max_ret_elem<I>{f, n - i}));
        ++i; ++f;
    }

    if (i != n) {
        return op.combine(result, {min_max_ret_elem<I>{f, n - i}, min_max_ret_elem<I>{f, n - i}});
    }

    return result;
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

TEST_CASE("[min_element] testing min_element_n selection algorithm, random access") {
    using T = int;
    vector<T> a = {3, 6, 2, 1, 4, 5, 1, 6, 2, 3};
    auto m = min_element_n(begin(a), a.size(), std::less<>());
    CHECK(std::get<0>(m) == next(begin(a), 3));
}

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

TEST_CASE("[min_max_element] testing min_max_element selection algorithm, random access") {
    using T = int;
    vector<T> a = {3, 6, 2, 1, 4, 5, 6, 2, 3};
    auto p = tao::algorithm::min_max_element(begin(a), end(a), std::less<>());
    CHECK(p.first  == next(begin(a), 3));
    CHECK(p.second == next(begin(a), 6));
}

TEST_CASE("[min_max_element] testing min_max_element_n selection algorithm, random access") {
    using T = int;
    vector<T> a = {3, 6, 2, 1, 4, 5, 6, 2, 3};
    auto p = tao::algorithm::min_max_element_n(begin(a), a.size(), std::less<>());
    CHECK(p.first.first  == next(begin(a), 3));
    CHECK(p.second.first == next(begin(a), 6));
    CHECK(p.first.second == a.size() - 3);
    CHECK(p.second.second == a.size() - 6);
}

#endif /*DOCTEST_LIBRARY_INCLUDED*/
