// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016-2018
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

struct no_natural_order {
    int id;
    int salary;
};

#include <tao/algorithm/copy.hpp>
#include <tao/algorithm/primes.hpp>
#include <tao/algorithm/rotate.hpp>
#include <tao/algorithm/selection.hpp>
#include <tao/algorithm/shift.hpp>
#include <tao/algorithm/swap.hpp>


#include <tao/algorithm/selection/min_element.hpp>
#include <tao/algorithm/selection/max_element.hpp>
#include <tao/algorithm/selection/min_max_element.hpp>
// #include <tao/algorithm/selection/selection_stability.hpp>
// #include <tao/algorithm/selection/selection_i_5.hpp>

#include <tao/algorithm/sorting/insertion_sort.hpp>
#include <tao/algorithm/sorting/selection_sort.hpp>
#include <tao/algorithm/sorting/min_max_sort.hpp>
