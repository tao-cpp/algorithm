//! \file tao/algorithm/integers.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016-2018
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_ALGORITHM_INTEGERS_HPP
#define TAO_ALGORITHM_INTEGERS_HPP

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

}} /*tao::algorithm*/

#endif /*TAO_ALGORITHM_INTEGERS_HPP*/
