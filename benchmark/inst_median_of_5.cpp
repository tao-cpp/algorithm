// Copyright (c) 2016-2021 Fernando Pelliccioni.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

// #include <boost/hana/product.hpp>
// #include <boost/hana/tuple.hpp>

#include <cstdlib>
#include <iostream>
#include <random>
#include <tuple>

#include <tao/benchmark/instrumented.hpp>
#include <tao/algorithm/selection/selection_i_5.hpp>

#define Integer typename

template <Integer I = int, I From = std::numeric_limits<I>::min(), I To = std::numeric_limits<I>::max()>
struct random_int_generator {
	using value_type = I;
	using dis_t = std::uniform_int_distribution<value_type>;
	static constexpr value_type from = From;
	static constexpr value_type to = To;

	random_int_generator()
		: mt{ rd() }
		, dis{ from, to }  // closed range [1, 1000]
	{}

	random_int_generator(random_int_generator const&) = default;

	auto operator()() {
		return dis(mt);
	}

	std::random_device rd;
	std::mt19937 mt;
	dis_t dis;
}; // Models: RandomIntGenerator

int main() {
    using namespace tao::algorithm;


    size_t const max = 100000;
    random_int_generator<int> gen;

    {
    instrumented<int>::initialize(0);
    for (size_t i = 0; i < max; ++i) {
        instrumented<int> a(gen());
        instrumented<int> b(gen());
        instrumented<int> c(gen());
        instrumented<int> d(gen());
        instrumented<int> e(gen());

        median_of_5(a, b, c, d, e, std::less<>());
    }
    double* count_p = instrumented<int>::counts;
    std::cout << "median_of_5 comparisons: " << count_p[instrumented_base::comparison] << std::endl;
    }

    {
    instrumented<int>::initialize(0);
    for (size_t i = 0; i < max; ++i) {
        instrumented<int> a(i++);
        instrumented<int> b(i++);
        instrumented<int> c(i++);
        instrumented<int> d(i++);
        instrumented<int> e(i++);

        median_of_5(a, b, c, d, e, std::less<>());
    }
    double* count_p = instrumented<int>::counts;
    std::cout << "median_of_5 comparisons: " << count_p[instrumented_base::comparison] << std::endl;
    }

    // ---------------------------------

    {
    instrumented<int>::initialize(0);
    for (size_t i = 0; i < max; ++i) {
        instrumented<int> a(gen());
        instrumented<int> b(gen());
        instrumented<int> c(gen());
        instrumented<int> d(gen());
        instrumented<int> e(gen());

        median_of_5_avg(a, b, c, d, e, std::less<>());
    }
    double* count_p = instrumented<int>::counts;
    std::cout << "median_of_5_avg comparisons: " << count_p[instrumented_base::comparison] << std::endl;
    }

    {
    instrumented<int>::initialize(0);
    for (size_t i = 0; i < max; ++i) {
        instrumented<int> a(i++);
        instrumented<int> b(i++);
        instrumented<int> c(i++);
        instrumented<int> d(i++);
        instrumented<int> e(i++);

        median_of_5_avg(a, b, c, d, e, std::less<>());
    }
    double* count_p = instrumented<int>::counts;
    std::cout << "median_of_5_avg comparisons: " << count_p[instrumented_base::comparison] << std::endl;
    }

    return 0;
}
