//! \file tao/algorithm/primes.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2017
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_ALGORITHM_PRIMES_HPP_
#define TAO_ALGORITHM_PRIMES_HPP_

#include <algorithm>
#include <iterator>
#include <utility>

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/integers.hpp>
#include <tao/algorithm/power.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao { namespace algorithm {

template <Integer I>
struct modulo_multiply {
    I modulus;
    modulo_multiply(I const& i) : modulus(i) {}
      
    I operator()(I const& n, I const& m) const {
        return (n * m) % modulus;
    }
};

template <Integer I>
bool miller_rabin_test(I n, I q, I k, I w) {

    // precondition: n > 1 && n - 1 == (2^k)*q && odd(q)
    
    modulo_multiply<I> mmult(n);
    I x = power_semigroup(w, q, mmult);
    if (x == I(1) || x == n - I(1)) return true;
    for (I i(1); i < k; ++i) {
    
        // invariant x == w^{2^{i-1}q}
        
        x = mmult(x, x);
        if (x == n - I(1)) return true;
        if (x == I(1))     return false;
    }
    return false;
}

#include <iostream>

template <Integer I>
std::pair<I, I> miller_rabin_q_k(I n) {
    // precondition: 

    // n - 1 = (2^k)*q

    I k(1);
    while (true) {
        I two_to_the_k = power_semigroup(2, k, std::multiplies<I>());
        // I q = (n - 1) / power_semigroup(2, k);
        // I r = (n - 1) % power_semigroup(2, k);

        // std::cout << "two_to_the_k: " << two_to_the_k << std::endl;

        if ((n - 1) % two_to_the_k == 0) {
            I q = (n - 1) / two_to_the_k;
            if (odd(q)) return {q, k};
        }
        ++k;
    }
}


template <Integer I>
bool prime(I n) {
    // n - 1 = (2^k)*q

    auto q_k = miller_rabin_q_k(n);

    auto q = q_k.first;
    auto k = q_k.second;


    std::cout << "q: " << q << std::endl;
    std::cout << "k: " << k << std::endl;

    auto w = 1; //TODO(fernando): try N random numbers from 0? to n
    return miller_rabin_test(n, q, k, w);
}

}} /*tao::algorithm*/

#endif /*TAO_ALGORITHM_PRIMES_HPP_*/
