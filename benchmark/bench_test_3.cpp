// Copyright (c) 2016-2020 Fernando Pelliccioni.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

// #include <boost/hana/product.hpp>
// #include <boost/hana/tuple.hpp>

#include "measure.hpp"
#include <cstdlib>
#include <tuple>


int main() {
    boost::hana::benchmark::measure([] {
        long double result = 0;
        for (int iteration = 0; iteration < 1 << 10; ++iteration) {
            ++result;
        }
    });

    return 1;
}
