#ifndef TAOCPP_BENCHMARK_STATISTICS_HPP_
#define TAOCPP_BENCHMARK_STATISTICS_HPP_

#include <algorithm>	//for std::sort
#include <array>
#include <chrono>
#include <numeric>		//for std::accumulate
#include <vector>
#include <tuple>

#include <tao/algorithm/accumulate.hpp>
#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/for_each.hpp>
#include <tao/algorithm/iterator.hpp>
#include <tao/algorithm/numerics.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao { namespace algorithm {

// ------------------------------------------------------------------------
// Mean
// ------------------------------------------------------------------------

template <Iterator I, Integral N, Real R = double>
inline
R mean_n(I f, N n) {
	//precondition: [f, n) is a valid range. TODO: mutable or read-only range?
	//              ValueType<I> is convertible to R

	using T = ValueType<I>;    
	return accumulate_n(f, n, T(0)) / R(n);
}

template <Iterator I, Integral N, Real R = double>
inline
R mean(I f, I l, N n) {
	//precondition: [f, l) is a valid range &&
	//				std::distance(f, l) == n 
	//              ValueType<I> is convertible to R      
	//              TODO: mutable or read-only range?

	using T = ValueType<I>;
	return std::accumulate(f, l, T(0)) / R(n);
}

template <Iterator I, Real R = double>
inline
R mean(I f, I l) {
	//precondition: [f, l) is a valid range. TODO: mutable or read-only range?
	//              ValueType<I> is convertible to R
	using T = ValueType<I>;
	return std::accumulate(f, l, T(0)) / R(std::distance(f, l));
}

template <Container C, Real R = double>
inline
R mean_c(C const& c) {
	//precondition: ValueType<C> is convertible to R      
	return mean<IteratorType<C>, SizeType<C>, R>(std::begin(c), std::end(c), size(c));
}

// ------------------------------------------------------------------------
// Median
// ------------------------------------------------------------------------

//Warning: Sorts the range [f, l)
template <Iterator I, Integral N, Real R = double>
// requires Mutable<I>
inline
R median(I f, I l, N n) {
	//precondition: [f, l) is a valid range &&
	//				std::distance(f, l) == n 

	if (n == N(0)) return R(0);

	std::sort(f, l);

	if (even(n)) {
		f = std::next(f, n / 2 - 1);
		return (*f + *std::next(f)) / R(2);
	} else {
		return R(*std::next(f, n / 2));
	}
}


//Warning: Sorts the contain of the Container
template <Container C, Real R = double>
inline
auto median_c(C& c) {
	return median(std::begin(c), std::end(c), size(c));
}


// ------------------------------------------------------------------------
// ------------------------------------------------------------------------

template <Iterator I, Integral N>
inline
auto variance_helper_n(I f, N n, ValueType<I> mean) {
	using T = ValueType<I>;

	//TODO: create an algorithm to do the following...
	// T s(0);
	// for_each_n(f, n, [&s, mean](T x) { 
	// 	s += (x - mean) * (x - mean); });
	// return s;

	const auto fun = [mean](T x) {return (x - mean) * (x - mean);};
	return accumulate_n(f, n, T(0), std::plus<>{}, fun);
}


//Note: it requires ForwardIterator because we are doing 2 passes over the range.
template <ForwardIterator I, Integral N>
inline
auto variance_helper_n(I f, N n) {
	return variance_helper_n(f, n, mean_n(f, n));
}


//real_type variance_helper_2(std::vector<real_type> const& data) {
//	real_type sum = 0;
//	real_type sum_sqr = 0;
//	size_t n = 0;
//	auto K = data[0];
//
//	std::for_each(begin(data), end(data), [K, &n, &sum, &sum_sqr](real_type x) {
//		sum += x - K;
//		sum_sqr += (x - K) * (x - K);
//		++n;
//	});
//
//	real_type v = (sum_sqr - (sum * sum) / n);
//	return v;
//}


/*
Sum(i, n) (Xi - X)^2
Sum(i, n) (Xi - (Sum(i, n) Xi) / n) ^ 2
*/

template <Iterator I, Integral N>
inline
auto population_variance_n(I f, N n, ValueType<I> mean) {
	//precondition: [f, n) is a valid range.
	return variance_helper_n(f, n, mean) / n;
}

template <ForwardIterator I, Integral N>
inline
auto population_variance_n(I f, N n) {
	//precondition: [f, n) is a valid range.
	return variance_helper_n(f, n) / n;
}

template <Iterator I, Integral N>
inline
auto sample_variance_n(I f, N n, ValueType<I> mean) { 
	//precondition: [f, n) is a valid range.
	return variance_helper_n(f, n, mean) / (n - 1); 
}

template <ForwardIterator I, Integral N>
inline
auto sample_variance_n(I f, N n) { 
	//precondition: [f, n) is a valid range.
	return variance_helper_n(f, n) / (n - 1); 
}

template <Iterator I, Integral N>
inline
auto sample_std_dev_n(I f, N n, ValueType<I> mean) {
	//precondition: [f, n) is a valid range.
	return std::sqrt(sample_variance_n(f, n, mean));
}

template <ForwardIterator I, Integral N>
inline
auto sample_std_dev_n(I f, N n) {
	//precondition: [f, n) is a valid range.
	return std::sqrt(sample_variance_n(f, n));
}

template <Container C>
// std::tuple<double, double, double> get_statistics(C& samples) {
auto get_statistics_mutate(C& samples) {
	using namespace std;

	//Note: I think that for the calculation of the Standard Deviation 2 passes over the data are needed. 
	//      The first one for the mean calculation.
	//      The mean is used for the calculation on the second pass.

	// double mean = accumulate(begin(samples), end(samples), 0.0) / samples.size();
	// double mean = accumulate(begin(samples), end(samples), 0.0) / size(samples);
	auto mean = mean_c(samples);

	// auto ssd = sample_std_dev_n(begin(samples), samples.size());
	auto ssd = sample_std_dev_n(begin(samples), size(samples), mean);

	// sort(begin(samples), end(samples));
	// double median = samples[samples.size() / 2];
	auto median = median_c(samples);

	return make_tuple(mean, ssd, median);
}

template <Container C>
inline
auto get_statistics_copy(C samples) {
	return get_statistics_mutate(samples);
}



// double combine_std_dev_1(int n1, double u1, double s1, int n2, double u2, double s2) {

// 	auto t1 = n1 * n1 * s1 * s1;
// 	auto t2 = n2 * n2 * s2 * s2;
// 	auto t3 = n2      * s1 * s1;
// 	auto t4 = n2      * s2 * s2;
// 	auto t5 = n1      * s1 * s1;
// 	auto t6 = n1      * s2 * s2;

// 	auto t7 = n1 * n2 * s1 * s1;
// 	auto t8 = n1 * n2 * s2 * s2;

// 	auto t9 = n1 * n2 * (u1 - u2) * (u1 - u2);

// 	auto num = t1 + t2 - t3 - t4 - t5 - t6 + t7 + t8 + t9;
// 	auto den = (n1 + n2 - 1) * (n1 + n2);

// 	auto res = std::sqrt(num / den);
// 	return res;
// }

// double combine_std_dev_2(int n1, double u1, double s1, int n2, double u2, double s2) {

// 	auto uc = (n1 * u1 + n2 * u2) / (n1 + n2);

// 	auto t1 = (n1 - 1) * s1 * s1;
// 	auto t2 = n1 * u1 * u1;

// 	auto t3 = (n2 - 1) * s2 * s2;
// 	auto t4 = n2 * u2 * u2;
	
// 	auto t5 = (n1 + n2) * uc * uc;


// 	auto num = t1 + t2 + t3 + t4 - t5;
// 	auto den = n1 + n2 - 1;

// 	auto res = std::sqrt(num / den);
// 	return res;
// }

}} /*tao::algorithm*/

#endif /*TAOCPP_BENCHMARK_STATISTICS_HPP_*/
