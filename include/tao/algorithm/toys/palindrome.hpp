//! \file tao/algorithm/accumulate.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016-2018
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_ALGORITHM_TOYS_PALINDROME_HPP_
#define TAO_ALGORITHM_TOYS_PALINDROME_HPP_

// #include <algorithm>
// #include <functional>
// #include <iterator>
// #include <utility>

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao { namespace algorithm {

//Complexity: 
//      Runtime:
//          Amortized: ???
//          Exact:     ???
//      Space:
//          O(???)
template <BidirectionalIterator I, Integer N>
	requires(Readable<I>)
bool palindrome_n(I f, I l, N n) {
    //precondition: readable_bounded_range(f, l) &&
    //              readable_counted_range(f, n)
    //              distance(f, l) == n

    n = half_nonnegative(n);
    while (n-- > N(0)) {
        swap(*f++, *--l);
    }

    //while (f != l && f != --l) std::swap(*f++, *l);

	if (f == l) return true;
	--l;

	while (f != l) {
		if ( *f != *l ) return false;
		++f;
		--l;
	}

	return true;
}


//Complexity: 
//      Runtime:
//          Amortized: ???
//          Exact:     ???
//      Space:
//          O(???)
template <BidirectionalIterator I>
	requires(Readable<I>)
bool palindrome(I f, I l) {
    //precondition: readable_bounded_range(f, l)

    using std::swap;

    //while (f != l && f != --l) swap(*f++, *l);

    while (true) {
        if (f == l) return;
        --l;
        if (f == l) return;
        swap(*f, *l);
        ++f;
    }


	if (f == l) return true;
	--l;

	while (f != l) {
		if ( *f != *l ) return false;
		++f;
		--l;
	}

	return true;
}

}} /*tao::algorithm*/

#endif /*TAO_ALGORITHM_TOYS_PALINDROME_HPP_*/
