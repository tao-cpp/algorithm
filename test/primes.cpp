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

    std::cout << "1 is prime: " << prime(1) << std::endl;
    std::cout << "2 is prime: " << prime(2) << std::endl;
    std::cout << "3 is prime: " << prime(3) << std::endl;
    std::cout << "4 is prime: " << prime(4) << std::endl;
    std::cout << "5 is prime: " << prime(5) << std::endl;
    std::cout << "6 is prime: " << prime(6) << std::endl;
    std::cout << "7 is prime: " << prime(7) << std::endl;

    std::cout << "10001 is prime: " << prime(10001) << std::endl;
    std::cout << "10007 is prime: " << prime(10007) << std::endl;
    std::cout << "1729 is prime: " << prime(1729) << std::endl;
    std::cout << "172081 is prime: " << prime(172081) << std::endl;
}