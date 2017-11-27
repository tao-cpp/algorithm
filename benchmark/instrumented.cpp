//! \file tao/benchmark/instrumented.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2017
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "instrumented.hpp"
#include <algorithm>

double instrumented_base::counts[];
const char* instrumented_base::counter_names[number_ops] = {"n", "copy", "assign", "destruct", "default", "equal", "less", "construct"};

void instrumented_base::initialize(size_t m) {
    std::fill(counts, counts + number_ops, 0.0);
    counts[n] = double(m);
}
