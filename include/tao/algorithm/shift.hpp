//! \file tao/algorithm/shift.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016-2018
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_ALGORITHM_SHIFT_HPP
#define TAO_ALGORITHM_SHIFT_HPP

#include <algorithm>
#include <iterator>
#include <utility>

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/swap.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao { namespace algorithm {

// -----------------------------------------------------------------
// shift_right_by_one
// -----------------------------------------------------------------

//TODO(fernando): see what we have to return

//Complexity: 
//      Runtime:
//          Amortized: O(n)
//          Exact:     2 * distance(f, l) - 1 assigments (move or copy)
//      Space:
//          O(1)
template <ForwardIterator I>
void shift_right_by_one(I f, I l, std::forward_iterator_tag) {
    //precondition: mutable_bounded_range(f, l)
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

template <BidirectionalIterator I>
void shift_right_by_one(I f, I l, std::bidirectional_iterator_tag) {
    //precondition: mutable_bounded_range(f, l)
    if (f == l) return;
    std::copy_backward(f, std::prev(l, 1), l);
}

//Complexity: 
//      Runtime:
//          Amortized: O(n)
//          Exact:     
//              for ForwardIterator:       
//              for BidirectionalIterator: 
//      Space:
//          O(1)
template <ForwardIterator I>
inline
void shift_right_by_one(I f, I l) {
    return shift_right_by_one(f, l, IteratorCategory<I>{});
}


// -----------------------------------------------------------------
// shift_right_by_one_n
// -----------------------------------------------------------------

//Complexity: 
//      Runtime:
//          Amortized: O(n)
//          Exact:     2 * distance(f, l) - 1 assigments (move or copy)
//      Space:
//          O(1)
template <ForwardIterator I, Integer N>
void shift_right_by_one_n(I f, N n, std::forward_iterator_tag) {
    //precondition: mutable_counted_range(f, n)
    if (n == N(0)) return;

    ValueType<I> a = std::move(*f);
    ++f; --n;
    ValueType<I> b;
    while (n != N(0)) {
        swap_2(*f++, b, a); --n;
        if (n == N(0)) return;
        swap_2(*f++, a, b); --n;
    }
}

//Complexity: 
//      Runtime:
//          Amortized: O(n)
//          Exact:     
//              for ForwardIterator:       
//              for BidirectionalIterator: 
//      Space:
//          O(1)
template <ForwardIterator I, Integer N>
inline
void shift_right_by_one_n(I f, N n) {
    return shift_right_by_one_n(f, n, IteratorCategory<I>{});
}



// ----------------------------------------------------------------

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

TEST_CASE("[shift] testing shift_right_by_one 0 elements random access") {
    using T = int;
    vector<T> a;
    shift_right_by_one(begin(a), end(a));
    CHECK(a == vector<T>());
}

TEST_CASE("[shift] testing shift_right_by_one 1 elements random access") {
    using T = int;
    vector<T> a = {1};
    shift_right_by_one(begin(a), end(a));
    CHECK(a == vector<T>{1});
}

TEST_CASE("[shift] testing shift_right_by_one 2 elements random access") {
    using T = int;
    vector<T> a = {1, 2};
    shift_right_by_one(begin(a), end(a));
    CHECK(a == vector<T>{1, 1});
}

TEST_CASE("[shift] testing shift_right_by_one 3 elements random access") {
    using T = int;
    vector<T> a = {1, 2, 3};
    shift_right_by_one(begin(a), end(a));
    CHECK(a == vector<T>{1, 1, 2});
}

TEST_CASE("[shift] testing shift_right_by_one 4 elements random access") {
    using T = int;
    vector<T> a = {1, 2, 3, 4};
    shift_right_by_one(begin(a), end(a));
    CHECK(a == vector<T>{1, 1, 2, 3});
}

TEST_CASE("[shift] testing shift_right_by_one 5 elements random access") {
    using T = int;
    vector<T> a = {1, 2, 3, 4, 5};
    shift_right_by_one(begin(a), end(a));
    CHECK(a == vector<T>{1, 1, 2, 3, 4});
}

TEST_CASE("[shift] testing shift_right_by_one 6 elements random access") {
    using T = int;
    vector<T> a = {1, 2, 3, 4, 5, 6};
    shift_right_by_one(begin(a), end(a));
    CHECK(a == vector<T>{1, 1, 2, 3, 4, 5});
}

TEST_CASE("[shift] testing shift_right_by_one 0 elements bidirectional") {
    using T = int;
    list<T> a;
    shift_right_by_one(begin(a), end(a));
    CHECK(a == list<T>());
}

TEST_CASE("[shift] testing shift_right_by_one 1 elements bidirectional") {
    using T = int;
    list<T> a = {1};
    shift_right_by_one(begin(a), end(a));
    CHECK(a == list<T>{1});
}

TEST_CASE("[shift] testing shift_right_by_one 2 elements bidirectional") {
    using T = int;
    list<T> a = {1, 2};
    shift_right_by_one(begin(a), end(a));
    CHECK(a == list<T>{1, 1});
}

TEST_CASE("[shift] testing shift_right_by_one 3 elements bidirectional") {
    using T = int;
    list<T> a = {1, 2, 3};
    shift_right_by_one(begin(a), end(a));
    CHECK(a == list<T>{1, 1, 2});
}

TEST_CASE("[shift] testing shift_right_by_one 4 elements bidirectional") {
    using T = int;
    list<T> a = {1, 2, 3, 4};
    shift_right_by_one(begin(a), end(a));
    CHECK(a == list<T>{1, 1, 2, 3});
}

TEST_CASE("[shift] testing shift_right_by_one 5 elements bidirectional") {
    using T = int;
    list<T> a = {1, 2, 3, 4, 5};
    shift_right_by_one(begin(a), end(a));
    CHECK(a == list<T>{1, 1, 2, 3, 4});
}

TEST_CASE("[shift] testing shift_right_by_one 6 elements bidirectional") {
    using T = int;
    list<T> a = {1, 2, 3, 4, 5, 6};
    shift_right_by_one(begin(a), end(a));
    CHECK(a == list<T>{1, 1, 2, 3, 4, 5});
}

TEST_CASE("[shift] testing shift_right_by_one 0 elements forward") {
    using T = int;
    forward_list<T> a;
    shift_right_by_one(begin(a), end(a));
    CHECK(a == forward_list<T>());
}

TEST_CASE("[shift] testing shift_right_by_one 1 elements forward") {
    using T = int;
    forward_list<T> a = {1};
    shift_right_by_one(begin(a), end(a));
    CHECK(a == forward_list<T>{1});
}

TEST_CASE("[shift] testing shift_right_by_one 2 elements forward") {
    using T = int;
    forward_list<T> a = {1, 2};
    shift_right_by_one(begin(a), end(a));
    CHECK(a == forward_list<T>{1, 1});
}

TEST_CASE("[shift] testing shift_right_by_one 3 elements forward") {
    using T = int;
    forward_list<T> a = {1, 2, 3};
    shift_right_by_one(begin(a), end(a));
    CHECK(a == forward_list<T>{1, 1, 2});
}

TEST_CASE("[shift] testing shift_right_by_one 4 elements forward") {
    using T = int;
    forward_list<T> a = {1, 2, 3, 4};
    shift_right_by_one(begin(a), end(a));
    CHECK(a == forward_list<T>{1, 1, 2, 3});
}

TEST_CASE("[shift] testing shift_right_by_one 5 elements forward") {
    using T = int;
    forward_list<T> a = {1, 2, 3, 4, 5};
    shift_right_by_one(begin(a), end(a));
    CHECK(a == forward_list<T>{1, 1, 2, 3, 4});
}

TEST_CASE("[shift] testing shift_right_by_one 6 elements forward") {
    using T = int;
    forward_list<T> a = {1, 2, 3, 4, 5, 6};
    shift_right_by_one(begin(a), end(a));
    CHECK(a == forward_list<T>{1, 1, 2, 3, 4, 5});
}

TEST_CASE("[shift] testing shift_right_by_one instrumented random access") {
    using T = instrumented<int>;
    vector<T> a = {1, 2, 3, 4, 5, 6};

    instrumented<int>::initialize(0);
    shift_right_by_one(begin(a), end(a));

    double* count_p = instrumented<int>::counts;
    CHECK(count_p[instrumented_base::copy_ctor] + 
          count_p[instrumented_base::copy_assignment] + 
          count_p[instrumented_base::move_ctor] + 
          count_p[instrumented_base::move_assignment] == a.size() - 1);
    CHECK(count_p[instrumented_base::destructor] == 0);
}

TEST_CASE("[shift] testing shift_right_by_one instrumented bidirectional") {
    using T = instrumented<int>;
    list<T> a = {1, 2, 3, 4, 5, 6};

    instrumented<int>::initialize(0);
    shift_right_by_one(begin(a), end(a));

    double* count_p = instrumented<int>::counts;
    CHECK(count_p[instrumented_base::copy_ctor] + 
          count_p[instrumented_base::copy_assignment] + 
          count_p[instrumented_base::move_ctor] + 
          count_p[instrumented_base::move_assignment] == a.size() - 1);
    CHECK(count_p[instrumented_base::destructor] == 0);
}

TEST_CASE("[shift] testing shift_right_by_one instrumented forward") {
    using T = instrumented<int>;
    forward_list<T> a = {1, 2, 3, 4, 5, 6};
    auto n = distance(begin(a), end(a));

    instrumented<int>::initialize(0);
    shift_right_by_one(begin(a), end(a));

    double* count_p = instrumented<int>::counts;
    CHECK(count_p[instrumented_base::copy_ctor] + 
          count_p[instrumented_base::copy_assignment] + 
          count_p[instrumented_base::move_ctor] + 
          count_p[instrumented_base::move_assignment] == 2 * n - 1);
    CHECK(count_p[instrumented_base::destructor] == 2);
}


TEST_CASE("[shift] testing shift_right_by_one_n 0 elements random access") {
    using T = int;
    vector<T> a;
    shift_right_by_one_n(begin(a), a.size());
    CHECK(a == vector<T>());
}

TEST_CASE("[shift] testing shift_right_by_one_n 1 elements random access") {
    using T = int;
    vector<T> a = {1};
    shift_right_by_one_n(begin(a), a.size());
    CHECK(a == vector<T>{1});
}

TEST_CASE("[shift] testing shift_right_by_one_n 2 elements random access") {
    using T = int;
    vector<T> a = {1, 2};
    shift_right_by_one_n(begin(a), a.size());
    CHECK(a == vector<T>{1, 1});
}

TEST_CASE("[shift] testing shift_right_by_one_n 3 elements random access") {
    using T = int;
    vector<T> a = {1, 2, 3};
    shift_right_by_one_n(begin(a), a.size());
    CHECK(a == vector<T>{1, 1, 2});
}

TEST_CASE("[shift] testing shift_right_by_one_n 4 elements random access") {
    using T = int;
    vector<T> a = {1, 2, 3, 4};
    shift_right_by_one_n(begin(a), a.size());
    CHECK(a == vector<T>{1, 1, 2, 3});
}

TEST_CASE("[shift] testing shift_right_by_one_n 5 elements random access") {
    using T = int;
    vector<T> a = {1, 2, 3, 4, 5};
    shift_right_by_one_n(begin(a), a.size());
    CHECK(a == vector<T>{1, 1, 2, 3, 4});
}

TEST_CASE("[shift] testing shift_right_by_one_n 6 elements random access") {
    using T = int;
    vector<T> a = {1, 2, 3, 4, 5, 6};
    shift_right_by_one_n(begin(a), a.size());
    CHECK(a == vector<T>{1, 1, 2, 3, 4, 5});
}

TEST_CASE("[shift] testing shift_right_by_one_n 0 elements bidirectional") {
    using T = int;
    list<T> a;
    shift_right_by_one_n(begin(a), a.size());
    CHECK(a == list<T>());
}

TEST_CASE("[shift] testing shift_right_by_one_n 1 elements bidirectional") {
    using T = int;
    list<T> a = {1};
    shift_right_by_one_n(begin(a), a.size());
    CHECK(a == list<T>{1});
}

TEST_CASE("[shift] testing shift_right_by_one_n 2 elements bidirectional") {
    using T = int;
    list<T> a = {1, 2};
    shift_right_by_one_n(begin(a), a.size());
    CHECK(a == list<T>{1, 1});
}

TEST_CASE("[shift] testing shift_right_by_one_n 3 elements bidirectional") {
    using T = int;
    list<T> a = {1, 2, 3};
    shift_right_by_one_n(begin(a), a.size());
    CHECK(a == list<T>{1, 1, 2});
}

TEST_CASE("[shift] testing shift_right_by_one_n 4 elements bidirectional") {
    using T = int;
    list<T> a = {1, 2, 3, 4};
    shift_right_by_one_n(begin(a), a.size());
    CHECK(a == list<T>{1, 1, 2, 3});
}

TEST_CASE("[shift] testing shift_right_by_one_n 5 elements bidirectional") {
    using T = int;
    list<T> a = {1, 2, 3, 4, 5};
    shift_right_by_one_n(begin(a), a.size());
    CHECK(a == list<T>{1, 1, 2, 3, 4});
}

TEST_CASE("[shift] testing shift_right_by_one_n 6 elements bidirectional") {
    using T = int;
    list<T> a = {1, 2, 3, 4, 5, 6};
    shift_right_by_one_n(begin(a), a.size());
    CHECK(a == list<T>{1, 1, 2, 3, 4, 5});
}

TEST_CASE("[shift] testing shift_right_by_one_n 0 elements forward") {
    using T = int;
    forward_list<T> a;
    auto n = distance(begin(a), end(a));
    shift_right_by_one_n(begin(a), n);
    CHECK(a == forward_list<T>());
}

TEST_CASE("[shift] testing shift_right_by_one_n 1 elements forward") {
    using T = int;
    forward_list<T> a = {1};
    auto n = distance(begin(a), end(a));
    shift_right_by_one_n(begin(a), n);
    CHECK(a == forward_list<T>{1});
}

TEST_CASE("[shift] testing shift_right_by_one_n 2 elements forward") {
    using T = int;
    forward_list<T> a = {1, 2};
    auto n = distance(begin(a), end(a));
    shift_right_by_one_n(begin(a), n);
    CHECK(a == forward_list<T>{1, 1});
}

TEST_CASE("[shift] testing shift_right_by_one_n 3 elements forward") {
    using T = int;
    forward_list<T> a = {1, 2, 3};
    auto n = distance(begin(a), end(a));
    shift_right_by_one_n(begin(a), n);
    CHECK(a == forward_list<T>{1, 1, 2});
}

TEST_CASE("[shift] testing shift_right_by_one_n 4 elements forward") {
    using T = int;
    forward_list<T> a = {1, 2, 3, 4};
    auto n = distance(begin(a), end(a));
    shift_right_by_one_n(begin(a), n);
    CHECK(a == forward_list<T>{1, 1, 2, 3});
}

TEST_CASE("[shift] testing shift_right_by_one_n 5 elements forward") {
    using T = int;
    forward_list<T> a = {1, 2, 3, 4, 5};
    auto n = distance(begin(a), end(a));
    shift_right_by_one_n(begin(a), n);
    CHECK(a == forward_list<T>{1, 1, 2, 3, 4});
}

TEST_CASE("[shift] testing shift_right_by_one_n 6 elements forward") {
    using T = int;
    forward_list<T> a = {1, 2, 3, 4, 5, 6};
    auto n = distance(begin(a), end(a));
    shift_right_by_one_n(begin(a), n);
    CHECK(a == forward_list<T>{1, 1, 2, 3, 4, 5});
}

TEST_CASE("[shift] testing shift_right_by_one_n instrumented random access") {
    using T = instrumented<int>;
    vector<T> a = {1, 2, 3, 4, 5, 6};

    instrumented<int>::initialize(0);
    shift_right_by_one_n(begin(a), a.size());

    double* count_p = instrumented<int>::counts;
    CHECK(count_p[instrumented_base::copy_ctor] + 
          count_p[instrumented_base::copy_assignment] + 
          count_p[instrumented_base::move_ctor] + 
          count_p[instrumented_base::move_assignment] == 2 * a.size() - 1);
    CHECK(count_p[instrumented_base::destructor] == 2);
}

TEST_CASE("[shift] testing shift_right_by_one_n instrumented bidirectional") {
    using T = instrumented<int>;
    list<T> a = {1, 2, 3, 4, 5, 6};

    instrumented<int>::initialize(0);
    shift_right_by_one_n(begin(a), a.size());

    double* count_p = instrumented<int>::counts;
    CHECK(count_p[instrumented_base::copy_ctor] + 
          count_p[instrumented_base::copy_assignment] + 
          count_p[instrumented_base::move_ctor] + 
          count_p[instrumented_base::move_assignment] == 2 * a.size() - 1);
    CHECK(count_p[instrumented_base::destructor] == 2);
}

TEST_CASE("[shift] testing shift_right_by_one_n instrumented forward") {
    using T = instrumented<int>;
    forward_list<T> a = {1, 2, 3, 4, 5, 6};
    auto n = distance(begin(a), end(a));

    instrumented<int>::initialize(0);
    shift_right_by_one_n(begin(a), n);

    double* count_p = instrumented<int>::counts;
    CHECK(count_p[instrumented_base::copy_ctor] + 
          count_p[instrumented_base::copy_assignment] + 
          count_p[instrumented_base::move_ctor] + 
          count_p[instrumented_base::move_assignment] == 2 * n - 1);
    CHECK(count_p[instrumented_base::destructor] == 2);
}


#endif /*DOCTEST_LIBRARY_INCLUDED*/
