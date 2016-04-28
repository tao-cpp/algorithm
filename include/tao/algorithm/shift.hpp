//! \file tao/algorithm/shift.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni, 2016
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef TAO_ALGORITHM_SHIFT_HPP
#define TAO_ALGORITHM_SHIFT_HPP

#include <algorithm>
#include <iterator>
#include <utility>

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/type_attributes.hpp>

template <ForwardIterator I>
void shift_right_by_one_forward_unguarded(I first, I last) {
    using std::swap;
    I current = first; 
    while (++current != last) swap(*first, *current);
}

//Complexity: 
//      Runtime:
//          Amortized: O(n)
//          Exact:     (n * distance(first, last) - (n * (n-1)) / 2) swaps
//      Space:
//          O(1)
template <ForwardIterator I, Integral N>
I shift_right(I first, I last, N n, std::forward_iterator_tag) {
    //precondition: [first, n) is a valid range
    while (n != 0) {
        shift_right_by_one_forward_unguarded(first, last);
        ++first;
        --n;
    }
    return first;
}

//Complexity: 
//      Runtime:
//          Amortized: O(n)
//          Exact:     (distance(first, last) - n) move-assigments or copy-assigments (depending of the ValueType<I> object)
//      Space:
//          O(1)
template <BidirectionalIterator I, Integral N>
I shift_right(I first, I last, N n, std::bidirectional_iterator_tag) {
    //precondition: distance(first, last) >= n
    using T = ValueType<I>;
    I butlast = std::prev(last, n);
    return std::move_backward(first, butlast, last);
}

//Complexity: 
//      Runtime:
//          Amortized: O(n)
//          Exact:     
//              for ForwardIterator:       (n * distance(first, last) - (n * (n-1)) / 2) swaps
//              for BidirectionalIterator: (distance(first, last) - n) move-assigments or copy-assigments (depending of the ValueType<I> object)
//      Space:
//          O(1)
template <ForwardIterator I, Integral N>
inline
I shift_right(I first, I last, N n) {
    return shift_right(first, last, n, IteratorCategory<I>{});
}

#endif /*TAO_ALGORITHM_SHIFT_HPP*/
