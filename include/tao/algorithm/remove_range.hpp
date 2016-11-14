//! \file tao/algorithm/remove_range.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_ALGORITHM_REMOVE_RANGE_HPP
#define TAO_ALGORITHM_REMOVE_RANGE_HPP

#include <algorithm>
#include <iterator>
#include <utility>

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao { namespace algorithm {


//Complexity: 
//      Runtime:
//          Amortized: O(n)
//          Exact:     TODO???
//      Space:
//          O(TODO???)
template <ForwardIterator I1, ForwardIterator I2>
// requires(Readable(I1) && Readable(I2) && ValueType(I1) == ValueType(I2) TODO???)
I1 remove_range_first(I1 f, I1 l, I2 fs, I2 ls) {
    // precondition: readable_weak_range(f, l) && readable_weak_range(fs, ls) TODO???
    I1 fn;
    std::tie(f, fn) = tao::algorithm::search(f, l, fs, ls);
    if (f == l) return f;
    return std::rotate(f, fn, l);
}

//Complexity: 
//      Runtime:
//          Amortized: O(n)
//          Exact:     TODO???
//      Space:
//          O(TODO???)
template <ForwardIterator I1, ForwardIterator I2>
// requires(Readable(I1) && Readable(I2) && ValueType(I1) == ValueType(I2) TODO???)
I1 remove_range(I1 f, I1 l, I2 fs, I2 ls) {
    // precondition: readable_weak_range(f, l) && readable_weak_range(fs, ls) TODO???
    I1 fn;
    std::tie(f, fn) = tao::algorithm::search(f, l, fs, ls);
    
    while (f != l) {
        l = std::rotate(f, fn, l);
        std::tie(f, fn) = tao::algorithm::search(f, l, fs, ls);
    }
    return l;
}

//TODO: implement remove_range_n. We need tao::rotate_n. 

}} /*tao::algorithm*/

#endif /*TAO_ALGORITHM_REMOVE_RANGE_HPP*/
