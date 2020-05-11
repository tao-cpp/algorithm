//! \file tao/benchmark/tipe_description.hpp
// Tao.Algorithm
//
// Copyright (c) 2016-2020 Fernando Pelliccioni.
//
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TAO_ALGORITHM_BENCHMARK_TIME_DESCRIPTION_HPP_
#define TAO_ALGORITHM_BENCHMARK_TIME_DESCRIPTION_HPP_

#include <deque>
#include <list>
#include <string>
#include <vector>

std::string type_description(double) { return std::string("double"); }
std::string type_description(long double) { return std::string("long double"); }
std::string type_description(float) { return std::string("float"); }
std::string type_description(uint8_t) { return std::string("uint8_t"); }
std::string type_description(uint16_t) { return std::string("uint16_t"); }
std::string type_description(uint32_t) { return std::string("uint32_t"); }
std::string type_description(uint64_t) { return std::string("uint64_t"); }
std::string type_description(int8_t) { return std::string("int8_t"); }
std::string type_description(int16_t) { return std::string("int16_t"); }
std::string type_description(int32_t) { return std::string("int32_t"); }
std::string type_description(int64_t) { return std::string("int64_t"); }

template <typename T, typename Alloc>
std::string type_description(const std::vector<T, Alloc>&) { return std::string("vector<") + type_description(T()) + std::string(">"); }

template <typename T, typename Alloc>
std::string type_description(const std::deque<T, Alloc>&) { return std::string("deque<") + type_description(T()) + std::string(">"); }

template <typename T, typename Alloc>
std::string type_description(const std::list<T, Alloc>&) { return std::string("list<") + type_description(T()) + std::string(">"); }

#endif /*TAO_ALGORITHM_BENCHMARK_TIME_DESCRIPTION_HPP_*/
