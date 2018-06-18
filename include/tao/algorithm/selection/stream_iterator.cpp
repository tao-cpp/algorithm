// clang++ -I/Users/fernando/dev/tao-cpp/algorithm/include/ -std=c++17 stream_iterator.cpp

#include <iostream>
#include <sstream>
#include <iterator>
#include <numeric>

#include <tao/algorithm/selection/min_element.hpp>
 
using namespace std;
using namespace tao::algorithm;


int main() {
    // std::istringstream str("0.1 0.2 0.3 0.4");
    // std::partial_sum(std::istream_iterator<double>(str),
    //                  std::istream_iterator<double>(),
    //                  std::ostream_iterator<double>(std::cout, " "));


    // auto f = std::istream_iterator<char>(std::cin);
    // auto l = std::istream_iterator<char>();

    // while (f != l) {
    //     char val = *f;
    //     char val2 = *f;
    //     if (val == char(13)) {
    //         return 0;
    //     }
    //     if (val == char(27)) {
    //         return 0;
    //     }
    //     if (val == char(10)) {
    //         return 0;
    //     }
    //     ++f;
    //     std::cout << val;
    // }


    auto f = std::istream_iterator<int>(std::cin);
    auto l = std::istream_iterator<int>();

// asdsa
    // auto v = min_value_nonempty(f, l, std::less<>());
    // std::cout << v << std::endl;

    auto e = tao::algorithm::min_element(f, l, std::less<>());
    std::cout << *e << std::endl;

}