// //! \file tao/algorithm/rotate.hpp
// // Tao.Algorithm
// //
// // Copyright (c) 2016-2021 Fernando Pelliccioni.
// //
// // Distributed under the MIT software license, see the accompanying
// // file COPYING or http://www.opensource.org/licenses/mit-license.php.

// #ifndef TAO_ALGORITHM_ROTATE_HPP_
// #define TAO_ALGORITHM_ROTATE_HPP_

// #include <algorithm>
// #include <iterator>
// #include <utility>

// // #include <iostream>

// #include <tao/algorithm/concepts.hpp>
// #include <tao/algorithm/copy.hpp>
// #include <tao/algorithm/iterator.hpp>
// #include <tao/algorithm/swap.hpp>
// #include <tao/algorithm/type_attributes.hpp>

// namespace tao { namespace algorithm {

// // -----------------------------------------------------------------
// // rotate_right_by_one
// // -----------------------------------------------------------------

// //TODO(fernando): see what we have to return

// //Complexity:
// //      Runtime:
// //          Amortized: O(n)
// //          Exact:     2 * n - 1 assigments (move or copy)
// //      Space:
// //          O(1)
// template <ForwardIterator I>
// void rotate_right_by_one(I f, I l, std::forward_iterator_tag) {
//     //precondition: mutable_bounded_range(f, l)
//     if (f == l) return;

//     I first = f;

//     ValueType<I> a = std::move(*f);
//     ++f;
//     ValueType<I> b;
//     while (f != l) {
//         shift_three(b, *f++, a);
//         if (f == l) {
//             *first = std::move(b);
//             return;
//         };
//         shift_three(a, *f++, b);
//     }
//     *first = std::move(a);
// }

// //Complexity:
// //      Runtime:
// //          Amortized: O(n)
// //          Exact:     n - 1 assigments (move or copy)
// //      Space:
// //          O(1)
// template <BidirectionalIterator I>
// void rotate_right_by_one(I f, I l, std::bidirectional_iterator_tag) {
//     //precondition: mutable_bounded_range(f, l)
//     if (f == l) return;
//     auto butlast = std::prev(l, 1);
//     auto x = std::move(*butlast);
//     tao::algorithm::move_backward(f, butlast, l);
//     *f = std::move(x);
// }

// //Complexity:
// //      Runtime:
// //          Amortized: O(n)
// //          Exact:
// //              for ForwardIterator:       2 * n - 1 assigments (move or copy)
// //              for BidirectionalIterator: n - 1 assigments (move or copy)
// //      Space:
// //          O(1)
// template <ForwardIterator I>
// inline
// void rotate_right_by_one(I f, I l) {
//     return rotate_right_by_one(f, l, IteratorCategory<I>{});
// }


// // -----------------------------------------------------------------
// // rotate_right_by_one_n
// // -----------------------------------------------------------------

// //Complexity:
// //      Runtime:
// //          Amortized: O(n)
// //          Exact:     2 * distance(f, l) - 1 assigments (move or copy)
// //      Space:
// //          O(1)
// template <ForwardIterator I>
// void rotate_right_by_one_n(I f, DistanceType<I> n, std::forward_iterator_tag) {
//     //precondition: mutable_counted_range(f, n)
//     using N = DistanceType<I>;

//     if (zero(n)) return;

//     I first = f;

//     ValueType<I> a = std::move(*f);
//     ValueType<I> b;
//     step_n(f, n);

//     while ( ! zero(n)) {
//         shift_three(b, *f, a);
//         step_n(f, n);

//         if (zero(n)) {
//             *first = std::move(b);
//             return;
//         };

//         shift_three(a, *f, b);
//         step_n(f, n);

//     }
//     *first = std::move(a);
// }

// //Complexity:
// //      Runtime:
// //          Amortized: O(n)
// //          Exact:     n - 1 assigments (move or copy)
// //      Space:
// //          O(1)
// template <BidirectionalIterator I>
// void rotate_right_by_one_n(I f, DistanceType<I> n, std::bidirectional_iterator_tag) {
//     //precondition: mutable_counted_range(f, n)
//     using N = DistanceType<I>;
//     if (n <= N(1)) return;

//     I butlast = std::next(f, n - 1);
//     I l = butlast;
//     ++l;

//     auto x = std::move(*butlast);
//     tao::algorithm::move_backward_n(butlast, n - 1, l);
//     *f = std::move(x);
// }


// //Complexity:
// //      Runtime:
// //          Amortized: O(n)
// //          Exact:
// //              for ForwardIterator:
// //              for BidirectionalIterator:
// //      Space:
// //          O(1)
// template <ForwardIterator I>
// inline
// void rotate_right_by_one_n(I f, DistanceType<I> n) {
//     return rotate_right_by_one_n(f, n, IteratorCategory<I>{});
// }




// // -----------------------------------------------------------------
// // rotate_left_by_one
// // -----------------------------------------------------------------

// //Complexity:
// //      Runtime:
// //          Amortized: O(n)
// //          Exact:     n - 1 assigments (move or copy)
// //      Space:
// //          O(1)
// template <ForwardIterator I>
// I rotate_left_by_one(I f, I l) {
//     //precondition: mutable_bounded_range(f, l)
//     if (f == l) return f;

//     I next = f;
//     ++next;

//     while (next != l) {
//         //invariant: distance(f, next) == 1
//         *f = std::move(*next);
//         ++f;
//         ++next;
//     }

//     return f;
// }


// // -----------------------------------------------------------------
// // rotate_left_by_one_n
// // -----------------------------------------------------------------

// //Complexity:
// //      Runtime:
// //          Amortized: O(n)
// //          Exact:     n - 1 assigments (move or copy)
// //      Space:
// //          O(1)
// template <ForwardIterator I>
// I rotate_left_by_one_n(I f, DistanceType<I> n) {
//     using N = DistanceType<I>;

//     //precondition: mutable_counted_range(f, n)
//     if (zero(n)) return f;

//     I next = f;
//     ++next;
//     --n;

//     while ( ! zero(n)) {
//         //invariant: distance(f, next) == 1
//         *f = std::move(*next);
//         ++f;
//         ++next;
//         --n;
//     }

//     return f;
// }

// // ----------------------------------------------------------------

// //Complexity:
// //      Runtime:
// //          Amortized: ???
// //          Exact:     ???
// //      Space:
// //          ???
// template <ForwardIterator I>
// void rotate_right_by_one_forward_unguarded(I f, I l) {
//     //precondition: mutable????_bounded_range(f, l)
//     //              distance(f, l) >= 1
//     using std::swap;
//     I current = f;
//     while (++current != l) swap(*f, *current);
// }

// //Complexity:
// //      Runtime:
// //          Amortized: O(n)
// //          Exact:     (n * distance(f, l) - (n * (n-1)) / 2) swaps
// //      Space:
// //          O(1)
// template <ForwardIterator I>
// I rotate_right(I f, I l, DistanceType<I> n, std::forward_iterator_tag) {
//     //precondition: n >= 0 &&
//     //              std::distance(f, l) >= n (so [f, n) is a valid range)
//     while (n > 0) {
//         rotate_right_by_one_forward_unguarded(f, l);
//         ++f;
//         --n;
//     }
//     return f;
// }

// //Complexity:
// //      Runtime:
// //          Amortized: O(n)
// //          Exact:     (distance(f, l) - n) move-assigments or copy-assigments (depending of the ValueType<I> object)
// //      Space:
// //          O(1)
// template <BidirectionalIterator I>
// I rotate_right(I f, I l, DistanceType<I> n, std::bidirectional_iterator_tag) {
//     //precondition: n >= 0 &&
//     //              std::distance(f, l) >= n (so [f, n) is a valid range)
//     I butlast = std::prev(l, n);
//     return tao::algorithm::move_backward(f, butlast, l);
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
// I rotate_right(I f, I l, DistanceType<I> n) {
//     return rotate_right(f, l, n, IteratorCategory<I>{});
// }


// //TODO: rotate_left

// // //Complexity:
// // //      Runtime:
// // //          Amortized: O(n)
// // //          Exact:     (n * distance(f, l) - (n * (n-1)) / 2) swaps
// // //      Space:
// // //          O(1)
// // template <ForwardIterator I>
// // I rotate_left(I f, I l, DistanceType<I> n, std::forward_iterator_tag) {
// //     // //precondition: n >= 0 &&
// //     // //              std::distance(f, l) >= n (so [f, n) is a valid range)
// //     // while (n > 0) {
// //     //     rotate_right_by_one_forward_unguarded(f, l);
// //     //     ++f;
// //     //     --n;
// //     // }
// //     // return f;
// // }


// // //Complexity:
// // //      Runtime:
// // //          Amortized: O(n)
// // //          Exact:     (distance(f, l) - n) move-assigments or copy-assigments (depending of the ValueType<I> object)
// // //      Space:
// // //          O(1)
// // template <BidirectionalIterator I>
// // I rotate_left(I f, I l, DistanceType<I> n, std::bidirectional_iterator_tag) {
// //     //precondition: n >= 0 &&
// //     //              std::distance(f, l) >= n (so [f, n) is a valid range)
// //     //return std::move(f, std::next(f, n), l);
// // }

// // //Complexity:
// // //      Runtime:
// // //          Amortized: O(n)
// // //          Exact:
// // //              for ForwardIterator:       (n * distance(f, l) - (n * (n-1)) / 2) swaps
// // //              for BidirectionalIterator: (distance(f, l) - n) move-assigments or copy-assigments (depending of the ValueType<I> object)
// // //      Space:
// // //          O(1)
// // template <ForwardIterator I>
// // inline
// // I rotate_left(I f, I l, DistanceType<I> n) {
// //     return rotate_left(f, l, n, IteratorCategory<I>{});
// // }

// }} /*tao::algorithm*/

// #endif /*TAO_ALGORITHM_rotate_HPP*/


// #ifdef DOCTEST_LIBRARY_INCLUDED

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




// #endif /*DOCTEST_LIBRARY_INCLUDED*/
