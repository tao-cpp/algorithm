//! \file tao/algorithm/swap.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016-2018
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_ALGORITHM_SWAP_HPP_
#define TAO_ALGORITHM_SWAP_HPP_

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

}} /*tao::algorithm*/

#endif /*TAO_ALGORITHM_SWAP_HPP_*/


#ifdef DOCTEST_LIBRARY_INCLUDED

// #include <iterator>
// #include <forward_list>
// #include <list>
// #include <vector>

// #include <tao/benchmark/instrumented.hpp>

// using namespace std;
// using namespace tao::algorithm;


// TEST_CASE("[shift] testing shift_right_by_one_temp") {
//     //using namespace tao::algorithm;

//     // using T = int;
//     using T = instrumented<int>;
//     instrumented<int>::initialize(0);

//     vector<T> a = {1, 2, 3, 4, 5, 6};

//     instrumented<int>::initialize(0);
//     shift_right_by_one_temp(begin(a), end(a));

//     // for (auto&& x : a) {
//     //     cout << x << endl;
//     // }


//     double* count_p = instrumented<int>::counts;
//     for (size_t i = 0; i < instrumented_base::number_ops; ++i) {
//         std::cout << instrumented_base::counter_names[i] << ": " 
//                   << count_p[i] 
//                   << std::endl;
//     }

//     CHECK(a == vector<T>{1, 1, 2, 3, 4, 5});
//     CHECK(a == vector<T>{1, 1, 2, 3, 4, 6});
    
// }


#endif /*DOCTEST_LIBRARY_INCLUDED*/
