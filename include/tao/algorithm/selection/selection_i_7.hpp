//! \file tao/algorithm/selection/selection_i_7.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016-2018
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//TODO(fernando): Do the Average algorithm!
//TODO(fernando): # of Comparisons are not good!

#ifndef TAO_ALGORITHM_SELECTION_SELECTION_I_7_HPP_
#define TAO_ALGORITHM_SELECTION_SELECTION_I_7_HPP_

#include <algorithm>
#include <iterator>
#include <utility>

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/relation.hpp>
#include <tao/algorithm/selection/selection_i_6.hpp>
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
//  select_3_7:       12 or 13 .... Acording to TAoCP = 10 comparisons

//the median of seven is the third smallest of the six elements remaining after we remove the smallest of the first six.???????????????????

template <int ia, int ib, int ic, int id, int ie, int fi, int ig,
          Regular T, Regular U, Regular V, Regular W, Regular X, Regular Y, Regular Z, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && SameType<X, Y> && SameType<Y, Z> && Domain<R, T>)
inline constexpr
auto select_3_7_abc_def(T&& a, U&& b, V&& c, W&& d, X&& e, Y&& f, Z&& g, R r) FN(
    // precondition: !r(b, a) && !r(c, b) && !r(e, d) && !r(f, e)  -->  a <= b && b <= c && d <= e && e <= f
    CMP((ia < id), R)(d, a, r) 
        ? (select_2_6_abc<ia,ib,ic,ie,fi,ig>(_a, _b, _c, _e, _f, _g, r))
        : (select_2_6_abc<id,ie,fi,ib,ic,ig>(_d, _e, _f, _b, _c, _g, r))
)

template <int ia, int ib, int ic, int id, int ie, int fi, int ig,
          Regular T, Regular U, Regular V, Regular W, Regular X, Regular Y, Regular Z, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && SameType<X, Y> && SameType<Y, Z> && Domain<R, T>)
inline constexpr
auto select_3_7_abc_de(T&& a, U&& b, V&& c, W&& d, X&& e, Y&& f, Z&& g, R r) FN(
    // precondition: !r(b, a) && !r(c, b) && !r(e, d)  -->  a <= b && b <= c && d <= e
    CMP((ie < fi), R)(f, e, r)          // f < e
        ? CMP((id < fi), R)(f, d, r)    // f < d
            ? (select_3_7_abc_def<ia,ib,ic,fi,id,ie,ig>(_a, _b, _c, _f, _d, _e, _g, r))
            : (select_3_7_abc_def<ia,ib,ic,id,fi,ie,ig>(_a, _b, _c, _d, _f, _e, _g, r))
        :     (select_3_7_abc_def<ia,ib,ic,id,ie,fi,ig>(_a, _b, _c, _d, _e, _f, _g, r))
)

template <int ia, int ib, int ic, int id, int ie, int fi, int ig,
          Regular T, Regular U, Regular V, Regular W, Regular X, Regular Y, Regular Z, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && SameType<X, Y> && SameType<Y, Z> && Domain<R, T>)
inline constexpr
auto select_3_7_abc(T&& a, U&& b, V&& c, W&& d, X&& e, Y&& f, Z&& g, R r) FN(
    // precondition: !r(b, a) && !r(c, b) -->  a <= b && b <= c
    CMP((id < ie), R)(e, d, r) // e < d
        ? (select_3_7_abc_de<ia,ib,ic,ie,id,fi,ig>(_a, _b, _c, _e, _d, _f, _g, r))
        : (select_3_7_abc_de<ia,ib,ic,id,ie,fi,ig>(_a, _b, _c, _d, _e, _f, _g, r))
)

template <int ia, int ib, int ic, int id, int ie, int fi, int ig,
          Regular T, Regular U, Regular V, Regular W, Regular X, Regular Y, Regular Z, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && SameType<X, Y> && SameType<Y, Z> && Domain<R, T>)
inline constexpr
auto select_3_7_ab(T&& a, U&& b, V&& c, W&& d, X&& e, Y&& f, Z&& g, R r) FN(
    // precondition: !r(b, a)  -->  a <= b
    CMP((ib < ic), R)(c, b, r)          // c < b
        ? CMP((ia < ic), R)(c, a, r)    // c < a
            ? (select_3_7_abc<ic,ia,ib,id,ie,fi,ig>(_c, _a, _b, _d, _e, _f, _g, r))
            : (select_3_7_abc<ia,ic,ib,id,ie,fi,ig>(_a, _c, _b, _d, _e, _f, _g, r))
        :     (select_3_7_abc<ia,ib,ic,id,ie,fi,ig>(_a, _b, _c, _d, _e, _f, _g, r))
)

template <int ia, int ib, int ic, int id, int ie, int fi, int ig,
          Regular T, Regular U, Regular V, Regular W, Regular X, Regular Y, Regular Z, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && SameType<X, Y> && SameType<Y, Z> && Domain<R, T>)
inline constexpr
auto select_3_7(T&& a, U&& b, V&& c, W&& d, X&& e, Y&& f, Z&& g, R r) FN(
    CMP((ia < ib), R)(b, a, r)
        ? (select_3_7_ab<ib,ia,ic,id,ie,fi,ig>(_b, _a, _c, _d, _e, _f, _g, r))
        : (select_3_7_ab<ia,ib,ic,id,ie,fi,ig>(_a, _b, _c, _d, _e, _f, _g, r))
)

template <Regular T, Regular U, Regular V, Regular W, Regular X, Regular Y, Regular Z, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && SameType<X, Y> && SameType<Y, Z> && Domain<R, T>)
inline constexpr
auto median_of_7(T&& a, U&& b, V&& c, W&& d, X&& e, Y&& f, Z&& g, R r) FN(
    (select_3_7<0,1,2,3,4,5,6>(_a, _b, _c, _d, _e, _f, _g, r))
)





// // ------------------------------------------------------------------
// // Average comparisons improved, Worst case is worst ?????????????
// // ------------------------------------------------------------------

// template <int ia, int ib, int ic, int id, int ie,
//           Regular T, Regular U, Regular V, Regular W, Regular X, StrictWeakOrdering R>
//     requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && Domain<R, T>)
// inline constexpr
// auto select_3_7_abc(T&& a, U&& b, V&& c, W&& d, X&& e, Y&& f, Z&& g, R r) FN(
//     // precondition: !r(b, a) && !r(c, b)  -->  a <= b && b <= c
//     CMP((ib < id), R)(d, b, r)               //d < b 
//         ? CMP((ib < ie), R)(e, b, r)         //e < b 
//             ? (select_2_3<ia,id,ie>(_a, _d, _e, r))
//             : _b
//         : CMP((ib < ie), R)(e, b, r)         //e < b 
//             ? _b 
//             : (select_0_3<ic,id,ie>(_c, _d, _e, r))
// )




















// template <int ia, int ib, int ic, int id, int ie, int fi, int ig,
//           Regular T, Regular U, Regular V, Regular W, Regular X, Regular Y, Regular Z, StrictWeakOrdering R>
//     requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && SameType<X, Y> && SameType<Y, Z> && Domain<R, T>)
// inline constexpr
// auto select_3_7_abcd(T&& a, U&& b, V&& c, W&& d, X&& e, Y&& f, Z&& g, R r) FN(
//     // precondition: !r(b, a) && !r(c, b) && !r(d, c)  -->  a <= b && b <= c && c <= d

//     CMP((ic < id), R)(d, c, r)                      // e < d

//         CMP((ic < id), R)(d, c, r)                  // e < c
//             ? CMP((ib < id), R)(d, b, r)            // e < b
//                 ? CMP((ia < id), R)(d, a, r)        // e < a
//                     ? (select_3_7_abcd<id,ia,ib,ic,ie,fi,ig>(_d, _a, _b, _c, _e, _f, _g, r))
//                     : (select_3_7_abcd<ia,id,ib,ic,ie,fi,ig>(_a, _d, _b, _c, _e, _f, _g, r))
//                 :     (select_3_7_abcd<ia,ib,id,ic,ie,fi,ig>(_a, _b, _d, _c, _e, _f, _g, r))
//             :         (select_3_7_abcd<ia,ib,ic,id,ie,fi,ig>(_a, _b, _c, _d, _e, _f, _g, r))
// )

// template <int ia, int ib, int ic, int id, int ie, int fi, int ig,
//           Regular T, Regular U, Regular V, Regular W, Regular X, Regular Y, Regular Z, StrictWeakOrdering R>
//     requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && SameType<X, Y> && SameType<Y, Z> && Domain<R, T>)
// inline constexpr
// auto select_3_7_abc_avg(T&& a, U&& b, V&& c, W&& d, X&& e, Y&& f, Z&& g, R r) FN(
//     // precondition: !r(b, a) && !r(c, b)  -->  a <= b && b <= c
//     CMP((ic < id), R)(d, c, r)                  // d < c
//         ? CMP((ib < id), R)(d, b, r)            // d < b
//             ? CMP((ia < id), R)(d, a, r)        // d < a
//                 ? (select_3_7_abcd<id,ia,ib,ic,ie,fi,ig>(_d, _a, _b, _c, _e, _f, _g, r))
//                 : (select_3_7_abcd<ia,id,ib,ic,ie,fi,ig>(_a, _d, _b, _c, _e, _f, _g, r))
//             :     (select_3_7_abcd<ia,ib,id,ic,ie,fi,ig>(_a, _b, _d, _c, _e, _f, _g, r))
//         :         (select_3_7_abcd<ia,ib,ic,id,ie,fi,ig>(_a, _b, _c, _d, _e, _f, _g, r))
// )

// template <int ia, int ib, int ic, int id, int ie, int fi, int ig,
//           Regular T, Regular U, Regular V, Regular W, Regular X, Regular Y, Regular Z, StrictWeakOrdering R>
//     requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && SameType<X, Y> && SameType<Y, Z> && Domain<R, T>)
// inline constexpr
// auto select_3_7_ab_avg(T&& a, U&& b, V&& c, W&& d, X&& e, Y&& f, Z&& g, R r) FN(
//     // precondition: !r(b, a)  -->  a <= b
//     CMP((ib < ic), R)(c, b, r)          // c < b
//         ? CMP((ia < ic), R)(c, a, r)    // c < a
//             ? (select_3_7_abc_avg<ic,ia,ib,id,ie,fi,ig>(_c, _a, _b, _d, _e, _f, _g, r))
//             : (select_3_7_abc_avg<ia,ic,ib,id,ie,fi,ig>(_a, _c, _b, _d, _e, _f, _g, r))
//         :     (select_3_7_abc_avg<ia,ib,ic,id,ie,fi,ig>(_a, _b, _c, _d, _e, _f, _g, r))
// )

// template <int ia, int ib, int ic, int id, int ie, int fi, int ig,
//           Regular T, Regular U, Regular V, Regular W, Regular X, Regular Y, Regular Z, StrictWeakOrdering R>
//     requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && SameType<X, Y> && SameType<Y, Z> && Domain<R, T>)
// inline constexpr
// auto select_3_7_avg(T&& a, U&& b, V&& c, W&& d, X&& e, Y&& f, Z&& g, R r) FN(
//     CMP((ia < ib), R)(b, a, r)
//         ? (select_3_7_ab_avg<ib,ia,ic,id,ie,fi,ig>(_b, _a, _c, _d, _e, _f, _g, r))
//         : (select_3_7_ab_avg<ia,ib,ic,id,ie,fi,ig>(_a, _b, _c, _d, _e, _f, _g, r))
// )

// template <Regular T, Regular U, Regular V, Regular W, Regular X, Regular Y, Regular Z, StrictWeakOrdering R>
//     requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && SameType<W, X> && SameType<X, Y> && SameType<Y, Z> && Domain<R, T>)
// inline constexpr
// auto median_of_7_avg(T&& a, U&& b, V&& c, W&& d, X&& e, Y&& f, Z&& g, R r) FN(
//     (select_3_7_avg<0,1,2,3,4,5,6>(_a, _b, _c, _d, _e, _f, _g, r))
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

#endif /*TAO_ALGORITHM_SELECTION_SELECTION_I_7_HPP_*/

#ifdef DOCTEST_LIBRARY_INCLUDED
using namespace tao::algorithm;
using namespace std;

void do_tests(int (&p)[7], int median) {

    do {
        int const& m = median_of_7(p[0], p[1], p[2], p[3], p[4], p[5], p[6], less<>());
        int* pp[7] = {&p[0], &p[1], &p[2], &p[3], &p[4], &p[5], &p[6]};

        stable_sort(begin(pp), end(pp), [](int* a, int* b){
            return *a < *b;
        });

        CHECK(m == median);
        CHECK(*pp[3] == median);
        CHECK(&m == pp[3]);

    } while (next_permutation(begin(p), end(p), less<>()));
}

TEST_CASE("[median_of_7] 1 testing median_of_7 selection algorithm") {
    int p[7] = {0, 1, 2, 3, 4, 5, 6};
    do_tests(p, 3);
}

TEST_CASE("[median_of_7] 2 testing median_of_7 selection algorithm") {
    int p[7] = {0, 0, 2, 3, 4, 5, 6};
    do_tests(p, 3);
}

TEST_CASE("[median_of_7] 3 testing median_of_7 selection algorithm") {
    int p[7] = {0, 0, 0, 3, 4, 5, 6};
    do_tests(p, 3);
}

TEST_CASE("[median_of_7] 4 testing median_of_7 selection algorithm") {
    int p[7] = {0, 0, 0, 0, 4, 5, 6};
    do_tests(p, 0);
}

TEST_CASE("[median_of_7] 5 testing median_of_7 selection algorithm") {
    int p[7] = {0, 0, 0, 0, 0, 5, 6};
    do_tests(p, 0);
}

TEST_CASE("[median_of_7] 6 testing median_of_7 selection algorithm") {
    int p[7] = {0, 0, 0, 0, 0, 0, 6};
    do_tests(p, 0);
}

TEST_CASE("[median_of_7] 7 testing median_of_7 selection algorithm") {
    int p[7] = {0, 0, 0, 0, 0, 0, 0};
    do_tests(p, 0);
}

TEST_CASE("[median_of_7] 8 testing median_of_7 selection algorithm") {
    int p[7] = {0, 0, 1, 1, 1, 1, 1};
    do_tests(p, 1);
}

TEST_CASE("[median_of_7] 9 testing median_of_7 selection algorithm") {
    int p[7] = {0, 0, 0, 1, 1, 1, 1};
    do_tests(p, 1);
}

TEST_CASE("[median_of_7] 9 testing median_of_7 selection algorithm") {
    int p[7] = {0, 0, 0, 0, 1, 1, 1};
    do_tests(p, 0);
}

TEST_CASE("[median_of_7] 10 testing median_of_7 selection algorithm") {
    int p[7] = {0, 0, 0, 0, 0, 1, 1};
    do_tests(p, 0);
}

#endif /*DOCTEST_LIBRARY_INCLUDED*/




