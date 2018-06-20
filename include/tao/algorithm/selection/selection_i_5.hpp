//! \file tao/algorithm/selection/selection_i_5.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016-2018
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_ALGORITHM_SELECTION_SELECTION_I_5_HPP_
#define TAO_ALGORITHM_SELECTION_SELECTION_I_5_HPP_

#include <algorithm>
#include <iterator>
#include <utility>

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/relation.hpp>
#include <tao/algorithm/selection/selection_stability.hpp>
#include <tao/algorithm/type_attributes.hpp>


#define FN(body) -> decltype(body) {return body;}
#define CMP(s, R) compare_strict_or_reflexive<(s), R>()
#define _a std::forward<T>(a)
#define _b std::forward<U>(b)
#define _c std::forward<V>(c)
#define _d std::forward<W>(d)
#define _e std::forward<X>(e)

namespace tao { namespace algorithm {

// ------------------------------------------------------------------------------
// 5 elements selection

// Complexity: 
//  select_2_5_ab_cd: ? comparisons
//  select_2_5_cd:    ? comparisons
//  select_2_5:       6 comparisons

//  select_0_5:       4 comparisons

//  select_1_5_ab_cd: ? comparisons
//  select_1_5_ab:    ? comparisons
//  select_1_5:       6 comparisons

//  select_3_5:       6 comparisons
//  select_4_5:       4 comparisons


// template <Regular T, Regular U, Regular V, Regular W, Regular X, StrictWeakOrdering R>
//     requires(Same<T, U, V, W, X> && Domain<R, T>)
// inline constexpr
// auto select_0_5(T&& a, U&& b, V&& c, W&& d, X&& e, R r) FN(
//     select_0_2(
//             select_0_4(_a, _b, _c, _d, r), 
//             _e, r)
// )

// // template <Regular T, Regular U, Regular V, Regular W>
// //     requires(Same<T, U, V, W>)
// // inline constexpr
// // auto select_0_5(T&& a, U&& b, V&& c, W&& d) FN(
    
// //     select_0_2(
// //             select_0_3(_a, _b, _c), 
// //             _d)
// // )

// template <Regular T, Regular U, Regular V, Regular W, Regular X, StrictWeakOrdering R>
//     requires(Same<T, U, V, W, X> && Domain<R, T>)
// inline constexpr
// auto select_4_5(T&& a, U&& b, V&& c, W&& d, X&& e, R r) FN(
//     select_1_2(
//             select_3_4(_a, _b, _c, _d, r), 
//             _e, r)
// )

// // template <Regular T, Regular U, Regular V, Regular W>
// //     requires(Same<T, U, V, W>)
// // inline constexpr
// // auto select_3_5(T&& a, U&& b, V&& c, W&& d) FN(
    
// //     select_1_2(
// //             select_2_3(_a, _b, _c), 
// //             _d)
// // )



// template <Regular T, Regular U, Regular V, Regular W, Regular X, StrictWeakOrdering R>
//     requires(Same<T, U, V, W, X> && Domain<R, T>)
// inline constexpr
// auto select_1_4_ab_cd(T&& a, U&& b, V&& c, W&& d, R r) FN(
//     // precondition: a <= b && c <= d

//     // cdab ...  (c < a)
//     // cadb ...  (c < a)
//     // cabd ...  (c < a)
//     // abcd ... !(c < a)
//     // acbd ... !(c < a)
//     // acdb ... !(c < a)

    
//     r(c, a) ? // c < a
//               select_0_2(_a, _d, r)
//             : select_0_2(_b, _c, r)
// )

// // template <Regular T, Regular U, Regular V, Regular W>
// //     requires(Same<T, U, V, W>)
// // inline constexpr
// // auto select_1_5_ab_cd(T&& a, U&& b, V&& c, W&& d) FN(
// //     // precondition: a <= b && c <= d

    
// //     c < a ? 
// //               select_0_2(_a, _d)
// //             : select_0_2(_b, _c)
// // )

// template <Regular T, Regular U, Regular V, Regular W, Regular X, StrictWeakOrdering R>
//     requires(Same<T, U, V, W, X> && Domain<R, T>)
// inline constexpr
// auto select_1_5_ab(T&& a, U&& b, V&& c, W&& d, R r) FN(
//     // precondition: a <= b
    
//     r(d, c) ? // d < c
//               select_1_5_ab_cd(_a, _b, _d, _c, r)
//             : select_1_5_ab_cd(_a, _b, _c, _d, r)
// )

// // template <Regular T, Regular U, Regular V, Regular W>
// //     requires(Same<T, U, V, W>)
// // inline constexpr
// // auto select_1_5_ab(T&& a, U&& b, V&& c, W&& d) FN(
// //     // precondition: a <= b
// //     d < c ? 
// //               select_1_5_ab_cd(_a, _b, _d, _c)
// //             : select_1_5_ab_cd(_a, _b, _c, _d)
// // )

// template <Regular T, Regular U, Regular V, Regular W, Regular X, StrictWeakOrdering R>
//     requires(Same<T, U, V, W, X> && Domain<R, T>)
// inline constexpr
// auto select_1_5(T&& a, U&& b, V&& c, W&& d, R r) FN(
//     r(b, a) ? // b < a
//               select_1_5_ab(_b, _a, _c, _d, r)
//             : select_1_5_ab(_a, _b, _c, _d, r)
// )

// // template <Regular T, Regular U, Regular V, Regular W>
// //     requires(Same<T, U, V, W>)
// // inline constexpr
// // auto select_1_5(T&& a, U&& b, V&& c, W&& d) FN(
// //     b < a ? 
// //               select_1_5_ab(_b, _a, _c, _d)
// //             : select_1_5_ab(_a, _b, _c, _d)
// // )



// ------------------------------------------------------------------------------------------------
// Order selection procedures with stability indices
// ------------------------------------------------------------------------------------------------

//the median of five is the second smallest of the four elements remaining after we remove the smallest of the first four.

template <int ia, int ib, int ic, int id, int ie,
          Regular T, Regular U, Regular V, Regular W, Regular X, StrictWeakOrdering R>
    requires(Same<T, U, V, W, X> && Domain<R, T>)
inline constexpr
auto select_2_5_ab_cd(T&& a, U&& b, V&& c, W&& d, X&& e, R r) FN(
    // precondition: !r(b, a) && !r(d, c) -->  a <= b && c <= d
    CMP((ia < ic), R)(c, a, r) 
        ? (select_1_4_ab<ia,ib,id,ie>(_a, _b, _d, _e, r))
        : (select_1_4_ab<ic,id,ib,ie>(_c, _d, _b, _e, r))
)

template <int ia, int ib, int ic, int id, int ie,
          Regular T, Regular U, Regular V, Regular W, Regular X, StrictWeakOrdering R>
    requires(Same<T, U, V, W, X> && Domain<R, T>)
inline constexpr
auto select_2_5_ab(T&& a, U&& b, V&& c, W&& d, X&& e, R r) FN(
    // precondition: !r(b, a)  -->  a <= b
    CMP((ic < id), R)(d, c, r)
        ? (select_2_5_ab_cd<ia,ib,id,ic,ie>(_a, _b, _d, _c, _e, r))
        : (select_2_5_ab_cd<ia,ib,ic,id,ie>(_a, _b, _c, _d, _e, r))
)

template <int ia, int ib, int ic, int id, int ie,
          Regular T, Regular U, Regular V, Regular W, Regular X, StrictWeakOrdering R>
    requires(Same<T, U, V, W, X> && Domain<R, T>)
inline constexpr
auto select_2_5(T&& a, U&& b, V&& c, W&& d, X&& e, R r) FN(
    CMP((ia < ib), R)(b, a, r)
        ? (select_2_5_ab<ib,ia,ic,id,ie>(_b, _a, _c, _d, _e, r))
        : (select_2_5_ab<ia,ib,ic,id,ie>(_a, _b, _c, _d, _e, r))
)

template <Regular T, Regular U, Regular V, Regular W, Regular X, StrictWeakOrdering R>
    requires(Same<T, U, V, W, X> && Domain<R, T>)
inline constexpr
auto median_of_5(T&& a, U&& b, V&& c, W&& d, X&& e, R r) FN(
    (select_2_5<0,1,2,3,4>(_a, _b, _c, _d, _e, r))
)

// ------------------------------------------------------------------
// Average comparisons improved, Worst case is worst
// ------------------------------------------------------------------

template <int ia, int ib, int ic, int id, int ie,
          Regular T, Regular U, Regular V, Regular W, Regular X, StrictWeakOrdering R>
    requires(Same<T, U, V, W, X> && Domain<R, T>)
inline constexpr
auto select_2_5_abc(T&& a, U&& b, V&& c, W&& d, X&& e, R r) FN(
    // precondition: !r(b, a) && !r(c, b)  -->  a <= b && b <= c
    CMP((ib < id), R)(d, b, r)               //d < b 
        ? CMP((ib < ie), R)(e, b, r)         //e < b 
            ? (select_2_3<ia,id,ie>(_a, _d, _e, r))
            : _b
        : CMP((ib < ie), R)(e, b, r)         //e < b 
            ? _b 
            : (select_0_3<ic,id,ie>(_c, _d, _e, r))
)

template <int ia, int ib, int ic, int id, int ie,
          Regular T, Regular U, Regular V, Regular W, Regular X, StrictWeakOrdering R>
    requires(Same<T, U, V, W, X> && Domain<R, T>)
inline constexpr
auto select_2_5_ab_avg(T&& a, U&& b, V&& c, W&& d, X&& e, R r) FN(
    // precondition: !r(b, a)  -->  a <= b
    CMP((ib < ic), R)(c, b, r)          // c < b
        ? CMP((ia < ic), R)(c, a, r)    // c < a
            ? (select_2_5_abc<ic,ia,ib,id,ie>(_c, _a, _b, _d, _e, r))
            : (select_2_5_abc<ia,ic,ib,id,ie>(_a, _c, _b, _d, _e, r))
        : (select_2_5_abc<ia,ib,ic,id,ie>(_a, _b, _c, _d, _e, r))
)

template <int ia, int ib, int ic, int id, int ie,
          Regular T, Regular U, Regular V, Regular W, Regular X, StrictWeakOrdering R>
    requires(Same<T, U, V, W, X> && Domain<R, T>)
inline constexpr
auto select_2_5_avg(T&& a, U&& b, V&& c, W&& d, X&& e, R r) FN(
    CMP((ia < ib), R)(b, a, r)
        ? (select_2_5_ab_avg<ib,ia,ic,id,ie>(_b, _a, _c, _d, _e, r))
        : (select_2_5_ab_avg<ia,ib,ic,id,ie>(_a, _b, _c, _d, _e, r))
)

template <Regular T, Regular U, Regular V, Regular W, Regular X, StrictWeakOrdering R>
    requires(Same<T, U, V, W, X> && Domain<R, T>)
inline constexpr
auto median_of_5_avg(T&& a, U&& b, V&& c, W&& d, X&& e, R r) FN(
    (select_2_5_avg<0,1,2,3,4>(_a, _b, _c, _d, _e, r))
)

}} /*tao::algorithm*/

#undef FN
#undef CMP
#undef _a
#undef _b
#undef _c
#undef _d
#undef _e

#include <tao/algorithm/concepts_undef.hpp>

#endif /*TAO_ALGORITHM_SELECTION_SELECTION_I_5_HPP_*/

#ifdef DOCTEST_LIBRARY_INCLUDED
using namespace tao::algorithm;
using namespace std;

void do_tests(int (&p)[5], int median) {

    do {
        int const& m1 = median_of_5(p[0], p[1], p[2], p[3], p[4], less<>());
        int const& m2 = median_of_5_avg(p[0], p[1], p[2], p[3], p[4], less<>());
        // int const& m = select_2_5<0,1,2,3,4>(p[0], p[1], p[2], p[3], p[4], less<>());
        int* pp[5] = {&p[0], &p[1], &p[2], &p[3], &p[4]};

        stable_sort(begin(pp), end(pp), [](int* a, int* b){
            return *a < *b;
        });

        CHECK(*pp[2] == median);
        CHECK(m1 == median);
        CHECK(&m1 == pp[2]);

        CHECK(m2 == median);
        CHECK(&m2 == pp[2]);

    } while (next_permutation(begin(p), end(p), less<>()));
}

TEST_CASE("[median_of_5] 1 testing median_of_5 selection algorithm") {
    int p[5] = {0, 1, 2, 3, 4};
    do_tests(p, 2);
}

TEST_CASE("[median_of_5] 2 testing median_of_5 selection algorithm") {
    int p[5] = {0, 0, 2, 3, 4};
    do_tests(p, 2);
}

TEST_CASE("[median_of_5] 3 testing median_of_5 selection algorithm") {
    int p[5] = {0, 0, 0, 3, 4};
    do_tests(p, 0);
}

TEST_CASE("[median_of_5] 4 testing median_of_5 selection algorithm") {
    int p[5] = {0, 0, 0, 0, 4};
    do_tests(p, 0);
}

TEST_CASE("[median_of_5] 5 testing median_of_5 selection algorithm") {
    int p[5] = {0, 0, 0, 0, 0};
    do_tests(p, 0);
}

TEST_CASE("[median_of_5] 6 testing median_of_5 selection algorithm") {
    int p[5] = {0, 0, 1, 1, 1};
    do_tests(p, 1);
}

TEST_CASE("[median_of_5] 7 testing median_of_5 selection algorithm") {
    int p[5] = {0, 0, 0, 1, 1};
    do_tests(p, 0);
}

#endif /*DOCTEST_LIBRARY_INCLUDED*/
