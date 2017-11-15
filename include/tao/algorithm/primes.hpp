//! \file tao/algorithm/primes.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2017
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef TAO_ALGORITHM_PRIMES_HPP_
#define TAO_ALGORITHM_PRIMES_HPP_

#include <random>
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
        // invariant x == w^((2^(i-1))*q)
        
        x = mmult(x, x);
        if (x == n - I(1)) return true;
        if (x == I(1))     return false;
    }
    return false;
}

template <Integer I>
std::pair<I, I> miller_rabin_q_k(I n) {
    // precondition: odd(n) && ??? TODO(fernando)

    // n - 1 = (2^k)*q

    I k(1);
    while (true) {
        I two_to_the_k = power_semigroup(2, k, std::multiplies<I>());
        if ((n - 1) % two_to_the_k == 0) {
            I q = (n - 1) / two_to_the_k;
            if (odd(q)) return {q, k};
        }
        ++k;
    }
}

template <Integer I>
bool prime(I n, I witnesses_n = I(100)) {
    if (n <= I(1)) return false;
    if (n == I(2)) return true;
    if (even(n)) return false;

    auto q_k = miller_rabin_q_k(n);
    auto q = q_k.first;
    auto k = q_k.second;

    witnesses_n = (std::min)(n - I(1), witnesses_n);

    using dis_t = std::uniform_int_distribution<I>;
	std::random_device rd;
	std::mt19937 mt(rd());
	dis_t dis(1, witnesses_n);

    for (I i(0); i < witnesses_n; ++i) {
        if ( ! miller_rabin_test(n, q, k, dis(mt)) ) return false;
    }

    return true;
}

template <Integer I>
bool composite(I n, I witnesses_n = I(100)) {
    return !prime(n, witnesses_n);
}

// sift ----------------------

template <RandomAccessIterator I, Integer N>
    requires(ValueType<I, bool> && Mutable<I>)
void mark_sieve(I first, I last, N factor) {
    // precondition: first != last
    *first = false;
    while (last - first > factor) {
        first = first + factor;
        *first = false;
    }
}

template <RandomAccessIterator I, Integer N>
    requires(ValueType<I, bool> && Mutable<I>)
void sift(I first, N n) {
    // precondition: [first, n) is a valid range
    I last = first + n;
    std::fill(first, last, true);
    N i(0);
    N index_square(3);
    N factor(3);
    while (index_square < n) {
        // invariant: index_square = 2i^2 + 6i + 3, factor = 2i + 3
        if (first[i]) mark_sieve(first + index_square, last, factor);
        ++i;
        index_square += factor;
        factor += N(2);
        index_square += factor;
    }
}


// template <Integer N>
// struct sift_gen {


// };


}} /*tao::algorithm*/

#endif /*TAO_ALGORITHM_PRIMES_HPP_*/

#ifdef DOCTEST_LIBRARY_INCLUDED

TEST_CASE("[primes] testing the Primality Test functionality") {
    using namespace tao::algorithm;
    CHECK( ! prime(1));
    CHECK(composite(1));

    CHECK(prime(2));
    CHECK(prime(3));
    CHECK( ! prime(4));
    CHECK(prime(5));
    CHECK( ! prime(6));
    CHECK(prime(7));

    CHECK( ! prime(10001));
    CHECK(prime(10007));
    CHECK( ! prime(1729));
    CHECK( ! prime(172081));
}

#endif /*DOCTEST_LIBRARY_INCLUDED*/
