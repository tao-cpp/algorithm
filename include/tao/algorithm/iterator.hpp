//! \file tao/algorithm/iterator.hpp
// Tao.Algorithm
//
// Copyright (c) 2016-2021 Fernando Pelliccioni.
//
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef TAO_ALGORITHM_ITERATOR_HPP_
#define TAO_ALGORITHM_ITERATOR_HPP_

#include <cstddef>
#include <utility>

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao { namespace algorithm {

// ---------------------------------------------------------------------
// Declarations in the C++17 Standard
// ---------------------------------------------------------------------
// template < class C >
// constexpr auto size( const C& c ) -> decltype(c.size());
// template < class T, size_t N >
// constexpr size_t size( const T (&array)[N] ) noexcept;
// ---------------------------------------------------------------------


template <typename T, std::size_t N>
inline constexpr
std::size_t size(T const (&)[N]) noexcept { return N; };

template <Container C>
inline constexpr
auto size(C const& c) noexcept { return c.size(); }
// SizeType<C> size(C const& c) noexcept { return c.size(); }

template <Iterator I>
inline constexpr
I successor(I x) noexcept { return ++x; }

template <BidirectionalIterator I>
inline constexpr
I predecessor(I x) noexcept { return --x; }


template <Iterator I>
void step_n(I& f, DistanceType<I>& n) {
    ++f;
    --n;
}

template <Iterator I>
void step(I& f) {
    ++f;
}

template <Iterator I, Iterator... Args>
void step(I& f, Args&... args) {
    ++f;
    step(args...);
}

template <ForwardIterator I, UnaryPredicate P>
	requires(Readable<I> && Domain<P, ValueType<I>>)
std::pair<I, DistanceType<I>> successor_while_n(I f, DistanceType<I> n, P p) {
    while ( ! zero(n) && p(*f)) {
        --n;
        ++f;
    }
    return {f, n};
}

template <BidirectionalIterator I, UnaryPredicate P>
	requires(Readable<I> && Domain<P, ValueType<I>>)
std::pair<I, DistanceType<I>> predecessor_while_n(I f, DistanceType<I> n, P p) {
    while ( ! zero(n) && p(*f)) {
        --n;
        --f;
    }
    return {f, n};
}


}} /*tao::algorithm*/

#endif //TAO_ALGORITHM_ITERATOR_HPP_
