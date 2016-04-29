//! \file tao/algorithm/type_attributes.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef TAO_ALGORITHM_TYPE_ATTRIBUTES_HPP
#define TAO_ALGORITHM_TYPE_ATTRIBUTES_HPP

#include <iterator>

#include <tao/algorithm/concepts.hpp>

// Iterators
template <Iterator I>
using ValueType = typename std::iterator_traits<I>::value_type;

template <Iterator I>
using IteratorCategory = typename std::iterator_traits<I>::iterator_category;

// Containers
template <Container C>
using SizeType = typename C::size_type;


#endif //TAO_ALGORITHM_TYPE_ATTRIBUTES_HPP
