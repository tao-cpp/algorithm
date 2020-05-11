// Tao.Algorithm
//
// Copyright (c) 2016-2020 Fernando Pelliccioni.
//
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <iostream>

#include <tao/algorithm/selection.hpp>

using namespace std;
using namespace tao::algorithm;

int main() {

    int i1 = 1;
    int i2 = 2;
    int i3 = 3;
    int const ci3 = 2;

    int m = select_0_2(i1, i2);

    std::cout << "i1: " << i1 << std::endl;
    std::cout << "i2: " << i2 << std::endl;
    std::cout << "m:  " << m << std::endl;

    select_0_2(i1, i2) += 10;
    // select_0_2(i1, 5) += 10;     // error, ok
    // select_0_2(5, i2) += 10;     // error, ok
    // select_0_2(5, 5) += 10;     // error, ok
    // select_0_2(i1, ci3) += 10;     // error, ok

    int m2 = select_0_2(1, 2);


    std::cout << "i1: " << i1 << std::endl;
    std::cout << "i2: " << i2 << std::endl;
    std::cout << "m2: " << m2 << std::endl;


    std::cout << "i1: " << i1 << std::endl;
    std::cout << "i2: " << i2 << std::endl;
    std::cout << "i3: " << i3 << std::endl;


    int m3 = select_0_3(i1, i2, i3);
    std::cout << "m3: " << m3 << std::endl;

    select_0_3(i1, i2, i3) += 100;

    std::cout << "i1: " << i1 << std::endl;
    std::cout << "i2: " << i2 << std::endl;
    std::cout << "i3: " << i3 << std::endl;

    select_1_3(i1, i2, i3) += 100;

    std::cout << "i1: " << i1 << std::endl;
    std::cout << "i2: " << i2 << std::endl;
    std::cout << "i3: " << i3 << std::endl;

    select_2_3(i1, i2, i3) += 100;

    std::cout << "i1: " << i1 << std::endl;
    std::cout << "i2: " << i2 << std::endl;
    std::cout << "i3: " << i3 << std::endl;


    // employee m = select_0_2(e1, e2);

    // // using another (unnatural) ordering
    // employee m2 = select_0_2(e1, e2, salary_comparator{});

    // // using another (unnatural) ordering, with lambdas   
    // employee m3 = select_0_2(e1, e2, [](employee const& a, 
    //                         employee const& b) {
    //     return a.name < b.name; 
    // });
}