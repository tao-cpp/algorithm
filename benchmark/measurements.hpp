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


