//! \file tao/algorithm/selection.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2017
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//TODO(fernando): complete!

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
#define _a std::forward<T>(a)
#define _b std::forward<U>(b)
#define _c std::forward<V>(c)
#define _d std::forward<W>(d)
#define _e std::forward<X>(e)
#define _f std::forward<Y>(f)
#define _g std::forward<Z>(g)

namespace tao { namespace algorithm {

// ------------------------------------------------------------------------------
// 7 elements selection

// Complexity: 
//  select_3_7:       10* comparisons


// ------------------------------------------------------------------------------------------------


// Order selection procedures with stability indices

// ---------------------------------

// template <int ia, int ib, int ic, int id, int ie,
//           Regular T, Regular U, Regular V, Regular W, Regular X, StrictWeakOrdering R>
//     requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && Domain<R, T>)
// inline constexpr
// auto select_3_7_ab_cd(T&& a, U&& b, V&& c, W&& d, X&& e, R r) FN(
//     // CMP((ia < ic), R)(c, a, r) 
//     //     ? (select_1_4_ab<ia,ib,id,ie>(_a, _b, _d, _e, r))
//     //     : (select_1_4_ab<ic,id,ib,ie>(_c, _d, _b, _e, r))

//     CMP((ia < ic), R)(c, a, r) 
//         ? (select_1_4_ab<ia,ib,id,ie>(_a, _b, _d, _e, r))
//         : (select_1_4_ab<ic,id,ib,ie>(_c, _d, _b, _e, r))

// )

// template <int ia, int ib, int ic, int id, int ie,
//           Regular T, Regular U, Regular V, Regular W, Regular X, StrictWeakOrdering R>
//     requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && Domain<R, T>)
// inline constexpr
// auto select_3_7_ab(T&& a, U&& b, V&& c, W&& d, X&& e, R r) FN(
//     CMP((ic < id), R)(d, c, r)
//         ? (select_3_7_ab_cd<ia,ib,id,ic,ie>(_a, _b, _d, _c, _e, r))
//         : (select_3_7_ab_cd<ia,ib,ic,id,ie>(_a, _b, _c, _d, _e, r))
// )

template <int ia, int ib, int ic, int id, int ie, int fi, int ig,
          Regular T, Regular U, Regular V, Regular W, Regular X, Regular Y, Regular Z, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && SameType<X, Y> && SameType<Y, Z> && Domain<R, T>)
inline constexpr
auto select_3_7(T&& a, U&& b, V&& c, W&& d, X&& e, Y&& f, Z&& g, R r) FN(
    CMP((ia < ib), R)(b, a, r)
        ? (select_3_7_ab<ib,ia,ic,id,ie,fi,ig>(_b, _a, _c, _d, _e, _f, _g, r))
        : (select_3_7_ab<ia,ib,ic,id,ie,fi,ig>(_a, _b, _c, _d, _e, _f, _g, r))
)

// template <Regular T, Regular U, Regular V, Regular W, Regular X, StrictWeakOrdering R>
//     requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && Domain<R, T>)
// inline constexpr
// auto median_of_5(T&& a, U&& b, V&& c, W&& d, X&& e, R r) FN(
//     (select_3_7<0,1,2,3,4>(_a, _b, _c, _d, _e, r))
// )




}} /*tao::algorithm*/

#undef FN
#undef CMP
#undef _a
#undef _b
#undef _c
#undef _d
#undef _e
#undef _f
#undef _g

#include <tao/algorithm/concepts_undef.hpp>

#endif /*TAO_ALGORITHM_SELECTION_I_5_HPP_*/


#ifdef DOCTEST_LIBRARY_INCLUDED
using namespace tao::algorithm;
using namespace std;

// void do_tests(int (&p)[5], int median) {

//     do {
//         // int const& m = median_of_5(p[0], p[1], p[2], p[3], p[4], less<>());
//         int const& m = select_3_7<0,1,2,3,4>(p[0], p[1], p[2], p[3], p[4], less<>());
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

#endif /*DOCTEST_LIBRARY_INCLUDED*/




