//! \file tao/algorithm/reverse.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016-2019
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_ALGORITHM_REVERSE_HPP_
#define TAO_ALGORITHM_REVERSE_HPP_

//Position Based Rearrangements

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
// reverse_n
// -----------------------------------------------------------------

//Complexity: 
//      Runtime:
//          Amortized: O(n)
//          Exact:     
//      Space:
//          O(1)

template <BidirectionalIterator I>
std::pair<I, I> reverse_n(I f, I l, DistanceType<I> n) {
    //precondition: mutable_bounded_range(f, n)
    //           && distance(f, l) == n

    while (n > DistanceType<I>(1)) {
        --l;
        std::iter_swap(f, l);
        ++f;
        n -= 2;
    }
    return {f, l};
}

// -----------------------------------------------------------------
// reverse
// -----------------------------------------------------------------

//Complexity: 
//      Runtime:
//          Amortized: O(n)
//          Exact:     
//      Space:
//          O(1)
template <BidirectionalIterator I>
std::pair<I, I> reverse(I f, I l, std::bidirectional_iterator_tag) {
    //precondition: mutable_bounded_range(f, l)

    while (true) {
        if (f == l) return {f, l};
        --l;
        if (f == l) return {f, next(l)};
        std::iter_swap(f, l);
        ++f; 
    }   
}

template <RandomAccessIterator I>
inline
std::pair<I, I> reverse(I f, I l, std::random_access_iterator_tag) {
    //precondition: mutable_bounded_range(f, l)
    return reverse_n(f, l, std::distance(f, l));
}


// -----------------------------------------------------------------
// reverse_copy
// -----------------------------------------------------------------

template <BidirectionalIterator I, Iterator O>
    requires(Readable<I> && Writable<O>)
O reverse_copy(I f, I l, O out) {
    //precondition: readable_bounded_range(f, l)
    //           && writable_counted_range(out, distance(f, l))

    while (f != l) {
        --l;
        *out = *l;
        ++out;
    }
    return out;
}

template <BidirectionalIterator I, Iterator O>
    requires(Readable<I> && Writable<O>)
std::pair<I, O> reverse_copy_n(I l, DistanceType<I> n, O out) {
    //precondition: readable_counted_range(l - n, n)
    //           && writable_counted_range(out, n)

    while (n > DistanceType<I>(0)) {
        --l;
        *out = *l;
        ++out;
        --n;
    }
    return {l, out};
}
template <Iterator I, BidirectionalIterator B>
B copy_reverse(I f, I l, B out) {
    while (f != l) {
        --out;
        *out = *f;
        ++f; 
    }
    return out;
}

template <Iterator I, BidirectionalIterator B>
std::pair<I, B> copy_reverse_n(I f, DistanceType<I> n, B out) {
    while (n > DistanceType<I>(0)) {
        --out;
        *out = *f;
        ++f;
        --n;
    }
    return {f, out};
}


// // -----------------------------------------------------------------
// // reverse_0
// // -----------------------------------------------------------------

// //Complexity: 
// //      Runtime:
// //          Amortized: O(n)
// //          Exact:     
// //      Space:
// //          O(1)
// template <BidirectionalIterator I>
// void reverse_0(I f, I l, std::bidirectional_iterator_tag) {
//     //precondition: mutable_bounded_range(f, l)

//     while (true) {
//         if (f == l) return;
//         --l;
//         if (f == l) return;
//         std::iter_swap(f, l);
//         ++f;
//     }    
// }



}} /*tao::algorithm*/

#endif /* TAO_ALGORITHM_REVERSE_HPP_ */


#ifdef DOCTEST_LIBRARY_INCLUDED

// #include <iterator>
// #include <forward_list>
// #include <list>
// #include <vector>

// #include <tao/benchmark/instrumented.hpp>

// using namespace std;
// using namespace tao::algorithm;

// // for (auto&& x : a) {
// //     cout << x << endl;
// // }

// // double* count_p = instrumented<int>::counts;
// // for (size_t i = 0; i < instrumented_base::number_ops; ++i) {
// //     std::cout << instrumented_base::counter_names[i] << ": " 
// //                 << count_p[i] 
// //                 << std::endl;
// // }

// // TEST_CASE("[rotate] testing rotate_right_by_one_forward_unguarded") {
// //     //using namespace tao::algorithm;

// //    // using T = int;
// //     using T = instrumented<int>;

// //     vector<T> a = {1, 2, 3, 4, 5, 6};

// //     instrumented<int>::initialize(0);
// //     // rotate_right_by_one_forward_unguarded(begin(a) + 1, begin(a) + 4);
// //     rotate_right_by_one_forward_unguarded(begin(a), end(a));

// //     double* count_p = instrumented<int>::counts;
// //     CHECK(a == vector<T>{6, 1, 2, 3, 4, 5});
// //     CHECK(count_p[instrumented_base::copy_ctor] + count_p[instrumented_base::copy_assignment] + count_p[instrumented_base::move_ctor] + count_p[instrumented_base::move_assignment] == 3 * (a.size() - 1));
// //     CHECK(count_p[instrumented_base::destructor] == a.size() - 1);

// // }

// TEST_CASE("[rotate] testing rotate_right_by_one 0 elements random access") {
//     using T = int;
//     vector<T> a;
//     rotate_right_by_one(begin(a), end(a));
//     CHECK(a == vector<T>());
// }

// TEST_CASE("[rotate] testing rotate_right_by_one 1 elements random access") {
//     using T = int;
//     vector<T> a = {1};
//     rotate_right_by_one(begin(a), end(a));
//     CHECK(a == vector<T>{1});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one 2 elements random access") {
//     using T = int;
//     vector<T> a = {1, 2};
//     rotate_right_by_one(begin(a), end(a));
//     CHECK(a == vector<T>{2, 1});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one 3 elements random access") {
//     using T = int;
//     vector<T> a = {1, 2, 3};
//     rotate_right_by_one(begin(a), end(a));
//     CHECK(a == vector<T>{3, 1, 2});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one 4 elements random access") {
//     using T = int;
//     vector<T> a = {1, 2, 3, 4};
//     rotate_right_by_one(begin(a), end(a));
//     CHECK(a == vector<T>{4, 1, 2, 3});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one 5 elements random access") {
//     using T = int;
//     vector<T> a = {1, 2, 3, 4, 5};
//     rotate_right_by_one(begin(a), end(a));
//     CHECK(a == vector<T>{5, 1, 2, 3, 4});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one 6 elements random access") {
//     using T = int;
//     vector<T> a = {1, 2, 3, 4, 5, 6};
//     rotate_right_by_one(begin(a), end(a));
//     CHECK(a == vector<T>{6, 1, 2, 3, 4, 5});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one 0 elements bidirectional") {
//     using T = int;
//     list<T> a;
//     rotate_right_by_one(begin(a), end(a));
//     CHECK(a == list<T>());
// }

// TEST_CASE("[rotate] testing rotate_right_by_one 1 elements bidirectional") {
//     using T = int;
//     list<T> a = {1};
//     rotate_right_by_one(begin(a), end(a));
//     CHECK(a == list<T>{1});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one 2 elements bidirectional") {
//     using T = int;
//     list<T> a = {1, 2};
//     rotate_right_by_one(begin(a), end(a));
//     CHECK(a == list<T>{2, 1});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one 3 elements bidirectional") {
//     using T = int;
//     list<T> a = {1, 2, 3};
//     rotate_right_by_one(begin(a), end(a));
//     CHECK(a == list<T>{3, 1, 2});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one 4 elements bidirectional") {
//     using T = int;
//     list<T> a = {1, 2, 3, 4};
//     rotate_right_by_one(begin(a), end(a));
//     CHECK(a == list<T>{4, 1, 2, 3});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one 5 elements bidirectional") {
//     using T = int;
//     list<T> a = {1, 2, 3, 4, 5};
//     rotate_right_by_one(begin(a), end(a));
//     CHECK(a == list<T>{5, 1, 2, 3, 4});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one 6 elements bidirectional") {
//     using T = int;
//     list<T> a = {1, 2, 3, 4, 5, 6};
//     rotate_right_by_one(begin(a), end(a));
//     CHECK(a == list<T>{6, 1, 2, 3, 4, 5});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one 0 elements forward") {
//     using T = int;
//     forward_list<T> a;
//     rotate_right_by_one(begin(a), end(a));
//     CHECK(a == forward_list<T>());
// }

// TEST_CASE("[rotate] testing rotate_right_by_one 1 elements forward") {
//     using T = int;
//     forward_list<T> a = {1};
//     rotate_right_by_one(begin(a), end(a));
//     CHECK(a == forward_list<T>{1});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one 2 elements forward") {
//     using T = int;
//     forward_list<T> a = {1, 2};
//     rotate_right_by_one(begin(a), end(a));
//     CHECK(a == forward_list<T>{2, 1});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one 3 elements forward") {
//     using T = int;
//     forward_list<T> a = {1, 2, 3};
//     rotate_right_by_one(begin(a), end(a));
//     CHECK(a == forward_list<T>{3, 1, 2});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one 4 elements forward") {
//     using T = int;
//     forward_list<T> a = {1, 2, 3, 4};
//     rotate_right_by_one(begin(a), end(a));
//     CHECK(a == forward_list<T>{4, 1, 2, 3});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one 5 elements forward") {
//     using T = int;
//     forward_list<T> a = {1, 2, 3, 4, 5};
//     rotate_right_by_one(begin(a), end(a));
//     CHECK(a == forward_list<T>{5, 1, 2, 3, 4});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one 6 elements forward") {
//     using T = int;
//     forward_list<T> a = {1, 2, 3, 4, 5, 6};
//     rotate_right_by_one(begin(a), end(a));
//     CHECK(a == forward_list<T>{6, 1, 2, 3, 4, 5});
// }


// // ---------------------------------------------------------------------------------------------------
// // TEST_CASE("[rotate] testing rotate_right_by_one 6 elements random access compare with std::rotate") {
// //     using T = int;
// //     vector<T> a = {1, 2, 3, 4, 5, 6};
// //     std::rotate(begin(a), end(a) - 1, end(a));
// //     CHECK(a == vector<T>{6, 1, 2, 3, 4, 5});
// // }

// // TEST_CASE("[rotate] testing rotate_right_by_one instrumented random access compare with std::rotate") {
// //     using T = instrumented<int>;
// //     vector<T> a = {1, 2, 3, 4, 5, 6};

// //     instrumented<int>::initialize(0);
// //     std::rotate(begin(a), std::prev(end(a), 1), end(a));

// //     double* count_p = instrumented<int>::counts;
// //     CHECK(count_p[instrumented_base::copy_ctor] + 
// //           count_p[instrumented_base::copy_assignment] + 
// //           count_p[instrumented_base::move_ctor] + 
// //           count_p[instrumented_base::move_assignment] == a.size() - 1);
// //     CHECK(count_p[instrumented_base::destructor] == 0);
// // }

// // TEST_CASE("[rotate] testing rotate_right_by_one instrumented bidirectional compare with std::rotate") {
// //     using T = instrumented<int>;
// //     list<T> a = {1, 2, 3, 4, 5, 6};

// //     instrumented<int>::initialize(0);
// //     std::rotate(begin(a), std::prev(end(a), 1), end(a));

// //     double* count_p = instrumented<int>::counts;
// //     CHECK(count_p[instrumented_base::copy_ctor] + 
// //           count_p[instrumented_base::copy_assignment] + 
// //           count_p[instrumented_base::move_ctor] + 
// //           count_p[instrumented_base::move_assignment] == a.size() - 1);
// //     CHECK(count_p[instrumented_base::destructor] == 0);
// // }

// // TEST_CASE("[rotate] testing rotate_right_by_one instrumented forward compare with std::rotate") {
// //     using T = instrumented<int>;
// //     forward_list<T> a = {1, 2, 3, 4, 5, 6};
// //     auto n = distance(begin(a), end(a));

// //     instrumented<int>::initialize(0);
// //     std::rotate(begin(a), std::next(begin(a), n - 1), end(a));

// //     double* count_p = instrumented<int>::counts;
// //     CHECK(count_p[instrumented_base::copy_ctor] + 
// //           count_p[instrumented_base::copy_assignment] + 
// //           count_p[instrumented_base::move_ctor] + 
// //           count_p[instrumented_base::move_assignment] == 2 * n - 1);
// //     CHECK(count_p[instrumented_base::destructor] == 0);
// // }
// // ---------------------------------------------------------------------------------------------------


// TEST_CASE("[rotate] testing rotate_right_by_one instrumented random access") {
//     using T = instrumented<int>;
//     vector<T> a = {1, 2, 3, 4, 5, 6};

//     instrumented<int>::initialize(0);
//     rotate_right_by_one(begin(a), end(a));

//     double* count_p = instrumented<int>::counts;
//     CHECK(count_p[instrumented_base::copy_ctor] + 
//           count_p[instrumented_base::copy_assignment] + 
//           count_p[instrumented_base::move_ctor] + 
//           count_p[instrumented_base::move_assignment] == a.size() + 1);
//     CHECK(count_p[instrumented_base::destructor] == 1);
// }

// TEST_CASE("[rotate] testing rotate_right_by_one instrumented bidirectional") {
//     using T = instrumented<int>;
//     list<T> a = {1, 2, 3, 4, 5, 6};

//     instrumented<int>::initialize(0);
//     rotate_right_by_one(begin(a), end(a));

//     double* count_p = instrumented<int>::counts;
//     CHECK(count_p[instrumented_base::copy_ctor] + 
//           count_p[instrumented_base::copy_assignment] + 
//           count_p[instrumented_base::move_ctor] + 
//           count_p[instrumented_base::move_assignment] == a.size() + 1);
//     CHECK(count_p[instrumented_base::destructor] == 1);
// }

// TEST_CASE("[rotate] testing rotate_right_by_one instrumented forward") {
//     using T = instrumented<int>;
//     forward_list<T> a = {1, 2, 3, 4, 5, 6};
//     auto n = distance(begin(a), end(a));

//     instrumented<int>::initialize(0);
//     rotate_right_by_one(begin(a), end(a));

//     double* count_p = instrumented<int>::counts;
//     CHECK(count_p[instrumented_base::copy_ctor] + 
//           count_p[instrumented_base::copy_assignment] + 
//           count_p[instrumented_base::move_ctor] + 
//           count_p[instrumented_base::move_assignment] == 2 * n);
//     CHECK(count_p[instrumented_base::destructor] == 2);
// }

// TEST_CASE("[rotate] testing rotate_right_by_one_n 0 elements random access") {
//     using T = int;
//     vector<T> a;
//     rotate_right_by_one_n(begin(a), a.size());
//     CHECK(a == vector<T>());
// }

// TEST_CASE("[rotate] testing rotate_right_by_one_n 1 elements random access") {
//     using T = int;
//     vector<T> a = {1};
//     rotate_right_by_one_n(begin(a), a.size());
//     CHECK(a == vector<T>{1});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one_n 2 elements random access") {
//     using T = int;
//     vector<T> a = {1, 2};
//     rotate_right_by_one_n(begin(a), a.size());
//     CHECK(a == vector<T>{2, 1});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one_n 3 elements random access") {
//     using T = int;
//     vector<T> a = {1, 2, 3};
//     rotate_right_by_one_n(begin(a), a.size());
//     CHECK(a == vector<T>{3, 1, 2});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one_n 4 elements random access") {
//     using T = int;
//     vector<T> a = {1, 2, 3, 4};
//     rotate_right_by_one_n(begin(a), a.size());
//     CHECK(a == vector<T>{4, 1, 2, 3});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one_n 5 elements random access") {
//     using T = int;
//     vector<T> a = {1, 2, 3, 4, 5};
//     rotate_right_by_one_n(begin(a), a.size());
//     CHECK(a == vector<T>{5, 1, 2, 3, 4});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one_n 6 elements random access") {
//     using T = int;
//     vector<T> a = {1, 2, 3, 4, 5, 6};
//     rotate_right_by_one_n(begin(a), a.size());
//     CHECK(a == vector<T>{6, 1, 2, 3, 4, 5});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one_n 0 elements bidirectional") {
//     using T = int;
//     list<T> a;
//     rotate_right_by_one_n(begin(a), a.size());
//     CHECK(a == list<T>());
// }

// TEST_CASE("[rotate] testing rotate_right_by_one_n 1 elements bidirectional") {
//     using T = int;
//     list<T> a = {1};
//     rotate_right_by_one_n(begin(a), a.size());
//     CHECK(a == list<T>{1});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one_n 2 elements bidirectional") {
//     using T = int;
//     list<T> a = {1, 2};
//     rotate_right_by_one_n(begin(a), a.size());
//     CHECK(a == list<T>{2, 1});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one_n 3 elements bidirectional") {
//     using T = int;
//     list<T> a = {1, 2, 3};
//     rotate_right_by_one_n(begin(a), a.size());
//     CHECK(a == list<T>{3, 1, 2});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one_n 4 elements bidirectional") {
//     using T = int;
//     list<T> a = {1, 2, 3, 4};
//     rotate_right_by_one_n(begin(a), a.size());
//     CHECK(a == list<T>{4, 1, 2, 3});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one_n 5 elements bidirectional") {
//     using T = int;
//     list<T> a = {1, 2, 3, 4, 5};
//     rotate_right_by_one_n(begin(a), a.size());
//     CHECK(a == list<T>{5, 1, 2, 3, 4});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one_n 6 elements bidirectional") {
//     using T = int;
//     list<T> a = {1, 2, 3, 4, 5, 6};
//     rotate_right_by_one_n(begin(a), a.size());
//     CHECK(a == list<T>{6, 1, 2, 3, 4, 5});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one_n 0 elements forward") {
//     using T = int;
//     forward_list<T> a;
//     auto n = distance(begin(a), end(a));
//     rotate_right_by_one_n(begin(a), n);
//     CHECK(a == forward_list<T>());
// }

// TEST_CASE("[rotate] testing rotate_right_by_one_n 1 elements forward") {
//     using T = int;
//     forward_list<T> a = {1};
//     auto n = distance(begin(a), end(a));
//     rotate_right_by_one_n(begin(a), n);
//     CHECK(a == forward_list<T>{1});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one_n 2 elements forward") {
//     using T = int;
//     forward_list<T> a = {1, 2};
//     auto n = distance(begin(a), end(a));
//     rotate_right_by_one_n(begin(a), n);
//     CHECK(a == forward_list<T>{2, 1});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one_n 3 elements forward") {
//     using T = int;
//     forward_list<T> a = {1, 2, 3};
//     auto n = distance(begin(a), end(a));
//     rotate_right_by_one_n(begin(a), n);
//     CHECK(a == forward_list<T>{3, 1, 2});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one_n 4 elements forward") {
//     using T = int;
//     forward_list<T> a = {1, 2, 3, 4};
//     auto n = distance(begin(a), end(a));
//     rotate_right_by_one_n(begin(a), n);
//     CHECK(a == forward_list<T>{4, 1, 2, 3});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one_n 5 elements forward") {
//     using T = int;
//     forward_list<T> a = {1, 2, 3, 4, 5};
//     auto n = distance(begin(a), end(a));
//     rotate_right_by_one_n(begin(a), n);
//     CHECK(a == forward_list<T>{5, 1, 2, 3, 4});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one_n 6 elements forward") {
//     using T = int;
//     forward_list<T> a = {1, 2, 3, 4, 5, 6};
//     auto n = distance(begin(a), end(a));
//     rotate_right_by_one_n(begin(a), n);
//     CHECK(a == forward_list<T>{6, 1, 2, 3, 4, 5});
// }

// TEST_CASE("[rotate] testing rotate_right_by_one_n instrumented random access") {
//     using T = instrumented<int>;
//     vector<T> a = {1, 2, 3, 4, 5, 6};

//     instrumented<int>::initialize(0);
//     rotate_right_by_one_n(begin(a), a.size());

//     double* count_p = instrumented<int>::counts;
//     CHECK(count_p[instrumented_base::copy_ctor] + 
//           count_p[instrumented_base::copy_assignment] + 
//           count_p[instrumented_base::move_ctor] + 
//           count_p[instrumented_base::move_assignment] == a.size() + 1);
//     CHECK(count_p[instrumented_base::destructor] == 1);
// }

// TEST_CASE("[rotate] testing rotate_right_by_one_n instrumented bidirectional") {
//     using T = instrumented<int>;
//     list<T> a = {1, 2, 3, 4, 5, 6};

//     instrumented<int>::initialize(0);
//     rotate_right_by_one_n(begin(a), a.size());

//     double* count_p = instrumented<int>::counts;
//     CHECK(count_p[instrumented_base::copy_ctor] + 
//           count_p[instrumented_base::copy_assignment] + 
//           count_p[instrumented_base::move_ctor] + 
//           count_p[instrumented_base::move_assignment] == a.size() + 1);
//     CHECK(count_p[instrumented_base::destructor] == 1);
// }

// TEST_CASE("[rotate] testing rotate_right_by_one_n instrumented forward") {
//     using T = instrumented<int>;
//     forward_list<T> a = {1, 2, 3, 4, 5, 6};
//     auto n = distance(begin(a), end(a));

//     instrumented<int>::initialize(0);
//     rotate_right_by_one_n(begin(a), n);

//     double* count_p = instrumented<int>::counts;
//     CHECK(count_p[instrumented_base::copy_ctor] + 
//           count_p[instrumented_base::copy_assignment] + 
//           count_p[instrumented_base::move_ctor] + 
//           count_p[instrumented_base::move_assignment] == 2 * n);
//     CHECK(count_p[instrumented_base::destructor] == 2);
// }

// TEST_CASE("[rotate] testing rotate_left_by_one 0 elements random access") {
//     using T = int;
//     vector<T> a;
//     auto ret = rotate_left_by_one(begin(a), end(a));
//     CHECK(a   == vector<T>());
//     CHECK(ret == end(a));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one 1 elements random access") {
//     using T = int;
//     vector<T> a = {1};
//     auto ret = rotate_left_by_one(begin(a), end(a));
//     CHECK(a == vector<T>{1});
//     CHECK(ret == std::next(begin(a), a.size() - 1));
    
// }

// TEST_CASE("[rotate] testing rotate_left_by_one 2 elements random access") {
//     using T = int;
//     vector<T> a = {1, 2};
//     auto ret = rotate_left_by_one(begin(a), end(a));
//     CHECK(a == vector<T>{2, 2});
//     CHECK(ret == std::next(begin(a), a.size() - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one 3 elements random access") {
//     using T = int;
//     vector<T> a = {1, 2, 3};
//     auto ret = rotate_left_by_one(begin(a), end(a));
//     CHECK(a == vector<T>{2, 3, 3});
//     CHECK(ret == std::next(begin(a), a.size() - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one 4 elements random access") {
//     using T = int;
//     vector<T> a = {1, 2, 3, 4};
//     auto ret = rotate_left_by_one(begin(a), end(a));
//     CHECK(a == vector<T>{2, 3, 4, 4});
//     CHECK(ret == std::next(begin(a), a.size() - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one 5 elements random access") {
//     using T = int;
//     vector<T> a = {1, 2, 3, 4, 5};
//     auto ret = rotate_left_by_one(begin(a), end(a));
//     CHECK(a == vector<T>{2, 3, 4, 5, 5});
//     CHECK(ret == std::next(begin(a), a.size() - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one 6 elements random access") {
//     using T = int;
//     vector<T> a = {1, 2, 3, 4, 5, 6};
//     auto ret = rotate_left_by_one(begin(a), end(a));
//     CHECK(a == vector<T>{2, 3, 4, 5, 6, 6});
//     CHECK(ret == std::next(begin(a), a.size() - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one 0 elements bidirectional") {
//     using T = int;
//     list<T> a;
//     auto ret = rotate_left_by_one(begin(a), end(a));
//     CHECK(a == list<T>());
//     CHECK(ret == end(a));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one 1 elements bidirectional") {
//     using T = int;
//     list<T> a = {1};
//     auto ret = rotate_left_by_one(begin(a), end(a));
//     CHECK(a == list<T>{1});
//     CHECK(ret == std::next(begin(a), a.size() - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one 2 elements bidirectional") {
//     using T = int;
//     list<T> a = {1, 2};
//     auto ret = rotate_left_by_one(begin(a), end(a));
//     CHECK(a == list<T>{2, 2});
//     CHECK(ret == std::next(begin(a), a.size() - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one 3 elements bidirectional") {
//     using T = int;
//     list<T> a = {1, 2, 3};
//     auto ret = rotate_left_by_one(begin(a), end(a));
//     CHECK(a == list<T>{2, 3, 3});
//     CHECK(ret == std::next(begin(a), a.size() - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one 4 elements bidirectional") {
//     using T = int;
//     list<T> a = {1, 2, 3, 4};
//     auto ret = rotate_left_by_one(begin(a), end(a));
//     CHECK(a == list<T>{2, 3, 4, 4});
//     CHECK(ret == std::next(begin(a), a.size() - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one 5 elements bidirectional") {
//     using T = int;
//     list<T> a = {1, 2, 3, 4, 5};
//     auto ret = rotate_left_by_one(begin(a), end(a));
//     CHECK(a == list<T>{2, 3, 4, 5, 5});
//     CHECK(ret == std::next(begin(a), a.size() - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one 6 elements bidirectional") {
//     using T = int;
//     list<T> a = {1, 2, 3, 4, 5, 6};
//     auto ret = rotate_left_by_one(begin(a), end(a));
//     CHECK(a == list<T>{2, 3, 4, 5, 6, 6});
//     CHECK(ret == std::next(begin(a), a.size() - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one 0 elements forward") {
//     using T = int;
//     forward_list<T> a;
//     auto n = distance(begin(a), end(a));
//     auto ret = rotate_left_by_one(begin(a), end(a));
//     CHECK(a == forward_list<T>());
//     CHECK(ret == end(a));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one 1 elements forward") {
//     using T = int;
//     forward_list<T> a = {1};
//     auto n = distance(begin(a), end(a));
//     auto ret = rotate_left_by_one(begin(a), end(a));
//     CHECK(a == forward_list<T>{1});
//     CHECK(ret == std::next(begin(a), n - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one 2 elements forward") {
//     using T = int;
//     forward_list<T> a = {1, 2};
//     auto n = distance(begin(a), end(a));
//     auto ret = rotate_left_by_one(begin(a), end(a));
//     CHECK(a == forward_list<T>{2, 2});
//     CHECK(ret == std::next(begin(a), n - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one 3 elements forward") {
//     using T = int;
//     forward_list<T> a = {1, 2, 3};
//     auto n = distance(begin(a), end(a));
//     auto ret = rotate_left_by_one(begin(a), end(a));
//     CHECK(a == forward_list<T>{2, 3, 3});
//     CHECK(ret == std::next(begin(a), n - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one 4 elements forward") {
//     using T = int;
//     forward_list<T> a = {1, 2, 3, 4};
//     auto n = distance(begin(a), end(a));
//     auto ret = rotate_left_by_one(begin(a), end(a));
//     CHECK(a == forward_list<T>{2, 3, 4, 4});
//     CHECK(ret == std::next(begin(a), n - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one 5 elements forward") {
//     using T = int;
//     forward_list<T> a = {1, 2, 3, 4, 5};
//     auto n = distance(begin(a), end(a));
//     auto ret = rotate_left_by_one(begin(a), end(a));
//     CHECK(a == forward_list<T>{2, 3, 4, 5, 5});
//     CHECK(ret == std::next(begin(a), n - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one 6 elements forward") {
//     using T = int;
//     forward_list<T> a = {1, 2, 3, 4, 5, 6};
//     auto n = distance(begin(a), end(a));
//     auto ret = rotate_left_by_one(begin(a), end(a));
//     CHECK(a == forward_list<T>{2, 3, 4, 5, 6, 6});
//     CHECK(ret == std::next(begin(a), n - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one instrumented random access") {
//     using T = instrumented<int>;
//     vector<T> a = {1, 2, 3, 4, 5, 6};

//     instrumented<int>::initialize(0);
//     auto ret = rotate_left_by_one(begin(a), end(a));

//     double* count_p = instrumented<int>::counts;
//     CHECK(count_p[instrumented_base::copy_ctor] + 
//           count_p[instrumented_base::copy_assignment] + 
//           count_p[instrumented_base::move_ctor] + 
//           count_p[instrumented_base::move_assignment] == a.size() - 1);
//     CHECK(count_p[instrumented_base::destructor] == 0);
// }

// TEST_CASE("[rotate] testing rotate_left_by_one instrumented bidirectional") {
//     using T = instrumented<int>;
//     list<T> a = {1, 2, 3, 4, 5, 6};

//     instrumented<int>::initialize(0);
//     auto ret = rotate_left_by_one(begin(a), end(a));

//     double* count_p = instrumented<int>::counts;
//     CHECK(count_p[instrumented_base::copy_ctor] + 
//           count_p[instrumented_base::copy_assignment] + 
//           count_p[instrumented_base::move_ctor] + 
//           count_p[instrumented_base::move_assignment] == a.size() - 1);
//     CHECK(count_p[instrumented_base::destructor] == 0);
// }

// TEST_CASE("[rotate] testing rotate_left_by_one instrumented forward") {
//     using T = instrumented<int>;
//     forward_list<T> a = {1, 2, 3, 4, 5, 6};
//     auto n = distance(begin(a), end(a));

//     instrumented<int>::initialize(0);
//     auto ret = rotate_left_by_one(begin(a), end(a));

//     double* count_p = instrumented<int>::counts;
//     CHECK(count_p[instrumented_base::copy_ctor] + 
//           count_p[instrumented_base::copy_assignment] + 
//           count_p[instrumented_base::move_ctor] + 
//           count_p[instrumented_base::move_assignment] == n - 1);
//     CHECK(count_p[instrumented_base::destructor] == 0);
// }

// TEST_CASE("[rotate] testing rotate_left_by_one_n 0 elements random access") {
//     using T = int;
//     vector<T> a;
//     auto ret = rotate_left_by_one_n(begin(a), a.size());
//     CHECK(a   == vector<T>());
//     CHECK(ret == end(a));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one_n 1 elements random access") {
//     using T = int;
//     vector<T> a = {1};
//     auto ret = rotate_left_by_one_n(begin(a), a.size());
//     CHECK(a == vector<T>{1});
//     CHECK(ret == std::next(begin(a), a.size() - 1));
    
// }

// TEST_CASE("[rotate] testing rotate_left_by_one_n 2 elements random access") {
//     using T = int;
//     vector<T> a = {1, 2};
//     auto ret = rotate_left_by_one_n(begin(a), a.size());
//     CHECK(a == vector<T>{2, 2});
//     CHECK(ret == std::next(begin(a), a.size() - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one_n 3 elements random access") {
//     using T = int;
//     vector<T> a = {1, 2, 3};
//     auto ret = rotate_left_by_one_n(begin(a), a.size());
//     CHECK(a == vector<T>{2, 3, 3});
//     CHECK(ret == std::next(begin(a), a.size() - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one_n 4 elements random access") {
//     using T = int;
//     vector<T> a = {1, 2, 3, 4};
//     auto ret = rotate_left_by_one_n(begin(a), a.size());
//     CHECK(a == vector<T>{2, 3, 4, 4});
//     CHECK(ret == std::next(begin(a), a.size() - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one_n 5 elements random access") {
//     using T = int;
//     vector<T> a = {1, 2, 3, 4, 5};
//     auto ret = rotate_left_by_one_n(begin(a), a.size());
//     CHECK(a == vector<T>{2, 3, 4, 5, 5});
//     CHECK(ret == std::next(begin(a), a.size() - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one_n 6 elements random access") {
//     using T = int;
//     vector<T> a = {1, 2, 3, 4, 5, 6};
//     auto ret = rotate_left_by_one_n(begin(a), a.size());
//     CHECK(a == vector<T>{2, 3, 4, 5, 6, 6});
//     CHECK(ret == std::next(begin(a), a.size() - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one_n 0 elements bidirectional") {
//     using T = int;
//     list<T> a;
//     auto ret = rotate_left_by_one_n(begin(a), a.size());
//     CHECK(a == list<T>());
//     CHECK(ret == end(a));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one_n 1 elements bidirectional") {
//     using T = int;
//     list<T> a = {1};
//     auto ret = rotate_left_by_one_n(begin(a), a.size());
//     CHECK(a == list<T>{1});
//     CHECK(ret == std::next(begin(a), a.size() - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one_n 2 elements bidirectional") {
//     using T = int;
//     list<T> a = {1, 2};
//     auto ret = rotate_left_by_one_n(begin(a), a.size());
//     CHECK(a == list<T>{2, 2});
//     CHECK(ret == std::next(begin(a), a.size() - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one_n 3 elements bidirectional") {
//     using T = int;
//     list<T> a = {1, 2, 3};
//     auto ret = rotate_left_by_one_n(begin(a), a.size());
//     CHECK(a == list<T>{2, 3, 3});
//     CHECK(ret == std::next(begin(a), a.size() - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one_n 4 elements bidirectional") {
//     using T = int;
//     list<T> a = {1, 2, 3, 4};
//     auto ret = rotate_left_by_one_n(begin(a), a.size());
//     CHECK(a == list<T>{2, 3, 4, 4});
//     CHECK(ret == std::next(begin(a), a.size() - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one_n 5 elements bidirectional") {
//     using T = int;
//     list<T> a = {1, 2, 3, 4, 5};
//     auto ret = rotate_left_by_one_n(begin(a), a.size());
//     CHECK(a == list<T>{2, 3, 4, 5, 5});
//     CHECK(ret == std::next(begin(a), a.size() - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one_n 6 elements bidirectional") {
//     using T = int;
//     list<T> a = {1, 2, 3, 4, 5, 6};
//     auto ret = rotate_left_by_one_n(begin(a), a.size());
//     CHECK(a == list<T>{2, 3, 4, 5, 6, 6});
//     CHECK(ret == std::next(begin(a), a.size() - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one_n 0 elements forward") {
//     using T = int;
//     forward_list<T> a;
//     auto n = distance(begin(a), end(a));
//     auto ret = rotate_left_by_one_n(begin(a), n);
//     CHECK(a == forward_list<T>());
//     CHECK(ret == end(a));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one_n 1 elements forward") {
//     using T = int;
//     forward_list<T> a = {1};
//     auto n = distance(begin(a), end(a));
//     auto ret = rotate_left_by_one_n(begin(a), n);
//     CHECK(a == forward_list<T>{1});
//     CHECK(ret == std::next(begin(a), n - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one_n 2 elements forward") {
//     using T = int;
//     forward_list<T> a = {1, 2};
//     auto n = distance(begin(a), end(a));
//     auto ret = rotate_left_by_one_n(begin(a), n);
//     CHECK(a == forward_list<T>{2, 2});
//     CHECK(ret == std::next(begin(a), n - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one_n 3 elements forward") {
//     using T = int;
//     forward_list<T> a = {1, 2, 3};
//     auto n = distance(begin(a), end(a));
//     auto ret = rotate_left_by_one_n(begin(a), n);
//     CHECK(a == forward_list<T>{2, 3, 3});
//     CHECK(ret == std::next(begin(a), n - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one_n 4 elements forward") {
//     using T = int;
//     forward_list<T> a = {1, 2, 3, 4};
//     auto n = distance(begin(a), end(a));
//     auto ret = rotate_left_by_one_n(begin(a), n);
//     CHECK(a == forward_list<T>{2, 3, 4, 4});
//     CHECK(ret == std::next(begin(a), n - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one_n 5 elements forward") {
//     using T = int;
//     forward_list<T> a = {1, 2, 3, 4, 5};
//     auto n = distance(begin(a), end(a));
//     auto ret = rotate_left_by_one_n(begin(a), n);
//     CHECK(a == forward_list<T>{2, 3, 4, 5, 5});
//     CHECK(ret == std::next(begin(a), n - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one_n 6 elements forward") {
//     using T = int;
//     forward_list<T> a = {1, 2, 3, 4, 5, 6};
//     auto n = distance(begin(a), end(a));
//     auto ret = rotate_left_by_one_n(begin(a), n);
//     CHECK(a == forward_list<T>{2, 3, 4, 5, 6, 6});
//     CHECK(ret == std::next(begin(a), n - 1));
// }

// TEST_CASE("[rotate] testing rotate_left_by_one_n instrumented random access") {
//     using T = instrumented<int>;
//     vector<T> a = {1, 2, 3, 4, 5, 6};

//     instrumented<int>::initialize(0);
//     auto ret = rotate_left_by_one_n(begin(a), a.size());

//     double* count_p = instrumented<int>::counts;
//     CHECK(count_p[instrumented_base::copy_ctor] + 
//           count_p[instrumented_base::copy_assignment] + 
//           count_p[instrumented_base::move_ctor] + 
//           count_p[instrumented_base::move_assignment] == a.size() - 1);
//     CHECK(count_p[instrumented_base::destructor] == 0);
// }

// TEST_CASE("[rotate] testing rotate_left_by_one_n instrumented bidirectional") {
//     using T = instrumented<int>;
//     list<T> a = {1, 2, 3, 4, 5, 6};

//     instrumented<int>::initialize(0);
//     auto ret = rotate_left_by_one_n(begin(a), a.size());

//     double* count_p = instrumented<int>::counts;
//     CHECK(count_p[instrumented_base::copy_ctor] + 
//           count_p[instrumented_base::copy_assignment] + 
//           count_p[instrumented_base::move_ctor] + 
//           count_p[instrumented_base::move_assignment] == a.size() - 1);
//     CHECK(count_p[instrumented_base::destructor] == 0);
// }

// TEST_CASE("[rotate] testing rotate_left_by_one_n instrumented forward") {
//     using T = instrumented<int>;
//     forward_list<T> a = {1, 2, 3, 4, 5, 6};
//     auto n = distance(begin(a), end(a));

//     instrumented<int>::initialize(0);
//     auto ret = rotate_left_by_one_n(begin(a), n);

//     double* count_p = instrumented<int>::counts;
//     CHECK(count_p[instrumented_base::copy_ctor] + 
//           count_p[instrumented_base::copy_assignment] + 
//           count_p[instrumented_base::move_ctor] + 
//           count_p[instrumented_base::move_assignment] == n - 1);
//     CHECK(count_p[instrumented_base::destructor] == 0);
// }




#endif /*DOCTEST_LIBRARY_INCLUDED*/
