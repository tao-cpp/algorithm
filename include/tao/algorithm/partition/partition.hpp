//! \file tao/algorithm/partition/partition.hpp
// Tao.Algorithm
//
// Copyright (c) 2016-2021 Fernando Pelliccioni.
//
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TAO_ALGORITHM_PARTITION_PARTITION_HPP_
#define TAO_ALGORITHM_PARTITION_PARTITION_HPP_

// #include <utility>
// #include <functional>   //std::not_fn(), C++17

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/integers.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao { namespace algorithm {

// Nico Lomuto's partition algorithm.
// ---------------------------------------------------------------------------

// template <ForwardIterator I, UnaryPredicate P>
//     requires(Mutable<I> && Domain<P, ValueType<I>>)
// I partition_semistable_1(I f, I l, P p) {
//     I i = std::find_if(f, l, p);
//     if (i == l) return i;

//     I j = successor(i);
//     while (true) {
//         j = std::find_if_not(j, l, p);
//         if (j == l) return i;
//         swap_step(i, j);
//     }
// }

// template <ForwardIterator I, UnaryPredicate P>
//     requires(Mutable<I> && Domain<P, ValueType<I>>)
// I partition_semistable_1(I f, I l, P p) {
//     f = std::find_if(f, l, p);
//     if (f == l) return f;   //TODO(fernando): one extra comparisson. Inline the std::find_if code.

//     I j = std::next(f);
//     while (j != l) {
//         // loop invariant: all_of((ORIGINAL)f, f, p) && none_of(f, j, p)); // invariant
//         if ( ! p(*j)) {
//             std::iter_swap(f, j);
//             ++f;
//         }
//         ++j;
//     }
//     return f;
// }

template <ForwardIterator I, UnaryPredicate P>
    requires(Mutable<I> && Domain<P, ValueType<I>>)
I partition_semistable(I f, I l, P p) {
    // precondition:    mutable_bounded_range(f, l)
    // postcondition:   partitioned(f, l, p)
    //                  && partition_point(f, l, p) == returned value
    //                  && semistability: the relative order of the elements not satisfying the Predicate p is preserved.
    // complexity:      n = distance(f, l) applications of the Predicate p.
    //                  iterators increments? TODO
    //                  exchanges? TODO
    using std::swap;

    while (true) {
        if (f == l) return f;
        if (p(*f)) break;
        ++f;
    }

    I j = f;
    while (++j != l) {
        // loop invariant: all_of((ORIGINAL)f, f, p) && none_of(f, j, p)); // invariant
        if ( ! p(*j)) {
            swap(*f, *j);
            ++f;
        }
    }
    return f;
}


// EoP's Excercise 11.5
// This algorithm is the same as partition_semistable but it performs n-1 predicate application instead of n predicate applications.
// To do this, it is necesary that que input range be a nonempty range and the partition point cannot be returned.
template <ForwardIterator I, UnaryPredicate P>
    requires(Mutable<I> && Domain<P, ValueType<I>>)
void partition_semistable_nonempty(I f, I l, P p) {
    // precondition:    mutable_bounded_range(f, l)
    //                  && f != l
    // postcondition:   partitioned(f, l, p)
    //                  && semistability: the relative order of the elements not satisfying the Predicate p is preserved.
    // complexity:      n - 1 = distance(f, l) - 1 applications of the Predicate p.
    //                  iterators increments? TODO
    //                  exchanges? TODO
    using std::swap;

    while ( ! p(*f)) {
        ++f;
        if (f == l) return;
    }

    I j = f;
    ++j;
    if (j == l) return;

    while (std::next(j) != l) {
        // loop invariant: all_of((ORIGINAL)f, f, p) && none_of(f, j, p)); // invariant
        if ( ! p(*j)) {
            swap(*f, *j);
            ++f;
        }
        ++j;
    }

    swap(*f, *j);
}


// C.A.R. Hoare's partition algorithm.
// ---------------------------------------------------------------------------

template <BidirectionalIterator I, UnaryPredicate P>
    requires(Mutable<I> && Domain<P, ValueType<I>>)
I partition_bidirectional(I f, I l, P p) {
    //precondition:  mutable_bounded_range(f, l)
    //postcondition: the relative order of the elements not satisfying the Predicate p is preserved.
    //complexity:    n = distance(f, l) applications of the Predicate p.
    //               iterators increments?
    //               exchanges?

    while (true) {
        f = find_if(f, l, p);
        l = find_backward_if_not(f, l, p);
        if (f == l) return f;

        // reverse_swap_step(l, f);
        --l;
        swap(*f, *l);
        ++f;
    }

}

//TODO(fernando): EoP's Excercise 11.6


}} /*tao::algorithm*/

#include <tao/algorithm/concepts_undef.hpp>

#endif /*TAO_ALGORITHM_PARTITION_PARTITION_HPP_*/

#ifdef DOCTEST_LIBRARY_INCLUDED
#include <forward_list>
#include <list>
#include <vector>

#include <tao/benchmark/instrumented.hpp>

using namespace tao::algorithm;
using namespace std;

TEST_CASE("[partition_semistable_nonempty]") {
    // CHECK(count_p[instrumented_base::comparison] == a.size() - 1);


    {
        vector a {2, 1, 1};
        partition_semistable_nonempty(begin(a), end(a), [](auto x){ return x % 2 == 0;});
        CHECK(a == (vector{1, 1, 2}));
    }

    {
        vector a {1, 2, 1};
        partition_semistable_nonempty(begin(a), end(a), [](auto x){ return x % 2 == 0;});
        CHECK(a == (vector{1, 1, 2}));
    }

    {
        vector a {1, 1, 2};
        partition_semistable_nonempty(begin(a), end(a), [](auto x){ return x % 2 == 0;});
        CHECK(a == (vector{1, 1, 2}));
    }

    {
        vector a {1, 2, 2};
        partition_semistable_nonempty(begin(a), end(a), [](auto x){ return x % 2 == 0;});
        CHECK(a == (vector{1, 2, 2}));
    }

    {
        vector a {2, 1, 2};
        partition_semistable_nonempty(begin(a), end(a), [](auto x){ return x % 2 == 0;});
        CHECK(a == (vector{1, 2, 2}));
    }

    {
        vector a {2, 2, 1};
        partition_semistable_nonempty(begin(a), end(a), [](auto x){ return x % 2 == 0;});
        CHECK(a == (vector{1, 2, 2}));
    }


    {
        vector a {1, 2};
        partition_semistable_nonempty(begin(a), end(a), [](auto x){ return x % 2 == 0;});
        CHECK(a == (vector{1, 2}));
    }


    {
        vector a {2, 1};
        partition_semistable_nonempty(begin(a), end(a), [](auto x){ return x % 2 == 0;});
        CHECK(a == (vector{1, 2}));
    }

    {
        vector a {1, 1, 1};
        partition_semistable_nonempty(begin(a), end(a), [](auto x){ return x % 2 == 0;});
        CHECK(a == (vector{1, 1, 1}));
    }

    {
        vector a {1, 1};
        partition_semistable_nonempty(begin(a), end(a), [](auto x){ return x % 2 == 0;});
        CHECK(a == (vector{1, 1}));
    }

    {
        vector a {1};
        partition_semistable_nonempty(begin(a), end(a), [](auto x){ return x % 2 == 0;});
        CHECK(a == (vector{1}));
    }


    {
        vector a {2, 2, 2};
        partition_semistable_nonempty(begin(a), end(a), [](auto x){ return x % 2 == 0;});
        CHECK(a == (vector{2, 2, 2}));
    }

    {
        vector a {2, 2};
        partition_semistable_nonempty(begin(a), end(a), [](auto x){ return x % 2 == 0;});
        CHECK(a == (vector{2, 2}));
    }

    {
        vector a {2};
        partition_semistable_nonempty(begin(a), end(a), [](auto x){ return x % 2 == 0;});
        CHECK(a == (vector{2}));
    }


    {
        vector a {1, 2, 3};
        partition_semistable_nonempty(begin(a), end(a), [](auto x){ return x % 2 == 0;});
        CHECK(a == (vector{1, 3, 2}));
    }

    {
        vector a {1, 3, 2};
        partition_semistable_nonempty(begin(a), end(a), [](auto x){ return x % 2 == 0;});
        CHECK(a == (vector{1, 3, 2}));
    }

    {
        vector a {3, 1, 2};
        partition_semistable_nonempty(begin(a), end(a), [](auto x){ return x % 2 == 0;});
        CHECK(a == (vector{3, 1, 2}));
    }

    {
        vector a {3, 2, 1};
        partition_semistable_nonempty(begin(a), end(a), [](auto x){ return x % 2 == 0;});
        CHECK(a == (vector{3, 1, 2}));
    }

    {
        vector a {2, 3, 1};
        partition_semistable_nonempty(begin(a), end(a), [](auto x){ return x % 2 == 0;});
        CHECK(a == (vector{3, 1, 2}));
    }

    {
        vector a {2, 1, 3};
        partition_semistable_nonempty(begin(a), end(a), [](auto x){ return x % 2 == 0;});
        CHECK(a == (vector{1, 3, 2}));
    }







    {
        vector a {2, 3, 4};
        partition_semistable_nonempty(begin(a), end(a), [](auto x){ return x % 2 == 0;});
        CHECK(a == (vector{3, 4, 2}) || a == (vector{3, 2, 4})); //full-stability can not be guaranteed
    }

    {
        vector a {2, 4, 3};
        partition_semistable_nonempty(begin(a), end(a), [](auto x){ return x % 2 == 0;});
        CHECK(a == (vector{3, 4, 2}) || a == (vector{3, 2, 4})); //full-stability can not be guaranteed
    }

    {
        vector a {4, 2, 3};
        partition_semistable_nonempty(begin(a), end(a), [](auto x){ return x % 2 == 0;});
        CHECK(a == (vector{3, 4, 2}) || a == (vector{3, 2, 4})); //full-stability can not be guaranteed
    }

    {
        vector a {4, 3, 2};
        partition_semistable_nonempty(begin(a), end(a), [](auto x){ return x % 2 == 0;});
        CHECK(a == (vector{3, 4, 2}) || a == (vector{3, 2, 4})); //full-stability can not be guaranteed
    }

    {
        vector a {3, 4, 2};
        partition_semistable_nonempty(begin(a), end(a), [](auto x){ return x % 2 == 0;});
        CHECK(a == (vector{3, 4, 2}) || a == (vector{3, 2, 4})); //full-stability can not be guaranteed
    }

    {
        vector a {3, 2, 4};
        partition_semistable_nonempty(begin(a), end(a), [](auto x){ return x % 2 == 0;});
        CHECK(a == (vector{3, 4, 2}) || a == (vector{3, 2, 4})); //full-stability can not be guaranteed
    }

}

#endif /*DOCTEST_LIBRARY_INCLUDED*/


/*

References:
// ---------------------------------------------------------------------------

    // https://cs.stackexchange.com/questions/11458/quicksort-partitioning-hoare-vs-lomuto

*/