//! \file tao/algorithm/numerics.hpp
// Tao.Algorithm
//
// Copyright (c) 2016-2021 Fernando Pelliccioni.
//
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef TAO_ALGORITHM_NUMERICS_HPP
#define TAO_ALGORITHM_NUMERICS_HPP

#include <cstddef>

#include <tao/algorithm/concepts.hpp>

namespace tao { namespace algorithm {

template <Number T>
constexpr T EpsilonForEquals = T(0.00001);


template <FloatingPoint F>
inline constexpr
F abs_static(F x) {
    // <cmath> abs function doen't support compilation-time values
    return x < 0 ? -x : x;
}

template <FloatingPoint F1, FloatingPoint F2, FloatingPoint F3>
inline constexpr
bool equal_epsilon(F1 a, F2 b, F3 epsilon) {
    return abs_static(a - b) < epsilon;
}

template <FloatingPoint F1, FloatingPoint F2>
inline constexpr
bool equal_epsilon(F1 a, F2 b) {
    //TODO: Epsilon<X> X must be the "bigger" type between F1 and F2
    return equal_epsilon(a, b, EpsilonForEquals<F1>);
}


}} /*tao::algorithm*/

#endif //TAO_ALGORITHM_NUMERICS_HPP
