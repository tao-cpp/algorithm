//! \file tao/algorithm/predicates.hpp
// Tao.Algorithm
//
// Copyright (c) 2016-2021 Fernando Pelliccioni.
//
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef TAO_ALGORITHM_PREDICATES_HPP_
#define TAO_ALGORITHM_PREDICATES_HPP_

#include <tao/algorithm/concepts.hpp>

template <UnaryPredicate P>
struct predicate_negator {
    P p;

    explicit
    predicate_negator(P p) : p(p) {}

    template <Semiregular T>
        requires(Domain<P, T>)
    T operator()(T const& x) const {
        return !p(x);
    }
};

#endif //TAO_ALGORITHM_PREDICATES_HPP_
