//! \file tao/benchmark/instrumented.cpp
// Tao.Algorithm
//
// Copyright (c) 2016-2020 Fernando Pelliccioni.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <tao/benchmark/instrumented.hpp>
#include <algorithm>

double instrumented_base::counts[];
const char* instrumented_base::counter_names[number_ops] = {"n", "default", "construct", "copy ctor", "copy assign", "move ctor", "move assign", "destruct", "equal", "less"}; //, "swap"

void instrumented_base::initialize(size_t m) {
    std::fill(counts, counts + number_ops, 0.0);
    counts[n] = double(m);
}
