#ifndef TAOCPP_BENCHMARK_MEASUREMENTS_HPP_
#define TAOCPP_BENCHMARK_MEASUREMENTS_HPP_

#include <algorithm>	//for std::sort
#include <array>
#include <chrono>
#include <numeric>		//for std::accumulate
#include <vector>
#include <tuple>

#include <iostream>		//REMOVE THIS


#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/type_attributes.hpp>


// //Concepts emulation
// #define Function typename
// #define Container typename

using real_type = double;
//using real_type = float;

template <Iterator I, Integer N>
auto mean_n(I f, N n) {
	using T = ValueType<I>;
	return std::accumulate(f, std::next(f, n), T(0)) / n;
}

template <ForwardIterator I, Integer N>
auto variance_helper_n(I f, N n) {
	using T = ValueType<I>;

	auto m = mean_n(f, n);
	T s(0);
	std::for_each(f, std::next(f, n), [&s, m](T x) { 
		s += (x - m) * (x - m); });

	return s;
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

template <typename I>
real_type population_variance_n(I f, size_t n) {
	auto s = variance_helper_n(f, n);
	return s / n;
}

//real_type sample_variance(std::vector<real_type> const& data) {
//	auto s = variance_helper(data);
//	return s / (data.size() - 1);
//}

template <typename I>
real_type sample_variance_n(I f, size_t n) {
	auto s = variance_helper_n(f, n);
	return s / (n - 1);
}

template <typename I>
real_type sample_std_dev_n(I f, size_t n) {
	auto s2 = sample_variance_n(f, n);
	return std::sqrt(s2);
}


//real_type population_variance_2(std::vector<real_type> const& data) {
//	auto s = variance_helper_2(data);
//	return s / data.size();
//}
//
//real_type sample_variance_2(std::vector<real_type> const& data) {
//	auto s = variance_helper_2(data);
//	return s / (data.size() - 1);
//}


double combine_std_dev_1(int n1, double u1, double s1, int n2, double u2, double s2) {

	auto t1 = n1 * n1 * s1 * s1;
	auto t2 = n2 * n2 * s2 * s2;
	auto t3 = n2      * s1 * s1;
	auto t4 = n2      * s2 * s2;
	auto t5 = n1      * s1 * s1;
	auto t6 = n1      * s2 * s2;

	auto t7 = n1 * n2 * s1 * s1;
	auto t8 = n1 * n2 * s2 * s2;

	auto t9 = n1 * n2 * (u1 - u2) * (u1 - u2);

	auto num = t1 + t2 - t3 - t4 - t5 - t6 + t7 + t8 + t9;
	auto den = (n1 + n2 - 1) * (n1 + n2);

	auto res = std::sqrt(num / den);
	return res;
}

double combine_std_dev_2(int n1, double u1, double s1, int n2, double u2, double s2) {

	auto uc = (n1 * u1 + n2 * u2) / (n1 + n2);

	auto t1 = (n1 - 1) * s1 * s1;
	auto t2 = n1 * u1 * u1;

	auto t3 = (n2 - 1) * s2 * s2;
	auto t4 = n2 * u2 * u2;
	
	auto t5 = (n1 + n2) * uc * uc;


	auto num = t1 + t2 + t3 + t4 - t5;
	auto den = n1 + n2 - 1;

	auto res = std::sqrt(num / den);
	return res;
}



// template <size_t Samples, Function F> 
// double measure_min(F f) { 
// 	using namespace std; 
// 	using namespace std::chrono; 

// 	// static const int num_trials{10}; 
// 	static const milliseconds min_time_per_trial{200}; 

// 	std::array<double, Samples> samples_list; 
// 	volatile decltype(f()) res; // to avoid optimizing f() away 

// 	for (size_t i{0}; i < Samples; ++i) { 
		
// 		size_t runs {0}; 
// 		high_resolution_clock::time_point t2; 
// 		high_resolution_clock::time_point t1 = high_resolution_clock::now();

// 		do { 
// 			res = f(); 
// 			++runs; 
// 			t2 = high_resolution_clock::now(); 
// 		} while (t2 - t1 < min_time_per_trial); 

// 		samples_list[i] = duration_cast<duration<double>>(t2 - t1).count() / runs; 
// 	} 

// 	(void)(res); // var not used warn 

// 	sort(begin(samples_list), end(samples_list)); 
// 	return accumulate(begin(samples_list) + 2, end(samples_list) - 2, 0.0) / (samples_list.size() - 4) * 1E6; 
// }

// template <size_t Samples, Function F> 
// double measure_min_void(F f) { 
// 	using namespace std; 
// 	using namespace std::chrono; 

// 	// static const int num_trials{10}; 
// 	static const milliseconds min_time_per_trial{200}; 

// 	std::array<double, Samples> samples_list; 

// 	for (size_t i{0}; i < Samples; ++i) { 
		
// 		size_t runs {0}; 
// 		high_resolution_clock::time_point t2; 
// 		high_resolution_clock::time_point t1 = high_resolution_clock::now();

// 		do { 
// 			f(); 
// 			++runs; 
// 			t2 = high_resolution_clock::now(); 
// 		} while (t2 - t1 < min_time_per_trial); 

// 		// cout << "runs: " << runs << endl;
// 		// auto ns = duration_cast<nanoseconds>(t2 - t1).count(); 
// 		// auto x1 = duration_cast<nanoseconds>(t2 - t1).count() / runs; 
// 		// auto x2 = duration_cast<duration<double>>(t2 - t1).count() / runs; 
// 		// cout << "ns: " << ns << endl;
// 		// cout << "x1: " << x1 << endl;
// 		// cout << "x2: " << x2 << endl;


// 		samples_list[i] = duration_cast<duration<double>>(t2 - t1).count() / runs; 
// 	} 

// 	sort(begin(samples_list), end(samples_list)); 

// 	auto n = distance(begin(samples_list) + size_t(Samples * 0.2), end(samples_list) - size_t(Samples * 0.2));
// 	//cout << "distance: " << n << endl;


// 	// auto a = accumulate(begin(samples_list) + size_t(Samples * 0.2), end(samples_list) - size_t(Samples * 0.2), 0.0);
// 	// cout << "1E6: " << 1E6 << endl;
// 	// cout << "a: " << a << endl;
// 	// cout << "a / (Samples * 0.6): " << (a / (Samples * 0.6)) << endl;
// 	// cout << "a / (Samples * 0.6) * 1E6: " << (a / (Samples * 0.6) * 1E6) << endl;

// 	return accumulate(begin(samples_list) + size_t(Samples * 0.2), end(samples_list) - size_t(Samples * 0.2), 0.0) / n * 1E6; 
// 	// return accumulate(begin(samples_list) + size_t(Samples * 0.2), end(samples_list) - size_t(Samples * 0.2), 0.0) / (Samples * 0.6) * 1E6; 
// 	// return accumulate(begin(samples_list) + 2, end(samples_list) - 2, 0.0) / (samples_list.size() - 4) * 1E6; 


// }

// template <size_t Samples, Function F1, Function F2> 
// double measure_void_v1(F1 setUp, F2 test) { 
// 	using namespace std; 
// 	using namespace std::chrono; 

// 	// static const int num_trials{10}; 
// 	static const milliseconds min_time_per_trial{200}; 

// 	std::array<double, Samples> samples_list; 

// 	for (size_t i{0}; i < Samples; ++i) { 
// 		setUp();
// 		high_resolution_clock::time_point t1 = high_resolution_clock::now();
// 		test(); 
// 		high_resolution_clock::time_point t2 = high_resolution_clock::now(); 

// 		// auto ns = duration_cast<nanoseconds>(t2 - t1).count(); 
// 		// auto x2 = duration_cast<duration<double>>(t2 - t1).count(); 

// 		// cout << "ns: " << ns << endl;
// 		// cout << "x2: " << x2 << endl;

// 		samples_list[i] = duration_cast<duration<double>>(t2 - t1).count(); 
// 	} 

// 	// cout << "SORTING..." << endl;
// 	//for_each(begin(samples_list), end(samples_list), [](double x) { cout << "trial: " << x << endl;}); 

// 	sort(begin(samples_list), end(samples_list)); 

// 	auto n = distance(begin(samples_list) + size_t(Samples * 0.2), end(samples_list) - size_t(Samples * 0.2));
// 	//cout << "distance: " << n << endl;


// 	// auto a = accumulate(begin(samples_list) + size_t(Samples * 0.2), end(samples_list) - size_t(Samples * 0.2), 0.0);
// 	// cout << "1E6: " << 1E6 << endl;
// 	// cout << "a: " << a << endl;
// 	// cout << "a / (Samples * 0.6): " << (a / (Samples * 0.6)) << endl;
// 	// cout << "a / (Samples * 0.6) * 1E6: " << (a / (Samples * 0.6) * 1E6) << endl;

// 	return accumulate(begin(samples_list) + size_t(Samples * 0.2), end(samples_list) - size_t(Samples * 0.2), 0.0) / n * 1E6; 
// 	// return accumulate(begin(samples_list) + size_t(Samples * 0.2), end(samples_list) - size_t(Samples * 0.2), 0.0) / (Samples * 0.6) * 1E6; 
// 	// return accumulate(begin(samples_list) + 2, end(samples_list) - 2, 0.0) / (samples_list.size() - 4) * 1E6; 


// }


template <Container C>
std::tuple<double, double, double> get_statistics(C& samples) {
	using namespace std;
	// ssd = sample_std_dev(samples_list)
	// m = mean(samples_list)
	//  # mean-median test
	// samples_list.sort()
	// median = samples_list[len(samples_list) // 2];
	// # mmtest = abs(m - median) / max(m, median);
	// # print("mean: ", m, " - median: ", median, " - mean-median test: ", mmtest)

	// return [m, ssd, median];


	auto ssd = sample_std_dev_n(begin(samples), samples.size());

	//cout << "sample standard deviation " << ssd << endl;
	//cout << "samples.size() " << samples.size() << endl;
	//cout << "ConcreteSamples " << samples.size() << endl;

	double mean = accumulate(begin(samples), end(samples), 0.0) / samples.size();


	sort(begin(samples), end(samples));
	double median = samples[samples.size() / 2];


	// for (auto& x : samples ) {
	// 	cout << "x: " << x << endl;
	// }


	// auto mmtest = std::abs(mean - median) / max(mean, median);
	// cout << "mean: " << mean << " - median: " << median << " - mean-median test: " << mmtest << endl;

	// return {mean, ssd, median};
	return make_tuple(mean, ssd, median);
}


template <size_t Count, Function F1, Function F2> 
auto amortize(F1 warm_up, F2 test) {
	using namespace std; 
	using namespace std::chrono;

	warm_up();

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	for (size_t i{0}; i < Count; ++i) {
		test();
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	auto ns = duration_cast<nanoseconds>(t2 - t1).count();
	return ns / Count;
}

template <size_t Samples, size_t AmortizeCount, Function F1, Function F2> 
auto measure_nullary_amortized_2(F1 warm_up, F2 test) {

	constexpr size_t ConcreteSamples = Samples * 0.8;
	std::array<int64_t, ConcreteSamples> samples_list;

	for (size_t i{0}; i < size_t(Samples * 0.2); ++i) {
		amortize<AmortizeCount>(warm_up, test);
	}

	for (size_t i{0}; i < ConcreteSamples; ++i) {
		auto ns = amortize<AmortizeCount>(warm_up, test);
		samples_list[i] = ns;
	}

	return get_statistics(samples_list);
}


template <size_t Samples, size_t AmortizeCount, Function F1, Function F2, Function F3>
auto measure_nullary_amortized(F1 setUp, F2 warm_up, F3 test) {
	constexpr size_t ConcreteSamples = Samples * 0.8;
	std::array<int64_t, ConcreteSamples> samples_list;

	for (size_t i{0}; i < size_t(Samples * 0.2); ++i) {
		setUp();
		amortize<AmortizeCount>(warm_up, test);
	}

	for (size_t i{0}; i < ConcreteSamples; ++i) {
		setUp();
		auto ns = amortize<AmortizeCount>(warm_up, test);
		samples_list[i] = ns;
	}

	return get_statistics(samples_list);
}

template <size_t Samples, Function F1, Function F2>
auto measure_nullary(F1 setUp, F2 test) {
	constexpr size_t ConcreteSamples = Samples * 0.8;
	std::array<int64_t, ConcreteSamples> samples_list;

	for (size_t i{0}; i < size_t(Samples * 0.2); ++i) {
		setUp();
		test();
	}

	for (size_t i{0}; i < ConcreteSamples; ++i) {
		setUp();
		auto ns = test();
		samples_list[i] = ns;
	}

	return get_statistics(samples_list);
}





// def measure_nullary(samples, setUp, test): 

// 	concrete_samples = int(samples * 0.8)
// 	samples_list = []

// 	for i in range(0, int(samples * 0.2)):
// 		setUp()
// 		test()

// 	for i in range(0, concrete_samples):
// 		setUp()
// 		ns = test()
// 		samples_list.append(ns)
// 		# print("ns: ", ns)

// 	return get_statistics(samples_list)

// def measure_unary(data, samples, setUp, test): 

// 	concrete_samples = int(samples * 0.8)
// 	samples_list = []
// 	data_copy = list(data)

// 	for i in range(0, int(samples * 0.2)):
// 		setUp()
// 		data = list(data_copy)
// 		test(data)

// 	for i in range(0, concrete_samples):
// 		setUp()
// 		data = list(data_copy)
// 		ns = test(data)
// 		samples_list.append(ns)
// 		# print("ns: ", ns)

// 	return get_statistics(samples_list)



// Concepts emulation undef
#undef Function


#endif /*TAOCPP_BENCHMARK_MEASUREMENTS_HPP_*/


