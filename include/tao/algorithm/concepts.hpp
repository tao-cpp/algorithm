//! \file tao/algorithm/concepts.hpp
// Tao.Algorithm
//
// Copyright (c) 2016-2020 Fernando Pelliccioni.
//
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

//TODO: this file must be reviewed


#ifndef TAO_ALGORITHM_CONCEPTS_HPP
#define TAO_ALGORITHM_CONCEPTS_HPP

#define Semiregular typename
#define Regular typename
#define TotallyOrdered typename




#define Number typename

//TODO: debe llamarse Integral (IntegralDomain) o Integer ???
#define Integral typename
#define Integer typename

#define Real typename               //Includes FloatingPoint and FixedPoint decimals
#define FloatingPoint typename
#define FixedPoint typename




#define Iterator typename

    /*
        ForwardIterator(T) ^=
              Iterator(T)
            ^ regular_unary_function (successor)
    */
#define ForwardIterator typename     // EoP 6.6. Forward Iterators
#define BidirectionalIterator typename
#define RandomAccessIterator typename


#define Container typename

#define UnaryPredicate typename

#define Relation typename
#define StrictWeakOrdering typename

#define Procedure typename
#define BinaryOperation typename

#define UnaryFunction typename
// #define NullaryFunction typename

            

#define RandomEngine typename
#define Sequence typename


#define NoncommutativeAdditiveMonoid typename
#define MultiplicativeMonoid typename
#define AdditiveGroup typename
#define MultiplicativeGroup typename
#define SemigroupOperation typename
#define MonoidOperation typename
#define GroupOperation typename

#define Generator typename


#define requires(...) 

#endif /*TAO_ALGORITHM_CONCEPTS_HPP*/
