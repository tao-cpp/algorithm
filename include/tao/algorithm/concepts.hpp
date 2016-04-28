#ifndef LIBNAME_CONCEPTS_HPP_
#define LIBNAME_CONCEPTS_HPP_

#define Integral typename


#define Iterator typename


    /*
        ForwardIterator(T) ^=
              Iterator(T)
            ^ regular_unary_function (successor)
    */
#define ForwardIterator typename     // EoP 6.6. Forward Iterators
            

#define BidirectionalIterator typename



#define Container typename

#define StrictWeakOrdering typename

#endif //LIBNAME_CONCEPTS_HPP_
