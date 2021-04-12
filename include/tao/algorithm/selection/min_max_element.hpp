//! \file tao/algorithm/selection/min_max_element.hpp
// Tao.Algorithm
//
// Copyright (c) 2016-2021 Fernando Pelliccioni.
//
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TAO_ALGORITHM_SELECTION_MIN_MAX_ELEMENT_HPP_
#define TAO_ALGORITHM_SELECTION_MIN_MAX_ELEMENT_HPP_

#include <algorithm>
#include <iterator>
#include <utility>

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/integers.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao { namespace algorithm {

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

    template <Regular T>
        requires(Domain<R, T>)
    std::pair<T, T> combine(std::pair<T, T> const& x, T const& val) const {
        if (r(val, x.first)) return {val, x.second};
        if (r(val, x.second)) return x;
        return {x.first, val};
    }
};

template <StrictWeakOrdering R>
struct compare_dereference {
    R r;

    template <Iterator I>
        requires(Readable<I> && Domain<R, ValueType<I>>)
    bool operator()(I const& x, I const& y) const {
        return r(*x, *y);
    }
};

template <ForwardIterator I, StrictWeakOrdering R>
    requires(Readable<I> && Domain<R, ValueType<I>>)
std::pair<I, I> min_max_element_even_length(I f, I l, R r) {
    // precondition:  distance(f, l) % 2 == 0 &&
    //                readable_bounded_range(f, l)
    // postcondition: result.first == stable_sort_copy(f, l, r)[0] &&
    //                result.second == stable_sort_copy(f, l, r)[distance(f, l) - 1]
    if (f == l) return {l, l};

    I prev = f;
    min_max<compare_dereference<R>> op{r};
    auto result = op.construct(prev, ++f);
    while (++f != l) {
        prev = f;
        result = op.combine(result, op.construct(prev, ++f));
    }
    return result;
}

template <ForwardIterator I, StrictWeakOrdering R>
    requires(Readable<I> && Domain<R, ValueType<I>>)
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
    auto result = op.construct(prev, f);
    ++f;
    DistanceType<I> i = 2;

    while (i != m) {
        prev = f;
        ++i; ++f;
        result = op.combine(result, op.construct(prev, f));
        ++i; ++f;
    }

    if (i != n) {
        // return op.combine(result, {f, f});
        return op.combine(result, f);
    }

    return result;
}

template <ForwardIterator I, StrictWeakOrdering R>
    requires(Readable<I> && Domain<R, ValueType<I>>)
std::pair<I, I> min_max_element(I f, I l, R r, std::forward_iterator_tag) {
    //precondition: readable_bounded_range(f, l)
    //postcondition: result.first == stable_sort_copy(f, l, r)[0] &&
    //               result.second == stable_sort_copy(f, l, r)[distance(f, l) - 1]

    I prev = f;
    if (f == l || ++f == l) return {prev, prev};

    min_max<compare_dereference<R>> op{r};
    auto result = op.construct(prev, f);
    while (++f != l) {
        prev = f;
        // if (++f == l) return op.combine(result, {prev, prev});
        if (++f == l) return op.combine(result, prev);

        result = op.combine(result, op.construct(prev, f));
    }
    return result;
}

template <RandomAccessIterator I, StrictWeakOrdering R>
    requires(Readable<I> && Domain<R, ValueType<I>>)
std::pair<I, I> min_max_element(I f, I l, R r, std::random_access_iterator_tag) {
    //precondition: readable_bounded_range(f, l)
    //postcondition: result.first == stable_sort_copy(f, l, r)[0] &&
    //               result.second == stable_sort_copy(f, l, r)[distance(f, l) - 1]

    auto n = std::distance(f, l);
    return min_max_element_n_basis(f, n, r);
}

template <ForwardIterator I, StrictWeakOrdering R>
    requires(Readable<I> && Domain<R, ValueType<I>>)
inline
auto min_max_element(I f, I l, R r) {
    //precondition:  readable_bounded_range(f, l)
    //postcondition: result.first == stable_sort_copy(f, l, r)[0] &&
    //               result.second == stable_sort_copy(f, l, r)[distance(f, l) - 1]

    return min_max_element(f, l, r, IteratorCategory<I>{});
}

template <ForwardIterator I, StrictWeakOrdering R>
    requires(Readable<I> && Domain<R, ValueType<I>>)
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
        // return op.combine(result, {min_max_ret_elem<I>{f, n - i}, min_max_ret_elem<I>{f, n - i}});
        return op.combine(result, min_max_ret_elem<I>{f, n - i});
    }

    return result;
}


template <Iterator I, StrictWeakOrdering R>
    requires(Readable<I> && Domain<R, ValueType<I>>)
pair<ValueType<I>, ValueType<I>> min_max_value_nonempty(I f, I l, R r) {
    using T = ValueType<I>;
    min_max<R> op{r};
    T val = std::move(*f);
    if (++f == l) return {val, val};
    auto result = op.construct(val, *f);
    while (++f != l) {
        val = std::move(*f);
        // if (++f == l) return op.combine(result, {val, val});
        if (++f == l) return op.combine(result, val);
        result = op.combine(result, op.construct(val, *f));
    }
    return result;
}

template <Iterator I, StrictWeakOrdering R>
    requires(Readable<I> && Domain<R, ValueType<I>>)
pair<ValueType<I>, ValueType<I>> min_max_value(I f, I l, R r) {
    using T = ValueType<I>;
    // if (f == l) return {supremum(r), infimum(r)};
    if (f == l) return {supremum<T>, infimum<T>};
    return min_max_value_nonempty(f, l, r);
}

// TODO(fernando): create min_max_value_n
// TODO(fernando): create min_max_value even vesion

}} /*tao::algorithm*/

#include <tao/algorithm/concepts_undef.hpp>

#endif /*TAO_ALGORITHM_SELECTION_MIN_MAX_ELEMENT_HPP_*/

#ifdef DOCTEST_LIBRARY_INCLUDED

#include <tao/benchmark/instrumented.hpp>

using namespace tao::algorithm;
using namespace std;


TEST_CASE("[min_max_element] testing min_max_element selection algorithm, instrumented, random access") {
    using T = instrumented<int>;
    vector<T> a = {3, 6, 2, 1, 4, 5, 1, 6, 2, 3};   //do it with random number of elements...

    instrumented<int>::initialize(0);
    auto p = tao::algorithm::min_max_element(begin(a), end(a), less<>());

    double* count_p = instrumented<int>::counts;
    // ceil(3/2 * 2) - 2
    CHECK(count_p[instrumented_base::comparison] <= (3 * a.size()) / 2 - 2);

    // for (size_t i = 0; i < instrumented_base::number_ops; ++i) {
    //     std::cout << instrumented_base::counter_names[i] << ": "
    //                 << count_p[i]
    //                 << std::endl;
    // }

    // CHECK(1 == 0);
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

TEST_CASE("[min_max_element] testing min_max_value selection algorithm, random access") {
    using T = int;
    vector<T> a = {3, 6, 2, 1, 4, 5, 6, 2, 3};
    auto p = tao::algorithm::min_max_value(begin(a), end(a), std::less<>());
    CHECK(p.first  == *next(begin(a), 3));
    CHECK(p.second == *next(begin(a), 6));

}



#endif /*DOCTEST_LIBRARY_INCLUDED*/
