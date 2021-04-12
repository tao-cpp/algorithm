//! \file tao/algorithm/integers.hpp
// Tao.Algorithm
//
// Copyright (c) 2016-2021 Fernando Pelliccioni.
//
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TAO_ALGORITHM_INTEGERS_HPP_
#define TAO_ALGORITHM_INTEGERS_HPP_

#include <iterator>

#include <tao/algorithm/concepts.hpp>

namespace tao { namespace algorithm {

template <Integer I>
inline constexpr
bool even(I const& a) { return (a & I(1)) == I(0); }

template <Integer I>
inline constexpr
bool odd(I const& a) { return (a & I(1)) != I(0); }

template <Integer N>
inline constexpr
N half(N n) { return n >> 1; }

template <Integer I>
inline constexpr
bool positive(I const& a) { return I(0) < a; }

template <Integer I>
inline constexpr
bool negative(I const& a) { return a < I(0); }

template <Integer I>
inline constexpr
bool zero(I const& a) { return a == I(0); }

template <Integer I>
inline constexpr
bool one(I const& a) { return a == I(1); }

template <Regular T>
constexpr auto supremum = std::numeric_limits<T>::max();

template <Regular T>
constexpr auto infimum = std::numeric_limits<T>::min();

}} /*tao::algorithm*/

#endif /*TAO_ALGORITHM_INTEGERS_HPP_*/
