//! \file tao/benchmark/timer.hpp
// Tao.Algorithm
//
// Copyright (c) 2016-2021 Fernando Pelliccioni.
//
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TAO_ALGORITHM_BENCHMARK_TIMER_HPP_
#define TAO_ALGORITHM_BENCHMARK_TIMER_HPP_

#include <chrono>
// #include <time.h>

class timer {
private:
    // clock_t start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
public:
    using result_type = double;

    void start() {
        // start_time = clock();
        start_time = std::chrono::high_resolution_clock::now();
    }

    result_type stop() {
        using namespace std::chrono;

        // return 1000000000. * ((clock() - start_time) / double(CLOCKS_PER_SEC));
        // return std::chrono::duration_cast<std::chrono::duration<result_type>>(std::chrono::high_resolution_clock::now() - start_time).count();

        return duration_cast<nanoseconds>(high_resolution_clock::now() - start_time).count();
    }
};

#endif /*TAO_ALGORITHM_BENCHMARK_TIMER_HPP_*/
