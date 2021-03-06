//! \file tao/algorithm/shift.hpp
// Tao.Algorithm
//
// Copyright (c) 2016-2021 Fernando Pelliccioni.
//
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TAO_ALGORITHM_SHIFT_HPP_
#define TAO_ALGORITHM_SHIFT_HPP_

#include <algorithm>
#include <iterator>
#include <utility>

// #include <iostream>


#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/copy.hpp>
#include <tao/algorithm/iterator.hpp>
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
//          Exact:     2 * n - 1 assigments (move or copy)
//      Space:
//          O(1)
template <ForwardIterator I>
    requires(Mutable<I>)
void shift_right_by_one(I f, I l, std::forward_iterator_tag) {
    //precondition: mutable_bounded_range(f, l)
    if (f == l) return;

    ValueType<I> a = std::move(*f++);
    ValueType<I> b;
    while (f != l) {
        shift_three(b, *f++, a);
        if (f == l) return;
        shift_three(a, *f++, b);
    }
}

//Complexity:
//      Runtime:
//          Amortized: O(n)
//          Exact:     n - 1 assigments (move or copy)
//      Space:
//          O(1)
template <BidirectionalIterator I>
    requires(Mutable<I>)
void shift_right_by_one(I f, I l, std::bidirectional_iterator_tag) {
    //precondition: mutable_bounded_range(f, l)
    if (f == l) return;
    tao::algorithm::move_backward(f, std::prev(l, 1), l);
}

//Complexity:
//      Runtime:
//          Amortized: O(n)
//          Exact:
//              for ForwardIterator:       2 * n - 1 assigments (move or copy)
//              for BidirectionalIterator: n - 1 assigments (move or copy)
//      Space:
//          O(1)
template <ForwardIterator I>
    requires(Mutable<I>)
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
template <ForwardIterator I>
    requires(Mutable<I>)
void shift_right_by_one_n(I f, DistanceType<I> n, std::forward_iterator_tag) {
    //precondition: mutable_counted_range(f, n)
    using N = DistanceType<I>;

    if (zero(n)) return;

    ValueType<I> a = std::move(*f);
    // ++f; --n;
    step_n(f, n);
    ValueType<I> b;
    while ( ! zero(n)) {
        // shift_three(b, *f++, a); --n;
        shift_three(b, *f, a);
        step_n(f, n);


        if (zero(n)) return;

        // shift_three(a, *f++, b); --n;
        shift_three(a, *f, b);
        step_n(f, n);
    }
}

//Complexity:
//      Runtime:
//          Amortized: O(n)
//          Exact:     n - 1 assigments (move or copy)
//      Space:
//          O(1)
template <BidirectionalIterator I>
    requires(Mutable<I>)
void shift_right_by_one_n(I f, DistanceType<I> n, std::bidirectional_iterator_tag) {
    //precondition: mutable_counted_range(f, n)
    using N = DistanceType<I>;
    if (n <= N(1)) return;

    I butlast = std::next(f, n - 1);   //very slow for bidirectional iterators, ok for random access
    I l = butlast;
    ++l;

    tao::algorithm::move_backward_n(butlast, n - 1, l);
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
    requires(Mutable<I>)
inline
void shift_right_by_one_n(I f, DistanceType<I> n) {
    return shift_right_by_one_n(f, n, IteratorCategory<I>{});
}







// -----------------------------------------------------------------
// shift_left_by_one
// -----------------------------------------------------------------

//Complexity:
//      Runtime:
//          Amortized: O(n)
//          Exact:     n - 1 assigments (move or copy)
//      Space:
//          O(1)
template <ForwardIterator I>
    requires(Mutable<I>)
I shift_left_by_one(I f, I l) {
    //precondition: mutable_bounded_range(f, l)
    if (f == l) return f;

    I next = f;
    ++next;

    while (next != l) {
        //invariant: distance(f, next) == 1
        *f = std::move(*next);
        ++f;
        ++next;
    }

    return f;
}


// -----------------------------------------------------------------
// shift_left_by_one_n
// -----------------------------------------------------------------

//Complexity:
//      Runtime:
//          Amortized: O(n)
//          Exact:     n - 1 assigments (move or copy)
//      Space:
//          O(1)
template <ForwardIterator I>
    requires(Mutable<I>)
I shift_left_by_one_n(I f, DistanceType<I> n) {
    //precondition:  mutable_counted_range(f, n)
    //postcondition: equal_n(old_f + 1, old_n - 1, new_f)
    using N = DistanceType<I>;

    if (zero(n)) return f;

    I next = f;
    ++next;
    --n;

    while ( ! zero(n)) {
        //invariant: distance(f, next) == 1
        *f = std::move(*next);
        ++f;
        ++next;
        --n;
    }

    return f;
}



// -----------------------------------------------------------------
// shift_right_while
// -----------------------------------------------------------------

//TODO(fernando): refactor
// template <ForwardIterator I, UnaryPredicate P>  //WeakStrictOrdering??
//     requires(Mutable<I>)
// I shift_right_while(I f, I l, P p, std::forward_iterator_tag) {
//     // precondition: mutable_bounded_range(f, l + 1)
//     while (f != l && p(*predecessor(l))) {
//         *l = std::move(*predecessor(l));
//         --l;
//     }
//     return l;
// }

template <ForwardIterator I, UnaryPredicate P>
    requires(Mutable<I>)
I shift_right_while(I f, I l, P p, std::forward_iterator_tag) {
    // precondition: mutable_bounded_range(f, l + 1)
    // if (f == l) return f;
    while (f != l && ! p(*predecessor(l))) {
        ++f;
    }

    return shift_right_by_one(f, l);
}

template <BidirectionalIterator I, UnaryPredicate P>
    requires(Mutable<I>)
I shift_right_while(I f, I l, P p, std::bidirectional_iterator_tag) {
    // precondition: mutable_bounded_range(f, l + 1)
    if (f == l) return f;
    --l;
    while (f != l && p(*predecessor(l))) {
        *l = std::move(*predecessor(l));
        --l;
    }
    return l;
}

template <ForwardIterator I, UnaryPredicate P>
    requires(Mutable<I>)
inline
I shift_right_while(I f, I l, P p) {
    return shift_right_while(f, l, p, IteratorCategory<I>{});
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
template <ForwardIterator I>
I shift_right(I f, I l, DistanceType<I> n, std::forward_iterator_tag) {
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
template <BidirectionalIterator I>
I shift_right(I f, I l, DistanceType<I> n, std::bidirectional_iterator_tag) {
    //precondition: n >= 0 &&
    //              std::distance(f, l) >= n (so [f, n) is a valid range)
    I butlast = std::prev(l, n);
    return tao::algorithm::move_backward(f, butlast, l);
}

//Complexity:
//      Runtime:
//          Amortized: O(n)
//          Exact:
//              for ForwardIterator:       (n * distance(f, l) - (n * (n-1)) / 2) swaps
//              for BidirectionalIterator: (distance(f, l) - n) move-assigments or copy-assigments (depending of the ValueType<I> object)
//      Space:
//          O(1)
template <ForwardIterator I>
inline
I shift_right(I f, I l, DistanceType<I> n) {
    return shift_right(f, l, n, IteratorCategory<I>{});
}


//TODO: shift_left

// //Complexity:
// //      Runtime:
// //          Amortized: O(n)
// //          Exact:     (n * distance(f, l) - (n * (n-1)) / 2) swaps
// //      Space:
// //          O(1)
// template <ForwardIterator I>
// I shift_left(I f, I l, DistanceType<I> n, std::forward_iterator_tag) {
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
// template <BidirectionalIterator I>
// I shift_left(I f, I l, DistanceType<I> n, std::bidirectional_iterator_tag) {
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
// template <ForwardIterator I>
// inline
// I shift_left(I f, I l, DistanceType<I> n) {
//     return shift_left(f, l, n, IteratorCategory<I>{});
// }

template <ForwardIterator I>
void rotate_right_by_one_ALEX(I f, I l) { //, std::forward_iterator_tag) {
    using std::swap;
    if (f == l) return;
    I current = f;
    while (++current != l) swap(*f, *current);
}


}} /*tao::algorithm*/

#endif /*TAO_ALGORITHM_SHIFT_HPP_*/


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


// ---------------------------------------------------------------------------------------------------
// TEST_CASE("[shift] testing shift_right_by_one 6 elements random access compare with std::rotate") {
//     using T = int;
//     vector<T> a = {1, 2, 3, 4, 5, 6};
//     std::rotate(begin(a), end(a) - 1, end(a));
//     CHECK(a == vector<T>{6, 1, 2, 3, 4, 5});
// }

// TEST_CASE("[shift] testing shift_right_by_one instrumented random access compare with std::rotate") {
//     using T = instrumented<int>;
//     vector<T> a = {1, 2, 3, 4, 5, 6};

//     instrumented<int>::initialize(0);
//     std::rotate(begin(a), std::prev(end(a), 1), end(a));

//     double* count_p = instrumented<int>::counts;
//     CHECK(count_p[instrumented_base::copy_ctor] +
//           count_p[instrumented_base::copy_assignment] +
//           count_p[instrumented_base::move_ctor] +
//           count_p[instrumented_base::move_assignment] == a.size() - 1);
//     CHECK(count_p[instrumented_base::destructor] == 0);
// }

// TEST_CASE("[shift] testing shift_right_by_one instrumented bidirectional compare with std::rotate") {
//     using T = instrumented<int>;
//     list<T> a = {1, 2, 3, 4, 5, 6};

//     instrumented<int>::initialize(0);
//     std::rotate(begin(a), std::prev(end(a), 1), end(a));

//     double* count_p = instrumented<int>::counts;
//     CHECK(count_p[instrumented_base::copy_ctor] +
//           count_p[instrumented_base::copy_assignment] +
//           count_p[instrumented_base::move_ctor] +
//           count_p[instrumented_base::move_assignment] == a.size() - 1);
//     CHECK(count_p[instrumented_base::destructor] == 0);
// }

// TEST_CASE("[shift] testing shift_right_by_one instrumented forward compare with std::rotate") {
//     using T = instrumented<int>;
//     forward_list<T> a = {1, 2, 3, 4, 5, 6};
//     auto n = distance(begin(a), end(a));

//     instrumented<int>::initialize(0);
//     std::rotate(begin(a), std::next(begin(a), n - 1), end(a));

//     double* count_p = instrumented<int>::counts;
//     CHECK(count_p[instrumented_base::copy_ctor] +
//           count_p[instrumented_base::copy_assignment] +
//           count_p[instrumented_base::move_ctor] +
//           count_p[instrumented_base::move_assignment] == 2 * n - 1);
//     CHECK(count_p[instrumented_base::destructor] == 0);
// }
// ---------------------------------------------------------------------------------------------------


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
          count_p[instrumented_base::move_assignment] == a.size() - 1);
    CHECK(count_p[instrumented_base::destructor] == 0);
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
          count_p[instrumented_base::move_assignment] == a.size() - 1);
    CHECK(count_p[instrumented_base::destructor] == 0);
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

TEST_CASE("[shift] testing shift_left_by_one 0 elements random access") {
    using T = int;
    vector<T> a;
    auto ret = shift_left_by_one(begin(a), end(a));
    CHECK(a   == vector<T>());
    CHECK(ret == end(a));
}

TEST_CASE("[shift] testing shift_left_by_one 1 elements random access") {
    using T = int;
    vector<T> a = {1};
    auto ret = shift_left_by_one(begin(a), end(a));
    CHECK(a == vector<T>{1});
    CHECK(ret == std::next(begin(a), a.size() - 1));

}

TEST_CASE("[shift] testing shift_left_by_one 2 elements random access") {
    using T = int;
    vector<T> a = {1, 2};
    auto ret = shift_left_by_one(begin(a), end(a));
    CHECK(a == vector<T>{2, 2});
    CHECK(ret == std::next(begin(a), a.size() - 1));
}

TEST_CASE("[shift] testing shift_left_by_one 3 elements random access") {
    using T = int;
    vector<T> a = {1, 2, 3};
    auto ret = shift_left_by_one(begin(a), end(a));
    CHECK(a == vector<T>{2, 3, 3});
    CHECK(ret == std::next(begin(a), a.size() - 1));
}

TEST_CASE("[shift] testing shift_left_by_one 4 elements random access") {
    using T = int;
    vector<T> a = {1, 2, 3, 4};
    auto ret = shift_left_by_one(begin(a), end(a));
    CHECK(a == vector<T>{2, 3, 4, 4});
    CHECK(ret == std::next(begin(a), a.size() - 1));
}

TEST_CASE("[shift] testing shift_left_by_one 5 elements random access") {
    using T = int;
    vector<T> a = {1, 2, 3, 4, 5};
    auto ret = shift_left_by_one(begin(a), end(a));
    CHECK(a == vector<T>{2, 3, 4, 5, 5});
    CHECK(ret == std::next(begin(a), a.size() - 1));
}

TEST_CASE("[shift] testing shift_left_by_one 6 elements random access") {
    using T = int;
    vector<T> a = {1, 2, 3, 4, 5, 6};
    auto ret = shift_left_by_one(begin(a), end(a));
    CHECK(a == vector<T>{2, 3, 4, 5, 6, 6});
    CHECK(ret == std::next(begin(a), a.size() - 1));
}

TEST_CASE("[shift] testing shift_left_by_one 0 elements bidirectional") {
    using T = int;
    list<T> a;
    auto ret = shift_left_by_one(begin(a), end(a));
    CHECK(a == list<T>());
    CHECK(ret == end(a));
}

TEST_CASE("[shift] testing shift_left_by_one 1 elements bidirectional") {
    using T = int;
    list<T> a = {1};
    auto ret = shift_left_by_one(begin(a), end(a));
    CHECK(a == list<T>{1});
    CHECK(ret == std::next(begin(a), a.size() - 1));
}

TEST_CASE("[shift] testing shift_left_by_one 2 elements bidirectional") {
    using T = int;
    list<T> a = {1, 2};
    auto ret = shift_left_by_one(begin(a), end(a));
    CHECK(a == list<T>{2, 2});
    CHECK(ret == std::next(begin(a), a.size() - 1));
}

TEST_CASE("[shift] testing shift_left_by_one 3 elements bidirectional") {
    using T = int;
    list<T> a = {1, 2, 3};
    auto ret = shift_left_by_one(begin(a), end(a));
    CHECK(a == list<T>{2, 3, 3});
    CHECK(ret == std::next(begin(a), a.size() - 1));
}

TEST_CASE("[shift] testing shift_left_by_one 4 elements bidirectional") {
    using T = int;
    list<T> a = {1, 2, 3, 4};
    auto ret = shift_left_by_one(begin(a), end(a));
    CHECK(a == list<T>{2, 3, 4, 4});
    CHECK(ret == std::next(begin(a), a.size() - 1));
}

TEST_CASE("[shift] testing shift_left_by_one 5 elements bidirectional") {
    using T = int;
    list<T> a = {1, 2, 3, 4, 5};
    auto ret = shift_left_by_one(begin(a), end(a));
    CHECK(a == list<T>{2, 3, 4, 5, 5});
    CHECK(ret == std::next(begin(a), a.size() - 1));
}

TEST_CASE("[shift] testing shift_left_by_one 6 elements bidirectional") {
    using T = int;
    list<T> a = {1, 2, 3, 4, 5, 6};
    auto ret = shift_left_by_one(begin(a), end(a));
    CHECK(a == list<T>{2, 3, 4, 5, 6, 6});
    CHECK(ret == std::next(begin(a), a.size() - 1));
}

TEST_CASE("[shift] testing shift_left_by_one 0 elements forward") {
    using T = int;
    forward_list<T> a;
    auto n = distance(begin(a), end(a));
    auto ret = shift_left_by_one(begin(a), end(a));
    CHECK(a == forward_list<T>());
    CHECK(ret == end(a));
}

TEST_CASE("[shift] testing shift_left_by_one 1 elements forward") {
    using T = int;
    forward_list<T> a = {1};
    auto n = distance(begin(a), end(a));
    auto ret = shift_left_by_one(begin(a), end(a));
    CHECK(a == forward_list<T>{1});
    CHECK(ret == std::next(begin(a), n - 1));
}

TEST_CASE("[shift] testing shift_left_by_one 2 elements forward") {
    using T = int;
    forward_list<T> a = {1, 2};
    auto n = distance(begin(a), end(a));
    auto ret = shift_left_by_one(begin(a), end(a));
    CHECK(a == forward_list<T>{2, 2});
    CHECK(ret == std::next(begin(a), n - 1));
}

TEST_CASE("[shift] testing shift_left_by_one 3 elements forward") {
    using T = int;
    forward_list<T> a = {1, 2, 3};
    auto n = distance(begin(a), end(a));
    auto ret = shift_left_by_one(begin(a), end(a));
    CHECK(a == forward_list<T>{2, 3, 3});
    CHECK(ret == std::next(begin(a), n - 1));
}

TEST_CASE("[shift] testing shift_left_by_one 4 elements forward") {
    using T = int;
    forward_list<T> a = {1, 2, 3, 4};
    auto n = distance(begin(a), end(a));
    auto ret = shift_left_by_one(begin(a), end(a));
    CHECK(a == forward_list<T>{2, 3, 4, 4});
    CHECK(ret == std::next(begin(a), n - 1));
}

TEST_CASE("[shift] testing shift_left_by_one 5 elements forward") {
    using T = int;
    forward_list<T> a = {1, 2, 3, 4, 5};
    auto n = distance(begin(a), end(a));
    auto ret = shift_left_by_one(begin(a), end(a));
    CHECK(a == forward_list<T>{2, 3, 4, 5, 5});
    CHECK(ret == std::next(begin(a), n - 1));
}

TEST_CASE("[shift] testing shift_left_by_one 6 elements forward") {
    using T = int;
    forward_list<T> a = {1, 2, 3, 4, 5, 6};
    auto n = distance(begin(a), end(a));
    auto ret = shift_left_by_one(begin(a), end(a));
    CHECK(a == forward_list<T>{2, 3, 4, 5, 6, 6});
    CHECK(ret == std::next(begin(a), n - 1));
}

TEST_CASE("[shift] testing shift_left_by_one instrumented random access") {
    using T = instrumented<int>;
    vector<T> a = {1, 2, 3, 4, 5, 6};

    instrumented<int>::initialize(0);
    auto ret = shift_left_by_one(begin(a), end(a));

    double* count_p = instrumented<int>::counts;
    CHECK(count_p[instrumented_base::copy_ctor] +
          count_p[instrumented_base::copy_assignment] +
          count_p[instrumented_base::move_ctor] +
          count_p[instrumented_base::move_assignment] == a.size() - 1);
    CHECK(count_p[instrumented_base::destructor] == 0);
}

TEST_CASE("[shift] testing shift_left_by_one instrumented bidirectional") {
    using T = instrumented<int>;
    list<T> a = {1, 2, 3, 4, 5, 6};

    instrumented<int>::initialize(0);
    auto ret = shift_left_by_one(begin(a), end(a));

    double* count_p = instrumented<int>::counts;
    CHECK(count_p[instrumented_base::copy_ctor] +
          count_p[instrumented_base::copy_assignment] +
          count_p[instrumented_base::move_ctor] +
          count_p[instrumented_base::move_assignment] == a.size() - 1);
    CHECK(count_p[instrumented_base::destructor] == 0);
}

TEST_CASE("[shift] testing shift_left_by_one instrumented forward") {
    using T = instrumented<int>;
    forward_list<T> a = {1, 2, 3, 4, 5, 6};
    auto n = distance(begin(a), end(a));

    instrumented<int>::initialize(0);
    auto ret = shift_left_by_one(begin(a), end(a));

    double* count_p = instrumented<int>::counts;
    CHECK(count_p[instrumented_base::copy_ctor] +
          count_p[instrumented_base::copy_assignment] +
          count_p[instrumented_base::move_ctor] +
          count_p[instrumented_base::move_assignment] == n - 1);
    CHECK(count_p[instrumented_base::destructor] == 0);
}

TEST_CASE("[shift] testing shift_left_by_one_n 0 elements random access") {
    using T = int;
    vector<T> a;
    auto ret = shift_left_by_one_n(begin(a), a.size());
    CHECK(a   == vector<T>());
    CHECK(ret == end(a));
}

TEST_CASE("[shift] testing shift_left_by_one_n 1 elements random access") {
    using T = int;
    vector<T> a = {1};
    auto ret = shift_left_by_one_n(begin(a), a.size());
    CHECK(a == vector<T>{1});
    CHECK(ret == std::next(begin(a), a.size() - 1));

}

TEST_CASE("[shift] testing shift_left_by_one_n 2 elements random access") {
    using T = int;
    vector<T> a = {1, 2};
    auto ret = shift_left_by_one_n(begin(a), a.size());
    CHECK(a == vector<T>{2, 2});
    CHECK(ret == std::next(begin(a), a.size() - 1));
}

TEST_CASE("[shift] testing shift_left_by_one_n 3 elements random access") {
    using T = int;
    vector<T> a = {1, 2, 3};
    auto ret = shift_left_by_one_n(begin(a), a.size());
    CHECK(a == vector<T>{2, 3, 3});
    CHECK(ret == std::next(begin(a), a.size() - 1));
}

TEST_CASE("[shift] testing shift_left_by_one_n 4 elements random access") {
    using T = int;
    vector<T> a = {1, 2, 3, 4};
    auto ret = shift_left_by_one_n(begin(a), a.size());
    CHECK(a == vector<T>{2, 3, 4, 4});
    CHECK(ret == std::next(begin(a), a.size() - 1));
}

TEST_CASE("[shift] testing shift_left_by_one_n 5 elements random access") {
    using T = int;
    vector<T> a = {1, 2, 3, 4, 5};
    auto ret = shift_left_by_one_n(begin(a), a.size());
    CHECK(a == vector<T>{2, 3, 4, 5, 5});
    CHECK(ret == std::next(begin(a), a.size() - 1));
}

TEST_CASE("[shift] testing shift_left_by_one_n 6 elements random access") {
    using T = int;
    vector<T> a = {1, 2, 3, 4, 5, 6};
    auto ret = shift_left_by_one_n(begin(a), a.size());
    CHECK(a == vector<T>{2, 3, 4, 5, 6, 6});
    CHECK(ret == std::next(begin(a), a.size() - 1));
}

TEST_CASE("[shift] testing shift_left_by_one_n 0 elements bidirectional") {
    using T = int;
    list<T> a;
    auto ret = shift_left_by_one_n(begin(a), a.size());
    CHECK(a == list<T>());
    CHECK(ret == end(a));
}

TEST_CASE("[shift] testing shift_left_by_one_n 1 elements bidirectional") {
    using T = int;
    list<T> a = {1};
    auto ret = shift_left_by_one_n(begin(a), a.size());
    CHECK(a == list<T>{1});
    CHECK(ret == std::next(begin(a), a.size() - 1));
}

TEST_CASE("[shift] testing shift_left_by_one_n 2 elements bidirectional") {
    using T = int;
    list<T> a = {1, 2};
    auto ret = shift_left_by_one_n(begin(a), a.size());
    CHECK(a == list<T>{2, 2});
    CHECK(ret == std::next(begin(a), a.size() - 1));
}

TEST_CASE("[shift] testing shift_left_by_one_n 3 elements bidirectional") {
    using T = int;
    list<T> a = {1, 2, 3};
    auto ret = shift_left_by_one_n(begin(a), a.size());
    CHECK(a == list<T>{2, 3, 3});
    CHECK(ret == std::next(begin(a), a.size() - 1));
}

TEST_CASE("[shift] testing shift_left_by_one_n 4 elements bidirectional") {
    using T = int;
    list<T> a = {1, 2, 3, 4};
    auto ret = shift_left_by_one_n(begin(a), a.size());
    CHECK(a == list<T>{2, 3, 4, 4});
    CHECK(ret == std::next(begin(a), a.size() - 1));
}

TEST_CASE("[shift] testing shift_left_by_one_n 5 elements bidirectional") {
    using T = int;
    list<T> a = {1, 2, 3, 4, 5};
    auto ret = shift_left_by_one_n(begin(a), a.size());
    CHECK(a == list<T>{2, 3, 4, 5, 5});
    CHECK(ret == std::next(begin(a), a.size() - 1));
}

TEST_CASE("[shift] testing shift_left_by_one_n 6 elements bidirectional") {
    using T = int;
    list<T> a = {1, 2, 3, 4, 5, 6};
    auto ret = shift_left_by_one_n(begin(a), a.size());
    CHECK(a == list<T>{2, 3, 4, 5, 6, 6});
    CHECK(ret == std::next(begin(a), a.size() - 1));
}

TEST_CASE("[shift] testing shift_left_by_one_n 0 elements forward") {
    using T = int;
    forward_list<T> a;
    auto n = distance(begin(a), end(a));
    auto ret = shift_left_by_one_n(begin(a), n);
    CHECK(a == forward_list<T>());
    CHECK(ret == end(a));
}

TEST_CASE("[shift] testing shift_left_by_one_n 1 elements forward") {
    using T = int;
    forward_list<T> a = {1};
    auto n = distance(begin(a), end(a));
    auto ret = shift_left_by_one_n(begin(a), n);
    CHECK(a == forward_list<T>{1});
    CHECK(ret == std::next(begin(a), n - 1));
}

TEST_CASE("[shift] testing shift_left_by_one_n 2 elements forward") {
    using T = int;
    forward_list<T> a = {1, 2};
    auto n = distance(begin(a), end(a));
    auto ret = shift_left_by_one_n(begin(a), n);
    CHECK(a == forward_list<T>{2, 2});
    CHECK(ret == std::next(begin(a), n - 1));
}

TEST_CASE("[shift] testing shift_left_by_one_n 3 elements forward") {
    using T = int;
    forward_list<T> a = {1, 2, 3};
    auto n = distance(begin(a), end(a));
    auto ret = shift_left_by_one_n(begin(a), n);
    CHECK(a == forward_list<T>{2, 3, 3});
    CHECK(ret == std::next(begin(a), n - 1));
}

TEST_CASE("[shift] testing shift_left_by_one_n 4 elements forward") {
    using T = int;
    forward_list<T> a = {1, 2, 3, 4};
    auto n = distance(begin(a), end(a));
    auto ret = shift_left_by_one_n(begin(a), n);
    CHECK(a == forward_list<T>{2, 3, 4, 4});
    CHECK(ret == std::next(begin(a), n - 1));
}

TEST_CASE("[shift] testing shift_left_by_one_n 5 elements forward") {
    using T = int;
    forward_list<T> a = {1, 2, 3, 4, 5};
    auto n = distance(begin(a), end(a));
    auto ret = shift_left_by_one_n(begin(a), n);
    CHECK(a == forward_list<T>{2, 3, 4, 5, 5});
    CHECK(ret == std::next(begin(a), n - 1));
}

TEST_CASE("[shift] testing shift_left_by_one_n 6 elements forward") {
    using T = int;
    forward_list<T> a = {1, 2, 3, 4, 5, 6};
    auto n = distance(begin(a), end(a));
    auto ret = shift_left_by_one_n(begin(a), n);
    CHECK(a == forward_list<T>{2, 3, 4, 5, 6, 6});
    CHECK(ret == std::next(begin(a), n - 1));
}

TEST_CASE("[shift] testing shift_left_by_one_n instrumented random access") {
    using T = instrumented<int>;
    vector<T> a = {1, 2, 3, 4, 5, 6};

    instrumented<int>::initialize(0);
    auto ret = shift_left_by_one_n(begin(a), a.size());

    double* count_p = instrumented<int>::counts;
    CHECK(count_p[instrumented_base::copy_ctor] +
          count_p[instrumented_base::copy_assignment] +
          count_p[instrumented_base::move_ctor] +
          count_p[instrumented_base::move_assignment] == a.size() - 1);
    CHECK(count_p[instrumented_base::destructor] == 0);
}

TEST_CASE("[shift] testing shift_left_by_one_n instrumented bidirectional") {
    using T = instrumented<int>;
    list<T> a = {1, 2, 3, 4, 5, 6};

    instrumented<int>::initialize(0);
    auto ret = shift_left_by_one_n(begin(a), a.size());

    double* count_p = instrumented<int>::counts;
    CHECK(count_p[instrumented_base::copy_ctor] +
          count_p[instrumented_base::copy_assignment] +
          count_p[instrumented_base::move_ctor] +
          count_p[instrumented_base::move_assignment] == a.size() - 1);
    CHECK(count_p[instrumented_base::destructor] == 0);
}

TEST_CASE("[shift] testing shift_left_by_one_n instrumented forward") {
    using T = instrumented<int>;
    forward_list<T> a = {1, 2, 3, 4, 5, 6};
    auto n = distance(begin(a), end(a));

    instrumented<int>::initialize(0);
    auto ret = shift_left_by_one_n(begin(a), n);

    double* count_p = instrumented<int>::counts;
    CHECK(count_p[instrumented_base::copy_ctor] +
          count_p[instrumented_base::copy_assignment] +
          count_p[instrumented_base::move_ctor] +
          count_p[instrumented_base::move_assignment] == n - 1);
    CHECK(count_p[instrumented_base::destructor] == 0);
}


// ------------------------------------------------------------------------

// TEST_CASE("[shift] testing rotate_right_by_one_ALEX instrumented random access") {
//     using T = instrumented<int>;
//     vector<T> a = {1, 2, 3, 4, 5, 6};

//     instrumented<int>::initialize(0);
//     rotate_right_by_one_ALEX(begin(a), end(a));

//     double* count_p = instrumented<int>::counts;
//     CHECK(count_p[instrumented_base::copy_ctor] +
//           count_p[instrumented_base::copy_assignment] +
//           count_p[instrumented_base::move_ctor] +
//           count_p[instrumented_base::move_assignment] == a.size() - 1);
//     CHECK(count_p[instrumented_base::destructor] == 0);
// }

// TEST_CASE("[shift] testing rotate_right_by_one_ALEX instrumented bidirectional") {
//     using T = instrumented<int>;
//     list<T> a = {1, 2, 3, 4, 5, 6};

//     instrumented<int>::initialize(0);
//     rotate_right_by_one_ALEX(begin(a), end(a));

//     // for (auto&& x : a) {
//     //     cout << x << ", ";
//     // }
//     // cout << endl;


//     double* count_p = instrumented<int>::counts;
//     // for (size_t i = 0; i < instrumented_base::number_ops; ++i) {
//     //     std::cout << instrumented_base::counter_names[i] << ": "
//     //         << count_p[i]
//     //         << std::endl;
//     // }

//     // CHECK(1 == 0);

//     CHECK(count_p[instrumented_base::copy_ctor] +
//           count_p[instrumented_base::copy_assignment] +
//           count_p[instrumented_base::move_ctor] +
//           count_p[instrumented_base::move_assignment] == a.size() - 1);
//     CHECK(count_p[instrumented_base::destructor] == 0);
// }

TEST_CASE("[shift] testing rotate_right_by_one_ALEX instrumented forward") {
    using T = instrumented<int>;
    forward_list<T> a = {1, 2, 3, 4, 5, 6};
    auto n = distance(begin(a), end(a));

    instrumented<int>::initialize(0);
    rotate_right_by_one_ALEX(begin(a), end(a));

    double* count_p = instrumented<int>::counts;
    // for (size_t i = 0; i < instrumented_base::number_ops; ++i) {
    //     std::cout << instrumented_base::counter_names[i] << ": "
    //                 << count_p[i]
    //                 << std::endl;
    // }

    CHECK(count_p[instrumented_base::copy_ctor] +
          count_p[instrumented_base::copy_assignment] +
          count_p[instrumented_base::move_ctor] +
          count_p[instrumented_base::move_assignment] == 3 * (n - 1));
    CHECK(count_p[instrumented_base::destructor] == 5);
}

#endif /*DOCTEST_LIBRARY_INCLUDED*/
