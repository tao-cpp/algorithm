//! \file tao/algorithm/selection.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2017
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_ALGORITHM_SELECTION_HPP_
#define TAO_ALGORITHM_SELECTION_HPP_

#include <algorithm>
#include <iterator>
#include <utility>

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/type_attributes.hpp>


#define FN(body) -> decltype(body) {return body;}

namespace tao { namespace algorithm {

// ------------------------------------------------------------------------------
// 2 elements selection
// Complexity: 1 comparison

// template <Regular T, Regular U, StrictWeakOrdering R>
//     requires(SameType<T, U> && Domain<R, T>)
// inline constexpr
// auto&& select_0_2(T&& a, U&& b, R r) {
//     return r(b, a) ? std::forward<U>(b) : std::forward<T>(a);
// }


template <Regular T, Regular U, StrictWeakOrdering R>
    requires(SameType<T, U> && Domain<R, T>)
inline constexpr
// auto&& select_0_2(T&& a, U&& b, R r) {
auto select_0_2(T&& a, U&& b, R r) FN(
    r(b, a) ? std::forward<U>(b) : std::forward<T>(a)
)


template <Regular T, Regular U>
    requires(SameType<T, U>)
inline constexpr
auto select_0_2(T&& a, U&& b) FN(
    b < a ? std::forward<U>(b) : std::forward<T>(a)
)

template <Regular T, Regular U, StrictWeakOrdering R>
    requires(SameType<T, U> && Domain<R, T>)
inline constexpr
auto select_1_2(T&& a, U&& b, R r) FN(
    r(b, a) ? std::forward<T>(a) : std::forward<U>(b)
)

template <Regular T, Regular U>
    requires(SameType<T, U>)
inline constexpr
auto select_1_2(T&& a, U&& b) FN(
    b < a ? std::forward<T>(a) : std::forward<U>(b)
)

// Aliases ----
template <Regular T, Regular U, StrictWeakOrdering R>
    requires(SameType<T, U> && Domain<R, T>)
inline constexpr
auto min(T&& a, U&& b, R r) FN(
    select_0_2(std::forward<T>(a), std::forward<U>(b), r)
)

template <Regular T, Regular U>
    requires(SameType<T, U>)
inline constexpr
auto min(T&& a, U&& b) FN(
    select_0_2(std::forward<T>(a), std::forward<U>(b))
)

template <Regular T, Regular U, StrictWeakOrdering R>
    requires(SameType<T, U> && Domain<R, T>)
inline constexpr
auto max(T&& a, U&& b, R r) FN(
    select_1_2(std::forward<T>(a), std::forward<U>(b), r)
)

template <Regular T, Regular U>
    requires(SameType<T, U>)
inline constexpr
auto max(T&& a, U&& b) FN(
    select_1_2(std::forward<T>(a), std::forward<U>(b))
)

// ------------------------------------------------------------------------------
// 3 elements selection
// Complexity: 
//  select_0_3:       2 comparisons
//  select_1_3_ab:
//      best case:    1 comparisons
//      worst case:   2 comparisons
//      average:    5/3 comparisons, assuming a uniform distribution of inputs
//  select_1_3: 
//      best case:    2 comparisons
//      worst case:   3 comparisons
//      average:    8/3 comparisons, assuming a uniform distribution of inputs
//  select_2_3:       2 comparisons

template <Regular T, Regular U, Regular V, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && Domain<R, T>)
inline constexpr
auto select_0_3(T&& a, U&& b, V&& c, R r) FN(
    
    select_0_2(
            select_0_2(std::forward<T>(a), std::forward<U>(b), r), 
            std::forward<V>(c), r)
)

template <Regular T, Regular U, Regular V>
    requires(SameType<T, U> && SameType<U, V>)
inline constexpr
auto select_0_3(T&& a, U&& b, V&& c) FN(
    
    select_0_2(
            select_0_2(std::forward<T>(a), std::forward<U>(b)), 
            std::forward<V>(c))
)

template <Regular T, Regular U, Regular V, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && Domain<R, T>)
inline constexpr
auto select_2_3(T&& a, U&& b, V&& c, R r) FN(
    
    select_1_2(
            select_1_2(std::forward<T>(a), std::forward<U>(b), r), 
            std::forward<V>(c), r)
)

template <Regular T, Regular U, Regular V>
    requires(SameType<T, U> && SameType<U, V>)
inline constexpr
auto select_2_3(T&& a, U&& b, V&& c) FN(
    
    select_1_2(
            select_1_2(std::forward<T>(a), std::forward<U>(b)), 
            std::forward<V>(c))
)

template <Regular T, Regular U, Regular V, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && Domain<R, T>)
inline constexpr
auto select_1_3_ab(T&& a, U&& b, V&& c, R r) FN(
    // precondition: a <= b
    
    ! r(c, b) ? //!(c < b) -> c >= b
                std::forward<U>(b) :                               // a, b, c are sorted
                select_1_2(std::forward<T>(a), std::forward<V>(c), r)  // b is not the median
)

template <Regular T, Regular U, Regular V, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && Domain<R, T>)
inline constexpr
auto select_1_3(T&& a, U&& b, V&& c, R r) FN(
    
    r(b, a) ? select_1_3_ab(std::forward<U>(b), std::forward<T>(a), std::forward<V>(c), r) 
            : select_1_3_ab(std::forward<T>(a), std::forward<U>(b), std::forward<V>(c), r)
)

template <Regular T, Regular U, Regular V>
    requires(SameType<T, U> && SameType<U, V>)
inline constexpr
auto select_1_3_ab(T&& a, U&& b, V&& c) FN(
    // precondition: a <= b
    
    !(c < b) ? //!(c < b) -> c >= b
                  std::forward<U>(b)                              // a, b, c are sorted
                : select_1_2(std::forward<T>(a), std::forward<V>(c))  // b is not the median
)

template <Regular T, Regular U, Regular V>
    requires(SameType<T, U> && SameType<U, V>)
inline constexpr
auto select_1_3(T&& a, U&& b, V&& c) FN(
    
    b < a ? 
              select_1_3_ab(std::forward<U>(b), std::forward<T>(a), std::forward<V>(c)) 
            : select_1_3_ab(std::forward<T>(a), std::forward<U>(b), std::forward<V>(c))
)

// ------------------------------------------------------------------------------
// 4 elements selection

// Complexity: 
//  select_0_4:       3 comparisons
//  select_1_4_ab_cd: 2 comparisons
//  select_1_4_ab:    3 comparisons
//  select_1_4:       4 comparisons
//  select_2_4_ab_cd: 2 comparisons
//  select_2_4_cd:    3 comparisons
//  select_2_4:       4 comparisons
//  select_3_4:       3 comparisons


template <Regular T, Regular U, Regular V, Regular W, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && Domain<R, T>)
inline constexpr
auto select_0_4(T&& a, U&& b, V&& c, W&& d, R r) FN(
    
    select_0_2(
            select_0_3(std::forward<T>(a), std::forward<U>(b), std::forward<V>(c), r), 
            std::forward<W>(d), r)
)

template <Regular T, Regular U, Regular V, Regular W>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W>)
inline constexpr
auto select_0_4(T&& a, U&& b, V&& c, W&& d) FN(
    
    select_0_2(
            select_0_3(std::forward<T>(a), std::forward<U>(b), std::forward<V>(c)), 
            std::forward<W>(d))
)

template <Regular T, Regular U, Regular V, Regular W, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && Domain<R, T>)
inline constexpr
auto select_3_4(T&& a, U&& b, V&& c, W&& d, R r) FN(
    
    select_1_2(
            select_2_3(std::forward<T>(a), std::forward<U>(b), std::forward<V>(c), r), 
            std::forward<W>(d), r)
)

template <Regular T, Regular U, Regular V, Regular W>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W>)
inline constexpr
auto select_3_4(T&& a, U&& b, V&& c, W&& d) FN(
    
    select_1_2(
            select_2_3(std::forward<T>(a), std::forward<U>(b), std::forward<V>(c)), 
            std::forward<W>(d))
)



template <Regular T, Regular U, Regular V, Regular W, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && Domain<R, T>)
inline constexpr
auto select_1_4_ab_cd(T&& a, U&& b, V&& c, W&& d, R r) FN(
    // precondition: a <= b && c <= d

    // cdab ...  (c < a)
    // cadb ...  (c < a)
    // cabd ...  (c < a)
    // abcd ... !(c < a)
    // acbd ... !(c < a)
    // acdb ... !(c < a)

    
    r(c, a) ? // c < a
              select_0_2(std::forward<T>(a), std::forward<W>(d), r)
            : select_0_2(std::forward<U>(b), std::forward<V>(c), r)
)

template <Regular T, Regular U, Regular V, Regular W>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W>)
inline constexpr
auto select_1_4_ab_cd(T&& a, U&& b, V&& c, W&& d) FN(
    // precondition: a <= b && c <= d

    
    c < a ? 
              select_0_2(std::forward<T>(a), std::forward<W>(d))
            : select_0_2(std::forward<U>(b), std::forward<V>(c))
)

template <Regular T, Regular U, Regular V, Regular W, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && Domain<R, T>)
inline constexpr
auto select_1_4_ab(T&& a, U&& b, V&& c, W&& d, R r) FN(
    // precondition: a <= b

    
    r(d, c) ? // d < c
              select_1_4_ab_cd(std::forward<T>(a), std::forward<U>(b), std::forward<W>(d), std::forward<V>(c), r)
            : select_1_4_ab_cd(std::forward<T>(a), std::forward<U>(b), std::forward<V>(c), std::forward<W>(d), r)
)

template <Regular T, Regular U, Regular V, Regular W>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W>)
inline constexpr
auto select_1_4_ab(T&& a, U&& b, V&& c, W&& d) FN(
    // precondition: a <= b

    
    d < c ? 
              select_1_4_ab_cd(std::forward<T>(a), std::forward<U>(b), std::forward<W>(d), std::forward<V>(c))
            : select_1_4_ab_cd(std::forward<T>(a), std::forward<U>(b), std::forward<V>(c), std::forward<W>(d))
)

template <Regular T, Regular U, Regular V, Regular W, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && Domain<R, T>)
inline constexpr
auto select_1_4(T&& a, U&& b, V&& c, W&& d, R r) FN(
    
    r(b, a) ? // b < a
              select_1_4_ab(std::forward<U>(b), std::forward<T>(a), std::forward<V>(c), std::forward<W>(d), r)
            : select_1_4_ab(std::forward<T>(a), std::forward<U>(b), std::forward<V>(c), std::forward<W>(d), r)
)

template <Regular T, Regular U, Regular V, Regular W>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W>)
inline constexpr
auto select_1_4(T&& a, U&& b, V&& c, W&& d) FN(
    b < a ? 
              select_1_4_ab(std::forward<U>(b), std::forward<T>(a), std::forward<V>(c), std::forward<W>(d))
            : select_1_4_ab(std::forward<T>(a), std::forward<U>(b), std::forward<V>(c), std::forward<W>(d))
)
        
template <Regular T, Regular U, Regular V, Regular W, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && Domain<R, T>)
inline constexpr
auto select_2_4_ab_cd(T&& a, U&& b, V&& c, W&& d, R r) FN(
    // precondition: a <= b && c <= d

    // acdb ...  (d < b)
    // cadb ...  (d < b)
    // cdab ...  (d < b)
    // abcd ... !(d < b)
    // acbd ... !(d < b)
    // cabd ... !(d < b)

    
    r(d, b) ? // d < b
              select_1_2(std::forward<T>(a), std::forward<W>(d), r)
            : select_1_2(std::forward<U>(b), std::forward<V>(c), r)
)

template <Regular T, Regular U, Regular V, Regular W>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W>)
inline constexpr
auto select_2_4_ab_cd(T&& a, U&& b, V&& c, W&& d) FN(
    // precondition: a <= b && c <= d

    
    d < b ? 
              select_1_2(std::forward<T>(a), std::forward<W>(d))
            : select_1_2(std::forward<U>(b), std::forward<V>(c))
)
        
template <Regular T, Regular U, Regular V, Regular W, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && Domain<R, T>)
inline constexpr
auto select_2_4_cd(T&& a, U&& b, V&& c, W&& d, R r) FN(
    // precondition: c <= d

    
    r(b, a) ? // b < a
              select_2_4_ab_cd(std::forward<T>(b), std::forward<U>(a), std::forward<W>(c), std::forward<V>(d), r)
            : select_2_4_ab_cd(std::forward<T>(a), std::forward<U>(b), std::forward<V>(c), std::forward<W>(d), r)
)

template <Regular T, Regular U, Regular V, Regular W>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W>)
inline constexpr
auto select_2_4_cd(T&& a, U&& b, V&& c, W&& d) FN(
    // precondition: c <= d

    
    b < a ? 
              select_2_4_ab_cd(std::forward<T>(b), std::forward<U>(a), std::forward<W>(c), std::forward<V>(d))
            : select_2_4_ab_cd(std::forward<T>(a), std::forward<U>(b), std::forward<V>(c), std::forward<W>(d))
)

template <Regular T, Regular U, Regular V, Regular W, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && Domain<R, T>)
inline constexpr
auto select_2_4(T&& a, U&& b, V&& c, W&& d, R r) FN(
    
    r(d, c) ? // d < c
              select_2_4_cd(std::forward<U>(a), std::forward<T>(b), std::forward<V>(d), std::forward<W>(c), r)
            : select_2_4_cd(std::forward<T>(a), std::forward<U>(b), std::forward<V>(c), std::forward<W>(d), r)
)

template <Regular T, Regular U, Regular V, Regular W>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W>)
inline constexpr
auto select_2_4(T&& a, U&& b, V&& c, W&& d) FN(
    d < c ?
              select_2_4_cd(std::forward<U>(a), std::forward<T>(b), std::forward<V>(d), std::forward<W>(c))
            : select_2_4_cd(std::forward<T>(a), std::forward<U>(b), std::forward<V>(c), std::forward<W>(d))
)

}} /*tao::algorithm*/

#undef FN
#include <tao/algorithm/concepts_undef.hpp>

#endif /*TAO_ALGORITHM_SELECTION_HPP_*/

#ifdef DOCTEST_LIBRARY_INCLUDED

TEST_CASE("[select_i_j] testing select_i_j selection algorithm") {
    using namespace tao::algorithm;
    using namespace std;

    int a = 3;
    int b = 3;
    int c = 4;
    int d = 4;


    SUBCASE("[select_i_2] testing select_i_2 selection algorithms") {
        CHECK(&select_0_2(a, b, less<>()) == &a);
        CHECK(&select_0_2(b, a, less<>()) == &b);
        CHECK(&select_0_2(a, c, less<>()) == &a);
        CHECK(&select_0_2(c, a, less<>()) == &a);
        CHECK(select_0_2(a, c, less<>()) == a);
        CHECK(select_0_2(c, a, less<>()) == a);

        CHECK(&select_1_2(a, b, less<>()) == &b);
        CHECK(&select_1_2(b, a, less<>()) == &a);
        CHECK(&select_1_2(a, c, less<>()) == &c);
        CHECK(&select_1_2(c, a, less<>()) == &c);
        CHECK(select_1_2(a, c, less<>()) == c);
        CHECK(select_1_2(c, a, less<>()) == c);

        CHECK(&select_0_2(a, b) == &a);
        CHECK(&select_0_2(b, a) == &b);
        CHECK(&select_0_2(a, c) == &a);
        CHECK(&select_0_2(c, a) == &a);
        CHECK(select_0_2(a, c) == a);
        CHECK(select_0_2(c, a) == a);

        CHECK(&select_1_2(a, b) == &b);
        CHECK(&select_1_2(b, a) == &a);
        CHECK(&select_1_2(a, c) == &c);
        CHECK(&select_1_2(c, a) == &c);
        CHECK(select_1_2(a, c) == c);
        CHECK(select_1_2(c, a) == c);
    }

    SUBCASE("[select_i_3] testing select_i_3 selection algorithm") {
        CHECK(&select_0_3(a, b, c, less<>()) == &a);
        CHECK(&select_0_3(a, c, b, less<>()) == &a);
        CHECK(&select_0_3(b, a, c, less<>()) == &b);
        CHECK(&select_0_3(b, c, a, less<>()) == &b);
        CHECK(&select_0_3(c, a, b, less<>()) == &a);
        CHECK(&select_0_3(c, b, a, less<>()) == &b);
        CHECK(select_0_3(a, c, d, less<>()) == a);
        CHECK(select_0_3(c, a, d, less<>()) == a);
        CHECK(select_0_3(d, c, a, less<>()) == a);

        CHECK(&select_2_3(b, c, d, less<>()) == &d);
        CHECK(&select_2_3(c, b, d, less<>()) == &d);
        CHECK(&select_2_3(b, d, c, less<>()) == &c);
        CHECK(&select_2_3(d, b, c, less<>()) == &c);
        CHECK(&select_2_3(c, d, b, less<>()) == &d);
        CHECK(&select_2_3(d, c, b, less<>()) == &c);
        CHECK(select_2_3(a, c, d, less<>()) == d);
        CHECK(select_2_3(c, a, d, less<>()) == c);
        CHECK(select_2_3(d, c, a, less<>()) == c);

        // Test select_1_3_ab
        CHECK(&select_1_3(a, b, c, less<>()) == &b);
        CHECK(&select_1_3(a, c, b, less<>()) == &b);
        CHECK(&select_1_3(b, a, c, less<>()) == &a);
        CHECK(&select_1_3(b, c, a, less<>()) == &a);
        CHECK(&select_1_3(c, a, b, less<>()) == &b);
        CHECK(&select_1_3(c, b, a, less<>()) == &a);
        CHECK(select_1_3(a, c, d, less<>()) == c);
        CHECK(select_1_3(c, a, d, less<>()) == c);
        CHECK(select_1_3(d, c, a, less<>()) == c);



        CHECK(&select_0_3(a, b, c) == &a);
        CHECK(&select_0_3(a, c, b) == &a);
        CHECK(&select_0_3(b, a, c) == &b);
        CHECK(&select_0_3(b, c, a) == &b);
        CHECK(&select_0_3(c, a, b) == &a);
        CHECK(&select_0_3(c, b, a) == &b);
        CHECK(select_0_3(a, c, d) == a);
        CHECK(select_0_3(c, a, d) == a);
        CHECK(select_0_3(d, c, a) == a);

        CHECK(&select_2_3(b, c, d) == &d);
        CHECK(&select_2_3(c, b, d) == &d);
        CHECK(&select_2_3(b, d, c) == &c);
        CHECK(&select_2_3(d, b, c) == &c);
        CHECK(&select_2_3(c, d, b) == &d);
        CHECK(&select_2_3(d, c, b) == &c);
        CHECK(select_2_3(a, c, d) == d);
        CHECK(select_2_3(c, a, d) == c);
        CHECK(select_2_3(d, c, a) == c);

        // Test select_1_3_ab
        CHECK(&select_1_3(a, b, c) == &b);
        CHECK(&select_1_3(a, c, b) == &b);
        CHECK(&select_1_3(b, a, c) == &a);
        CHECK(&select_1_3(b, c, a) == &a);
        CHECK(&select_1_3(c, a, b) == &b);
        CHECK(&select_1_3(c, b, a) == &a);
        CHECK(select_1_3(a, c, d) == c);
        CHECK(select_1_3(c, a, d) == c);
        CHECK(select_1_3(d, c, a) == c);        
    }
}


TEST_CASE("[select_i_4] testing select_i_4 selection algorithm") {
    using namespace tao::algorithm;
    using namespace std;

    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;

    CHECK(select_0_4(a, b, c, d, less<>()) == a);
    CHECK(select_0_4(a, b, d, c, less<>()) == a);
    CHECK(select_0_4(a, c, b, d, less<>()) == a);
    CHECK(select_0_4(a, c, d, b, less<>()) == a);
    CHECK(select_0_4(a, d, b, c, less<>()) == a);
    CHECK(select_0_4(a, d, c, b, less<>()) == a);

    CHECK(select_0_4(b, a, c, d, less<>()) == a);
    CHECK(select_0_4(b, a, d, c, less<>()) == a);
    CHECK(select_0_4(b, c, a, d, less<>()) == a);
    CHECK(select_0_4(b, c, d, a, less<>()) == a);
    CHECK(select_0_4(b, d, a, c, less<>()) == a);
    CHECK(select_0_4(b, d, c, a, less<>()) == a);

    CHECK(select_0_4(c, a, b, d, less<>()) == a);
    CHECK(select_0_4(c, a, d, b, less<>()) == a);
    CHECK(select_0_4(c, b, a, d, less<>()) == a);
    CHECK(select_0_4(c, b, d, a, less<>()) == a);
    CHECK(select_0_4(c, d, a, b, less<>()) == a);
    CHECK(select_0_4(c, d, b, a, less<>()) == a);

    CHECK(select_0_4(d, a, b, c, less<>()) == a);
    CHECK(select_0_4(d, a, c, b, less<>()) == a);
    CHECK(select_0_4(d, b, a, c, less<>()) == a);
    CHECK(select_0_4(d, b, c, a, less<>()) == a);
    CHECK(select_0_4(d, c, a, b, less<>()) == a);
    CHECK(select_0_4(d, c, b, a, less<>()) == a);


    CHECK(select_1_4(a, b, c, d, less<>()) == b);
    CHECK(select_1_4(a, b, d, c, less<>()) == b);
    CHECK(select_1_4(a, c, b, d, less<>()) == b);
    CHECK(select_1_4(a, c, d, b, less<>()) == b);
    CHECK(select_1_4(a, d, b, c, less<>()) == b);
    CHECK(select_1_4(a, d, c, b, less<>()) == b);

    CHECK(select_1_4(b, a, c, d, less<>()) == b);
    CHECK(select_1_4(b, a, d, c, less<>()) == b);
    CHECK(select_1_4(b, c, a, d, less<>()) == b);
    CHECK(select_1_4(b, c, d, a, less<>()) == b);
    CHECK(select_1_4(b, d, a, c, less<>()) == b);
    CHECK(select_1_4(b, d, c, a, less<>()) == b);

    CHECK(select_1_4(c, a, b, d, less<>()) == b);
    CHECK(select_1_4(c, a, d, b, less<>()) == b);
    CHECK(select_1_4(c, b, a, d, less<>()) == b);
    CHECK(select_1_4(c, b, d, a, less<>()) == b);
    CHECK(select_1_4(c, d, a, b, less<>()) == b);
    CHECK(select_1_4(c, d, b, a, less<>()) == b);

    CHECK(select_1_4(d, a, b, c, less<>()) == b);
    CHECK(select_1_4(d, a, c, b, less<>()) == b);
    CHECK(select_1_4(d, b, a, c, less<>()) == b);
    CHECK(select_1_4(d, b, c, a, less<>()) == b);
    CHECK(select_1_4(d, c, a, b, less<>()) == b);
    CHECK(select_1_4(d, c, b, a, less<>()) == b);
 

    CHECK(select_2_4(a, b, c, d, less<>()) == c);
    CHECK(select_2_4(a, b, d, c, less<>()) == c);
    CHECK(select_2_4(a, c, b, d, less<>()) == c);
    CHECK(select_2_4(a, c, d, b, less<>()) == c);
    CHECK(select_2_4(a, d, b, c, less<>()) == c);
    CHECK(select_2_4(a, d, c, b, less<>()) == c);

    CHECK(select_2_4(b, a, c, d, less<>()) == c);
    CHECK(select_2_4(b, a, d, c, less<>()) == c);
    CHECK(select_2_4(b, c, a, d, less<>()) == c);
    CHECK(select_2_4(b, c, d, a, less<>()) == c);
    CHECK(select_2_4(b, d, a, c, less<>()) == c);
    CHECK(select_2_4(b, d, c, a, less<>()) == c);

    CHECK(select_2_4(c, a, b, d, less<>()) == c);
    CHECK(select_2_4(c, a, d, b, less<>()) == c);
    CHECK(select_2_4(c, b, a, d, less<>()) == c);
    CHECK(select_2_4(c, b, d, a, less<>()) == c);
    CHECK(select_2_4(c, d, a, b, less<>()) == c);
    CHECK(select_2_4(c, d, b, a, less<>()) == c);

    CHECK(select_2_4(d, a, b, c, less<>()) == c);
    CHECK(select_2_4(d, a, c, b, less<>()) == c);
    CHECK(select_2_4(d, b, a, c, less<>()) == c);
    CHECK(select_2_4(d, b, c, a, less<>()) == c);
    CHECK(select_2_4(d, c, a, b, less<>()) == c);
    CHECK(select_2_4(d, c, b, a, less<>()) == c);


    CHECK(select_3_4(a, b, c, d, less<>()) == d);
    CHECK(select_3_4(a, b, d, c, less<>()) == d);
    CHECK(select_3_4(a, c, b, d, less<>()) == d);
    CHECK(select_3_4(a, c, d, b, less<>()) == d);
    CHECK(select_3_4(a, d, b, c, less<>()) == d);
    CHECK(select_3_4(a, d, c, b, less<>()) == d);

    CHECK(select_3_4(b, a, c, d, less<>()) == d);
    CHECK(select_3_4(b, a, d, c, less<>()) == d);
    CHECK(select_3_4(b, c, a, d, less<>()) == d);
    CHECK(select_3_4(b, c, d, a, less<>()) == d);
    CHECK(select_3_4(b, d, a, c, less<>()) == d);
    CHECK(select_3_4(b, d, c, a, less<>()) == d);

    CHECK(select_3_4(c, a, b, d, less<>()) == d);
    CHECK(select_3_4(c, a, d, b, less<>()) == d);
    CHECK(select_3_4(c, b, a, d, less<>()) == d);
    CHECK(select_3_4(c, b, d, a, less<>()) == d);
    CHECK(select_3_4(c, d, a, b, less<>()) == d);
    CHECK(select_3_4(c, d, b, a, less<>()) == d);

    CHECK(select_3_4(d, a, b, c, less<>()) == d);
    CHECK(select_3_4(d, a, c, b, less<>()) == d);
    CHECK(select_3_4(d, b, a, c, less<>()) == d);
    CHECK(select_3_4(d, b, c, a, less<>()) == d);
    CHECK(select_3_4(d, c, a, b, less<>()) == d);
    CHECK(select_3_4(d, c, b, a, less<>()) == d);


    // ----


    CHECK(select_0_4(a, b, c, d) == a);
    CHECK(select_0_4(a, b, d, c) == a);
    CHECK(select_0_4(a, c, b, d) == a);
    CHECK(select_0_4(a, c, d, b) == a);
    CHECK(select_0_4(a, d, b, c) == a);
    CHECK(select_0_4(a, d, c, b) == a);

    CHECK(select_0_4(b, a, c, d) == a);
    CHECK(select_0_4(b, a, d, c) == a);
    CHECK(select_0_4(b, c, a, d) == a);
    CHECK(select_0_4(b, c, d, a) == a);
    CHECK(select_0_4(b, d, a, c) == a);
    CHECK(select_0_4(b, d, c, a) == a);

    CHECK(select_0_4(c, a, b, d) == a);
    CHECK(select_0_4(c, a, d, b) == a);
    CHECK(select_0_4(c, b, a, d) == a);
    CHECK(select_0_4(c, b, d, a) == a);
    CHECK(select_0_4(c, d, a, b) == a);
    CHECK(select_0_4(c, d, b, a) == a);

    CHECK(select_0_4(d, a, b, c) == a);
    CHECK(select_0_4(d, a, c, b) == a);
    CHECK(select_0_4(d, b, a, c) == a);
    CHECK(select_0_4(d, b, c, a) == a);
    CHECK(select_0_4(d, c, a, b) == a);
    CHECK(select_0_4(d, c, b, a) == a);


    CHECK(select_1_4(a, b, c, d) == b);
    CHECK(select_1_4(a, b, d, c) == b);
    CHECK(select_1_4(a, c, b, d) == b);
    CHECK(select_1_4(a, c, d, b) == b);
    CHECK(select_1_4(a, d, b, c) == b);
    CHECK(select_1_4(a, d, c, b) == b);

    CHECK(select_1_4(b, a, c, d) == b);
    CHECK(select_1_4(b, a, d, c) == b);
    CHECK(select_1_4(b, c, a, d) == b);
    CHECK(select_1_4(b, c, d, a) == b);
    CHECK(select_1_4(b, d, a, c) == b);
    CHECK(select_1_4(b, d, c, a) == b);

    CHECK(select_1_4(c, a, b, d) == b);
    CHECK(select_1_4(c, a, d, b) == b);
    CHECK(select_1_4(c, b, a, d) == b);
    CHECK(select_1_4(c, b, d, a) == b);
    CHECK(select_1_4(c, d, a, b) == b);
    CHECK(select_1_4(c, d, b, a) == b);

    CHECK(select_1_4(d, a, b, c) == b);
    CHECK(select_1_4(d, a, c, b) == b);
    CHECK(select_1_4(d, b, a, c) == b);
    CHECK(select_1_4(d, b, c, a) == b);
    CHECK(select_1_4(d, c, a, b) == b);
    CHECK(select_1_4(d, c, b, a) == b);
 

    CHECK(select_2_4(a, b, c, d) == c);
    CHECK(select_2_4(a, b, d, c) == c);
    CHECK(select_2_4(a, c, b, d) == c);
    CHECK(select_2_4(a, c, d, b) == c);
    CHECK(select_2_4(a, d, b, c) == c);
    CHECK(select_2_4(a, d, c, b) == c);

    CHECK(select_2_4(b, a, c, d) == c);
    CHECK(select_2_4(b, a, d, c) == c);
    CHECK(select_2_4(b, c, a, d) == c);
    CHECK(select_2_4(b, c, d, a) == c);
    CHECK(select_2_4(b, d, a, c) == c);
    CHECK(select_2_4(b, d, c, a) == c);

    CHECK(select_2_4(c, a, b, d) == c);
    CHECK(select_2_4(c, a, d, b) == c);
    CHECK(select_2_4(c, b, a, d) == c);
    CHECK(select_2_4(c, b, d, a) == c);
    CHECK(select_2_4(c, d, a, b) == c);
    CHECK(select_2_4(c, d, b, a) == c);

    CHECK(select_2_4(d, a, b, c) == c);
    CHECK(select_2_4(d, a, c, b) == c);
    CHECK(select_2_4(d, b, a, c) == c);
    CHECK(select_2_4(d, b, c, a) == c);
    CHECK(select_2_4(d, c, a, b) == c);
    CHECK(select_2_4(d, c, b, a) == c);


    CHECK(select_3_4(a, b, c, d) == d);
    CHECK(select_3_4(a, b, d, c) == d);
    CHECK(select_3_4(a, c, b, d) == d);
    CHECK(select_3_4(a, c, d, b) == d);
    CHECK(select_3_4(a, d, b, c) == d);
    CHECK(select_3_4(a, d, c, b) == d);

    CHECK(select_3_4(b, a, c, d) == d);
    CHECK(select_3_4(b, a, d, c) == d);
    CHECK(select_3_4(b, c, a, d) == d);
    CHECK(select_3_4(b, c, d, a) == d);
    CHECK(select_3_4(b, d, a, c) == d);
    CHECK(select_3_4(b, d, c, a) == d);

    CHECK(select_3_4(c, a, b, d) == d);
    CHECK(select_3_4(c, a, d, b) == d);
    CHECK(select_3_4(c, b, a, d) == d);
    CHECK(select_3_4(c, b, d, a) == d);
    CHECK(select_3_4(c, d, a, b) == d);
    CHECK(select_3_4(c, d, b, a) == d);

    CHECK(select_3_4(d, a, b, c) == d);
    CHECK(select_3_4(d, a, c, b) == d);
    CHECK(select_3_4(d, b, a, c) == d);
    CHECK(select_3_4(d, b, c, a) == d);
    CHECK(select_3_4(d, c, a, b) == d);
    CHECK(select_3_4(d, c, b, a) == d);

}

#endif /*DOCTEST_LIBRARY_INCLUDED*/







// ------------------------------------------------------------------------------
// Original EoP code

// template <Regular T, StrictWeakOrdering R>
//     requires(Domain<R, T>)
// T const& select_0_2(T const& a, T const& b, R r) {
//     if (r(b, a)) return b;
//     return a;
// }

// template <Regular T, StrictWeakOrdering R>
//     requires(Domain<R, T>)
// T const& select_1_2(T const& a, T const& b, R r) {
//     if (r(b, a)) return a;
//     return b;
// }

// template <typename R>
//     requires(Relation(R))
// T const& select_0_3(T const& a, T const& b, T const& c, R r) {
//     return select_0_2(select_0_2(a, b, r), c, r);
// }

// template <typename R>
//     requires(Relation(R))
// const Domain(R)& select_2_3(const Domain(R)& a,
//                             const Domain(R)& b,
//                             const Domain(R)& c, R r)
// {
//     return select_1_2(select_1_2(a, b, r), c, r);
// }

// template <typename R>
//     requires(Relation(R))
// const Domain(R)& select_1_3_ab(const Domain(R)& a,
//                                const Domain(R)& b,
//                                const Domain(R)& c, R r)
// {
//     if (!r(c, b)) return b;     // $a$, $b$, $c$ are sorted
//     return select_1_2(a, c, r); // $b$ is not the median
// }

// template <typename R>
//     requires(Relation(R))
// const Domain(R)& select_1_3(const Domain(R)& a,
//                             const Domain(R)& b,
//                             const Domain(R)& c, R r)
// {
//     if (r(b, a)) return select_1_3_ab(b, a, c, r);
//     return              select_1_3_ab(a, b, c, r);
// }

// template <typename R>
//     requires(Relation(R))
// const Domain(R)& select_1_4_ab_cd(const Domain(R)& a,
//                                   const Domain(R)& b,
//                                   const Domain(R)& c,
//                                   const Domain(R)& d, R r) {
//     if (r(c, a)) return select_0_2(a, d, r);
//     return              select_0_2(b, c, r);
// }

// template <typename R>
//     requires(Relation(R))
// const Domain(R)& select_1_4_ab(const Domain(R)& a,
//                                const Domain(R)& b,
//                                const Domain(R)& c,
//                                const Domain(R)& d, R r) {
//     if (r(d, c)) return select_1_4_ab_cd(a, b, d, c, r);
//     return              select_1_4_ab_cd(a, b, c, d, r);
// }

// template <typename R>
//     requires(Relation(R))
// const Domain(R)& select_1_4(const Domain(R)& a,
//                             const Domain(R)& b,
//                             const Domain(R)& c,
//                             const Domain(R)& d, R r) {
//     if (r(b, a)) return select_1_4_ab(b, a, c, d, r);
//     return              select_1_4_ab(a, b, c, d, r);
// }

// // Exercise 4.4: select_2_4
