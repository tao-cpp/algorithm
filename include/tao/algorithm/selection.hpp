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

namespace tao { namespace algorithm {

// ------------------------------------------------------------------------------
// 2 elements selection

template <Regular T, Regular U, StrictWeakOrdering R>
    requires(SameType<T, U> && Domain<R, T>)
inline constexpr
auto&& select_0_2(T&& a, U&& b, R r) {
    return r(b, a) ? std::forward<U>(b) : std::forward<T>(a);
}

template <Regular T, Regular U>
    requires(SameType<T, U>)
inline constexpr
// auto select_0_2(T&& a, U&& b) -> decltype(b < a ? std::forward<U>(b) : std::forward<T>(a)) {
auto&& select_0_2(T&& a, U&& b) {
    return b < a ? std::forward<U>(b) : std::forward<T>(a);
}

template <Regular T, Regular U, StrictWeakOrdering R>
    requires(SameType<T, U> && Domain<R, T>)
inline constexpr
auto&& select_1_2(T&& a, U&& b, R r) {
    return r(b, a) ? std::forward<T>(a) : std::forward<U>(b);
}

template <Regular T, Regular U>
    requires(SameType<T, U>)
inline constexpr
auto&& select_1_2(T&& a, U&& b) {
    return b < a ? std::forward<T>(a) : std::forward<U>(b);
}

// Aliases
template <Regular T, Regular U, StrictWeakOrdering R>
    requires(SameType<T, U> && Domain<R, T>)
inline constexpr
auto&& min(T&& a, U&& b, R r) {
    return select_0_2(std::forward<T>(a), std::forward<U>(b), r);
}

template <Regular T, Regular U>
    requires(SameType<T, U>)
inline constexpr
auto&& min(T&& a, U&& b) {
    return select_0_2(std::forward<T>(a), std::forward<U>(b));
}

template <Regular T, Regular U, StrictWeakOrdering R>
    requires(SameType<T, U> && Domain<R, T>)
inline constexpr
auto&& max(T&& a, U&& b, R r) {
    return select_1_2(std::forward<T>(a), std::forward<U>(b), r);
}

template <Regular T, Regular U>
    requires(SameType<T, U>)
inline constexpr
auto&& max(T&& a, U&& b) {
    return select_1_2(std::forward<T>(a), std::forward<U>(b));
}

// ------------------------------------------------------------------------------
// 3 elements selection

template <Regular T, Regular U, Regular V, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && Domain<R, T>)
inline constexpr
auto&& select_0_3(T&& a, U&& b, V&& c, R r) {
    using std::forward;
    return select_0_2(
            select_0_2(forward<T>(a), forward<U>(b), r), 
            forward<V>(c), r);
}

template <Regular T, Regular U, Regular V>
    requires(SameType<T, U> && SameType<U, V>)
inline constexpr
auto&& select_0_3(T&& a, U&& b, V&& c) {
    using std::forward;
    return select_0_2(
            select_0_2(forward<T>(a), forward<U>(b)), 
            forward<V>(c));
}

template <Regular T, Regular U, Regular V, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && Domain<R, T>)
inline constexpr
auto&& select_2_3(T&& a, U&& b, V&& c, R r) {
    using std::forward;
    return select_1_2(
            select_1_2(forward<T>(a), forward<U>(b), r), 
            forward<V>(c), r);
}

template <Regular T, Regular U, Regular V>
    requires(SameType<T, U> && SameType<U, V>)
inline constexpr
auto&& select_2_3(T&& a, U&& b, V&& c) {
    using std::forward;
    return select_1_2(
            select_1_2(forward<T>(a), forward<U>(b)), 
            forward<V>(c));
}

template <Regular T, Regular U, Regular V, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && Domain<R, T>)
inline constexpr
auto&& select_1_3_ab(T&& a, U&& b, V&& c, R r) {
    // precondition: a <= b
    using std::forward;
    return ! r(c, b) ? //!(c < b) -> c >= b
                forward<U>(b) :                               // a, b, c are sorted
                select_1_2(forward<T>(a), forward<V>(c), r);  // b is not the median
}

template <Regular T, Regular U, Regular V, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && Domain<R, T>)
inline constexpr
auto&& select_1_3(T&& a, U&& b, V&& c, R r) {
    using std::forward;
    return r(b, a) ? select_1_3_ab(forward<U>(b), forward<T>(a), forward<V>(c), r) 
                   : select_1_3_ab(forward<T>(a), forward<U>(b), forward<V>(c), r);
}

template <Regular T, Regular U, Regular V>
    requires(SameType<T, U> && SameType<U, V>)
inline constexpr
auto&& select_1_3_ab(T&& a, U&& b, V&& c) {
    // precondition: a <= b
    using std::forward;
    return !(c < b) ? //!(c < b) -> c >= b
                  forward<U>(b)                              // a, b, c are sorted
                : select_1_2(forward<T>(a), forward<V>(c));  // b is not the median
}

template <Regular T, Regular U, Regular V>
    requires(SameType<T, U> && SameType<U, V>)
inline constexpr
auto&& select_1_3(T&& a, U&& b, V&& c) {
    using std::forward;
    return b < a ? 
              select_1_3_ab(forward<U>(b), forward<T>(a), forward<V>(c)) 
            : select_1_3_ab(forward<T>(a), forward<U>(b), forward<V>(c));
}




template <Regular T, Regular U, Regular V, Regular W, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && Domain<R, T>)
inline constexpr
auto&& select_1_4_ab_cd(T&& a, U&& b, V&& c, W&& d, R r) {
    // precondition: a <= b && c <= d

    // cdab ...  (c < a)
    // cadb ...  (c < a)
    // cabd ...  (c < a)

    // abcd ... !(c < a)
    // acbd ... !(c < a)
    // acdb ... !(c < a)

    using std::forward;
    return r(c, a) ? // c < a
              select_0_2(forward<T>(a), forward<W>(d), r)
            : select_0_2(forward<U>(b), forward<V>(c), r);
}

template <Regular T, Regular U, Regular V, Regular W, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && Domain<R, T>)
inline constexpr
auto&& select_1_4_ab(T&& a, U&& b, V&& c, W&& d, R r) {
    using std::forward;
    return r(d, c) ? // d < c
              select_1_4_ab_cd(forward<T>(a), forward<U>(b), forward<W>(d), forward<V>(c), r)
            : select_1_4_ab_cd(forward<T>(a), forward<U>(b), forward<V>(c), forward<W>(d), r);
}

template <Regular T, Regular U, Regular V, Regular W, StrictWeakOrdering R>
    requires(SameType<T, U> && SameType<U, V> && SameType<V, W> && Domain<R, T>)
inline constexpr
auto&& select_1_4(T&& a, U&& b, V&& c, W&& d, R r) {
    using std::forward;
    return r(b, a) ? // b < a
              select_1_4_ab(forward<U>(b), forward<T>(a), forward<V>(c), forward<W>(d), r)
            : select_1_4_ab(forward<T>(a), forward<U>(b), forward<V>(c), forward<W>(d), r);
}


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



}} /*tao::algorithm*/

#endif /*TAO_ALGORITHM_SELECTION_HPP_*/


#ifdef DOCTEST_LIBRARY_INCLUDED

TEST_CASE("[select_i_2] testing select_i_2 selection algorithm") {
    using namespace tao::algorithm;
    using namespace std;

    int a = 3;
    int b = 3;
    int c = 4;
    int d = 4;


    SUBCASE("[select_i_j] testing select_i_j selection algorithms") {
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

#endif /*DOCTEST_LIBRARY_INCLUDED*/

