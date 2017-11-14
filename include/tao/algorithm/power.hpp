//! \file tao/algorithm/power.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2017
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_ALGORITHM_POWER_HPP_
#define TAO_ALGORITHM_POWER_HPP_

#include <algorithm>
#include <iterator>
#include <utility>

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao { namespace algorithm {

template <NoncommutativeAdditiveMonoid T>
T identity_element(std::plus<T>) {
    return T(0);
}

template <MultiplicativeMonoid T>
T identity_element(std::multiplies<T>) {
    return T(1);
}

template <AdditiveGroup T>
std::negate<T> inverse_operation(std::plus<T>) {
    return std::negate<T>();
}

template <MultiplicativeGroup T>
struct reciprocal {
    T operator()(T const& x) const {
        return T(1) / x;
    }
};

template <MultiplicativeGroup T>
reciprocal<T> inverse_operation(std::multiplies<T>) {
    return reciprocal<T>();
}



template <Regular A, Integer N, SemigroupOperation Op>
    requires(Domain<Op, A>)
A power_accumulate_semigroup(A r, A a, N n, Op op) {
    // precondition: n >= 0
    if (n == 0) return r;
    while (true) {
        if (odd(n)) {
            r = op(r, a);
            if (n == 1) return r;
        }
        n = half(n);
        a = op(a, a);
    }
}

template <Regular A, Integer N, SemigroupOperation Op>
    requires(Domain<Op, A>)
A power_semigroup(A a, N n, Op op) {
    // precondition: n > 0
    while (!odd(n)) {
        a = op(a, a);
        n = half(n);
    }
    if (n == 1) return a;
    return power_accumulate_semigroup(a, op(a, a), half(n - 1), op);
}

template <Regular A, Integer N, MonoidOperation Op>
    requires(Domain<Op, A>)
A power_monoid(A a, N n, Op op) {
    // precondition: n >= 0
    if (n == 0) return identity_element(op);
    return power_semigroup(a, n, op);
}

template <Regular A, Integer N, GroupOperation Op>
    requires(Domain<Op, A>)
A power_group(A a, N n, Op op) {
    if (n < 0) {
        n = -n;
        a = inverse_operation(op)(a); 
    }
    return power_monoid(a, n, op);
}









}} /*tao::algorithm*/

#endif /*TAO_ALGORITHM_POWER_HPP_*/
