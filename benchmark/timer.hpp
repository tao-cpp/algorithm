//! \file tao/benchmark/timer.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016-2018
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

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
