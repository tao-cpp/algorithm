//! \file tao/algorithm/shift.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016
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

namespace tao { namespace algorithm {


//TODO(fernando): find a better name
template <Regular T>
inline
void swap_2(T& a, T& b, T& c) noexcept {
    b = std::move(a);
    a = std::move(c);
}

template <ForwardIterator I>
void shift_right_by_one_temp(I f, I l) {
    //precondition: mutable????_bounded_range(f, l)

    using std::swap;

    if (f == l) return;

    ValueType<I> a = std::move(*f);
    ++f;

    ValueType<I> b;

    while (f != l) {
        swap_2(*f++, b, a);
        if (f == l) return;
        swap_2(*f++, a, b);
    }
}


//Complexity: 
//      Runtime:
//          Amortized: ???
//          Exact:     ???
//      Space:
//          ???
template <ForwardIterator I>
void shift_right_by_one_forward_unguarded(I f, I l) {
    //precondition: mutable????_bounded_range(f, l)
    //              distance(f, l) >= 1
    using std::swap;
    I current = f; 
    while (++current != l) swap(*f, *current);
}

//Complexity: 
//      Runtime:
//          Amortized: O(n)
//          Exact:     (n * distance(f, l) - (n * (n-1)) / 2) swaps
//      Space:
//          O(1)
template <ForwardIterator I, Integral N>
I shift_right(I f, I l, N n, std::forward_iterator_tag) {
    //precondition: n >= 0 &&
    //              std::distance(f, l) >= n (so [f, n) is a valid range)
    while (n > 0) {
        shift_right_by_one_forward_unguarded(f, l);
        ++f;
        --n;
    }
    return f;
}

//Complexity: 
//      Runtime:
//          Amortized: O(n)
//          Exact:     (distance(f, l) - n) move-assigments or copy-assigments (depending of the ValueType<I> object)
//      Space:
//          O(1)
template <BidirectionalIterator I, Integral N>
I shift_right(I f, I l, N n, std::bidirectional_iterator_tag) {
    //precondition: n >= 0 && 
    //              std::distance(f, l) >= n (so [f, n) is a valid range)
    I butl = std::prev(l, n);
    return std::move_backward(f, butl, l);
}

//Complexity: 
//      Runtime:
//          Amortized: O(n)
//          Exact:     
//              for ForwardIterator:       (n * distance(f, l) - (n * (n-1)) / 2) swaps
//              for BidirectionalIterator: (distance(f, l) - n) move-assigments or copy-assigments (depending of the ValueType<I> object)
//      Space:
//          O(1)
template <ForwardIterator I, Integral N>
inline
I shift_right(I f, I l, N n) {
    return shift_right(f, l, n, IteratorCategory<I>{});
}


//TODO: shift_left

// //Complexity: 
// //      Runtime:
// //          Amortized: O(n)
// //          Exact:     (n * distance(f, l) - (n * (n-1)) / 2) swaps
// //      Space:
// //          O(1)
// template <ForwardIterator I, Integral N>
// I shift_left(I f, I l, N n, std::forward_iterator_tag) {
//     // //precondition: n >= 0 &&
//     // //              std::distance(f, l) >= n (so [f, n) is a valid range)
//     // while (n > 0) {
//     //     shift_right_by_one_forward_unguarded(f, l);
//     //     ++f;
//     //     --n;
//     // }
//     // return f;
// }


// //Complexity: 
// //      Runtime:
// //          Amortized: O(n)
// //          Exact:     (distance(f, l) - n) move-assigments or copy-assigments (depending of the ValueType<I> object)
// //      Space:
// //          O(1)
// template <BidirectionalIterator I, Integral N>
// I shift_left(I f, I l, N n, std::bidirectional_iterator_tag) {
//     //precondition: n >= 0 && 
//     //              std::distance(f, l) >= n (so [f, n) is a valid range)
//     //return std::move(f, std::next(f, n), l);
// }

// //Complexity: 
// //      Runtime:
// //          Amortized: O(n)
// //          Exact:     
// //              for ForwardIterator:       (n * distance(f, l) - (n * (n-1)) / 2) swaps
// //              for BidirectionalIterator: (distance(f, l) - n) move-assigments or copy-assigments (depending of the ValueType<I> object)
// //      Space:
// //          O(1)
// template <ForwardIterator I, Integral N>
// inline
// I shift_left(I f, I l, N n) {
//     return shift_left(f, l, n, IteratorCategory<I>{});
// }

}} /*tao::algorithm*/

#endif /*TAO_ALGORITHM_SHIFT_HPP*/


#ifdef DOCTEST_LIBRARY_INCLUDED

#include <iterator>
#include <forward_list>
#include <list>
#include <vector>

#include <tao/benchmark/instrumented.hpp>

using namespace std;
using namespace tao::algorithm;

// for (auto&& x : a) {
//     cout << x << endl;
// }

// double* count_p = instrumented<int>::counts;
// for (size_t i = 0; i < instrumented_base::number_ops; ++i) {
//     std::cout << instrumented_base::counter_names[i] << ": " 
//                 << count_p[i] 
//                 << std::endl;
// }

// TEST_CASE("[shift] testing shift_right_by_one_forward_unguarded") {
//     //using namespace tao::algorithm;

//    // using T = int;
//     using T = instrumented<int>;

//     vector<T> a = {1, 2, 3, 4, 5, 6};

//     instrumented<int>::initialize(0);
//     // shift_right_by_one_forward_unguarded(begin(a) + 1, begin(a) + 4);
//     shift_right_by_one_forward_unguarded(begin(a), end(a));

//     double* count_p = instrumented<int>::counts;
//     CHECK(a == vector<T>{6, 1, 2, 3, 4, 5});
//     CHECK(count_p[instrumented_base::copy_ctor] + count_p[instrumented_base::copy_assignment] + count_p[instrumented_base::move_ctor] + count_p[instrumented_base::move_assignment] == 3 * (a.size() - 1));
//     CHECK(count_p[instrumented_base::destructor] == a.size() - 1);

// }


TEST_CASE("[shift] testing shift_right_by_one_temp") {
    //using namespace tao::algorithm;

    // using T = int;
    using T = instrumented<int>;
    instrumented<int>::initialize(0);

    vector<T> a = {1, 2, 3, 4, 5, 6};

    instrumented<int>::initialize(0);
    shift_right_by_one_temp(begin(a), end(a));

    // for (auto&& x : a) {
    //     cout << x << endl;
    // }


    double* count_p = instrumented<int>::counts;
    for (size_t i = 0; i < instrumented_base::number_ops; ++i) {
        std::cout << instrumented_base::counter_names[i] << ": " 
                  << count_p[i] 
                  << std::endl;
    }

    CHECK(a == vector<T>{1, 1, 2, 3, 4, 5});
    CHECK(a == vector<T>{1, 1, 2, 3, 4, 6});
    
}


// n: 0
// default: 0
// construct: 0
// copy ctor: 2
// copy assign: 9
// move ctor: 0
// move assign: 0
// destruct: 2
// equal: 0
// less: 0

#endif /*DOCTEST_LIBRARY_INCLUDED*/
