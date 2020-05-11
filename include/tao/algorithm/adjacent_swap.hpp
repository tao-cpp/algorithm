//! \file tao/algorithm/adjacent_swap.hpp
// Tao.Algorithm
//
// Copyright (c) 2016-2020 Fernando Pelliccioni.
//
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TAO_ALGORITHM_ADJACENT_SWAP_HPP_
#define TAO_ALGORITHM_ADJACENT_SWAP_HPP_

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

template <ForwardIterator I>
I adjacent_swap(I f, I l, std::forward_iterator_tag) {
    //precondition: mutable_bounded_range(f, l)
    while (f != l) {
        I n = f; ++n;
        if (n == l) return f;
        std::iter_swap(f, n);
        ++n;
        f = n;
    }
    return f;
}

//Complexity: 
//      Runtime:
//          Amortized: O(n)
//          Exact:
//      Space:
//          O(1)
template <RandomAccessIterator I>
I adjacent_swap(I f, I l, std::random_access_iterator_tag) {
    //precondition: mutable_bounded_range(f, l)
    auto n = l - f;
    while (n > 1) {
        std::iter_swap(f, f + 1);
        f += 2;
        n -= 2;
    }
    return f;
}

template <ForwardIterator I>
inline
I adjacent_swap(I f, I l) {
    //precondition: mutable_bounded_range(f, l)
    return adjacent_swap(f, l, IteratorCategory<I>{});
}

// -----------------------------------------------------------------
// adjacent_swap_0
// -----------------------------------------------------------------

//Complexity: 
//      Runtime:
//          Amortized: O(n)
//          Exact:
//      Space:
//          O(1)
// template <ForwardIterator I>
// void adjacent_swap_0(I f, I l, std::forward_iterator_tag) {
//     //precondition: mutable_bounded_range(f, l)
//     using std::swap;

//     while (f != l) {
//         I n = f; ++n;
//         if (n == l) return;
//         swap(*f, *n);
//         ++n;
//         f = n;
//     }
// }

}} /*tao::algorithm*/

#endif /* TAO_ALGORITHM_ADJACENT_SWAP_HPP_ */


#ifdef DOCTEST_LIBRARY_INCLUDED

#include <iterator>
#include <forward_list>
#include <list>
#include <vector>

#include <tao/benchmark/instrumented.hpp>

using namespace std;
using namespace tao::algorithm;


TEST_CASE("[adjacent_swap] testing adjacent_swap 0 elements random access") {
    using T = int;
    vector<T> a;
    auto ret = adjacent_swap(begin(a), end(a));
    CHECK(a == vector<T>());
    CHECK(ret == end(a));
}

TEST_CASE("[adjacent_swap] testing adjacent_swap 1 elements random access") {
    using T = int;
    vector<T> a = {1};
    auto ret = adjacent_swap(begin(a), end(a));
    CHECK(a == vector<T>{1});
    CHECK(ret == begin(a));
    CHECK(*ret == 1);
}

TEST_CASE("[adjacent_swap] testing adjacent_swap 2 elements random access") {
    using T = int;
    vector<T> a = {1, 2};
    auto ret = adjacent_swap(begin(a), end(a));
    CHECK(a == vector<T>{2, 1});
    CHECK(ret == end(a));
}

TEST_CASE("[adjacent_swap] testing adjacent_swap 3 elements random access") {
    using T = int;
    vector<T> a = {1, 2, 3};
    auto ret = adjacent_swap(begin(a), end(a));
    CHECK(a == vector<T>{2, 1, 3});
    CHECK(ret == prev(end(a)));
    CHECK(*ret == 3);
}

TEST_CASE("[adjacent_swap] testing adjacent_swap 4 elements random access") {
    using T = int;
    vector<T> a = {1, 2, 3, 4};
    auto ret = adjacent_swap(begin(a), end(a));
    CHECK(a == vector<T>{2, 1, 4, 3});
    CHECK(ret == end(a));
}

TEST_CASE("[adjacent_swap] testing adjacent_swap 5 elements random access") {
    using T = int;
    vector<T> a = {1, 2, 3, 4, 5};
    auto ret = adjacent_swap(begin(a), end(a));
    CHECK(a == vector<T>{2, 1, 4, 3, 5});
    CHECK(ret == prev(end(a)));
    CHECK(*ret == 5);
}

TEST_CASE("[adjacent_swap] testing adjacent_swap 0 elements bidirectional") {
    using T = int;
    list<T> a;
    auto ret = adjacent_swap(begin(a), end(a));
    CHECK(a == list<T>());
    CHECK(ret == end(a));
}

TEST_CASE("[adjacent_swap] testing adjacent_swap 1 elements bidirectional") {
    using T = int;
    list<T> a = {1};
    auto ret = adjacent_swap(begin(a), end(a));
    CHECK(a == list<T>{1});
    CHECK(ret == begin(a));
    CHECK(*ret == 1);
}

TEST_CASE("[adjacent_swap] testing adjacent_swap 2 elements bidirectional") {
    using T = int;
    list<T> a = {1, 2};
    auto ret = adjacent_swap(begin(a), end(a));
    CHECK(a == list<T>{2, 1});
    CHECK(ret == end(a));
}

TEST_CASE("[adjacent_swap] testing adjacent_swap 3 elements bidirectional") {
    using T = int;
    list<T> a = {1, 2, 3};
    auto ret = adjacent_swap(begin(a), end(a));
    CHECK(a == list<T>{2, 1, 3});
    CHECK(ret == prev(end(a)));
    CHECK(*ret == 3);
}

TEST_CASE("[adjacent_swap] testing adjacent_swap 4 elements bidirectional") {
    using T = int;
    list<T> a = {1, 2, 3, 4};
    auto ret = adjacent_swap(begin(a), end(a));
    CHECK(a == list<T>{2, 1, 4, 3});
    CHECK(ret == end(a));
}

TEST_CASE("[adjacent_swap] testing adjacent_swap 5 elements bidirectional") {
    using T = int;
    list<T> a = {1, 2, 3, 4, 5};
    auto ret = adjacent_swap(begin(a), end(a));
    CHECK(a == list<T>{2, 1, 4, 3, 5});
    CHECK(ret == prev(end(a)));
    CHECK(*ret == 5);
}


TEST_CASE("[adjacent_swap] testing adjacent_swap 0 elements forward") {
    using T = int;
    forward_list<T> a;
    auto ret = adjacent_swap(begin(a), end(a));
    CHECK(a == forward_list<T>());
    CHECK(ret == end(a));
}

TEST_CASE("[adjacent_swap] testing adjacent_swap 1 elements forward") {
    using T = int;
    forward_list<T> a = {1};
    auto ret = adjacent_swap(begin(a), end(a));
    CHECK(a == forward_list<T>{1});
    CHECK(ret == begin(a));
    CHECK(*ret == 1);
}

TEST_CASE("[adjacent_swap] testing adjacent_swap 2 elements forward") {
    using T = int;
    forward_list<T> a = {1, 2};
    auto ret = adjacent_swap(begin(a), end(a));
    CHECK(a == forward_list<T>{2, 1});
    CHECK(ret == end(a));
}

TEST_CASE("[adjacent_swap] testing adjacent_swap 3 elements forward") {
    using T = int;
    forward_list<T> a = {1, 2, 3};
    auto ret = adjacent_swap(begin(a), end(a));
    CHECK(a == forward_list<T>{2, 1, 3});
    CHECK(ret == next(begin(a), 3 - 1));
    CHECK(*ret == 3);
}

TEST_CASE("[adjacent_swap] testing adjacent_swap 4 elements forward") {
    using T = int;
    forward_list<T> a = {1, 2, 3, 4};
    auto ret = adjacent_swap(begin(a), end(a));
    CHECK(a == forward_list<T>{2, 1, 4, 3});
    CHECK(ret == end(a));
}

TEST_CASE("[adjacent_swap] testing adjacent_swap 5 elements forward") {
    using T = int;
    forward_list<T> a = {1, 2, 3, 4, 5};
    auto ret = adjacent_swap(begin(a), end(a));
    CHECK(a == forward_list<T>{2, 1, 4, 3, 5});
    CHECK(ret == next(begin(a), 5 - 1));
    CHECK(*ret == 5);
}

// // ---------------------------------------------------------------------------------------------------
// // TEST_CASE("[adjacent_swap] testing adjacent_swap 6 elements random access compare with std::adjacent_swap") {
// //     using T = int;
// //     vector<T> a = {1, 2, 3, 4, 5, 6};
// //     std::auto ret = adjacent_swap(begin(a), end(a) - 1, end(a));
// //     CHECK(a == vector<T>{6, 1, 2, 3, 4, 5});
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap instrumented random access compare with std::adjacent_swap") {
// //     using T = instrumented<int>;
// //     vector<T> a = {1, 2, 3, 4, 5, 6};

// //     instrumented<int>::initialize(0);
// //     std::auto ret = adjacent_swap(begin(a), std::prev(end(a), 1), end(a));

// //     double* count_p = instrumented<int>::counts;
// //     CHECK(count_p[instrumented_base::copy_ctor] + 
// //           count_p[instrumented_base::copy_assignment] + 
// //           count_p[instrumented_base::move_ctor] + 
// //           count_p[instrumented_base::move_assignment] == a.size() - 1);
// //     CHECK(count_p[instrumented_base::destructor] == 0);
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap instrumented bidirectional compare with std::adjacent_swap") {
// //     using T = instrumented<int>;
// //     list<T> a = {1, 2, 3, 4, 5, 6};

// //     instrumented<int>::initialize(0);
// //     std::auto ret = adjacent_swap(begin(a), std::prev(end(a), 1), end(a));

// //     double* count_p = instrumented<int>::counts;
// //     CHECK(count_p[instrumented_base::copy_ctor] + 
// //           count_p[instrumented_base::copy_assignment] + 
// //           count_p[instrumented_base::move_ctor] + 
// //           count_p[instrumented_base::move_assignment] == a.size() - 1);
// //     CHECK(count_p[instrumented_base::destructor] == 0);
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap instrumented forward compare with std::adjacent_swap") {
// //     using T = instrumented<int>;
// //     forward_list<T> a = {1, 2, 3, 4, 5, 6};
// //     auto n = distance(begin(a), end(a));

// //     instrumented<int>::initialize(0);
// //     std::auto ret = adjacent_swap(begin(a), std::next(begin(a), n - 1), end(a));

// //     double* count_p = instrumented<int>::counts;
// //     CHECK(count_p[instrumented_base::copy_ctor] + 
// //           count_p[instrumented_base::copy_assignment] + 
// //           count_p[instrumented_base::move_ctor] + 
// //           count_p[instrumented_base::move_assignment] == 2 * n - 1);
// //     CHECK(count_p[instrumented_base::destructor] == 0);
// // }
// // ---------------------------------------------------------------------------------------------------


// TEST_CASE("[adjacent_swap] testing adjacent_swap instrumented random access") {
//     using T = instrumented<int>;
//     vector<T> a = {1, 2, 3, 4, 5, 6};

//     instrumented<int>::initialize(0);
//     auto ret = adjacent_swap(begin(a), end(a));

//     double* count_p = instrumented<int>::counts;
//     CHECK(count_p[instrumented_base::copy_ctor] + 
//           count_p[instrumented_base::copy_assignment] + 
//           count_p[instrumented_base::move_ctor] + 
//           count_p[instrumented_base::move_assignment] == a.size() + 1);
//     CHECK(count_p[instrumented_base::destructor] == 1);
// }

// TEST_CASE("[adjacent_swap] testing adjacent_swap instrumented bidirectional") {
//     using T = instrumented<int>;
//     list<T> a = {1, 2, 3, 4, 5, 6};

//     instrumented<int>::initialize(0);
//     auto ret = adjacent_swap(begin(a), end(a));

//     double* count_p = instrumented<int>::counts;
//     CHECK(count_p[instrumented_base::copy_ctor] + 
//           count_p[instrumented_base::copy_assignment] + 
//           count_p[instrumented_base::move_ctor] + 
//           count_p[instrumented_base::move_assignment] == a.size() + 1);
//     CHECK(count_p[instrumented_base::destructor] == 1);
// }

// TEST_CASE("[adjacent_swap] testing adjacent_swap instrumented forward") {
//     using T = instrumented<int>;
//     forward_list<T> a = {1, 2, 3, 4, 5, 6};
//     auto n = distance(begin(a), end(a));

//     instrumented<int>::initialize(0);
//     auto ret = adjacent_swap(begin(a), end(a));

//     double* count_p = instrumented<int>::counts;
//     CHECK(count_p[instrumented_base::copy_ctor] + 
//           count_p[instrumented_base::copy_assignment] + 
//           count_p[instrumented_base::move_ctor] + 
//           count_p[instrumented_base::move_assignment] == 2 * n);
//     CHECK(count_p[instrumented_base::destructor] == 2);
// }



// // TEST_CASE("[adjacent_swap] testing adjacent_swap_n 0 elements random access") {
// //     using T = int;
// //     vector<T> a;
// //     adjacent_swap_n(begin(a), a.size());
// //     CHECK(a == vector<T>());
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_n 1 elements random access") {
// //     using T = int;
// //     vector<T> a = {1};
// //     adjacent_swap_n(begin(a), a.size());
// //     CHECK(a == vector<T>{1});
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_n 2 elements random access") {
// //     using T = int;
// //     vector<T> a = {1, 2};
// //     adjacent_swap_n(begin(a), a.size());
// //     CHECK(a == vector<T>{2, 1});
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_n 3 elements random access") {
// //     using T = int;
// //     vector<T> a = {1, 2, 3};
// //     adjacent_swap_n(begin(a), a.size());
// //     CHECK(a == vector<T>{3, 1, 2});
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_n 4 elements random access") {
// //     using T = int;
// //     vector<T> a = {1, 2, 3, 4};
// //     adjacent_swap_n(begin(a), a.size());
// //     CHECK(a == vector<T>{4, 1, 2, 3});
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_n 5 elements random access") {
// //     using T = int;
// //     vector<T> a = {1, 2, 3, 4, 5};
// //     adjacent_swap_n(begin(a), a.size());
// //     CHECK(a == vector<T>{5, 1, 2, 3, 4});
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_n 6 elements random access") {
// //     using T = int;
// //     vector<T> a = {1, 2, 3, 4, 5, 6};
// //     adjacent_swap_n(begin(a), a.size());
// //     CHECK(a == vector<T>{6, 1, 2, 3, 4, 5});
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_n 0 elements bidirectional") {
// //     using T = int;
// //     list<T> a;
// //     adjacent_swap_n(begin(a), a.size());
// //     CHECK(a == list<T>());
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_n 1 elements bidirectional") {
// //     using T = int;
// //     list<T> a = {1};
// //     adjacent_swap_n(begin(a), a.size());
// //     CHECK(a == list<T>{1});
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_n 2 elements bidirectional") {
// //     using T = int;
// //     list<T> a = {1, 2};
// //     adjacent_swap_n(begin(a), a.size());
// //     CHECK(a == list<T>{2, 1});
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_n 3 elements bidirectional") {
// //     using T = int;
// //     list<T> a = {1, 2, 3};
// //     adjacent_swap_n(begin(a), a.size());
// //     CHECK(a == list<T>{3, 1, 2});
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_n 4 elements bidirectional") {
// //     using T = int;
// //     list<T> a = {1, 2, 3, 4};
// //     adjacent_swap_n(begin(a), a.size());
// //     CHECK(a == list<T>{4, 1, 2, 3});
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_n 5 elements bidirectional") {
// //     using T = int;
// //     list<T> a = {1, 2, 3, 4, 5};
// //     adjacent_swap_n(begin(a), a.size());
// //     CHECK(a == list<T>{5, 1, 2, 3, 4});
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_n 6 elements bidirectional") {
// //     using T = int;
// //     list<T> a = {1, 2, 3, 4, 5, 6};
// //     adjacent_swap_n(begin(a), a.size());
// //     CHECK(a == list<T>{6, 1, 2, 3, 4, 5});
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_n 0 elements forward") {
// //     using T = int;
// //     forward_list<T> a;
// //     auto n = distance(begin(a), end(a));
// //     adjacent_swap_n(begin(a), n);
// //     CHECK(a == forward_list<T>());
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_n 1 elements forward") {
// //     using T = int;
// //     forward_list<T> a = {1};
// //     auto n = distance(begin(a), end(a));
// //     adjacent_swap_n(begin(a), n);
// //     CHECK(a == forward_list<T>{1});
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_n 2 elements forward") {
// //     using T = int;
// //     forward_list<T> a = {1, 2};
// //     auto n = distance(begin(a), end(a));
// //     adjacent_swap_n(begin(a), n);
// //     CHECK(a == forward_list<T>{2, 1});
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_n 3 elements forward") {
// //     using T = int;
// //     forward_list<T> a = {1, 2, 3};
// //     auto n = distance(begin(a), end(a));
// //     adjacent_swap_n(begin(a), n);
// //     CHECK(a == forward_list<T>{3, 1, 2});
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_n 4 elements forward") {
// //     using T = int;
// //     forward_list<T> a = {1, 2, 3, 4};
// //     auto n = distance(begin(a), end(a));
// //     adjacent_swap_n(begin(a), n);
// //     CHECK(a == forward_list<T>{4, 1, 2, 3});
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_n 5 elements forward") {
// //     using T = int;
// //     forward_list<T> a = {1, 2, 3, 4, 5};
// //     auto n = distance(begin(a), end(a));
// //     adjacent_swap_n(begin(a), n);
// //     CHECK(a == forward_list<T>{5, 1, 2, 3, 4});
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_n 6 elements forward") {
// //     using T = int;
// //     forward_list<T> a = {1, 2, 3, 4, 5, 6};
// //     auto n = distance(begin(a), end(a));
// //     adjacent_swap_n(begin(a), n);
// //     CHECK(a == forward_list<T>{6, 1, 2, 3, 4, 5});
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_n instrumented random access") {
// //     using T = instrumented<int>;
// //     vector<T> a = {1, 2, 3, 4, 5, 6};

// //     instrumented<int>::initialize(0);
// //     adjacent_swap_n(begin(a), a.size());

// //     double* count_p = instrumented<int>::counts;
// //     CHECK(count_p[instrumented_base::copy_ctor] + 
// //           count_p[instrumented_base::copy_assignment] + 
// //           count_p[instrumented_base::move_ctor] + 
// //           count_p[instrumented_base::move_assignment] == a.size() + 1);
// //     CHECK(count_p[instrumented_base::destructor] == 1);
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_n instrumented bidirectional") {
// //     using T = instrumented<int>;
// //     list<T> a = {1, 2, 3, 4, 5, 6};

// //     instrumented<int>::initialize(0);
// //     adjacent_swap_n(begin(a), a.size());

// //     double* count_p = instrumented<int>::counts;
// //     CHECK(count_p[instrumented_base::copy_ctor] + 
// //           count_p[instrumented_base::copy_assignment] + 
// //           count_p[instrumented_base::move_ctor] + 
// //           count_p[instrumented_base::move_assignment] == a.size() + 1);
// //     CHECK(count_p[instrumented_base::destructor] == 1);
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_n instrumented forward") {
// //     using T = instrumented<int>;
// //     forward_list<T> a = {1, 2, 3, 4, 5, 6};
// //     auto n = distance(begin(a), end(a));

// //     instrumented<int>::initialize(0);
// //     adjacent_swap_n(begin(a), n);

// //     double* count_p = instrumented<int>::counts;
// //     CHECK(count_p[instrumented_base::copy_ctor] + 
// //           count_p[instrumented_base::copy_assignment] + 
// //           count_p[instrumented_base::move_ctor] + 
// //           count_p[instrumented_base::move_assignment] == 2 * n);
// //     CHECK(count_p[instrumented_base::destructor] == 2);
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one 0 elements random access") {
// //     using T = int;
// //     vector<T> a;
// //     auto ret = adjacent_swap_left_by_one(begin(a), end(a));
// //     CHECK(a   == vector<T>());
// //     CHECK(ret == end(a));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one 1 elements random access") {
// //     using T = int;
// //     vector<T> a = {1};
// //     auto ret = adjacent_swap_left_by_one(begin(a), end(a));
// //     CHECK(a == vector<T>{1});
// //     CHECK(ret == std::next(begin(a), a.size() - 1));
    
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one 2 elements random access") {
// //     using T = int;
// //     vector<T> a = {1, 2};
// //     auto ret = adjacent_swap_left_by_one(begin(a), end(a));
// //     CHECK(a == vector<T>{2, 2});
// //     CHECK(ret == std::next(begin(a), a.size() - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one 3 elements random access") {
// //     using T = int;
// //     vector<T> a = {1, 2, 3};
// //     auto ret = adjacent_swap_left_by_one(begin(a), end(a));
// //     CHECK(a == vector<T>{2, 3, 3});
// //     CHECK(ret == std::next(begin(a), a.size() - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one 4 elements random access") {
// //     using T = int;
// //     vector<T> a = {1, 2, 3, 4};
// //     auto ret = adjacent_swap_left_by_one(begin(a), end(a));
// //     CHECK(a == vector<T>{2, 3, 4, 4});
// //     CHECK(ret == std::next(begin(a), a.size() - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one 5 elements random access") {
// //     using T = int;
// //     vector<T> a = {1, 2, 3, 4, 5};
// //     auto ret = adjacent_swap_left_by_one(begin(a), end(a));
// //     CHECK(a == vector<T>{2, 3, 4, 5, 5});
// //     CHECK(ret == std::next(begin(a), a.size() - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one 6 elements random access") {
// //     using T = int;
// //     vector<T> a = {1, 2, 3, 4, 5, 6};
// //     auto ret = adjacent_swap_left_by_one(begin(a), end(a));
// //     CHECK(a == vector<T>{2, 3, 4, 5, 6, 6});
// //     CHECK(ret == std::next(begin(a), a.size() - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one 0 elements bidirectional") {
// //     using T = int;
// //     list<T> a;
// //     auto ret = adjacent_swap_left_by_one(begin(a), end(a));
// //     CHECK(a == list<T>());
// //     CHECK(ret == end(a));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one 1 elements bidirectional") {
// //     using T = int;
// //     list<T> a = {1};
// //     auto ret = adjacent_swap_left_by_one(begin(a), end(a));
// //     CHECK(a == list<T>{1});
// //     CHECK(ret == std::next(begin(a), a.size() - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one 2 elements bidirectional") {
// //     using T = int;
// //     list<T> a = {1, 2};
// //     auto ret = adjacent_swap_left_by_one(begin(a), end(a));
// //     CHECK(a == list<T>{2, 2});
// //     CHECK(ret == std::next(begin(a), a.size() - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one 3 elements bidirectional") {
// //     using T = int;
// //     list<T> a = {1, 2, 3};
// //     auto ret = adjacent_swap_left_by_one(begin(a), end(a));
// //     CHECK(a == list<T>{2, 3, 3});
// //     CHECK(ret == std::next(begin(a), a.size() - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one 4 elements bidirectional") {
// //     using T = int;
// //     list<T> a = {1, 2, 3, 4};
// //     auto ret = adjacent_swap_left_by_one(begin(a), end(a));
// //     CHECK(a == list<T>{2, 3, 4, 4});
// //     CHECK(ret == std::next(begin(a), a.size() - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one 5 elements bidirectional") {
// //     using T = int;
// //     list<T> a = {1, 2, 3, 4, 5};
// //     auto ret = adjacent_swap_left_by_one(begin(a), end(a));
// //     CHECK(a == list<T>{2, 3, 4, 5, 5});
// //     CHECK(ret == std::next(begin(a), a.size() - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one 6 elements bidirectional") {
// //     using T = int;
// //     list<T> a = {1, 2, 3, 4, 5, 6};
// //     auto ret = adjacent_swap_left_by_one(begin(a), end(a));
// //     CHECK(a == list<T>{2, 3, 4, 5, 6, 6});
// //     CHECK(ret == std::next(begin(a), a.size() - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one 0 elements forward") {
// //     using T = int;
// //     forward_list<T> a;
// //     auto n = distance(begin(a), end(a));
// //     auto ret = adjacent_swap_left_by_one(begin(a), end(a));
// //     CHECK(a == forward_list<T>());
// //     CHECK(ret == end(a));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one 1 elements forward") {
// //     using T = int;
// //     forward_list<T> a = {1};
// //     auto n = distance(begin(a), end(a));
// //     auto ret = adjacent_swap_left_by_one(begin(a), end(a));
// //     CHECK(a == forward_list<T>{1});
// //     CHECK(ret == std::next(begin(a), n - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one 2 elements forward") {
// //     using T = int;
// //     forward_list<T> a = {1, 2};
// //     auto n = distance(begin(a), end(a));
// //     auto ret = adjacent_swap_left_by_one(begin(a), end(a));
// //     CHECK(a == forward_list<T>{2, 2});
// //     CHECK(ret == std::next(begin(a), n - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one 3 elements forward") {
// //     using T = int;
// //     forward_list<T> a = {1, 2, 3};
// //     auto n = distance(begin(a), end(a));
// //     auto ret = adjacent_swap_left_by_one(begin(a), end(a));
// //     CHECK(a == forward_list<T>{2, 3, 3});
// //     CHECK(ret == std::next(begin(a), n - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one 4 elements forward") {
// //     using T = int;
// //     forward_list<T> a = {1, 2, 3, 4};
// //     auto n = distance(begin(a), end(a));
// //     auto ret = adjacent_swap_left_by_one(begin(a), end(a));
// //     CHECK(a == forward_list<T>{2, 3, 4, 4});
// //     CHECK(ret == std::next(begin(a), n - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one 5 elements forward") {
// //     using T = int;
// //     forward_list<T> a = {1, 2, 3, 4, 5};
// //     auto n = distance(begin(a), end(a));
// //     auto ret = adjacent_swap_left_by_one(begin(a), end(a));
// //     CHECK(a == forward_list<T>{2, 3, 4, 5, 5});
// //     CHECK(ret == std::next(begin(a), n - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one 6 elements forward") {
// //     using T = int;
// //     forward_list<T> a = {1, 2, 3, 4, 5, 6};
// //     auto n = distance(begin(a), end(a));
// //     auto ret = adjacent_swap_left_by_one(begin(a), end(a));
// //     CHECK(a == forward_list<T>{2, 3, 4, 5, 6, 6});
// //     CHECK(ret == std::next(begin(a), n - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one instrumented random access") {
// //     using T = instrumented<int>;
// //     vector<T> a = {1, 2, 3, 4, 5, 6};

// //     instrumented<int>::initialize(0);
// //     auto ret = adjacent_swap_left_by_one(begin(a), end(a));

// //     double* count_p = instrumented<int>::counts;
// //     CHECK(count_p[instrumented_base::copy_ctor] + 
// //           count_p[instrumented_base::copy_assignment] + 
// //           count_p[instrumented_base::move_ctor] + 
// //           count_p[instrumented_base::move_assignment] == a.size() - 1);
// //     CHECK(count_p[instrumented_base::destructor] == 0);
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one instrumented bidirectional") {
// //     using T = instrumented<int>;
// //     list<T> a = {1, 2, 3, 4, 5, 6};

// //     instrumented<int>::initialize(0);
// //     auto ret = adjacent_swap_left_by_one(begin(a), end(a));

// //     double* count_p = instrumented<int>::counts;
// //     CHECK(count_p[instrumented_base::copy_ctor] + 
// //           count_p[instrumented_base::copy_assignment] + 
// //           count_p[instrumented_base::move_ctor] + 
// //           count_p[instrumented_base::move_assignment] == a.size() - 1);
// //     CHECK(count_p[instrumented_base::destructor] == 0);
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one instrumented forward") {
// //     using T = instrumented<int>;
// //     forward_list<T> a = {1, 2, 3, 4, 5, 6};
// //     auto n = distance(begin(a), end(a));

// //     instrumented<int>::initialize(0);
// //     auto ret = adjacent_swap_left_by_one(begin(a), end(a));

// //     double* count_p = instrumented<int>::counts;
// //     CHECK(count_p[instrumented_base::copy_ctor] + 
// //           count_p[instrumented_base::copy_assignment] + 
// //           count_p[instrumented_base::move_ctor] + 
// //           count_p[instrumented_base::move_assignment] == n - 1);
// //     CHECK(count_p[instrumented_base::destructor] == 0);
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one_n 0 elements random access") {
// //     using T = int;
// //     vector<T> a;
// //     auto ret = adjacent_swap_left_by_one_n(begin(a), a.size());
// //     CHECK(a   == vector<T>());
// //     CHECK(ret == end(a));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one_n 1 elements random access") {
// //     using T = int;
// //     vector<T> a = {1};
// //     auto ret = adjacent_swap_left_by_one_n(begin(a), a.size());
// //     CHECK(a == vector<T>{1});
// //     CHECK(ret == std::next(begin(a), a.size() - 1));
    
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one_n 2 elements random access") {
// //     using T = int;
// //     vector<T> a = {1, 2};
// //     auto ret = adjacent_swap_left_by_one_n(begin(a), a.size());
// //     CHECK(a == vector<T>{2, 2});
// //     CHECK(ret == std::next(begin(a), a.size() - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one_n 3 elements random access") {
// //     using T = int;
// //     vector<T> a = {1, 2, 3};
// //     auto ret = adjacent_swap_left_by_one_n(begin(a), a.size());
// //     CHECK(a == vector<T>{2, 3, 3});
// //     CHECK(ret == std::next(begin(a), a.size() - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one_n 4 elements random access") {
// //     using T = int;
// //     vector<T> a = {1, 2, 3, 4};
// //     auto ret = adjacent_swap_left_by_one_n(begin(a), a.size());
// //     CHECK(a == vector<T>{2, 3, 4, 4});
// //     CHECK(ret == std::next(begin(a), a.size() - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one_n 5 elements random access") {
// //     using T = int;
// //     vector<T> a = {1, 2, 3, 4, 5};
// //     auto ret = adjacent_swap_left_by_one_n(begin(a), a.size());
// //     CHECK(a == vector<T>{2, 3, 4, 5, 5});
// //     CHECK(ret == std::next(begin(a), a.size() - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one_n 6 elements random access") {
// //     using T = int;
// //     vector<T> a = {1, 2, 3, 4, 5, 6};
// //     auto ret = adjacent_swap_left_by_one_n(begin(a), a.size());
// //     CHECK(a == vector<T>{2, 3, 4, 5, 6, 6});
// //     CHECK(ret == std::next(begin(a), a.size() - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one_n 0 elements bidirectional") {
// //     using T = int;
// //     list<T> a;
// //     auto ret = adjacent_swap_left_by_one_n(begin(a), a.size());
// //     CHECK(a == list<T>());
// //     CHECK(ret == end(a));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one_n 1 elements bidirectional") {
// //     using T = int;
// //     list<T> a = {1};
// //     auto ret = adjacent_swap_left_by_one_n(begin(a), a.size());
// //     CHECK(a == list<T>{1});
// //     CHECK(ret == std::next(begin(a), a.size() - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one_n 2 elements bidirectional") {
// //     using T = int;
// //     list<T> a = {1, 2};
// //     auto ret = adjacent_swap_left_by_one_n(begin(a), a.size());
// //     CHECK(a == list<T>{2, 2});
// //     CHECK(ret == std::next(begin(a), a.size() - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one_n 3 elements bidirectional") {
// //     using T = int;
// //     list<T> a = {1, 2, 3};
// //     auto ret = adjacent_swap_left_by_one_n(begin(a), a.size());
// //     CHECK(a == list<T>{2, 3, 3});
// //     CHECK(ret == std::next(begin(a), a.size() - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one_n 4 elements bidirectional") {
// //     using T = int;
// //     list<T> a = {1, 2, 3, 4};
// //     auto ret = adjacent_swap_left_by_one_n(begin(a), a.size());
// //     CHECK(a == list<T>{2, 3, 4, 4});
// //     CHECK(ret == std::next(begin(a), a.size() - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one_n 5 elements bidirectional") {
// //     using T = int;
// //     list<T> a = {1, 2, 3, 4, 5};
// //     auto ret = adjacent_swap_left_by_one_n(begin(a), a.size());
// //     CHECK(a == list<T>{2, 3, 4, 5, 5});
// //     CHECK(ret == std::next(begin(a), a.size() - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one_n 6 elements bidirectional") {
// //     using T = int;
// //     list<T> a = {1, 2, 3, 4, 5, 6};
// //     auto ret = adjacent_swap_left_by_one_n(begin(a), a.size());
// //     CHECK(a == list<T>{2, 3, 4, 5, 6, 6});
// //     CHECK(ret == std::next(begin(a), a.size() - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one_n 0 elements forward") {
// //     using T = int;
// //     forward_list<T> a;
// //     auto n = distance(begin(a), end(a));
// //     auto ret = adjacent_swap_left_by_one_n(begin(a), n);
// //     CHECK(a == forward_list<T>());
// //     CHECK(ret == end(a));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one_n 1 elements forward") {
// //     using T = int;
// //     forward_list<T> a = {1};
// //     auto n = distance(begin(a), end(a));
// //     auto ret = adjacent_swap_left_by_one_n(begin(a), n);
// //     CHECK(a == forward_list<T>{1});
// //     CHECK(ret == std::next(begin(a), n - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one_n 2 elements forward") {
// //     using T = int;
// //     forward_list<T> a = {1, 2};
// //     auto n = distance(begin(a), end(a));
// //     auto ret = adjacent_swap_left_by_one_n(begin(a), n);
// //     CHECK(a == forward_list<T>{2, 2});
// //     CHECK(ret == std::next(begin(a), n - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one_n 3 elements forward") {
// //     using T = int;
// //     forward_list<T> a = {1, 2, 3};
// //     auto n = distance(begin(a), end(a));
// //     auto ret = adjacent_swap_left_by_one_n(begin(a), n);
// //     CHECK(a == forward_list<T>{2, 3, 3});
// //     CHECK(ret == std::next(begin(a), n - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one_n 4 elements forward") {
// //     using T = int;
// //     forward_list<T> a = {1, 2, 3, 4};
// //     auto n = distance(begin(a), end(a));
// //     auto ret = adjacent_swap_left_by_one_n(begin(a), n);
// //     CHECK(a == forward_list<T>{2, 3, 4, 4});
// //     CHECK(ret == std::next(begin(a), n - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one_n 5 elements forward") {
// //     using T = int;
// //     forward_list<T> a = {1, 2, 3, 4, 5};
// //     auto n = distance(begin(a), end(a));
// //     auto ret = adjacent_swap_left_by_one_n(begin(a), n);
// //     CHECK(a == forward_list<T>{2, 3, 4, 5, 5});
// //     CHECK(ret == std::next(begin(a), n - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one_n 6 elements forward") {
// //     using T = int;
// //     forward_list<T> a = {1, 2, 3, 4, 5, 6};
// //     auto n = distance(begin(a), end(a));
// //     auto ret = adjacent_swap_left_by_one_n(begin(a), n);
// //     CHECK(a == forward_list<T>{2, 3, 4, 5, 6, 6});
// //     CHECK(ret == std::next(begin(a), n - 1));
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one_n instrumented random access") {
// //     using T = instrumented<int>;
// //     vector<T> a = {1, 2, 3, 4, 5, 6};

// //     instrumented<int>::initialize(0);
// //     auto ret = adjacent_swap_left_by_one_n(begin(a), a.size());

// //     double* count_p = instrumented<int>::counts;
// //     CHECK(count_p[instrumented_base::copy_ctor] + 
// //           count_p[instrumented_base::copy_assignment] + 
// //           count_p[instrumented_base::move_ctor] + 
// //           count_p[instrumented_base::move_assignment] == a.size() - 1);
// //     CHECK(count_p[instrumented_base::destructor] == 0);
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one_n instrumented bidirectional") {
// //     using T = instrumented<int>;
// //     list<T> a = {1, 2, 3, 4, 5, 6};

// //     instrumented<int>::initialize(0);
// //     auto ret = adjacent_swap_left_by_one_n(begin(a), a.size());

// //     double* count_p = instrumented<int>::counts;
// //     CHECK(count_p[instrumented_base::copy_ctor] + 
// //           count_p[instrumented_base::copy_assignment] + 
// //           count_p[instrumented_base::move_ctor] + 
// //           count_p[instrumented_base::move_assignment] == a.size() - 1);
// //     CHECK(count_p[instrumented_base::destructor] == 0);
// // }

// // TEST_CASE("[adjacent_swap] testing adjacent_swap_left_by_one_n instrumented forward") {
// //     using T = instrumented<int>;
// //     forward_list<T> a = {1, 2, 3, 4, 5, 6};
// //     auto n = distance(begin(a), end(a));

// //     instrumented<int>::initialize(0);
// //     auto ret = adjacent_swap_left_by_one_n(begin(a), n);

// //     double* count_p = instrumented<int>::counts;
// //     CHECK(count_p[instrumented_base::copy_ctor] + 
// //           count_p[instrumented_base::copy_assignment] + 
// //           count_p[instrumented_base::move_ctor] + 
// //           count_p[instrumented_base::move_assignment] == n - 1);
// //     CHECK(count_p[instrumented_base::destructor] == 0);
// // }




#endif /*DOCTEST_LIBRARY_INCLUDED*/
