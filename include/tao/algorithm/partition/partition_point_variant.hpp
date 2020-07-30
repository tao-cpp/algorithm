//! \file tao/algorithm/partition/partition_point_variant.hpp
// Tao.Algorithm
//
// Copyright (c) 2016-2020 Fernando Pelliccioni.
//
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TAO_ALGORITHM_PARTITION_PARTITION_POINT_VARIANT_HPP_
#define TAO_ALGORITHM_PARTITION_PARTITION_POINT_VARIANT_HPP_

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/integers.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao { namespace algorithm {

template <ForwardIterator I, UnaryPredicate P>
    requires(Readable<I> && Domain<P, ValueType<I>>)
I partition_point_variant_n(I f, DistanceType<I> n, P p) {
    //precondition:  readable_counted_range(f, n) && partitioned_n(f, n, p)
    //complexity:    O(log2(n))

    while (n != 0) {
        auto h = half_nonnegative(n);
        I m = std::next(f, h);

        if (p(m)) {
            n = h;
        } else {
            n -= h + 1;
            f = std::next(m);
        }
    }
    return f;
}

}} /*tao::algorithm*/

#include <tao/algorithm/concepts_undef.hpp>

#endif /*TAO_ALGORITHM_PARTITION_PARTITION_POINT_VARIANT_HPP_*/
