//! \file tao/algorithm/find.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016-2019
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_ALGORITHM_FIND_HPP_
#define TAO_ALGORITHM_FIND_HPP_

#include <algorithm>
#include <functional>
#include <iterator>
#include <utility>

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/integers.hpp>
#include <tao/algorithm/swap.hpp>
#include <tao/algorithm/type_attributes.hpp>
#include <tao/algorithm/predicates.hpp>

namespace tao { namespace algorithm {

template <Iterator I>
    requires(Readable<I>)
I find(I f, I l, ValueType<I> const& x) {
    //precondition: readable_bounded_range(f, l)
    while (f != l && *f != x) ++f;
    return f;
}

template <Iterator I>
    requires(Readable<I>)
std::pair<I, DistanceType<I>> find_n(I f, DistanceType<I> n, ValueType<I> const& x) {
    //precondition: readable_weak_range(f, n)
    while (!zero(n) && *f != x) {
        ++f;
        --n;
    }
    return {f, n};
}

template <Iterator I, UnaryPredicate P>
    requires(Readable<I>, Domain<P, ValueType<I>)
I find_if(I f, I l, P p) {
    //precondition: readable_bounded_range(f, l)
    while (f != l && ! p(*f)) ++f;
    return f;
}

template <Iterator I, UnaryPredicate P>
    requires(Readable<I>, Domain<P, ValueType<I>)
std::pair<I, DistanceType<I>> find_if_n(I f, DistanceType<I> n, P p) {
    //precondition: readable_weak_range(f, n)
    while (!zero(n) && ! p(*f)) {
        ++f;
        --n;
    }
    return {f, n};
}

template <Iterator I>
    requires(Readable<I>)
I find_unguarded(I f, ValueType<I> const& x) {
    //precondition: There exists l : I, such that: readable_bounded_range(f, l) && some(f, l, ???) TODO(fernando): ???
    while (*f != x) ++f;
    return f;
}

template <Iterator I, UnaryPredicate P>
    requires(Readable<I>, Domain<P, ValueType<I>)
I find_if_unguarded(I f, P p) {
    //precondition: There exists l : I, such that: readable_bounded_range(f, l) && some(f, l, p)
    while (! p(*f)) ++f;
    return f;
}


// Quantifier functions:
// ---------------------------------------------------------------------------

template <Iterator I, UnaryPredicate P>
    requires(Readable<I>, Domain<P, ValueType<I>)
inline
bool all(I f, I l, P p) {
    //precondition: readable_bounded_range(f, l)
    return l == tao::algorithm::find_if(f, l, predicate_negator<P>{p});
}

template <Iterator I, UnaryPredicate P>
    requires(Readable<I>, Domain<P, ValueType<I>)
inline
bool none(I f, I l, P p) {
    //precondition: readable_bounded_range(f, l)
    return l == tao::algorithm::find_if(f, l, p);
}

template <Iterator I, UnaryPredicate P>
    requires(Readable<I>, Domain<P, ValueType<I>)
inline
bool not_all(I f, I l, P p) {
    //precondition: readable_bounded_range(f, l)
    return ! tao::algorithm::all(f, l, p);
}

//some = any
template <Iterator I, UnaryPredicate P>
    requires(Readable<I>, Domain<P, ValueType<I>)
inline
bool some(I f, I l, P p) {
    //precondition: readable_bounded_range(f, l)
    return ! tao::algorithm::none(f, l, p);
}

template <Iterator I, UnaryPredicate P>
    requires(Readable<I>, Domain<P, ValueType<I>)
inline
bool all_n(I f, DistanceType<I> n, P p) {
    //precondition: readable_weak_range(f, l)
    return 0 == tao::algorithm::find_if_n(f, n, predicate_negator<P>{p}).second;
}

template <Iterator I, UnaryPredicate P>
    requires(Readable<I>, Domain<P, ValueType<I>)
inline
bool none_n(I f, DistanceType<I> n, P p) {
    //precondition: readable_weak_range(f, l)
    return 0 == tao::algorithm::find_if_n(f, n, p).second;
}

template <Iterator I, UnaryPredicate P>
    requires(Readable<I>, Domain<P, ValueType<I>)
inline
bool not_all_n(I f, DistanceType<I> n, P p) {
    //precondition: readable_weak_range(f, l)
    return ! tao::algorithm::all_n(f, n, p);
}

//some = any
template <Iterator I, UnaryPredicate P>
    requires(Readable<I>, Domain<P, ValueType<I>)
inline
bool some_n(I f, DistanceType<I> n, P p) {
    //precondition: readable_weak_range(f, l)
    return ! tao::algorithm::none_n(f, n, p);
}

// ---------------------------------------------------------------------------

template <Iterator I0, Iterator I1, Relation R>
    requires(Readable<I0>, Readable<I1>, Same<ValueType<I0>, ValueType<I1>> 
             && Domain<R, ValueType<I0>>)
std::pair<I0, I1> find_mismatch(I0 f0, I0 l0, I1 f1, I1 l1, R r) {
    //precondition: readable_bounded_range(f0, l0) &&
    //              readable_bounded_range(f1, l1)
    //postcondition: TODO(Fernando): EoP Ex 6.4 pag. 102

    while (f0 != l0 && f1 != l1 && r(*f0, *f1)) {
        ++f0;
        ++f1;
    }
    return {f0, f1};
}

template <Iterator I0, Iterator I1>
    requires(Readable<I0>, Readable<I1>, Same<ValueType<I0>, ValueType<I1>> 
             && Regular<ValueType<I0>>)
inline
std::pair<I0, I1> find_mismatch(I0 f0, I0 l0, I1 f1, I1 l1) {
    //precondition: readable_bounded_range(f0, l0) &&
    //              readable_bounded_range(f1, l1)
    //postcondition: TODO(Fernando): EoP Ex 6.4 pag. 102
    return tao::algorithm::find_mismatch(f0, l0, f1, l1, std::equal_to<>{});
}

template <Iterator I0, Iterator I1, Relation R>
    requires(Readable<I0>, Readable<I1>, Same<ValueType<I0>, ValueType<I1>> 
             && Domain<R, ValueType<I0>>)
std::tuple<I0, I1, DistanceType<I1>> find_mismatch_bn(I0 f0, I0 l0, I1 f1, DistanceType<I1> n1, R r) {
    //precondition: readable_bounded_range(f0, l0) &&
    //              readable_weak_range(f1, l1)
    //postcondition: TODO(Fernando): EoP Ex 6.4 pag. 102

    while (f0 != l0 && n1 != 0 && r(*f0, *f1)) {
        ++f0;
        ++f1;
        --n1;
    }
    return {f0, f1, n1};
}

template <Iterator I0, Iterator I1>
    requires(Readable<I0>, Readable<I1>, Same<ValueType<I0>, ValueType<I1>> 
             && Regular<ValueType<I0>>)
inline
std::tuple<I0, I1, DistanceType<I1>> find_mismatch_bn(I0 f0, I0 l0, I1 f1, DistanceType<I1> n1) {
    //precondition: readable_bounded_range(f0, l0) &&
    //              readable_weak_range(f1, l1)
    //postcondition: TODO(Fernando): EoP Ex 6.4 pag. 102
    return tao::algorithm::find_mismatch_bn(f0, l0, f1, n1, std::equal_to<>{});
}

template <Iterator I0, Iterator I1, Relation R>
    requires(Readable<I0>, Readable<I1>, Same<ValueType<I0>, ValueType<I1>> 
             && Domain<R, ValueType<I0>>)
std::tuple<I0, DistanceType<I0>, I1> find_mismatch_nb(I0 f0, DistanceType<I0> n0, I1 f1, I1 l1, R r) {
    //precondition: readable_weak_range(f0, l0) &&
    //              readable_bounded_range(f1, l1)
    //postcondition: TODO(Fernando): EoP Ex 6.4 pag. 102

    while (n0 != 0 && f1 != l1 && r(*f0, *f1)) {
        ++f0;
        ++f1;
        --n0;
    }
    return {f0, n0, f1};
}

template <Iterator I0, Iterator I1>
    requires(Readable<I0>, Readable<I1>, Same<ValueType<I0>, ValueType<I1>> 
             && Regular<ValueType<I0>>)
inline
std::tuple<I0, DistanceType<I0>, I1> find_mismatch_nb(I0 f0, DistanceType<I0> n0, I1 f1, I1 l1) {
    //precondition: readable_weak_range(f0, l0) &&
    //              readable_bounded_range(f1, l1)
    //postcondition: TODO(Fernando): EoP Ex 6.4 pag. 102
    return tao::algorithm::find_mismatch_nb(f0, n0, f1, l1, std::equal_to<>{});
}

template <Iterator I0, Iterator I1, Relation R>
    requires(Readable<I0>, Readable<I1>, Same<ValueType<I0>, ValueType<I1>> 
             && Domain<R, ValueType<I0>>)
std::tuple<I0, DistanceType<I0>, I1, DistanceType<I1>> find_mismatch_nn(I0 f0, DistanceType<I0> n0, I1 f1, DistanceType<I1> n1, R r) {
    //precondition: readable_weak_range(f0, l0) &&
    //              readable_weak_range(f1, l1)
    //postcondition: TODO(Fernando): EoP Ex 6.4 pag. 102

    while (n0 != 0 && n1 != 0 && r(*f0, *f1)) {
        ++f0;
        ++f1;
        --n0;
        --n1;
    }
    return {f0, n0, f1, n1};
}

template <Iterator I0, Iterator I1>
    requires(Readable<I0>, Readable<I1>, Same<ValueType<I0>, ValueType<I1>> 
             && Regular<ValueType<I0>>)
inline
std::tuple<I0, DistanceType<I0>, I1, DistanceType<I1>> find_mismatch_nn(I0 f0, DistanceType<I0> n0, I1 f1, DistanceType<I1> n1) {
    //precondition: readable_weak_range(f0, l0) &&
    //              readable_weak_range(f1, l1)
    //postcondition: TODO(Fernando): EoP Ex 6.4 pag. 102
    return tao::algorithm::find_mismatch_nn(f0, n0, f1, n1, std::equal_to<>{});
}

// ---------------------------------------------------------------------------

template <Iterator I, Relation R>
    requires(Readable<I> && Domain<R, ValueType<I>>)
I find_adjacent_mismatch(I f, I l, R r, std::input_iterator_tag) {
    //precondition: readable_bounded_range(f, l)
    if (f == l) return l;

    auto x = *f;    //copy
    ++f;

    while (f != l && r(x, *f)) {
        x = *f;     //copy
        ++f;
    }
    return f;
}

template <ForwardIterator I, Relation R>
    requires(Readable<I> && Domain<R, ValueType<I>>)
I find_adjacent_mismatch(I f, I l, R r, std::forward_iterator_tag) {
    //precondition: readable_bounded_range(f, l)
    if (f == l) return l;

    auto x = f;
    ++f;

    while (f != l && r(*x, *f)) {
        x = f;
        ++f;
    }
    return f;
}

template <Iterator I, Relation R>
    requires(Readable<I> && Domain<R, ValueType<I>>)
inline
I find_adjacent_mismatch(I f, I l, R r) {
    return find_adjacent_mismatch(f, l, r, IteratorCategory<I>{});
}

}} /*tao::algorithm*/

#endif /*TAO_ALGORITHM_FIND_HPP_*/


#ifdef DOCTEST_LIBRARY_INCLUDED

#include <iterator>
#include <forward_list>
#include <list>
#include <vector>

#include <tao/benchmark/instrumented.hpp>

using namespace std;
using namespace tao::algorithm;

// TEST_CASE("[shift] testing shift_right_by_one 0 elements random access") {
//     using T = int;
//     vector<T> a;
//     shift_right_by_one(begin(a), end(a));
//     CHECK(a == vector<T>());
// }

#endif /*DOCTEST_LIBRARY_INCLUDED*/
