//! \file tao/algorithm/numerics.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef TAO_ALGORITHM_NUMERICS_HPP
#define TAO_ALGORITHM_NUMERICS_HPP

#include <cstddef>

#include <tao/algorithm/concepts.hpp>

namespace tao { namespace algorithm {

template <Integral I>
inline
bool even(I const& a) { return (a bitand I(1)) == I(0); }

template <Integral I>
inline
bool odd(I const& a) { return (a bitand I(1)) != I(0); }

}} /*tao::algorithm*/

#endif //TAO_ALGORITHM_NUMERICS_HPP
