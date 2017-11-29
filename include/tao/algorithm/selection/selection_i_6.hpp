//! \file tao/algorithm/selection/selection_i_6.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2017
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_ALGORITHM_SELECTION_SELECTION_I_6_HPP_
#define TAO_ALGORITHM_SELECTION_SELECTION_I_6_HPP_

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
#define _f std::forward<Y>(f)

namespace tao { namespace algorithm {

// ------------------------------------------------------------------------------
// 6 elements selection

// Complexity: 

//      select_2_6_abc = 1 + select_2_6_abc_de = 1 + 4 = 5 or 1 + 5 = 6

//      select_2_6_abc_de = -- 1 + select_2_6_abc_def = 1 + 3 = 4
//                          -- 2 + select_2_6_abc_def = 2 + 3 = 5

//      select_2_6_abc_def = 2 + select_0_2 = 2 + 1 = 3



template <int ia, int ib, int ic, int id, int ie, int fi,
          Regular T, Regular U, Regular V, Regular W, Regular X, Regular Y, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && SameType<X, Y> && Domain<R, T>)
inline constexpr
auto select_2_6_abc_def(T&& a, U&& b, V&& c, W&& d, X&& e, Y&& f, R r) FN(
    // precondition: !r(b, a) && !r(c, b) && !r(e, d) && !r(f, e)  -->  a <= b && b <= c && d <= e && e <= f
    CMP((ia < id), R)(d, a, r)                  // d < a
        ? CMP((ia < ie), R)(e, a, r)            // e < a
            ? (select_0_2<ia,fi>(_a, _f, r))
            : (select_0_2<ib,ie>(_b, _e, r))
        : CMP((ib < id), R)(d, b, r)            // d < b
            ? (select_0_2<ib,ie>(_b, _e, r))
            : (select_0_2<ic,id>(_c, _d, r))
)

template <int ia, int ib, int ic, int id, int ie, int fi,
          Regular T, Regular U, Regular V, Regular W, Regular X, Regular Y, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && SameType<X, Y> && Domain<R, T>)
inline constexpr
auto select_2_6_abc_de(T&& a, U&& b, V&& c, W&& d, X&& e, Y&& f, R r) FN(
    // precondition: !r(b, a) && !r(c, b) && !r(e, d)  -->  a <= b && b <= c && d <= e
    CMP((ie < fi), R)(f, e, r)          // f < e
        ? CMP((id < fi), R)(f, d, r)    // f < d
            ? (select_2_6_abc_def<ia,ib,ic,fi,id,ie>(_a, _b, _c, _f, _d, _e, r))
            : (select_2_6_abc_def<ia,ib,ic,id,fi,ie>(_a, _b, _c, _d, _f, _e, r))
        :     (select_2_6_abc_def<ia,ib,ic,id,ie,fi>(_a, _b, _c, _d, _e, _f, r))
)

template <int ia, int ib, int ic, int id, int ie, int fi,
          Regular T, Regular U, Regular V, Regular W, Regular X, Regular Y, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && SameType<X, Y> && Domain<R, T>)
inline constexpr
auto select_2_6_abc(T&& a, U&& b, V&& c, W&& d, X&& e, Y&& f, R r) FN(
    // precondition: !r(b, a) && !r(c, b)  -->  a <= b && b <= c
    CMP((id < ie), R)(e, d, r) // e < d
            ? (select_2_6_abc_de<ia,ib,ic,ie,id,fi>(_a, _b, _c, _e, _d, _f, r))
            : (select_2_6_abc_de<ia,ib,ic,id,ie,fi>(_a, _b, _c, _d, _e, _f, r))
)

}} /*tao::algorithm*/

#undef FN
#undef CMP
#undef _a
#undef _b
#undef _c
#undef _d
#undef _e
#undef _f

#include <tao/algorithm/concepts_undef.hpp>

#endif /*TAO_ALGORITHM_SELECTION_SELECTION_I_6_HPP_*/


// #ifdef DOCTEST_LIBRARY_INCLUDED
// using namespace tao::algorithm;
// using namespace std;

// void do_tests(int (&p)[5], int median) {

//     do {
//         int const& m1 = median_of_5(p[0], p[1], p[2], p[3], p[4], less<>());
//         int const& m2 = median_of_5_avg(p[0], p[1], p[2], p[3], p[4], less<>());
//         // int const& m = select_2_5<0,1,2,3,4>(p[0], p[1], p[2], p[3], p[4], less<>());
//         int* pp[5] = {&p[0], &p[1], &p[2], &p[3], &p[4]};

//         stable_sort(begin(pp), end(pp), [](int* a, int* b){
//             return *a < *b;
//         });

//         CHECK(*pp[2] == median);
//         CHECK(m1 == median);
//         CHECK(&m1 == pp[2]);

//         CHECK(m2 == median);
//         CHECK(&m2 == pp[2]);

//     } while (next_permutation(begin(p), end(p), less<>()));
// }

// TEST_CASE("[median_of_5] 1 testing median_of_5 selection algorithm") {
//     int p[5] = {0, 1, 2, 3, 4};
//     do_tests(p, 2);
// }

// TEST_CASE("[median_of_5] 2 testing median_of_5 selection algorithm") {
//     int p[5] = {0, 0, 2, 3, 4};
//     do_tests(p, 2);
// }

// TEST_CASE("[median_of_5] 3 testing median_of_5 selection algorithm") {
//     int p[5] = {0, 0, 0, 3, 4};
//     do_tests(p, 0);
// }

// TEST_CASE("[median_of_5] 4 testing median_of_5 selection algorithm") {
//     int p[5] = {0, 0, 0, 0, 4};
//     do_tests(p, 0);
// }

// TEST_CASE("[median_of_5] 5 testing median_of_5 selection algorithm") {
//     int p[5] = {0, 0, 0, 0, 0};
//     do_tests(p, 0);
// }

// TEST_CASE("[median_of_5] 6 testing median_of_5 selection algorithm") {
//     int p[5] = {0, 0, 1, 1, 1};
//     do_tests(p, 1);
// }

// TEST_CASE("[median_of_5] 7 testing median_of_5 selection algorithm") {
//     int p[5] = {0, 0, 0, 1, 1};
//     do_tests(p, 0);
// }

// #endif /*DOCTEST_LIBRARY_INCLUDED*/
