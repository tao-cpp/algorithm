// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2017
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>

#include <tao/algorithm/primes.hpp>

using namespace std;
using namespace tao::algorithm;

int main() {
    std::cout << "10001 is prime: " << prime(10001);
    std::cout << "10007 is prime: " << prime(10007);
    std::cout << "1729 is prime: " << prime(1729);
    
}