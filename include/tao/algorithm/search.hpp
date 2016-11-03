//! \file tao/algorithm/search.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_ALGORITHM_SEARCH_HPP
#define TAO_ALGORITHM_SEARCH_HPP

#include <algorithm>
#include <iterator>
#include <utility>

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao { namespace algorithm {


//Note: std::search is wrong, because, in some cases we will need the last iterator.
//TODO: Implement another search algorithms, like Boyer-Moore, ...

//Complexity: 
//      Runtime:
//          Amortized: O(n)
//          Exact:     TODO???
//      Space:
//          O(TODO???)
template <ForwardIterator I1, ForwardIterator I2>
// requires(Readable(I1) && Readable(I2) && ValueType(I1) == ValueType(I2) TODO???)
std::pair<I1, I1> search(I1 f, I1 l, I2 fs, I2 ls) {
    // precondition: readable_weak_range(f, l) && readable_weak_range(fs, ls) TODO???

    while (true) {
        I1 it = f;
        I2 it_s = fs;
        while (true) {
            if (it_s == ls) return std::make_pair(f, it);
            if (it == l) return std::make_pair(l, l);
            if (*it != *it_s) break;
            ++it;
            ++it_s;
        }
        ++f;
    }
}


//Note: is called search_counted_range, because search_n exists in the C++ Standard Library with different semantics.

//Complexity: 
//      Runtime:
//          Amortized: O(n)
//          Exact:     TODO???
//      Space:
//          O(TODO???)
template <ForwardIterator I1, ForwardIterator I2>
// requires(Readable(I1) && Readable(I2) && ValueType(I1) == ValueType(I2) TODO???)
std::pair<I1, DistanceType<I1>> search_counted_range(I1 f, DistanceType<I1> n, I2 fs, DistanceType<I2> ns) {
    // Precondition: readable_weak_range(f, n) && readable_weak_range(fs, ns) TODO???

    while (n >= ns) {
        I1 it = f;
        I2 it_s = fs;

        DistanceType<I1> n2 = n;
        DistanceType<I2> ns2 = ns;

        while (true) {
            if (ns2 == 0) return std::make_pair(f, ns);
            if (n2 == 0) return std::make_pair(it, 0);
            if (*it != *it_s) break;

            ++it;
            ++it_s;
            --n2;
            --ns2;
        }
        ++f;
        --n;
    }
    return std::make_pair(f, 0);
}


}} /*tao::algorithm*/

#endif /*TAO_ALGORITHM_SEARCH_HPP*/
