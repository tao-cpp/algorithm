//! \file tao/algorithm/predicates.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016-2019
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


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
