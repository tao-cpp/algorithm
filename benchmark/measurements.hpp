#ifndef TAOCPP_BENCHMARK_MEASUREMENTS_HPP_
#define TAOCPP_BENCHMARK_MEASUREMENTS_HPP_

#include <algorithm>
#include <array>
#include <chrono>
#include <numeric>
#include <tuple>

#include <vector>
#include <list>
#include <forward_list>

#include <limits>
#include <numeric>
#include <random>


#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/iterator.hpp>
#include <tao/algorithm/statistics.hpp>
#include <tao/algorithm/type_attributes.hpp>

using namespace std::string_literals;
// using namespace tao::algorithm;

namespace detail {

std::string iterator_category_str(std::input_iterator_tag) {
    return "input_iterator"s;
}

std::string iterator_category_str(std::output_iterator_tag) {
    return "output_iterator"s;
}

std::string iterator_category_str(std::forward_iterator_tag) {
    return "forward_iterator"s;
}

std::string iterator_category_str(std::bidirectional_iterator_tag) {
    return "bidirectional_iterator"s;
}

std::string iterator_category_str(std::random_access_iterator_tag) {
    return "random_access_iterator"s;
}

} // namespace detail

template <Iterator I>
inline
std::string iterator_category_str() {
    return detail::iterator_category_str(IteratorCategory<I>{});
}

template <Container C>
inline
std::string iterator_category_str(C const&) {
	return iterator_category_str<IteratorType<C>>();
}


//---------------------

namespace detail {

std::string builtin_type_name(int8_t) {
    return "int8_t"s;
}

std::string builtin_type_name(uint8_t) {
    return "uint8_t"s;
}

std::string builtin_type_name(int16_t) {
    return "int16_t"s;
}

std::string builtin_type_name(uint16_t) {
    return "uint16_t"s;
}

std::string builtin_type_name(int32_t) {
    return "int32_t"s;
}

std::string builtin_type_name(uint32_t) {
    return "uint32_t"s;
}

std::string builtin_type_name(int64_t) {
    return "int64_t"s;
}

std::string builtin_type_name(uint64_t) {
    return "uint64_t"s;
}

} // namespace detail

//TODO: Concept BuiltinType
template <typename T>
inline
std::string builtin_type_name() {
    return detail::builtin_type_name(T{});
}


//---------------------



template <Integral I = int, I From = std::numeric_limits<I>::min(), I To = std::numeric_limits<I>::max()>
struct random_int_generator {
	using value_type = I;
	using dis_t = std::uniform_int_distribution<value_type>;
	static constexpr value_type from = From;
	static constexpr value_type to = To;

	random_int_generator()
		: mt{ rd() }
		, dis{ from, to }  // closed range [1, 1000]		
	{}

	random_int_generator(random_int_generator const&) = default;

	auto operator()() {
		return dis(mt);
	}

	std::random_device rd;
	std::mt19937 mt;
	dis_t dis;
}; // Models: RandomIntGenerator


//---------------------



// template <RandomEngine E>
// std::vector<typename E::value_type> random_array_creator(size_t max, E & eng) {
// 	std::vector<typename E::value_type> array;
// 	array.reserve(max);

// 	// cout << "to: " << to << endl;

// 	for (size_t i{0}; i < max; ++i) {
// 		auto s = eng();
// 		array.emplace_back(s);
// 	}

// 	return array;
// }


//---------------------
template <typename T>
inline
void reserve(std::vector<T>& c, SizeType<std::vector<T>> cap) {
	c.reserve(cap);
}

template <typename T>
inline
void reserve(std::list<T> const&, SizeType<std::list<T>>) {
	//do nothing
}

template <typename T>
inline
void reserve(std::forward_list<T> const&, SizeType<std::forward_list<T>>) {
	//do nothing
}

//---------------------

template <typename T>
inline
void push_back_or_front(std::vector<T>& c, T const& x) {
	c.push_back(x);
}

template <typename T>
inline
void push_back_or_front(std::list<T>& c, T const& x) {
	c.push_back(x);
}

template <typename T>
inline
void push_back_or_front(std::forward_list<T>& c, T const& x) {
	c.push_front(x);
}

//---------------------

template <typename T>
inline
auto size_or_distance(std::vector<T> const& c) {
	// ambiguous call in MSVC 14 that implements std::size
	// using tao::algorithm::size;
	// return size(c);
	return tao::algorithm::size(c);
}

template <typename T>
inline
auto size_or_distance(std::list<T> const& c) {
	// ambiguous call in MSVC 14 that implements std::size
	// using tao::algorithm::size;
	// return size(c);
	return tao::algorithm::size(c);
}

template <typename T>
inline
auto size_or_distance(std::forward_list<T> const& c) {
	return std::distance(std::begin(c), std::end(c));
}

//---------------------

template <typename T>
inline
auto back_or_front_inserter(std::vector<T>& c) {
	return std::back_inserter(c);
}

template <typename T>
inline
auto back_or_front_inserter(std::list<T>& c) {
	return std::back_inserter(c);
}

template <typename T>
inline
auto back_or_front_inserter(std::forward_list<T>& c) {
	return std::front_inserter(c);
}

//---------------------




template <template <typename T, typename A = std::allocator<T>> class Target, Container Source>
inline
Target<typename Source::value_type> container_move(Source& c) {
	Target<typename Source::value_type> res;
	reserve(res, size_or_distance(c));
	// res.insert(std::end(res), std::make_move_iterator(std::begin(c)), std::make_move_iterator(std::end(c)));
	std::move(std::begin(c), std::end(c), back_or_front_inserter(res));
	return res;
}

template <template <typename T, typename A = std::allocator<T>> class Target, Container Source>
inline
Target<typename Source::value_type> container_copy(Source const& c) {
	Target<typename Source::value_type> res;
	reserve(res, size_or_distance(c));
	// res.insert(std::end(res), std::begin(c), std::end(c));
	std::copy(std::begin(c), std::end(c), back_or_front_inserter(res));
	return res;
}

//---------------------


template <template <typename T, typename A = std::allocator<T>> class C, RandomEngine E>
C<typename E::value_type> random_container_creator(size_t max, E & eng) {
	C<typename E::value_type> cont;
	reserve(cont, max);

	for (size_t i{0}; i < max; ++i) {
		auto s = eng();
		push_back_or_front(cont, s);
	}

	return cont;
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



template <size_t Count, Procedure P1, Procedure P2> 
auto amortize(P1 warm_up, P2 test) {
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

template <size_t Samples, size_t AmortizeCount, Procedure P1, Procedure P2> 
auto measure_nullary_amortized_2(P1 warm_up, P2 test) {
	using tao::algorithm::get_statistics_mutate;

	constexpr size_t ConcreteSamples = Samples * 0.8;
	std::array<int64_t, ConcreteSamples> samples_list;

	for (size_t i{0}; i < size_t(Samples * 0.2); ++i) {
		amortize<AmortizeCount>(warm_up, test);
	}

	for (size_t i{0}; i < ConcreteSamples; ++i) {
		auto ns = amortize<AmortizeCount>(warm_up, test);
		samples_list[i] = ns;
	}

	return get_statistics_mutate(samples_list);
}


template <size_t Samples, size_t AmortizeCount, Procedure P1, Procedure P2, Procedure P3>
auto measure_nullary_amortized(P1 setUp, P2 warm_up, P3 test) {
	using tao::algorithm::get_statistics_mutate;

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

	return get_statistics_mutate(samples_list);
}

template <size_t Samples, Procedure P1, Procedure P2>
auto measure_nullary(P1 setUp, P2 test) {
	using namespace std;
	using namespace std::chrono;
	using tao::algorithm::get_statistics_mutate;

	constexpr size_t ConcreteSamples = Samples * 0.8;
	std::array<int64_t, ConcreteSamples> samples_list;

	for (size_t i{0}; i < size_t(Samples * 0.2); ++i) {
		setUp();
		test();
	}

	for (size_t i{0}; i < ConcreteSamples; ++i) {
		setUp();
		// auto ns = test();

		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		test();
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		auto ns = duration_cast<nanoseconds>(t2 - t1).count();

		samples_list[i] = ns;
	}

	return get_statistics_mutate(samples_list);
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


