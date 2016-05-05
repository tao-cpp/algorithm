//! \file tao/algorithm/iterator.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef TAO_ALGORITHM_ITERATOR_HPP
#define TAO_ALGORITHM_ITERATOR_HPP

#include <cstddef>

#include <tao/algorithm/concepts.hpp>

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

}} /*tao::algorithm*/

#endif //TAO_ALGORITHM_ITERATOR_HPP
