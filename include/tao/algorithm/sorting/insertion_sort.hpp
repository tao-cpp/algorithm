//! \file tao/algorithm/sorting/insertion_sort.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016-2018
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// C++ Standard used: C++17

#ifndef TAO_ALGORITHM_SORTING_INSERTION_SORT_HPP_
#define TAO_ALGORITHM_SORTING_INSERTION_SORT_HPP_

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/type_attributes.hpp>
#include <tao/algorithm/iterator.hpp>
#include <tao/algorithm/rotate.hpp>

namespace tao { namespace algorithm {

template <BidirectionalIterator I, Relation R>  //WeakStrictOrdering??
    requires(Mutable<I>)
I shift_right_while(I f, I l, R r) {
    // precondition: mutable_bounded_range(f, l + 1) && is_sorted(f, l, r)
    while (f != l && r(*predecessor(l))) {
        *l = *predecessor(l);
        --l;
    }
    return l;
}



template <BidirectionalIterator I, Relation R>  //WeakStrictOrdering??
    requires(Mutable<I>)
I linear_insert(I f, I current, R r) {
    // precondition: mutable_bounded_range(f, current + 1) && is_sorted(f, current, r)
    auto value = *current;
    while (f != current && r(value, *predecessor(current))) {
        *current = *predecessor(current);
        --current;
    }
    *current = value;
    return current;
}





// template <ForwardIterator I, Relation R>
//     requires(WeakStrictOrdering<ValueType<I>>)
// I linear_insert(I f, I c, R r) {
//     //precondition: writable_counted_range(f, c) TODO(fernando): ?????
//     //precondition: sorted(f, c, r)

//     if (f == c) return f; //TODO(fernando): is it necessary?

//     auto value = *c;
//     --c;

//     while (r(v, *c)) {
//         //invariant: TODO(fernando): ?????
//         *successor(c) = *c;
//         if (f == c) {
//             *c = value;
//             return c;
//         }
//         --c;
//     }
//     ++c;
//     *c = value;
//     return c; 
// }

// template <ForwardIterator I, Relation R>
//     requires(WeakStrictOrdering<ValueType<I>>)
// I insertion_sort_linear(I f, I l, R r) {
//     if (f == l) return f;

//     I s = f;
//     ++f;

//     while (f != l) {
//         linear_insert(s, f, r);
//         // ++f;
//         step(f, s);
//     }
//     return f;
// }

// template <ForwardIterator I>
// void insertion_sort_linear_n(I f, DistanceType<I> n) {
// }

// template <ForwardIterator I, Relation R>
//     requires(Mutable<I> && WeakStrictOrdering<R, ValueType<I>>)
// I binary_insert_n(I f, DistanceType<I> n, I current, R r) {
//     // precondition: mutable_bounded_range(f, current + 1) &&
//     //               is_sorted(f, current, r) && distance(f, current) == n

//     I where = upper_bound_n(f, n, *current, r);
//     rotate_right_by_one(where, ++current);
//     return where; 
// }

template <ForwardIterator I, Relation R>
    requires(Mutable<I> && WeakStrictOrdering<R, ValueType<I>>)
I binary_insert(I f, I current, R r) {
    // precondition: mutable_bounded_range(f, current + 1) && 
    //               is_sorted(f, current, r)

    I where = upper_bound(f, current, *current, r);
    rotate_right_by_one(where, ++current);
    return where; 
}

template <ForwardIterator I, Relation R>
    requires(Mutable<I> && WeakStrictOrdering<R, ValueType<I>>)
I insertion_sort_binary(I f, I l, R r) {
    //precondition: mutable_bounded_range(f, l)
    if (f == l) return f;
    I s = f++;
    while (f != l) {
        //invariant: is_sorted(s, f, r) && distance(s, f) == 1
        binary_insert(s, f++, r);
    }
    return f;
}

template <ForwardIterator I, Relation R>
    requires(Mutable<I> && WeakStrictOrdering<R, ValueType<I>>)
I insertion_sort_binary_n(I f, DistanceType<I> n, R r) {
    //precondition: mutable_bounded_range(f, l)

    using N = DistanceType<I>;
    if (n == N(0)) return f;
    I s = f++;
    while (n != N(0)) {
        //invariant: is_sorted(s, f, r) && distance(s, f) == 1
        binary_insert(s, f++, r);
        --n;
    }
    return f;
}

}} /*tao::algorithm*/

#include <tao/algorithm/concepts_undef.hpp>

#endif /*TAO_ALGORITHM_SORTING_INSERTION_SORT_HPP_*/

#ifdef DOCTEST_LIBRARY_INCLUDED

#include <tao/benchmark/instrumented.hpp>

TEST_CASE("[insertion_sort] testing insertion_sort_binary 6 elements random access sorted") {
    using T = int;
    vector<T> a = {1, 2, 3, 4, 5, 6};
    insertion_sort_binary(begin(a), end(a), std::less<>());
    CHECK(a == vector<T>{1, 2, 3, 4, 5, 6});
}

TEST_CASE("[insertion_sort] testing insertion_sort_binary 6 elements random access reverse") {
    using T = int;
    vector<T> a = {6, 5, 4, 3, 2, 1};
    insertion_sort_binary(begin(a), end(a), std::less<>());
    CHECK(a == vector<T>{1, 2, 3, 4, 5, 6});
}

TEST_CASE("[insertion_sort] testing insertion_sort_binary 6 elements random access random") {
    using T = int;
    vector<T> a = {3, 6, 2, 1, 4, 5};
    insertion_sort_binary(begin(a), end(a), std::less<>());
    CHECK(a == vector<T>{1, 2, 3, 4, 5, 6});
}








TEST_CASE("[insertion_sort] testing insertion_sort_binary_n 6 elements random access sorted") {
    using T = int;
    vector<T> a = {1, 2, 3, 4, 5, 6};
    insertion_sort_binary_n(begin(a), a.size(), std::less<>());
    CHECK(a == vector<T>{1, 2, 3, 4, 5, 6});
}

TEST_CASE("[insertion_sort] testing insertion_sort_binary_n 6 elements random access reverse") {
    using T = int;
    vector<T> a = {6, 5, 4, 3, 2, 1};
    insertion_sort_binary_n(begin(a), a.size(), std::less<>());
    CHECK(a == vector<T>{1, 2, 3, 4, 5, 6});
}

TEST_CASE("[insertion_sort] testing insertion_sort_binary_n 6 elements random access random") {
    using T = int;
    vector<T> a = {3, 6, 2, 1, 4, 5};
    insertion_sort_binary_n(begin(a), a.size(), std::less<>());
    CHECK(a == vector<T>{1, 2, 3, 4, 5, 6});
}






TEST_CASE("[insertion_sort] testing insertion_sort_binary instrumented random access") {
    using T = instrumented<int>;
    vector<T> a = {1, 2, 3, 4, 5, 6};

    instrumented<int>::initialize(0);
    insertion_sort_binary(begin(a), end(a), std::less<>());

    double* count_p = instrumented<int>::counts;
    CHECK(count_p[instrumented_base::comparison] <= std::pow(a.size(), 2)); //insertion sort worst case
}

TEST_CASE("[insertion_sort] testing insertion_sort_binary instrumented bidirectional") {
    using T = instrumented<int>;
    list<T> a = {1, 2, 3, 4, 5, 6};

    instrumented<int>::initialize(0);
    insertion_sort_binary(begin(a), end(a), std::less<>());

    double* count_p = instrumented<int>::counts;
    CHECK(count_p[instrumented_base::comparison] <= std::pow(a.size(), 2)); //insertion sort worst case
}

TEST_CASE("[insertion_sort] testing insertion_sort_binary instrumented forward") {
    using T = instrumented<int>;
    forward_list<T> a = {1, 2, 3, 4, 5, 6};
    auto n = distance(begin(a), end(a));

    instrumented<int>::initialize(0);
    insertion_sort_binary(begin(a), end(a), std::less<>());

    double* count_p = instrumented<int>::counts;
    CHECK(count_p[instrumented_base::comparison] <= std::pow(n, 2)); //insertion sort worst case
}


// using random_eng_t = random_int_generator<int32_t>;
// random_eng_t eng;
// auto data_random_access = random_container_creator<std::vector>(array_size, eng);


#endif /*DOCTEST_LIBRARY_INCLUDED*/
