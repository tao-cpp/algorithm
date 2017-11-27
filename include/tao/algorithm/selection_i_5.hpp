//! \file tao/algorithm/selection.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2017
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_ALGORITHM_SELECTION_I_5_HPP_
#define TAO_ALGORITHM_SELECTION_I_5_HPP_

#include <algorithm>
#include <iterator>
#include <utility>

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/relation.hpp>
#include <tao/algorithm/selection_stability.hpp>
#include <tao/algorithm/type_attributes.hpp>


#define FN(body) -> decltype(body) {return body;}
#define CMP(s, R) compare_strict_or_reflexive<(s), R>()

namespace tao { namespace algorithm {

// ------------------------------------------------------------------------------
// 5 elements selection

// Complexity: 
//  select_0_5:       4 comparisons

//  select_1_5_ab_cd: ? comparisons
//  select_1_5_ab:    ? comparisons
//  select_1_5:       6 comparisons

//  select_2_5_ab_cd: ? comparisons
//  select_2_5_cd:    ? comparisons
//  select_2_5:       6 comparisons

//  select_3_5:       6 comparisons
//  select_4_5:       4 comparisons


template <Regular T, Regular U, Regular V, Regular W, Regular X, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && Domain<R, T>)
inline constexpr
auto select_0_5(T&& a, U&& b, V&& c, W&& d, X&& e, R r) FN(
    select_0_2(
            select_0_4(std::forward<T>(a), std::forward<U>(b), std::forward<V>(c), std::forward<W>(d), r), 
            std::forward<X>(e), r)
)

// template <Regular T, Regular U, Regular V, Regular W>
//     requires(SameType<T, U> && SameType<U, V> && SameType<V, W>)
// inline constexpr
// auto select_0_5(T&& a, U&& b, V&& c, W&& d) FN(
    
//     select_0_2(
//             select_0_3(std::forward<T>(a), std::forward<U>(b), std::forward<V>(c)), 
//             std::forward<W>(d))
// )

template <Regular T, Regular U, Regular V, Regular W, Regular X, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && Domain<R, T>)
inline constexpr
auto select_4_5(T&& a, U&& b, V&& c, W&& d, X&& e, R r) FN(
    select_1_2(
            select_3_4(std::forward<T>(a), std::forward<U>(b), std::forward<V>(c), std::forward<W>(d), r), 
            std::forward<X>(e), r)
)

// template <Regular T, Regular U, Regular V, Regular W>
//     requires(SameType<T, U> && SameType<U, V> && SameType<V, W>)
// inline constexpr
// auto select_3_5(T&& a, U&& b, V&& c, W&& d) FN(
    
//     select_1_2(
//             select_2_3(std::forward<T>(a), std::forward<U>(b), std::forward<V>(c)), 
//             std::forward<W>(d))
// )



template <Regular T, Regular U, Regular V, Regular W, Regular X, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && Domain<R, T>)
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

// template <Regular T, Regular U, Regular V, Regular W>
//     requires(SameType<T, U> && SameType<U, V> && SameType<V, W>)
// inline constexpr
// auto select_1_5_ab_cd(T&& a, U&& b, V&& c, W&& d) FN(
//     // precondition: a <= b && c <= d

    
//     c < a ? 
//               select_0_2(std::forward<T>(a), std::forward<W>(d))
//             : select_0_2(std::forward<U>(b), std::forward<V>(c))
// )

template <Regular T, Regular U, Regular V, Regular W, Regular X, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && Domain<R, T>)
inline constexpr
auto select_1_5_ab(T&& a, U&& b, V&& c, W&& d, R r) FN(
    // precondition: a <= b
    
    r(d, c) ? // d < c
              select_1_5_ab_cd(std::forward<T>(a), std::forward<U>(b), std::forward<W>(d), std::forward<V>(c), r)
            : select_1_5_ab_cd(std::forward<T>(a), std::forward<U>(b), std::forward<V>(c), std::forward<W>(d), r)
)

// template <Regular T, Regular U, Regular V, Regular W>
//     requires(SameType<T, U> && SameType<U, V> && SameType<V, W>)
// inline constexpr
// auto select_1_5_ab(T&& a, U&& b, V&& c, W&& d) FN(
//     // precondition: a <= b
//     d < c ? 
//               select_1_5_ab_cd(std::forward<T>(a), std::forward<U>(b), std::forward<W>(d), std::forward<V>(c))
//             : select_1_5_ab_cd(std::forward<T>(a), std::forward<U>(b), std::forward<V>(c), std::forward<W>(d))
// )

template <Regular T, Regular U, Regular V, Regular W, Regular X, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && Domain<R, T>)
inline constexpr
auto select_1_5(T&& a, U&& b, V&& c, W&& d, R r) FN(
    r(b, a) ? // b < a
              select_1_5_ab(std::forward<U>(b), std::forward<T>(a), std::forward<V>(c), std::forward<W>(d), r)
            : select_1_5_ab(std::forward<T>(a), std::forward<U>(b), std::forward<V>(c), std::forward<W>(d), r)
)

// template <Regular T, Regular U, Regular V, Regular W>
//     requires(SameType<T, U> && SameType<U, V> && SameType<V, W>)
// inline constexpr
// auto select_1_5(T&& a, U&& b, V&& c, W&& d) FN(
//     b < a ? 
//               select_1_5_ab(std::forward<U>(b), std::forward<T>(a), std::forward<V>(c), std::forward<W>(d))
//             : select_1_5_ab(std::forward<T>(a), std::forward<U>(b), std::forward<V>(c), std::forward<W>(d))
// )



// ------------------------------------------------------------------------------------------------


// Order selection procedures with stability indices


// compare_strict_or_reflexive<(ia < ib), R>()(b, a, r)) ? b : a;

// template <int ia, int ib, Regular T, Regular U, StrictWeakOrdering R>
//     requires(SameType<T, U> && Domain<R, T>)
// inline constexpr
// auto select_0_2(T&& a, U&& b, R r) FN(
//     CMP((ia < ib), R)(b, a, r) ? std::forward<U>(b) : std::forward<T>(a)
// )

// template <int ia, int ib, Regular T, Regular U, StrictWeakOrdering R>
//     requires(SameType<T, U> && Domain<R, T>)
// inline constexpr
// auto select_1_2(T&& a, U&& b, R r) FN(
//     CMP((ia < ib), R)(b, a, r) ? std::forward<T>(a) : std::forward<U>(b)
// )

// template <int ia, int ib, int ic, int id, 
//          Regular T, Regular U, Regular V, Regular W, StrictWeakOrdering R>
//     requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && Domain<R, T>)
// inline constexpr
// auto select_1_4_ab_cd(T&& a, U&& b, V&& c, W&& d, R r) FN(
//     CMP((ia < ic), R)(c, a, r)
//         ? (select_0_2<ia,id>(std::forward<T>(a), std::forward<W>(d), r))
//         : (select_0_2<ib,ic>(std::forward<U>(b), std::forward<V>(c), r))
// )

// template <int ia, int ib, int ic, int id,
//          Regular T, Regular U, Regular V, Regular W, StrictWeakOrdering R>
//     requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && Domain<R, T>)
// inline constexpr
// auto select_1_4_ab(T&& a, U&& b, V&& c, W&& d, R r) FN(
//     CMP((ic < id), R)(d, c, r)
//         ? (select_1_4_ab_cd<ia,ib,id,ic>(std::forward<T>(a), std::forward<U>(b), std::forward<W>(d), std::forward<V>(c), r))
//         : (select_1_4_ab_cd<ia,ib,ic,id>(std::forward<T>(a), std::forward<U>(b), std::forward<V>(c), std::forward<W>(d), r))
// )

// template <int ia, int ib, int ic, int id, 
//          Regular T, Regular U, Regular V, Regular W, StrictWeakOrdering R>
//     requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && Domain<R, T>)
// inline constexpr
// auto select_1_4(T&& a, U&& b, V&& c, W&& d, R r) FN(
//     CMP((ia < ib), R)(b, a, r)
//         ? (select_1_4_ab<ib,ia,ic,id>(std::forward<U>(b), std::forward<T>(a), std::forward<V>(c), std::forward<W>(d), r))
//         : (select_1_4_ab<ia,ib,ic,id>(std::forward<T>(a), std::forward<U>(b), std::forward<V>(c), std::forward<W>(d), r))
// )

// ---------------------------------

template <int ia, int ib, int ic, int id, int ie,
          Regular T, Regular U, Regular V, Regular W, Regular X, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && Domain<R, T>)
inline constexpr
auto select_2_5_ab_cd(T&& a, U&& b, V&& c, W&& d, X&& e, R r) FN(
    CMP((ia < ic), R)(c, a, r) 
        ? (select_1_4_ab<ia,ib,id,ie>(std::forward<T>(a), std::forward<U>(b), std::forward<W>(d), std::forward<X>(e), r))
        : (select_1_4_ab<ic,id,ib,ie>(std::forward<V>(c), std::forward<W>(d), std::forward<U>(b), std::forward<X>(e), r))
)

template <int ia, int ib, int ic, int id, int ie,
          Regular T, Regular U, Regular V, Regular W, Regular X, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && Domain<R, T>)
inline constexpr
auto select_2_5_ab(T&& a, U&& b, V&& c, W&& d, X&& e, R r) FN(
    CMP((ic < id), R)(d, c, r)
        ? (select_2_5_ab_cd<ia,ib,id,ic,ie>(std::forward<T>(a), std::forward<U>(b), std::forward<W>(d), std::forward<V>(c), std::forward<X>(e), r))
        : (select_2_5_ab_cd<ia,ib,ic,id,ie>(std::forward<T>(a), std::forward<U>(b), std::forward<V>(c), std::forward<W>(d), std::forward<X>(e), r))
)

template <int ia, int ib, int ic, int id, int ie,
          Regular T, Regular U, Regular V, Regular W, Regular X, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && Domain<R, T>)
inline constexpr
auto select_2_5(T&& a, U&& b, V&& c, W&& d, X&& e, R r) FN(
    CMP((ia < ib), R)(b, a, r)
        ? (select_2_5_ab<ib,ia,ic,id,ie>(std::forward<U>(b), std::forward<T>(a), std::forward<V>(c), std::forward<W>(d), std::forward<X>(e), r))
        : (select_2_5_ab<ia,ib,ic,id,ie>(std::forward<T>(a), std::forward<U>(b), std::forward<V>(c), std::forward<W>(d), std::forward<X>(e), r))
)

template <Regular T, Regular U, Regular V, Regular W, Regular X, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && Domain<R, T>)
inline constexpr
auto median_of_5(T&& a, U&& b, V&& c, W&& d, X&& e, R r) FN(
    (select_2_5<0,1,2,3,4>(std::forward<T>(a), std::forward<U>(b), std::forward<V>(c), std::forward<W>(d), std::forward<X>(e), r))
)

}} /*tao::algorithm*/

#undef FN
#undef CMP

#include <tao/algorithm/concepts_undef.hpp>

#endif /*TAO_ALGORITHM_SELECTION_I_5_HPP_*/


// #ifdef DOCTEST_LIBRARY_INCLUDED

// void do_tests(int (&p)[5], int median) {
//     using namespace tao::algorithm;
//     using namespace std;

//     do {
//         int const& m = median_of_5(p[0], p[1], p[2], p[3], p[4], less<>());
//         int* pp[5] = {&p[0], &p[1], &p[2], &p[3], &p[4]};

//         stable_sort(begin(pp), end(pp), [](int* a, int* b){
//             return *a < *b;
//         });

//         CHECK(m == median);
//         CHECK(*pp[2] == median);
//         CHECK(&m == pp[2]);

//     } while (next_permutation(begin(p), end(p), less<>()));
// }

// TEST_CASE("[select_i_5] 1 testing select_i_5 selection algorithm") {
//     int p[5] = {0, 1, 2, 3, 4};
//     do_tests(p, 2);
// }

// TEST_CASE("[select_i_5] 2 testing select_i_5 selection algorithm") {
//     int p[5] = {0, 0, 2, 3, 4};
//     do_tests(p, 2);
// }

// TEST_CASE("[select_i_5] 3 testing select_i_5 selection algorithm") {
//     int p[5] = {0, 0, 0, 3, 4};
//     do_tests(p, 0);
// }

// TEST_CASE("[select_i_5] 4 testing select_i_5 selection algorithm") {
//     int p[5] = {0, 0, 0, 0, 4};
//     do_tests(p, 0);
// }

// TEST_CASE("[select_i_5] 5 testing select_i_5 selection algorithm") {
//     int p[5] = {0, 0, 0, 0, 0};
//     do_tests(p, 0);
// }

// TEST_CASE("[select_i_5] 6 testing select_i_5 selection algorithm") {
//     int p[5] = {0, 0, 1, 1, 1};
//     do_tests(p, 1);
// }

// TEST_CASE("[select_i_5] 7 testing select_i_5 selection algorithm") {
//     int p[5] = {0, 0, 0, 1, 1};
//     do_tests(p, 0);
// }

// #endif /*DOCTEST_LIBRARY_INCLUDED*/




