//! \file tao/algorithm/relation.hpp
// Tao.Algorithm
//
// Copyright (c) 2016-2021 Fernando Pelliccioni.
//
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TAO_ALGORITHM_RELATION_HPP_
#define TAO_ALGORITHM_RELATION_HPP_

// #include <algorithm>
// #include <iterator>
// #include <utility>

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao { namespace algorithm {

template <bool strict, StrictWeakOrdering R>
struct compare_strict_or_reflexive;

template <StrictWeakOrdering R>
struct compare_strict_or_reflexive<true, R> { // strict
    template <Regular T, Regular U>
        requires(Same<T, U> && Domain<R, T>)
    inline constexpr
    bool operator()(T&& a, U&& b, R r) const {
        return r(std::forward<T>(a), std::forward<U>(b));
    }
};

template <StrictWeakOrdering R>
struct compare_strict_or_reflexive<false, R> { // reflexive
    template <Regular T, Regular U>
        requires(Same<T, U> && Domain<R, T>)
    inline constexpr
    bool operator()(T&& a, U&& b, R r) const {
        return !r(std::forward<U>(b), std::forward<T>(a)); // complement_of_converse(r(a, b))
    }
};

}} /*tao::algorithm*/

#include <tao/algorithm/concepts_undef.hpp>

#endif /*TAO_ALGORITHM_RELATION_HPP_*/

#ifdef DOCTEST_LIBRARY_INCLUDED
#endif /*DOCTEST_LIBRARY_INCLUDED*/




