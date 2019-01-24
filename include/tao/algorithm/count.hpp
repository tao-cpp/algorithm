//! \file tao/algorithm/count.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016-2019
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_ALGORITHM_COUNT_HPP_
#define TAO_ALGORITHM_COUNT_HPP_

// #include <algorithm>
// #include <iterator>
// #include <utility>

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/type_attributes.hpp>
#include <tao/algorithm/for_each.hpp>

namespace tao { namespace algorithm {

//Complexity: 
template <Iterator I, UnaryPredicate P, Iterator J>
    requires(Readable<I> && Procedure<Proc> && Arity<Proc> == 1 &&
        ValueType<I> == Domain<P>)
J count_if(I f, I l, P p, J j) {
    // precondition: readable_bounded_range(f, l)
    while (f != l) {
        if (p(*f)) ++j;
        ++f;
    }
    return j;
}

template <Iterator I, UnaryPredicate P>
    requires(Readable<I> && Procedure<Proc> && Arity<Proc> == 1 &&
        ValueType<I> == Domain<P>)
DistanceType<I> count_if(I f, I l, P p) {
    // precondition: readable_bounded_range(f, l)
    return count_if(f, l, p, DistanceType<I>(0));
}


//EoP Exercise 6.2 page 98
template <UnaryPredicate P, Iterator J>
struct count_if_func {
    P p;
    J j;

    explicit 
    count_if_func(P p, J j) 
        : p(p), j(j) 
    {}

    template <Regular T>
        requires(T == Domain<P>)
    void operator()(T const& x) {
        if (p(x)) {
            ++j;
        }
    }
};


template <Iterator I, UnaryPredicate P, Iterator J>
    requires(Readable<I> && Procedure<Proc> && Arity<Proc> == 1 &&
        ValueType<I> == Domain<P>)
J count_if_2(I f, I l, P p, J j) {

    auto proc = tao::algorithm::for_each(f, l, count_if_func<P, J>(p, j));
    return proc.j;
}


}} /*tao::algorithm*/

#endif /*TAO_ALGORITHM_COUNT_HPP_*/


#ifdef DOCTEST_LIBRARY_INCLUDED
#include <vector>

using namespace tao::algorithm;
using namespace std;

TEST_CASE("[count_if_2] testing max_element selection algorithm, random access, no natural order, stability check") {
    vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto even = [](int x) {
        return x % 2 == 0;
    };

    size_t init = 0;
    auto res = count_if_2(begin(a), end(a), even, init);


    CHECK(res == 4);
}

#endif /*DOCTEST_LIBRARY_INCLUDED*/
