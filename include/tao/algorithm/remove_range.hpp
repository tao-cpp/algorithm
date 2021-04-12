//! \file tao/algorithm/remove_range.hpp
// Tao.Algorithm
//
// Copyright (c) 2016-2021 Fernando Pelliccioni.
//
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TAO_ALGORITHM_REMOVE_RANGE_HPP
#define TAO_ALGORITHM_REMOVE_RANGE_HPP

#include <algorithm>
#include <iterator>
#include <utility>

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/search.hpp>
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
