//! \file tao/algorithm/selection/selection_stability.hpp
// Tao.Algorithm
//
// Copyright (c) 2016-2020 Fernando Pelliccioni.
//
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

// Order selection procedures with stability indices

#ifndef TAO_ALGORITHM_SELECTION_STABILITY_HPP_
#define TAO_ALGORITHM_SELECTION_STABILITY_HPP_

#include <algorithm>
#include <iterator>
#include <utility>

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/relation.hpp>
#include <tao/algorithm/type_attributes.hpp>


#define FN(body) -> decltype(body) {return body;}
#define CMP(s, R) compare_strict_or_reflexive<(s), R>()
// compare_strict_or_reflexive<(ia < ib), R>()(b, a, r)) ? b : a;

#define _a std::forward<T>(a)
#define _b std::forward<U>(b)
#define _c std::forward<V>(c)
#define _d std::forward<W>(d)

namespace tao { namespace algorithm {

// ------------------------------------------------------------------------------
// 2 elements selection
// Complexity: 1 comparison

template <int ia, int ib, Regular T, Regular U, StrictWeakOrdering R>
    requires(Same<T, U> && Domain<R, T>)
inline constexpr
auto select_0_2(T&& a, U&& b, R r) FN(
    CMP((ia < ib), R)(b, a, r) ? _b : _a
)

template <int ia, int ib, Regular T, Regular U>
    requires(Same<T, U>)
inline constexpr
auto select_0_2(T&& a, U&& b) FN(
    (select_0_2<ia,ib>(_a, _b, std::less<>()))
)

template <int ia, int ib, Regular T, Regular U, StrictWeakOrdering R>
    requires(Same<T, U> && Domain<R, T>)
inline constexpr
auto select_1_2(T&& a, U&& b, R r) FN(
    CMP((ia < ib), R)(b, a, r) ? _a : _b
)

template <int ia, int ib, Regular T, Regular U>
    requires(Same<T, U>)
inline constexpr
auto select_1_2(T&& a, U&& b) FN(
    (select_1_2<ia,ib>(_a, _b, std::less<>()))
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

template <int ia, int ib, int ic, Regular T, Regular U, Regular V, StrictWeakOrdering R>
    requires(Same<T, U, V> && Domain<R, T>)
inline constexpr
auto select_0_3(T&& a, U&& b, V&& c, R r) FN(
    CMP((ia < ib), R)(b, a, r) 
        ? (select_0_2<ib,ic>(_b, _c, r))
        : (select_0_2<ia,ic>(_a, _c, r))
)

// template <int ia, int ib, int ic, Regular T, Regular U, Regular V>
//     requires(Same<T, U, V>)
// inline constexpr
// auto select_0_3(T&& a, U&& b, V&& c) FN(
    
//     select_0_2(
//             select_0_2(_a, _b), 
//             _c)
// )

template <int ia, int ib, int ic, Regular T, Regular U, Regular V, StrictWeakOrdering R>
    requires(Same<T, U, V> && Domain<R, T>)
inline constexpr
auto select_2_3(T&& a, U&& b, V&& c, R r) FN(
    CMP((ia < ib), R)(b, a, r) 
        ? (select_1_2<ia,ic>(_a, _c, r))
        : (select_1_2<ib,ic>(_b, _c, r))
            
)

// template <int ia, int ib, int ic, Regular T, Regular U, Regular V>
//     requires(Same<T, U, V>)
// inline constexpr
// auto select_2_3(T&& a, U&& b, V&& c) FN(
    
//     select_1_2(
//             select_1_2(_a, _b), 
//             _c)
// )

template <int ia, int ib, int ic, Regular T, Regular U, Regular V, StrictWeakOrdering R>
    requires(Same<T, U, V> && Domain<R, T>)
inline constexpr
auto select_1_3_ab(T&& a, U&& b, V&& c, R r) FN(
    // precondition: a <= b
    
    ! CMP((ib < ic), R)(c, b, r) //!(c < b) -> c >= b
        ? _b                                              // a, b, c are sorted
        : (select_1_2<ia,ic>(_a, _c, r))  // b is not the median
)

template <int ia, int ib, int ic, Regular T, Regular U, Regular V, StrictWeakOrdering R>
    requires(Same<T, U, V> && Domain<R, T>)
inline constexpr
auto select_1_3(T&& a, U&& b, V&& c, R r) FN(
    CMP((ia < ib), R)(b, a, r) 
        ? (select_1_3_ab<ib,ia,ic>(_b, _a, _c, r))
        : (select_1_3_ab<ia,ib,ic>(_a, _b, _c, r))
)

// template <int ia, int ib, int ic, Regular T, Regular U, Regular V>
//     requires(Same<T, U, V>)
// inline constexpr
// auto select_1_3_ab(T&& a, U&& b, V&& c) FN(
//     // precondition: a <= b
    
//     !(c < b) ? //!(c < b) -> c >= b
//                   _b                              // a, b, c are sorted
//                 : select_1_2(_a, _c)  // b is not the median
// )

// template <int ia, int ib, int ic, Regular T, Regular U, Regular V>
//     requires(Same<T, U, V>)
// inline constexpr
// auto select_1_3(T&& a, U&& b, V&& c) FN(
    
//     b < a ? 
//               select_1_3_ab(_b, _a, _c) 
//             : select_1_3_ab(_a, _b, _c)
// )

// // ------------------------------------------------------------------------------
// // 4 elements selection

// // Complexity: 
// //  select_0_4:       3 comparisons
// //  select_1_4_ab_cd: 2 comparisons
// //  select_1_4_ab:    3 comparisons
// //  select_1_4:       4 comparisons
// //  select_2_4_ab_cd: 2 comparisons
// //  select_2_4_cd:    3 comparisons
// //  select_2_4:       4 comparisons
// //  select_3_4:       3 comparisons


// template <int ia, int ib, int ic, int id,
//           Regular T, Regular U, Regular V, Regular W, StrictWeakOrdering R>
//     requires(Same<T, U, V, W> && Domain<R, T>)
// inline constexpr
// auto select_0_4(T&& a, U&& b, V&& c, W&& d, R r) FN(
    
//     select_0_2(
//             select_0_3(_a, _b, _c, r), 
//             _d, r)
// )

// template <int ia, int ib, int ic, int id,
//           Regular T, Regular U, Regular V, Regular W>
//     requires(Same<T, U, V, W>)
// inline constexpr
// auto select_0_4(T&& a, U&& b, V&& c, W&& d) FN(
    
//     select_0_2(
//             select_0_3(_a, _b, _c), 
//             _d)
// )

// template <int ia, int ib, int ic, int id,
//           Regular T, Regular U, Regular V, Regular W, StrictWeakOrdering R>
//     requires(Same<T, U, V, W> && Domain<R, T>)
// inline constexpr
// auto select_3_4(T&& a, U&& b, V&& c, W&& d, R r) FN(
    
//     select_1_2(
//             select_2_3(_a, _b, _c, r), 
//             _d, r)
// )

// template <int ia, int ib, int ic, int id,
//           Regular T, Regular U, Regular V, Regular W>
//     requires(Same<T, U, V, W>)
// inline constexpr
// auto select_3_4(T&& a, U&& b, V&& c, W&& d) FN(
    
//     select_1_2(
//             select_2_3(_a, _b, _c), 
//             _d)
// )



template <int ia, int ib, int ic, int id,
          Regular T, Regular U, Regular V, Regular W, StrictWeakOrdering R>
    requires(Same<T, U, V, W> && Domain<R, T>)
inline constexpr
auto select_1_4_ab_cd(T&& a, U&& b, V&& c, W&& d, R r) FN(
    // precondition: a <= b && c <= d

    // cdab ...  (c < a)
    // cadb ...  (c < a)
    // cabd ...  (c < a)
    // abcd ... !(c < a)
    // acbd ... !(c < a)
    // acdb ... !(c < a)

    CMP((ia < ic), R)(c, a, r) // c < a
        ? (select_0_2<ia,id>(_a, _d, r))
        : (select_0_2<ib,ic>(_b, _c, r))
)

// template <int ia, int ib, int ic, int id,
//           Regular T, Regular U, Regular V, Regular W>
//     requires(Same<T, U, V, W>)
// inline constexpr
// auto select_1_4_ab_cd(T&& a, U&& b, V&& c, W&& d) FN(
//     // precondition: a <= b && c <= d
//     c < a ? 
//               select_0_2(_a, _d)
//             : select_0_2(_b, _c)
// )

template <int ia, int ib, int ic, int id,
          Regular T, Regular U, Regular V, Regular W, StrictWeakOrdering R>
    requires(Same<T, U, V, W> && Domain<R, T>)
inline constexpr
auto select_1_4_ab(T&& a, U&& b, V&& c, W&& d, R r) FN(
    // precondition: a <= b
    CMP((ic < id), R)(d, c, r) // d < c
            ? (select_1_4_ab_cd<ia,ib,id,ic>(_a, _b, _d, _c, r))
            : (select_1_4_ab_cd<ia,ib,ic,id>(_a, _b, _c, _d, r))
)

// template <int ia, int ib, int ic, int id,
//           Regular T, Regular U, Regular V, Regular W>
//     requires(Same<T, U, V, W>)
// inline constexpr
// auto select_1_4_ab(T&& a, U&& b, V&& c, W&& d) FN(
//     // precondition: a <= b

    
//     d < c ? 
//               select_1_4_ab_cd(_a, _b, _d, _c)
//             : select_1_4_ab_cd(_a, _b, _c, _d)
// )

// template <int ia, int ib, int ic, int id,
//           Regular T, Regular U, Regular V, Regular W, StrictWeakOrdering R>
//     requires(Same<T, U, V, W> && Domain<R, T>)
// inline constexpr
// auto select_1_4(T&& a, U&& b, V&& c, W&& d, R r) FN(
    
//     CMP((ia < ib), R)(b, a) ? // b < a
//               select_1_4_ab(_b, _a, _c, _d, r)
//             : select_1_4_ab(_a, _b, _c, _d, r)
// )

// template <int ia, int ib, int ic, int id,
//           Regular T, Regular U, Regular V, Regular W>
//     requires(Same<T, U, V, W>)
// inline constexpr
// auto select_1_4(T&& a, U&& b, V&& c, W&& d) FN(
//     b < a ? 
//               select_1_4_ab(_b, _a, _c, _d)
//             : select_1_4_ab(_a, _b, _c, _d)
// )
        
// template <int ia, int ib, int ic, int id,
//           Regular T, Regular U, Regular V, Regular W, StrictWeakOrdering R>
//     requires(Same<T, U, V, W> && Domain<R, T>)
// inline constexpr
// auto select_2_4_ab_cd(T&& a, U&& b, V&& c, W&& d, R r) FN(
//     // precondition: a <= b && c <= d

//     // acdb ...  (d < b)
//     // cadb ...  (d < b)
//     // cdab ...  (d < b)
//     // abcd ... !(d < b)
//     // acbd ... !(d < b)
//     // cabd ... !(d < b)

    
//     CMP((ia < ib), R)(d, b) ? // d < b
//               select_1_2(_a, _d, r)
//             : select_1_2(_b, _c, r)
// )

// template <int ia, int ib, int ic, int id,
//           Regular T, Regular U, Regular V, Regular W>
//     requires(Same<T, U, V, W>)
// inline constexpr
// auto select_2_4_ab_cd(T&& a, U&& b, V&& c, W&& d) FN(
//     // precondition: a <= b && c <= d

    
//     d < b ? 
//               select_1_2(_a, _d)
//             : select_1_2(_b, _c)
// )
        
// template <int ia, int ib, int ic, int id,
//           Regular T, Regular U, Regular V, Regular W, StrictWeakOrdering R>
//     requires(Same<T, U, V, W> && Domain<R, T>)
// inline constexpr
// auto select_2_4_cd(T&& a, U&& b, V&& c, W&& d, R r) FN(
//     // precondition: c <= d

    
//     CMP((ia < ib), R)(b, a) ? // b < a
//               select_2_4_ab_cd(std::forward<T>(b), std::forward<U>(a), std::forward<W>(c), std::forward<V>(d), r)
//             : select_2_4_ab_cd(_a, _b, _c, _d, r)
// )

// template <int ia, int ib, int ic, int id,
//           Regular T, Regular U, Regular V, Regular W>
//     requires(Same<T, U, V, W>)
// inline constexpr
// auto select_2_4_cd(T&& a, U&& b, V&& c, W&& d) FN(
//     // precondition: c <= d

    
//     b < a ? 
//               select_2_4_ab_cd(std::forward<T>(b), std::forward<U>(a), std::forward<W>(c), std::forward<V>(d))
//             : select_2_4_ab_cd(_a, _b, _c, _d)
// )

// template <int ia, int ib, int ic, int id,
//           Regular T, Regular U, Regular V, Regular W, StrictWeakOrdering R>
//     requires(Same<T, U, V, W> && Domain<R, T>)
// inline constexpr
// auto select_2_4(T&& a, U&& b, V&& c, W&& d, R r) FN(
    
//     CMP((ia < ib), R)(d, c) ? // d < c
//               select_2_4_cd(std::forward<U>(a), std::forward<T>(b), std::forward<V>(d), std::forward<W>(c), r)
//             : select_2_4_cd(_a, _b, _c, _d, r)
// )

// template <int ia, int ib, int ic, int id,
//           Regular T, Regular U, Regular V, Regular W>
//     requires(Same<T, U, V, W>)
// inline constexpr
// auto select_2_4(T&& a, U&& b, V&& c, W&& d) FN(
//     d < c ?
//               select_2_4_cd(std::forward<U>(a), std::forward<T>(b), std::forward<V>(d), std::forward<W>(c))
//             : select_2_4_cd(_a, _b, _c, _d)
// )

}} /*tao::algorithm*/

#undef FN
#undef CMP

#undef _a
#undef _b
#undef _c
#undef _d

#include <tao/algorithm/concepts_undef.hpp>

#endif /*TAO_ALGORITHM_SELECTION_STABILITY_HPP_*/

#ifdef DOCTEST_LIBRARY_INCLUDED

TEST_CASE("[select_i_j] testing select_i_j selection algorithm") {
    using namespace tao::algorithm;
    using namespace std;

    int a = 3;
    int b = 3;
    int c = 4;
    int d = 4;
    int a2 = 3;


    SUBCASE("[select_i_2] (0,1) testing select_i_2 selection algorithms") {
        CHECK(select_0_2<0,1>(a, c, less<>()) == a);
        CHECK(select_0_2<0,1>(c, a, less<>()) == a);
        CHECK(&select_0_2<0,1>(a, b, less<>()) == &a);
        CHECK(&select_0_2<0,1>(b, a, less<>()) == &b);
        CHECK(&select_0_2<0,1>(a, c, less<>()) == &a);
        CHECK(&select_0_2<0,1>(c, a, less<>()) == &a);

        CHECK(select_1_2<0,1>(a, c, less<>()) == c);
        CHECK(select_1_2<0,1>(c, a, less<>()) == c);
        CHECK(&select_1_2<0,1>(a, b, less<>()) == &b);
        CHECK(&select_1_2<0,1>(b, a, less<>()) == &a);
        CHECK(&select_1_2<0,1>(a, c, less<>()) == &c);
        CHECK(&select_1_2<0,1>(c, a, less<>()) == &c);

        CHECK(select_0_2<0,1>(a, c) == a);
        CHECK(select_0_2<0,1>(c, a) == a);
        CHECK(&select_0_2<0,1>(a, b) == &a);
        CHECK(&select_0_2<0,1>(b, a) == &b);
        CHECK(&select_0_2<0,1>(a, c) == &a);
        CHECK(&select_0_2<0,1>(c, a) == &a);

        CHECK(select_1_2<0,1>(a, c) == c);
        CHECK(select_1_2<0,1>(c, a) == c);
        CHECK(&select_1_2<0,1>(a, b) == &b);
        CHECK(&select_1_2<0,1>(b, a) == &a);
        CHECK(&select_1_2<0,1>(a, c) == &c);
        CHECK(&select_1_2<0,1>(c, a) == &c);
    }

    SUBCASE("[select_i_2] (1,0) testing select_i_2 selection algorithms") {
        CHECK(select_0_2<1,0>(a, c, less<>()) == a);
        CHECK(select_0_2<1,0>(c, a, less<>()) == a);
        CHECK(&select_0_2<1,0>(a, b, less<>()) == &b);
        CHECK(&select_0_2<1,0>(b, a, less<>()) == &a);
        CHECK(&select_0_2<1,0>(a, c, less<>()) == &a);
        CHECK(&select_0_2<1,0>(c, a, less<>()) == &a);

        CHECK(select_1_2<1,0>(a, c, less<>()) == c);
        CHECK(select_1_2<1,0>(c, a, less<>()) == c);
        CHECK(&select_1_2<1,0>(a, b, less<>()) == &a);
        CHECK(&select_1_2<1,0>(b, a, less<>()) == &b);
        CHECK(&select_1_2<1,0>(a, c, less<>()) == &c);
        CHECK(&select_1_2<1,0>(c, a, less<>()) == &c);

        CHECK(select_0_2<1,0>(a, c) == a);
        CHECK(select_0_2<1,0>(c, a) == a);
        CHECK(&select_0_2<1,0>(a, b) == &b);
        CHECK(&select_0_2<1,0>(b, a) == &a);
        CHECK(&select_0_2<1,0>(a, c) == &a);
        CHECK(&select_0_2<1,0>(c, a) == &a);

        CHECK(select_1_2<1,0>(a, c) == c);
        CHECK(select_1_2<1,0>(c, a) == c);
        CHECK(&select_1_2<1,0>(a, b) == &a);
        CHECK(&select_1_2<1,0>(b, a) == &b);
        CHECK(&select_1_2<1,0>(a, c) == &c);
        CHECK(&select_1_2<1,0>(c, a) == &c);
    }

    SUBCASE("[select_i_3] (0,1,2) testing select_i_3 selection algorithm") {
        CHECK( select_0_3<0,1,2>(a, c, d,  less<>()) == a);
        CHECK( select_0_3<0,1,2>(c, a, d,  less<>()) == a);
        CHECK( select_0_3<0,1,2>(d, c, a,  less<>()) == a);
        CHECK(&select_0_3<0,1,2>(a, b, c,  less<>()) == &a);
        CHECK(&select_0_3<0,1,2>(a, c, b,  less<>()) == &a);
        CHECK(&select_0_3<0,1,2>(b, a, c,  less<>()) == &b);
        CHECK(&select_0_3<0,1,2>(b, c, a,  less<>()) == &b);
        CHECK(&select_0_3<0,1,2>(c, a, b,  less<>()) == &a);
        CHECK(&select_0_3<0,1,2>(c, b, a,  less<>()) == &b);
        CHECK(&select_0_3<0,1,2>(a, b, a2, less<>()) == &a);
        CHECK(&select_0_3<0,1,2>(a, a2, b, less<>()) == &a);
        CHECK(&select_0_3<0,1,2>(b, a, a2, less<>()) == &b);
        CHECK(&select_0_3<0,1,2>(b, a2, a, less<>()) == &b);
        CHECK(&select_0_3<0,1,2>(a2, a, b, less<>()) == &a2);
        CHECK(&select_0_3<0,1,2>(a2, b, a, less<>()) == &a2);

        CHECK( select_2_3<0,1,2>(a, c, d,  less<>()) == d);
        CHECK( select_2_3<0,1,2>(c, a, d,  less<>()) == c);
        CHECK( select_2_3<0,1,2>(d, c, a,  less<>()) == c);
        CHECK(&select_2_3<0,1,2>(b, c, d,  less<>()) == &d);
        CHECK(&select_2_3<0,1,2>(c, b, d,  less<>()) == &d);
        CHECK(&select_2_3<0,1,2>(b, d, c,  less<>()) == &c);
        CHECK(&select_2_3<0,1,2>(d, b, c,  less<>()) == &c);
        CHECK(&select_2_3<0,1,2>(c, d, b,  less<>()) == &d);
        CHECK(&select_2_3<0,1,2>(d, c, b,  less<>()) == &c);
        CHECK(&select_2_3<0,1,2>(a, b, a2, less<>()) == &a2);
        CHECK(&select_2_3<0,1,2>(a, a2, b, less<>()) == &b);
        CHECK(&select_2_3<0,1,2>(b, a, a2, less<>()) == &a2);
        CHECK(&select_2_3<0,1,2>(b, a2, a, less<>()) == &a);
        CHECK(&select_2_3<0,1,2>(a2, a, b, less<>()) == &b);
        CHECK(&select_2_3<0,1,2>(a2, b, a, less<>()) == &a);

        CHECK( select_1_3<0,1,2>(a, c, d,  less<>()) == c);
        CHECK( select_1_3<0,1,2>(c, a, d,  less<>()) == c);
        CHECK( select_1_3<0,1,2>(d, c, a,  less<>()) == c);
        CHECK(&select_1_3<0,1,2>(a, b, c,  less<>()) == &b);
        CHECK(&select_1_3<0,1,2>(a, c, b,  less<>()) == &b);
        CHECK(&select_1_3<0,1,2>(b, a, c,  less<>()) == &a);
        CHECK(&select_1_3<0,1,2>(b, c, a,  less<>()) == &a);
        CHECK(&select_1_3<0,1,2>(c, a, b,  less<>()) == &b);
        CHECK(&select_1_3<0,1,2>(c, b, a,  less<>()) == &a);
        CHECK(&select_1_3<0,1,2>(a, b, a2, less<>()) == &b);
        CHECK(&select_1_3<0,1,2>(a, a2, b, less<>()) == &a2);
        CHECK(&select_1_3<0,1,2>(b, a, a2, less<>()) == &a);
        CHECK(&select_1_3<0,1,2>(b, a2, a, less<>()) == &a2);
        CHECK(&select_1_3<0,1,2>(a2, a, b, less<>()) == &a);
        CHECK(&select_1_3<0,1,2>(a2, b, a, less<>()) == &b);

        // CHECK(&select_0_3<0,1,2>(a, b, c) == &a);
        // CHECK(&select_0_3<0,1,2>(a, c, b) == &a);
        // CHECK(&select_0_3<0,1,2>(b, a, c) == &b);
        // CHECK(&select_0_3<0,1,2>(b, c, a) == &b);
        // CHECK(&select_0_3<0,1,2>(c, a, b) == &a);
        // CHECK(&select_0_3<0,1,2>(c, b, a) == &b);
        // CHECK(select_0_3<0,1,2>(a, c, d) == a);
        // CHECK(select_0_3<0,1,2>(c, a, d) == a);
        // CHECK(select_0_3<0,1,2>(d, c, a) == a);

        // CHECK(&select_2_3<0,1,2>(b, c, d) == &d);
        // CHECK(&select_2_3<0,1,2>(c, b, d) == &d);
        // CHECK(&select_2_3<0,1,2>(b, d, c) == &c);
        // CHECK(&select_2_3<0,1,2>(d, b, c) == &c);
        // CHECK(&select_2_3<0,1,2>(c, d, b) == &d);
        // CHECK(&select_2_3<0,1,2>(d, c, b) == &c);
        // CHECK(select_2_3<0,1,2>(a, c, d) == d);
        // CHECK(select_2_3<0,1,2>(c, a, d) == c);
        // CHECK(select_2_3<0,1,2>(d, c, a) == c);

        // CHECK(&select_1_3<0,1,2>(a, b, c) == &b);
        // CHECK(&select_1_3<0,1,2>(a, c, b) == &b);
        // CHECK(&select_1_3<0,1,2>(b, a, c) == &a);
        // CHECK(&select_1_3<0,1,2>(b, c, a) == &a);
        // CHECK(&select_1_3<0,1,2>(c, a, b) == &b);
        // CHECK(&select_1_3<0,1,2>(c, b, a) == &a);
        // CHECK(select_1_3<0,1,2>(a, c, d) == c);
        // CHECK(select_1_3<0,1,2>(c, a, d) == c);
        // CHECK(select_1_3<0,1,2>(d, c, a) == c);        
    }

    SUBCASE("[select_i_3] (0,2,1) testing select_i_3 selection algorithm") {
        CHECK( select_0_3<0,2,1>(a, c, d,  less<>()) == a);
        CHECK( select_0_3<0,2,1>(c, a, d,  less<>()) == a);
        CHECK( select_0_3<0,2,1>(d, c, a,  less<>()) == a);
        CHECK(&select_0_3<0,2,1>(a, b, c,  less<>()) == &a);
        CHECK(&select_0_3<0,2,1>(a, c, b,  less<>()) == &a);
        CHECK(&select_0_3<0,2,1>(b, a, c,  less<>()) == &b);
        CHECK(&select_0_3<0,2,1>(b, c, a,  less<>()) == &b);
        CHECK(&select_0_3<0,2,1>(c, a, b,  less<>()) == &b);
        CHECK(&select_0_3<0,2,1>(c, b, a,  less<>()) == &a);
        CHECK(&select_0_3<0,2,1>(a, b, a2, less<>()) == &a);
        CHECK(&select_0_3<0,2,1>(a, a2, b, less<>()) == &a);
        CHECK(&select_0_3<0,2,1>(b, a, a2, less<>()) == &b);
        CHECK(&select_0_3<0,2,1>(b, a2, a, less<>()) == &b);
        CHECK(&select_0_3<0,2,1>(a2, a, b, less<>()) == &a2);
        CHECK(&select_0_3<0,2,1>(a2, b, a, less<>()) == &a2);

        CHECK( select_2_3<0,2,1>(a, c, d,  less<>()) == d);
        CHECK( select_2_3<0,2,1>(c, a, d,  less<>()) == c);
        CHECK( select_2_3<0,2,1>(d, c, a,  less<>()) == c);
        CHECK(&select_2_3<0,2,1>(b, c, d,  less<>()) == &c);
        CHECK(&select_2_3<0,2,1>(c, b, d,  less<>()) == &d);
        CHECK(&select_2_3<0,2,1>(b, d, c,  less<>()) == &d);
        CHECK(&select_2_3<0,2,1>(d, b, c,  less<>()) == &c);
        CHECK(&select_2_3<0,2,1>(c, d, b,  less<>()) == &d);
        CHECK(&select_2_3<0,2,1>(d, c, b,  less<>()) == &c);
        CHECK(&select_2_3<0,2,1>(a, b, a2, less<>()) == &b);
        CHECK(&select_2_3<0,2,1>(a, a2, b, less<>()) == &a2);
        CHECK(&select_2_3<0,2,1>(b, a, a2, less<>()) == &a);
        CHECK(&select_2_3<0,2,1>(b, a2, a, less<>()) == &a2);
        CHECK(&select_2_3<0,2,1>(a2, a, b, less<>()) == &a);
        CHECK(&select_2_3<0,2,1>(a2, b, a, less<>()) == &b);

        CHECK( select_1_3<0,2,1>(a, c, d,  less<>()) == c);
        CHECK( select_1_3<0,2,1>(c, a, d,  less<>()) == c);
        CHECK( select_1_3<0,2,1>(d, c, a,  less<>()) == c);
        CHECK(&select_1_3<0,2,1>(a, b, c,  less<>()) == &b);
        CHECK(&select_1_3<0,2,1>(a, c, b,  less<>()) == &b);
        CHECK(&select_1_3<0,2,1>(b, a, c,  less<>()) == &a);
        CHECK(&select_1_3<0,2,1>(b, c, a,  less<>()) == &a);
        CHECK(&select_1_3<0,2,1>(c, a, b,  less<>()) == &a);
        CHECK(&select_1_3<0,2,1>(c, b, a,  less<>()) == &b);
        CHECK(&select_1_3<0,2,1>(a, b, a2, less<>()) == &a2);
        CHECK(&select_1_3<0,2,1>(a, a2, b, less<>()) == &b);
        CHECK(&select_1_3<0,2,1>(b, a, a2, less<>()) == &a2);
        CHECK(&select_1_3<0,2,1>(b, a2, a, less<>()) == &a);
        CHECK(&select_1_3<0,2,1>(a2, a, b, less<>()) == &b);
        CHECK(&select_1_3<0,2,1>(a2, b, a, less<>()) == &a);
    }

    SUBCASE("[select_i_3] (1,0,2) testing select_i_3 selection algorithm") {
        CHECK( select_0_3<1,0,2>(a, c, d,  less<>()) == a);
        CHECK( select_0_3<1,0,2>(c, a, d,  less<>()) == a);
        CHECK( select_0_3<1,0,2>(d, c, a,  less<>()) == a);
        CHECK(&select_0_3<1,0,2>(a, b, c,  less<>()) == &b);
        CHECK(&select_0_3<1,0,2>(a, c, b,  less<>()) == &a);
        CHECK(&select_0_3<1,0,2>(b, a, c,  less<>()) == &a);
        CHECK(&select_0_3<1,0,2>(b, c, a,  less<>()) == &b);
        CHECK(&select_0_3<1,0,2>(c, a, b,  less<>()) == &a);
        CHECK(&select_0_3<1,0,2>(c, b, a,  less<>()) == &b);
        CHECK(&select_0_3<1,0,2>(a, b, a2, less<>()) == &b);
        CHECK(&select_0_3<1,0,2>(a, a2, b, less<>()) == &a2);
        CHECK(&select_0_3<1,0,2>(b, a, a2, less<>()) == &a);
        CHECK(&select_0_3<1,0,2>(b, a2, a, less<>()) == &a2);
        CHECK(&select_0_3<1,0,2>(a2, a, b, less<>()) == &a);
        CHECK(&select_0_3<1,0,2>(a2, b, a, less<>()) == &b);

        CHECK( select_2_3<1,0,2>(a, c, d,  less<>()) == d);
        CHECK( select_2_3<1,0,2>(c, a, d,  less<>()) == c);
        CHECK( select_2_3<1,0,2>(d, c, a,  less<>()) == c);
        CHECK(&select_2_3<1,0,2>(b, c, d,  less<>()) == &d);
        CHECK(&select_2_3<1,0,2>(c, b, d,  less<>()) == &d);
        CHECK(&select_2_3<1,0,2>(b, d, c,  less<>()) == &c);
        CHECK(&select_2_3<1,0,2>(d, b, c,  less<>()) == &c);
        CHECK(&select_2_3<1,0,2>(c, d, b,  less<>()) == &c);
        CHECK(&select_2_3<1,0,2>(d, c, b,  less<>()) == &d);
        CHECK(&select_2_3<1,0,2>(a, b, a2, less<>()) == &a2);
        CHECK(&select_2_3<1,0,2>(a, a2, b, less<>()) == &b);
        CHECK(&select_2_3<1,0,2>(b, a, a2, less<>()) == &a2);
        CHECK(&select_2_3<1,0,2>(b, a2, a, less<>()) == &a);
        CHECK(&select_2_3<1,0,2>(a2, a, b, less<>()) == &b);
        CHECK(&select_2_3<1,0,2>(a2, b, a, less<>()) == &a);

        CHECK( select_1_3<1,0,2>(a, c, d,  less<>()) == c);
        CHECK( select_1_3<1,0,2>(c, a, d,  less<>()) == c);
        CHECK( select_1_3<1,0,2>(d, c, a,  less<>()) == c);
        CHECK(&select_1_3<1,0,2>(a, b, c,  less<>()) == &a);
        CHECK(&select_1_3<1,0,2>(a, c, b,  less<>()) == &b);
        CHECK(&select_1_3<1,0,2>(b, a, c,  less<>()) == &b);
        CHECK(&select_1_3<1,0,2>(b, c, a,  less<>()) == &a);
        CHECK(&select_1_3<1,0,2>(c, a, b,  less<>()) == &b);
        CHECK(&select_1_3<1,0,2>(c, b, a,  less<>()) == &a);
        CHECK(&select_1_3<1,0,2>(a, b, a2, less<>()) == &a);
        CHECK(&select_1_3<1,0,2>(a, a2, b, less<>()) == &a);
        CHECK(&select_1_3<1,0,2>(b, a, a2, less<>()) == &b);
        CHECK(&select_1_3<1,0,2>(b, a2, a, less<>()) == &b);
        CHECK(&select_1_3<1,0,2>(a2, a, b, less<>()) == &a2);
        CHECK(&select_1_3<1,0,2>(a2, b, a, less<>()) == &a2);
    }

    SUBCASE("[select_i_3] (1,2,0) testing select_i_3 selection algorithm") {
        CHECK( select_0_3<1,2,0>(a, c, d,  less<>()) == a);
        CHECK( select_0_3<1,2,0>(c, a, d,  less<>()) == a);
        CHECK( select_0_3<1,2,0>(d, c, a,  less<>()) == a);
        CHECK(&select_0_3<1,2,0>(a, b, c,  less<>()) == &a);
        CHECK(&select_0_3<1,2,0>(a, c, b,  less<>()) == &b);
        CHECK(&select_0_3<1,2,0>(b, a, c,  less<>()) == &b);
        CHECK(&select_0_3<1,2,0>(b, c, a,  less<>()) == &a);
        CHECK(&select_0_3<1,2,0>(c, a, b,  less<>()) == &b);
        CHECK(&select_0_3<1,2,0>(c, b, a,  less<>()) == &a);
        CHECK(&select_0_3<1,2,0>(a, b, a2, less<>()) == &a2);
        CHECK(&select_0_3<1,2,0>(a, a2, b, less<>()) == &b);
        CHECK(&select_0_3<1,2,0>(b, a, a2, less<>()) == &a2);
        CHECK(&select_0_3<1,2,0>(b, a2, a, less<>()) == &a);
        CHECK(&select_0_3<1,2,0>(a2, a, b, less<>()) == &b);
        CHECK(&select_0_3<1,2,0>(a2, b, a, less<>()) == &a);

        CHECK( select_2_3<1,2,0>(a, c, d,  less<>()) == d);
        CHECK( select_2_3<1,2,0>(c, a, d,  less<>()) == c);
        CHECK( select_2_3<1,2,0>(d, c, a,  less<>()) == c);
        CHECK(&select_2_3<1,2,0>(b, c, d,  less<>()) == &c);
        CHECK(&select_2_3<1,2,0>(c, b, d,  less<>()) == &c);
        CHECK(&select_2_3<1,2,0>(b, d, c,  less<>()) == &d);
        CHECK(&select_2_3<1,2,0>(d, b, c,  less<>()) == &d);
        CHECK(&select_2_3<1,2,0>(c, d, b,  less<>()) == &d);
        CHECK(&select_2_3<1,2,0>(d, c, b,  less<>()) == &c);
        CHECK(&select_2_3<1,2,0>(a, b, a2, less<>()) == &b);
        CHECK(&select_2_3<1,2,0>(a, a2, b, less<>()) == &a2);
        CHECK(&select_2_3<1,2,0>(b, a, a2, less<>()) == &a);
        CHECK(&select_2_3<1,2,0>(b, a2, a, less<>()) == &a2);
        CHECK(&select_2_3<1,2,0>(a2, a, b, less<>()) == &a);
        CHECK(&select_2_3<1,2,0>(a2, b, a, less<>()) == &b);

        CHECK( select_1_3<1,2,0>(a, c, d,  less<>()) == c);
        CHECK( select_1_3<1,2,0>(c, a, d,  less<>()) == c);
        CHECK( select_1_3<1,2,0>(d, c, a,  less<>()) == c);
        CHECK(&select_1_3<1,2,0>(a, b, c,  less<>()) == &b);
        CHECK(&select_1_3<1,2,0>(a, c, b,  less<>()) == &a);
        CHECK(&select_1_3<1,2,0>(b, a, c,  less<>()) == &a);
        CHECK(&select_1_3<1,2,0>(b, c, a,  less<>()) == &b);
        CHECK(&select_1_3<1,2,0>(c, a, b,  less<>()) == &a);
        CHECK(&select_1_3<1,2,0>(c, b, a,  less<>()) == &b);
        CHECK(&select_1_3<1,2,0>(a, b, a2, less<>()) == &a);
        CHECK(&select_1_3<1,2,0>(a, a2, b, less<>()) == &a);
        CHECK(&select_1_3<1,2,0>(b, a, a2, less<>()) == &b);
        CHECK(&select_1_3<1,2,0>(b, a2, a, less<>()) == &b);
        CHECK(&select_1_3<1,2,0>(a2, a, b, less<>()) == &a2);
        CHECK(&select_1_3<1,2,0>(a2, b, a, less<>()) == &a2);
    }

    SUBCASE("[select_i_3] (2,0,1) testing select_i_3 selection algorithm") {
        CHECK( select_0_3<2,0,1>(a, c, d,  less<>()) == a);
        CHECK( select_0_3<2,0,1>(c, a, d,  less<>()) == a);
        CHECK( select_0_3<2,0,1>(d, c, a,  less<>()) == a);
        CHECK(&select_0_3<2,0,1>(a, b, c,  less<>()) == &b);
        CHECK(&select_0_3<2,0,1>(a, c, b,  less<>()) == &b);
        CHECK(&select_0_3<2,0,1>(b, a, c,  less<>()) == &a);
        CHECK(&select_0_3<2,0,1>(b, c, a,  less<>()) == &a);
        CHECK(&select_0_3<2,0,1>(c, a, b,  less<>()) == &a);
        CHECK(&select_0_3<2,0,1>(c, b, a,  less<>()) == &b);
        CHECK(&select_0_3<2,0,1>(a, b, a2, less<>()) == &b);
        CHECK(&select_0_3<2,0,1>(a, a2, b, less<>()) == &a2);
        CHECK(&select_0_3<2,0,1>(b, a, a2, less<>()) == &a);
        CHECK(&select_0_3<2,0,1>(b, a2, a, less<>()) == &a2);
        CHECK(&select_0_3<2,0,1>(a2, a, b, less<>()) == &a);
        CHECK(&select_0_3<2,0,1>(a2, b, a, less<>()) == &b);

        CHECK( select_2_3<2,0,1>(a, c, d,  less<>()) == d);
        CHECK( select_2_3<2,0,1>(c, a, d,  less<>()) == c);
        CHECK( select_2_3<2,0,1>(d, c, a,  less<>()) == c);
        CHECK(&select_2_3<2,0,1>(b, c, d,  less<>()) == &d);
        CHECK(&select_2_3<2,0,1>(c, b, d,  less<>()) == &c);
        CHECK(&select_2_3<2,0,1>(b, d, c,  less<>()) == &c);
        CHECK(&select_2_3<2,0,1>(d, b, c,  less<>()) == &d);
        CHECK(&select_2_3<2,0,1>(c, d, b,  less<>()) == &c);
        CHECK(&select_2_3<2,0,1>(d, c, b,  less<>()) == &d);
        CHECK(&select_2_3<2,0,1>(a, b, a2, less<>()) == &a);
        CHECK(&select_2_3<2,0,1>(a, a2, b, less<>()) == &a);
        CHECK(&select_2_3<2,0,1>(b, a, a2, less<>()) == &b);
        CHECK(&select_2_3<2,0,1>(b, a2, a, less<>()) == &b);
        CHECK(&select_2_3<2,0,1>(a2, a, b, less<>()) == &a2);
        CHECK(&select_2_3<2,0,1>(a2, b, a, less<>()) == &a2);

        CHECK( select_1_3<2,0,1>(a, c, d,  less<>()) == c);
        CHECK( select_1_3<2,0,1>(c, a, d,  less<>()) == c);
        CHECK( select_1_3<2,0,1>(d, c, a,  less<>()) == c);
        CHECK(&select_1_3<2,0,1>(a, b, c,  less<>()) == &a);
        CHECK(&select_1_3<2,0,1>(a, c, b,  less<>()) == &a);
        CHECK(&select_1_3<2,0,1>(b, a, c,  less<>()) == &b);
        CHECK(&select_1_3<2,0,1>(b, c, a,  less<>()) == &b);
        CHECK(&select_1_3<2,0,1>(c, a, b,  less<>()) == &b);
        CHECK(&select_1_3<2,0,1>(c, b, a,  less<>()) == &a);
        CHECK(&select_1_3<2,0,1>(a, b, a2, less<>()) == &a2);
        CHECK(&select_1_3<2,0,1>(a, a2, b, less<>()) == &b);
        CHECK(&select_1_3<2,0,1>(b, a, a2, less<>()) == &a2);
        CHECK(&select_1_3<2,0,1>(b, a2, a, less<>()) == &a);
        CHECK(&select_1_3<2,0,1>(a2, a, b, less<>()) == &b);
        CHECK(&select_1_3<2,0,1>(a2, b, a, less<>()) == &a);
    }

    SUBCASE("[select_i_3] (2,1,0) testing select_i_3 selection algorithm") {
        CHECK( select_0_3<2,1,0>(a, c, d,  less<>()) == a);
        CHECK( select_0_3<2,1,0>(c, a, d,  less<>()) == a);
        CHECK( select_0_3<2,1,0>(d, c, a,  less<>()) == a);
        CHECK(&select_0_3<2,1,0>(a, b, c,  less<>()) == &b);
        CHECK(&select_0_3<2,1,0>(a, c, b,  less<>()) == &b);
        CHECK(&select_0_3<2,1,0>(b, a, c,  less<>()) == &a);
        CHECK(&select_0_3<2,1,0>(b, c, a,  less<>()) == &a);
        CHECK(&select_0_3<2,1,0>(c, a, b,  less<>()) == &b);
        CHECK(&select_0_3<2,1,0>(c, b, a,  less<>()) == &a);
        CHECK(&select_0_3<2,1,0>(a, b, a2, less<>()) == &a2);
        CHECK(&select_0_3<2,1,0>(a, a2, b, less<>()) == &b);
        CHECK(&select_0_3<2,1,0>(b, a, a2, less<>()) == &a2);
        CHECK(&select_0_3<2,1,0>(b, a2, a, less<>()) == &a);
        CHECK(&select_0_3<2,1,0>(a2, a, b, less<>()) == &b);
        CHECK(&select_0_3<2,1,0>(a2, b, a, less<>()) == &a);

        CHECK( select_2_3<2,1,0>(a, c, d,  less<>()) == d);
        CHECK( select_2_3<2,1,0>(c, a, d,  less<>()) == c);
        CHECK( select_2_3<2,1,0>(d, c, a,  less<>()) == c);
        CHECK(&select_2_3<2,1,0>(b, c, d,  less<>()) == &c);
        CHECK(&select_2_3<2,1,0>(c, b, d,  less<>()) == &c);
        CHECK(&select_2_3<2,1,0>(b, d, c,  less<>()) == &d);
        CHECK(&select_2_3<2,1,0>(d, b, c,  less<>()) == &d);
        CHECK(&select_2_3<2,1,0>(c, d, b,  less<>()) == &c);
        CHECK(&select_2_3<2,1,0>(d, c, b,  less<>()) == &d);
        CHECK(&select_2_3<2,1,0>(a, b, a2, less<>()) == &a);
        CHECK(&select_2_3<2,1,0>(a, a2, b, less<>()) == &a);
        CHECK(&select_2_3<2,1,0>(b, a, a2, less<>()) == &b);
        CHECK(&select_2_3<2,1,0>(b, a2, a, less<>()) == &b);
        CHECK(&select_2_3<2,1,0>(a2, a, b, less<>()) == &a2);
        CHECK(&select_2_3<2,1,0>(a2, b, a, less<>()) == &a2);

        CHECK( select_1_3<2,1,0>(a, c, d,  less<>()) == c);
        CHECK( select_1_3<2,1,0>(c, a, d,  less<>()) == c);
        CHECK( select_1_3<2,1,0>(d, c, a,  less<>()) == c);
        CHECK(&select_1_3<2,1,0>(a, b, c,  less<>()) == &a);
        CHECK(&select_1_3<2,1,0>(a, c, b,  less<>()) == &a);
        CHECK(&select_1_3<2,1,0>(b, a, c,  less<>()) == &b);
        CHECK(&select_1_3<2,1,0>(b, c, a,  less<>()) == &b);
        CHECK(&select_1_3<2,1,0>(c, a, b,  less<>()) == &a);
        CHECK(&select_1_3<2,1,0>(c, b, a,  less<>()) == &b);
        CHECK(&select_1_3<2,1,0>(a, b, a2, less<>()) == &b);
        CHECK(&select_1_3<2,1,0>(a, a2, b, less<>()) == &a2);
        CHECK(&select_1_3<2,1,0>(b, a, a2, less<>()) == &a);
        CHECK(&select_1_3<2,1,0>(b, a2, a, less<>()) == &a2);
        CHECK(&select_1_3<2,1,0>(a2, a, b, less<>()) == &a);
        CHECK(&select_1_3<2,1,0>(a2, b, a, less<>()) == &b);
    }        
}


// TEST_CASE("[select_i_4] testing select_i_4 selection algorithm") {
//     using namespace tao::algorithm;
//     using namespace std;

//     int a = 1;
//     int b = 2;
//     int c = 3;
//     int d = 4;

//     CHECK(select_0_4(a, b, c, d, less<>()) == a);
//     CHECK(select_0_4(a, b, d, c, less<>()) == a);
//     CHECK(select_0_4(a, c, b, d, less<>()) == a);
//     CHECK(select_0_4(a, c, d, b, less<>()) == a);
//     CHECK(select_0_4(a, d, b, c, less<>()) == a);
//     CHECK(select_0_4(a, d, c, b, less<>()) == a);

//     CHECK(select_0_4(b, a, c, d, less<>()) == a);
//     CHECK(select_0_4(b, a, d, c, less<>()) == a);
//     CHECK(select_0_4(b, c, a, d, less<>()) == a);
//     CHECK(select_0_4(b, c, d, a, less<>()) == a);
//     CHECK(select_0_4(b, d, a, c, less<>()) == a);
//     CHECK(select_0_4(b, d, c, a, less<>()) == a);

//     CHECK(select_0_4(c, a, b, d, less<>()) == a);
//     CHECK(select_0_4(c, a, d, b, less<>()) == a);
//     CHECK(select_0_4(c, b, a, d, less<>()) == a);
//     CHECK(select_0_4(c, b, d, a, less<>()) == a);
//     CHECK(select_0_4(c, d, a, b, less<>()) == a);
//     CHECK(select_0_4(c, d, b, a, less<>()) == a);

//     CHECK(select_0_4(d, a, b, c, less<>()) == a);
//     CHECK(select_0_4(d, a, c, b, less<>()) == a);
//     CHECK(select_0_4(d, b, a, c, less<>()) == a);
//     CHECK(select_0_4(d, b, c, a, less<>()) == a);
//     CHECK(select_0_4(d, c, a, b, less<>()) == a);
//     CHECK(select_0_4(d, c, b, a, less<>()) == a);


//     CHECK(select_1_4(a, b, c, d, less<>()) == b);
//     CHECK(select_1_4(a, b, d, c, less<>()) == b);
//     CHECK(select_1_4(a, c, b, d, less<>()) == b);
//     CHECK(select_1_4(a, c, d, b, less<>()) == b);
//     CHECK(select_1_4(a, d, b, c, less<>()) == b);
//     CHECK(select_1_4(a, d, c, b, less<>()) == b);

//     CHECK(select_1_4(b, a, c, d, less<>()) == b);
//     CHECK(select_1_4(b, a, d, c, less<>()) == b);
//     CHECK(select_1_4(b, c, a, d, less<>()) == b);
//     CHECK(select_1_4(b, c, d, a, less<>()) == b);
//     CHECK(select_1_4(b, d, a, c, less<>()) == b);
//     CHECK(select_1_4(b, d, c, a, less<>()) == b);

//     CHECK(select_1_4(c, a, b, d, less<>()) == b);
//     CHECK(select_1_4(c, a, d, b, less<>()) == b);
//     CHECK(select_1_4(c, b, a, d, less<>()) == b);
//     CHECK(select_1_4(c, b, d, a, less<>()) == b);
//     CHECK(select_1_4(c, d, a, b, less<>()) == b);
//     CHECK(select_1_4(c, d, b, a, less<>()) == b);

//     CHECK(select_1_4(d, a, b, c, less<>()) == b);
//     CHECK(select_1_4(d, a, c, b, less<>()) == b);
//     CHECK(select_1_4(d, b, a, c, less<>()) == b);
//     CHECK(select_1_4(d, b, c, a, less<>()) == b);
//     CHECK(select_1_4(d, c, a, b, less<>()) == b);
//     CHECK(select_1_4(d, c, b, a, less<>()) == b);
 

//     CHECK(select_2_4(a, b, c, d, less<>()) == c);
//     CHECK(select_2_4(a, b, d, c, less<>()) == c);
//     CHECK(select_2_4(a, c, b, d, less<>()) == c);
//     CHECK(select_2_4(a, c, d, b, less<>()) == c);
//     CHECK(select_2_4(a, d, b, c, less<>()) == c);
//     CHECK(select_2_4(a, d, c, b, less<>()) == c);

//     CHECK(select_2_4(b, a, c, d, less<>()) == c);
//     CHECK(select_2_4(b, a, d, c, less<>()) == c);
//     CHECK(select_2_4(b, c, a, d, less<>()) == c);
//     CHECK(select_2_4(b, c, d, a, less<>()) == c);
//     CHECK(select_2_4(b, d, a, c, less<>()) == c);
//     CHECK(select_2_4(b, d, c, a, less<>()) == c);

//     CHECK(select_2_4(c, a, b, d, less<>()) == c);
//     CHECK(select_2_4(c, a, d, b, less<>()) == c);
//     CHECK(select_2_4(c, b, a, d, less<>()) == c);
//     CHECK(select_2_4(c, b, d, a, less<>()) == c);
//     CHECK(select_2_4(c, d, a, b, less<>()) == c);
//     CHECK(select_2_4(c, d, b, a, less<>()) == c);

//     CHECK(select_2_4(d, a, b, c, less<>()) == c);
//     CHECK(select_2_4(d, a, c, b, less<>()) == c);
//     CHECK(select_2_4(d, b, a, c, less<>()) == c);
//     CHECK(select_2_4(d, b, c, a, less<>()) == c);
//     CHECK(select_2_4(d, c, a, b, less<>()) == c);
//     CHECK(select_2_4(d, c, b, a, less<>()) == c);


//     CHECK(select_3_4(a, b, c, d, less<>()) == d);
//     CHECK(select_3_4(a, b, d, c, less<>()) == d);
//     CHECK(select_3_4(a, c, b, d, less<>()) == d);
//     CHECK(select_3_4(a, c, d, b, less<>()) == d);
//     CHECK(select_3_4(a, d, b, c, less<>()) == d);
//     CHECK(select_3_4(a, d, c, b, less<>()) == d);

//     CHECK(select_3_4(b, a, c, d, less<>()) == d);
//     CHECK(select_3_4(b, a, d, c, less<>()) == d);
//     CHECK(select_3_4(b, c, a, d, less<>()) == d);
//     CHECK(select_3_4(b, c, d, a, less<>()) == d);
//     CHECK(select_3_4(b, d, a, c, less<>()) == d);
//     CHECK(select_3_4(b, d, c, a, less<>()) == d);

//     CHECK(select_3_4(c, a, b, d, less<>()) == d);
//     CHECK(select_3_4(c, a, d, b, less<>()) == d);
//     CHECK(select_3_4(c, b, a, d, less<>()) == d);
//     CHECK(select_3_4(c, b, d, a, less<>()) == d);
//     CHECK(select_3_4(c, d, a, b, less<>()) == d);
//     CHECK(select_3_4(c, d, b, a, less<>()) == d);

//     CHECK(select_3_4(d, a, b, c, less<>()) == d);
//     CHECK(select_3_4(d, a, c, b, less<>()) == d);
//     CHECK(select_3_4(d, b, a, c, less<>()) == d);
//     CHECK(select_3_4(d, b, c, a, less<>()) == d);
//     CHECK(select_3_4(d, c, a, b, less<>()) == d);
//     CHECK(select_3_4(d, c, b, a, less<>()) == d);


//     // ----


//     CHECK(select_0_4(a, b, c, d) == a);
//     CHECK(select_0_4(a, b, d, c) == a);
//     CHECK(select_0_4(a, c, b, d) == a);
//     CHECK(select_0_4(a, c, d, b) == a);
//     CHECK(select_0_4(a, d, b, c) == a);
//     CHECK(select_0_4(a, d, c, b) == a);

//     CHECK(select_0_4(b, a, c, d) == a);
//     CHECK(select_0_4(b, a, d, c) == a);
//     CHECK(select_0_4(b, c, a, d) == a);
//     CHECK(select_0_4(b, c, d, a) == a);
//     CHECK(select_0_4(b, d, a, c) == a);
//     CHECK(select_0_4(b, d, c, a) == a);

//     CHECK(select_0_4(c, a, b, d) == a);
//     CHECK(select_0_4(c, a, d, b) == a);
//     CHECK(select_0_4(c, b, a, d) == a);
//     CHECK(select_0_4(c, b, d, a) == a);
//     CHECK(select_0_4(c, d, a, b) == a);
//     CHECK(select_0_4(c, d, b, a) == a);

//     CHECK(select_0_4(d, a, b, c) == a);
//     CHECK(select_0_4(d, a, c, b) == a);
//     CHECK(select_0_4(d, b, a, c) == a);
//     CHECK(select_0_4(d, b, c, a) == a);
//     CHECK(select_0_4(d, c, a, b) == a);
//     CHECK(select_0_4(d, c, b, a) == a);


//     CHECK(select_1_4(a, b, c, d) == b);
//     CHECK(select_1_4(a, b, d, c) == b);
//     CHECK(select_1_4(a, c, b, d) == b);
//     CHECK(select_1_4(a, c, d, b) == b);
//     CHECK(select_1_4(a, d, b, c) == b);
//     CHECK(select_1_4(a, d, c, b) == b);

//     CHECK(select_1_4(b, a, c, d) == b);
//     CHECK(select_1_4(b, a, d, c) == b);
//     CHECK(select_1_4(b, c, a, d) == b);
//     CHECK(select_1_4(b, c, d, a) == b);
//     CHECK(select_1_4(b, d, a, c) == b);
//     CHECK(select_1_4(b, d, c, a) == b);

//     CHECK(select_1_4(c, a, b, d) == b);
//     CHECK(select_1_4(c, a, d, b) == b);
//     CHECK(select_1_4(c, b, a, d) == b);
//     CHECK(select_1_4(c, b, d, a) == b);
//     CHECK(select_1_4(c, d, a, b) == b);
//     CHECK(select_1_4(c, d, b, a) == b);

//     CHECK(select_1_4(d, a, b, c) == b);
//     CHECK(select_1_4(d, a, c, b) == b);
//     CHECK(select_1_4(d, b, a, c) == b);
//     CHECK(select_1_4(d, b, c, a) == b);
//     CHECK(select_1_4(d, c, a, b) == b);
//     CHECK(select_1_4(d, c, b, a) == b);
 

//     CHECK(select_2_4(a, b, c, d) == c);
//     CHECK(select_2_4(a, b, d, c) == c);
//     CHECK(select_2_4(a, c, b, d) == c);
//     CHECK(select_2_4(a, c, d, b) == c);
//     CHECK(select_2_4(a, d, b, c) == c);
//     CHECK(select_2_4(a, d, c, b) == c);

//     CHECK(select_2_4(b, a, c, d) == c);
//     CHECK(select_2_4(b, a, d, c) == c);
//     CHECK(select_2_4(b, c, a, d) == c);
//     CHECK(select_2_4(b, c, d, a) == c);
//     CHECK(select_2_4(b, d, a, c) == c);
//     CHECK(select_2_4(b, d, c, a) == c);

//     CHECK(select_2_4(c, a, b, d) == c);
//     CHECK(select_2_4(c, a, d, b) == c);
//     CHECK(select_2_4(c, b, a, d) == c);
//     CHECK(select_2_4(c, b, d, a) == c);
//     CHECK(select_2_4(c, d, a, b) == c);
//     CHECK(select_2_4(c, d, b, a) == c);

//     CHECK(select_2_4(d, a, b, c) == c);
//     CHECK(select_2_4(d, a, c, b) == c);
//     CHECK(select_2_4(d, b, a, c) == c);
//     CHECK(select_2_4(d, b, c, a) == c);
//     CHECK(select_2_4(d, c, a, b) == c);
//     CHECK(select_2_4(d, c, b, a) == c);


//     CHECK(select_3_4(a, b, c, d) == d);
//     CHECK(select_3_4(a, b, d, c) == d);
//     CHECK(select_3_4(a, c, b, d) == d);
//     CHECK(select_3_4(a, c, d, b) == d);
//     CHECK(select_3_4(a, d, b, c) == d);
//     CHECK(select_3_4(a, d, c, b) == d);

//     CHECK(select_3_4(b, a, c, d) == d);
//     CHECK(select_3_4(b, a, d, c) == d);
//     CHECK(select_3_4(b, c, a, d) == d);
//     CHECK(select_3_4(b, c, d, a) == d);
//     CHECK(select_3_4(b, d, a, c) == d);
//     CHECK(select_3_4(b, d, c, a) == d);

//     CHECK(select_3_4(c, a, b, d) == d);
//     CHECK(select_3_4(c, a, d, b) == d);
//     CHECK(select_3_4(c, b, a, d) == d);
//     CHECK(select_3_4(c, b, d, a) == d);
//     CHECK(select_3_4(c, d, a, b) == d);
//     CHECK(select_3_4(c, d, b, a) == d);

//     CHECK(select_3_4(d, a, b, c) == d);
//     CHECK(select_3_4(d, a, c, b) == d);
//     CHECK(select_3_4(d, b, a, c) == d);
//     CHECK(select_3_4(d, b, c, a) == d);
//     CHECK(select_3_4(d, c, a, b) == d);
//     CHECK(select_3_4(d, c, b, a) == d);

// }

#endif /*DOCTEST_LIBRARY_INCLUDED*/
