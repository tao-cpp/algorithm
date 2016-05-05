// Clang: clang++ -O3 -std=c++1y mult_total.cpp
// GCC:   g++ -Wall -Wextra -pedantic -I%BOOST_ROOT% -O3 -std=c++1y mult_total.cpp
// MSVC:  



#include "measurements.hpp"
#include "tools.hpp"
#include <iostream>

#include <boost/multiprecision/cpp_int.hpp>
// #include "boost_multiprecision_cpp_int_ext.hpp"

using namespace std;
using namespace boost;
using namespace boost::multiprecision;


using int101_t = number<cpp_int_backend<101, 101, signed_magnitude, unchecked, void>>;
using int201_t = number<cpp_int_backend<201, 201, signed_magnitude, unchecked, void>>;
//2 ^ 201 / 2 - 1 = 1606938044258990275541962092341162602522202993782792835301375    -> 61 chars

#define VectorOfInts typename
#define VectorOfPairs typename
#define VectorOfTriples typename
#define Integer typename


//-------------------------------------------------------


void mult_original_1() {
	int a = 5, b = 10;
	int c = a * b;
}


void mult_original_100() {
	int a = 5, b = 10;

	for (size_t i{0}; i < 100000; ++i) {
	    int c = a * b;
	}
}


//--------------------------

// template <typename IntMax, typename IntMin>
// inline
// int64_t mult_a(std::vector<std::pair<IntMax, IntMin>>& c) {
template <VectorOfPairs V>
inline
int64_t mult_a(V& c) {
	using namespace std;
	using namespace std::chrono;

	auto f = std::begin(c);
	auto m = f + c.size() * 0.2;
	auto l = std::end(c);

	// cout << "(*f).first: " << (*f).first << endl;
	// cout << "distance: " << distance(m, l) << endl;


	while (f != m) {
		auto a = (*f).first;
		auto b = (*f).second;
		//(*f).first = static_cast<IntMax>(a) * b;
		(*f).first = a * b;
		++f;
	}

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	while (m != l) {
		auto a = (*m).first;
		auto b = (*m).second;
		//(*m).first = static_cast<IntMax>(a) * b;
		(*m).first = a * b;
		++m;
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto ns = duration_cast<nanoseconds>(t2 - t1).count();

	// cout << "ns: " << ns << endl;

	return ns;
}



template <VectorOfPairs V>
inline
int64_t mult_a_warm_up(V& c) {

	auto f = std::begin(c);
	auto m = f + c.size() * 0.2;
	// auto l = std::end(c);

	while (f != m) {
		auto a = (*f).first;
		auto b = (*f).second;
		//(*f).first = static_cast<IntMax>(a) * b;
		(*f).first = a * b;
		++f;
	}

	return 0;
}


template <VectorOfPairs V>
inline
int64_t mult_a_without_measurements(V& c) {
	auto f = std::begin(c);
	auto m = f + c.size() * 0.2;
	auto l = std::end(c);

	while (m != l) {
		auto a = (*m).first;
		auto b = (*m).second;
		//(*m).first = static_cast<IntMax>(a) * b;
		(*m).first = a * b;
		++m;
	}

	return 0ll;
}


//--------------------------

template <VectorOfPairs V1, VectorOfInts V2>
inline
int64_t mult_b(V1 const& input, V2& output) {
	using namespace std;
	using namespace std::chrono;

	size_t f = 0;
	size_t m = input.size() * 0.2;
	size_t l = input.size();

	while (f != m) {
		auto a = input[f].first;
		auto b = input[f].second;
		output[f] = a * b;
		++f;
	}

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	while (m != l) {
		auto a = input[m].first;
		auto b = input[m].second;
		output[m] = a * b;
		++m;
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto ns = duration_cast<nanoseconds>(t2 - t1).count();

	return ns;
}



template <VectorOfPairs V1, VectorOfInts V2>
inline
int64_t mult_b_warm_up(V1 const& input, V2& output) {

	size_t f = 0;
	size_t m = input.size() * 0.2;
	// size_t l = input.size();

	while (f != m) {
		auto a = input[f].first;
		auto b = input[f].second;
		output[f] = a * b;
		++f;
	}

	return 0;
}


template <VectorOfPairs V1, VectorOfInts V2>
inline
int64_t mult_b_without_measurements(V1 const& input, V2& output) {
	// size_t f = 0;
	size_t m = input.size() * 0.2;
	size_t l = input.size();

	while (m != l) {
		auto a = input[m].first;
		auto b = input[m].second;
		output[m] = a * b;
		++m;
	}

	return 0ll;
}



// def mult_b(input, output):

// 	f = 0
// 	l = len(input);
// 	m = f + int(l * 0.2);

// 	while f != m:
// 		a = input[f][0]
// 		b = input[f][1]
		
// 		# print(output[f]);

// 		output[f] = a * b

// 		f += 1

// 	t1 = hrc.nanoseconds_since_epoch()

// 	while m != l: 
// 		a = input[m][0]
// 		b = input[m][1]

// 		output[m] = a * b
// 		m += 1;

// 	t2 = hrc.nanoseconds_since_epoch()
// 	return t2 - t1

//--------------------------

template <VectorOfTriples V>
inline
int64_t mult_d(V& c) {
	using namespace std;
	using namespace std::chrono;

	auto f = std::begin(c);
	auto m = f + c.size() * 0.2;
	auto l = std::end(c);

	while (f != m) {
		auto a = get<0>(*f);
		auto b = get<1>(*f);
		get<2>(*f) = a * b;
		++f;
	}

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	while (m != l) {
		auto a = get<0>(*m);
		auto b = get<1>(*m);
		get<2>(*m) = a * b;
		++m;
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto ns = duration_cast<nanoseconds>(t2 - t1).count();

	return ns;
}



// def mult_d(data):

// 	f = 0
// 	l = len(data);
// 	m = f + int(l * 0.2);

// 	while f != m:
// 		a = data[f][0]
// 		b = data[f][1]
		
// 		# data[f][2] = a * b		# tuples are immutables in Python
// 		data[f] = [a, b, a * b]		# workaround

// 		f += 1

// 	# print("------------------------------------")

// 	t1 = hrc.nanoseconds_since_epoch()

// 	while m != l: 
// 		a = data[m][0]
// 		b = data[m][1]

// 		# data[m][2] = a * b			# tuples are immutables in Python
// 		data[m] = [a, b, a * b]		# workaround

// 		m += 1;

// 	t2 = hrc.nanoseconds_since_epoch()
// 	return t2 - t1


//--------------------------


template <VectorOfInts V1, VectorOfInts V2>
inline
int64_t mult_e(V1& input_output, V2 const& input) {
	using namespace std;
	using namespace std::chrono;

	size_t f = 0;
	size_t m = input.size() * 0.2;
	size_t l = input.size();

	while (f != m) {
		auto a = input_output[f];
		auto b = input[f];
		input_output[f] = a * b;
		++f;
	}

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	while (m != l) {
		auto a = input_output[m];
		auto b = input[m];
		input_output[m] = a * b;
		++m;
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto ns = duration_cast<nanoseconds>(t2 - t1).count();

	return ns;
}



template <VectorOfInts V1, VectorOfInts V2>
inline
int64_t mult_e_warm_up(V1& input_output, V2 const& input) {

	size_t f = 0;
	size_t m = input.size() * 0.2;
	// size_t l = input.size();

	while (f != m) {
		auto a = input_output[f];
		auto b = input[f];
		input_output[f] = a * b;
		++f;
	}

	return 0;
}


template <VectorOfInts V1, VectorOfInts V2>
inline
int64_t mult_e_without_measurements(V1& input_output, V2 const& input) {
	// size_t f = 0;
	size_t m = input.size() * 0.2;
	size_t l = input.size();

	while (m != l) {
		auto a = input_output[m];
		auto b = input[m];
		input_output[m] = a * b;
		++m;
	}

	return 0ll;
}



// def mult_e(input_output, input):

// 	# print(input_output[0]);

// 	f = 0
// 	l = len(input);
// 	m = f + int(l * 0.2);

// 	while f != m:
// 		a = input_output[f]
// 		b = input[f]
		
// 		input_output[f] = a * b

// 		f += 1
	

// 	t1 = hrc.nanoseconds_since_epoch()

// 	while m != l: 
// 		a = input_output[m]
// 		b = input[m]

// 		input_output[m] = a * b
// 		m += 1;

// 	t2 = hrc.nanoseconds_since_epoch()
// 	return t2 - t1


//--------------------------

template <VectorOfPairs V>
inline
int64_t mult_f(V const& c) {
	using namespace std;
	using namespace std::chrono;

	auto f = std::begin(c);
	auto m = f + c.size() * 0.2;
	auto l = std::end(c);

	while (f != m) {
		auto a = (*f).first;
		auto b = (*f).second;
		auto prod = a * b;
		++f;
	}

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	while (m != l) {
		auto a = (*m).first;
		auto b = (*m).second;
		auto prod = a * b;
		++m;
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto ns = duration_cast<nanoseconds>(t2 - t1).count();

	// cout << "ns: " << ns << endl;

	return ns;
}


template <VectorOfPairs V>
inline
int64_t mult_f_without_measurements(V const& c) {
	auto f = std::begin(c);
	auto m = f + c.size() * 0.2;
	auto l = std::end(c);

	while (m != l) {
		auto a = (*m).first;
		auto b = (*m).second;
		auto prod = a * b;
		++m;
	}

	return 0ll;
}


//-------------------------------------------------------

void measure_and_print_mult_original_1() {

	auto t = measure_nullary_amortized_2<1000, 1000>(
					[]() {},
					[]() { mult_original_1(); });

	cout << "mult_original_1            ;1000;1000;" << get<0>(t) << ";" << get<1>(t) << ";" << get<2>(t) << endl;
}

void measure_and_print_mult_original_100() {

	auto t = measure_nullary_amortized_2<1000, 1000>(
					[]() {},
					[]() { mult_original_100(); });

	cout << "mult_original_100          ;1000;1000;" << get<0>(t) << ";" << get<1>(t) << ";" << get<2>(t) << endl;
}




//---------------------------------

template <VectorOfPairs V>
void measure_and_print_mult_a_32(V const& copy) {

	V data;

	// version original, sin amortizacion

	auto t = measure_nullary<1000>(
		[&]() {data = copy;},
		[&]() {return mult_a(data); });

	cout << "mult_a                     ;" << data.size() << ";" << get<0>(t) << ";" << get<1>(t) << ";" << get<2>(t) << endl;	



	//---------------------------------


	// versiones con amortizacion

	// auto t = measure_nullary_amortized<1000, 100>(
	//  []() {},
	// 	[&]() {data = copy;},
	// 	[&]() {return mult_a(data); });

	// auto t = measure_nullary_amortized<1000, 100>(
	// 	[]() {},
	// 	[&]() {data = copy;},
	// 	[&]() {return mult_a_without_measurements(data); });




	// auto t = measure_nullary_amortized<1000, 100>(
	// 	[&]() { return mult_a_warm_up(data); },
	// 	[&]() {data = copy;},
	// 	[&]() {return mult_a_without_measurements(data); });



	//---------------------------------

	// //Versión dinámica...
	// if ( copy.size() == 16 * 1024) {
	// 	auto t = measure_nullary_amortized<1000, 1000>(
	// 		[&]() { return mult_a_warm_up(data); },
	// 		[&]() {data = copy;},
	// 		[&]() {return mult_a_without_measurements(data); });

	// 	cout << "mult_a                     ;" << data.size() << ";" << get<0>(t) << ";" << get<1>(t) << ";" << get<2>(t) << endl;

	// } else if ( copy.size() >= 2 * 1024 * 1024) {
	// 	auto t = measure_nullary<1000>(
	// 		[&]() {data = copy;},
	// 		[&]() {return mult_a(data); });

	// 	cout << "mult_a                     ;" << data.size() << ";" << get<0>(t) << ";" << get<1>(t) << ";" << get<2>(t) << endl;
	// } else {

	// 	auto t = measure_nullary_amortized<1000, 100>(
	// 		[&]() { return mult_a_warm_up(data); },
	// 		[&]() {data = copy;},
	// 		[&]() {return mult_a_without_measurements(data); });

	// 	cout << "mult_a                     ;" << data.size() << ";" << get<0>(t) << ";" << get<1>(t) << ";" << get<2>(t) << endl;
	// }


	// cout << "data[500]: " << data[500].first << endl;

}


template <VectorOfPairs V>
void measure_and_print_mult_a_101(V const& copy) {

	// auto data = copy;
	V data;

	// version original, sin amortizacion

	// auto t = measure_nullary<1000>(
	// 	[&]() {data = copy;},
	// 	[&]() {return mult_a(data); });

	// cout << "mult_a                     ;" << data.size() << ";" << get<0>(t) << ";" << get<1>(t) << ";" << get<2>(t) << endl;	


	//Versión dinámica...
	if ( copy.size() >= 128 * 1024) {
		auto t = measure_nullary<1000>(
			[&]() {data = copy;},
			[&]() {return mult_a(data); });

		cout << "mult_A                     ;" << data.size() << ";" << get<0>(t) << ";" << get<1>(t) << ";" << get<2>(t) << endl;
	} else {

		auto t = measure_nullary_amortized<1000, 100>(
			[&]() { return mult_a_warm_up(data); },
			[&]() {data = copy;},
			[&]() {return mult_a_without_measurements(data); });

		cout << "mult_a                     ;" << data.size() << ";" << get<0>(t) << ";" << get<1>(t) << ";" << get<2>(t) << endl;
	}
}



//---------------------------------

template <VectorOfInts V>
void clear_vector(V& v) { 

	auto f = std::begin(v);
	auto l = std::end(v);

	while (f != l) {
		*f = 0;
		++f;
	}
}

template <Integer IntMax, VectorOfPairs V1>
void measure_and_print_mult_b_32(V1 const& input) {

	vector<IntMax> output(input.size());

	// version original, sin amortizacion

	// auto t = measure_nullary<1000>(
	// 	[&]() {clear_vector(output);},
	// 	[&]() {return mult_b(input, output); });

	// cout << "mult_b                     ;" << input.size() << ";" << get<0>(t) << ";" << get<1>(t) << ";" << get<2>(t) << endl;	



	//Versión dinámica 2...
	if ( input.size() < 64 * 1024) {

		auto t = measure_nullary_amortized<1000, 100>(
			[&]() { return mult_b_warm_up(input, output); },
			[&]() {clear_vector(output);},
			[&]() {return mult_b_without_measurements(input, output); });

		cout << "mult_b                     ;" << input.size() << ";" << get<0>(t) << ";" << get<1>(t) << ";" << get<2>(t) << endl;

	} else if ( input.size() >= 2 * 1024 * 1024) {

		auto t = measure_nullary<1000>(
			[&]() {clear_vector(output);},
			[&]() {return mult_b(input, output); });

		cout << "mult_b                     ;" << input.size() << ";" << get<0>(t) << ";" << get<1>(t) << ";" << get<2>(t) << endl;
	} else {

		auto t = measure_nullary_amortized<1000, 100>(
			[&]() { return mult_b_warm_up(input, output); },
			[&]() {clear_vector(output);},
			[&]() {return mult_b_without_measurements(input, output); });

		cout << "mult_b                     ;" << input.size() << ";" << get<0>(t) << ";" << get<1>(t) << ";" << get<2>(t) << endl;
	}	
}



//---------------------------------

template <typename IntMax, typename IntMin>
auto pairs_to_triples(vector<pair<IntMin, IntMin>> const& c) {
	vector<tuple<IntMin, IntMin, IntMax>> res;
	res.reserve(c.size());

	for (auto&& x : c) 
		res.emplace_back(get<0>(x), get<1>(x), 0);

	return res;
}


template <VectorOfPairs V>
void measure_and_print_mult_d(V const& copyP) {
	// version original, sin amortizacion

	// auto dataT = pairs_to_triples(copyP);

	// auto t = measure_nullary<1000>(
	// 	[&]() {data = copy;},
	// 	[&]() {return mult_d(data); });

	// cout << "mult_d                     ;" << copyP.size() << ";" << get<0>(t) << ";" << get<1>(t) << ";" << get<2>(t) << endl;	
}



// template <VectorOfInts V1, VectorOfInts V2>
// void measure_and_print_mult_e(V1& input_output_copy, V2 const& input) {
// 	// version original, sin amortizacion

// 	V1 input_output;

// 	auto t = measure_nullary<1000>(
// 		[&]() {input_output = input_output_copy;},
// 		[&]() {return mult_e(input_output, input); });

// 	cout << "mult_e                     ;" << input.size() << ";" << get<0>(t) << ";" << get<1>(t) << ";" << get<2>(t) << endl;	
// }


//---------------------------------

template <VectorOfInts V1, VectorOfInts V2>
void measure_and_print_mult_e_32(V1& input_output_copy, V2 const& input) {


	// version original, sin amortizacion
	// V1 input_output;

	// auto t = measure_nullary<1000>(
	// 	[&]() {input_output = input_output_copy;},
	// 	[&]() {return mult_e(input_output, input); });

	// cout << "mult_e                     ;" << input.size() << ";" << get<0>(t) << ";" << get<1>(t) << ";" << get<2>(t) << endl;	


	// //Versión dinámica 1 ...
	// if ( input.size() >= 2 * 1024 * 1024) {
	// 	V1 input_output;

	// 	auto t = measure_nullary<1000>(
	// 		[&]() {input_output = input_output_copy;},
	// 		[&]() {return mult_e(input_output, input); });		

	// 	cout << "mult_E                     ;" << input.size() << ";" << get<0>(t) << ";" << get<1>(t) << ";" << get<2>(t) << endl;	
	// } else {

	// 	V1 input_output = input_output_copy;

	// 	auto t = measure_nullary_amortized<1000, 100>(
	// 		[&]() { return mult_e_warm_up(input_output, input); },
	// 		[&]() {input_output = input_output_copy;},
	// 		[&]() {return mult_e_without_measurements(input_output, input); });

	// 	cout << "mult_e                     ;" << input.size() << ";" << get<0>(t) << ";" << get<1>(t) << ";" << get<2>(t) << endl;	
	// }





	//Versión dinámica 2...
	if ( input.size() < 64 * 1024) {

		V1 input_output = input_output_copy;

		auto t = measure_nullary_amortized<1000, 1000>(
			[&]() { return mult_e_warm_up(input_output, input); },
			[&]() {input_output = input_output_copy;},
			[&]() {return mult_e_without_measurements(input_output, input); });

		cout << "mult_e                     ;" << input.size() << ";" << get<0>(t) << ";" << get<1>(t) << ";" << get<2>(t) << endl;

	} else if ( input.size() >= 2 * 1024 * 1024) {

		V1 input_output;

		auto t = measure_nullary<1000>(
			[&]() {input_output = input_output_copy;},
			[&]() {return mult_e(input_output, input); });

		cout << "mult_E                     ;" << input.size() << ";" << get<0>(t) << ";" << get<1>(t) << ";" << get<2>(t) << endl;
	} else {

		V1 input_output = input_output_copy;

		auto t = measure_nullary_amortized<1000, 100>(
			[&]() { return mult_e_warm_up(input_output, input); },
			[&]() {input_output = input_output_copy;},
			[&]() {return mult_e_without_measurements(input_output, input); });

		cout << "mult_é                     ;" << input.size() << ";" << get<0>(t) << ";" << get<1>(t) << ";" << get<2>(t) << endl;
	}
}


//---------------------------------


template <VectorOfPairs V>
void measure_and_print_mult_f_32(V const& data) {
	// version original, sin amortizacion

	// auto t = measure_nullary<1000>(
	// 	[]() {},
	// 	[&]() {return mult_f(data); });

	auto t = measure_nullary_amortized<1000, 1000>(
		[]() {},
		[]() {},
		[&]() {return mult_f_without_measurements(data); });

	cout << "mult_f                     ;" << data.size() << ";" << get<0>(t) << ";" << get<1>(t) << ";" << get<2>(t) << endl;	
}


template <VectorOfPairs V>
void measure_and_print_mult_f_101(V const& data) {
	// version original, sin amortizacion

	auto t = measure_nullary<1000>(
		[]() {},
		[&]() {return mult_f(data); });

	cout << "mult_f                     ;" << data.size() << ";" << get<0>(t) << ";" << get<1>(t) << ";" << get<2>(t) << endl;	
}


//---------------------------------

template <typename IntMax, typename IntMin>
void run_mearurements_a_32(size_t min_size, size_t max_size) {
	using random_big = random_bigint_generator<int32_t>;
	random_big eng;
	random_pair_generator<random_big> pair_eng(eng);

	size_t array_size = min_size;
	while (array_size <= max_size) {
		// auto data1 = random_array_creator<pair<int64_t, int32_t>>(array_size, pair_eng);
		auto data1 = random_array_creator<pair<IntMax, IntMin>>(array_size, pair_eng);
		// auto data2 = copy_convert_vector(data1);


		// measure_and_print_mult_a_32(data1);
		measure_and_print_mult_b_32<IntMax>(data1);
		// measure_and_print_mult_f_32(data1);

		cout << "-------------------------" << endl;

		array_size *= 2;
	}
}

template <typename IntMax, typename IntMin>
void run_mearurements_a_101(size_t min_size, size_t max_size) {
	using random_big = random_bigint_generator<int32_t>;
	random_big eng;
	random_pair_generator<random_big> pair_eng(eng);

	size_t array_size = min_size;
	while (array_size <= max_size) {
		auto data1 = random_array_creator<pair<IntMax, IntMin>>(array_size, pair_eng);

		// measure_and_print_mult_a_101(data1);
		// measure_and_print_mult_f_101(data1);

		cout << "-------------------------" << endl;

		array_size *= 2;
	}
}


template <typename IntMax, typename IntMin>
void run_mearurements_b_32(size_t min_size, size_t max_size) {
	using random_big = random_bigint_generator<int32_t>;
	random_big eng;

	size_t array_size = min_size;
	while (array_size <= max_size) {
		auto input_a = random_array_creator<IntMax>(array_size, eng);
		auto input_b = random_array_creator<IntMin>(array_size, eng);

		measure_and_print_mult_e_32(input_a, input_b);

		cout << "-------------------------" << endl;

		array_size *= 2;
	}
}


void run_mearurements_c() {
	measure_and_print_mult_original_1();
	measure_and_print_mult_original_100();
}

//-------------------------------------------------------


int main(int /*argc*/, char const * /*argv*/[]) {


	cout.precision(30);
	std::cout << "starting..." << endl;

	//size_t min_size = 8;
	size_t min_size = 16 * 1024;
	// size_t min_size = 8 * 1024 * 1024;

	// size_t max_size = 16 * 1024;
	size_t max_size = 8 * 1024 * 1024;
	//size_t max_size = 16 * 1024 * 1024;		// Out of memory for mult_big_vector_hot

	cout << "Types int64_t and int32_t ---------------------------------------\n";
	run_mearurements_a_32<int64_t, int32_t>(min_size, max_size);
	// run_mearurements_b_32<int64_t, int32_t>(min_size, max_size);


	// cout << "Types int201_t and int101_t ---------------------------------------\n";
	// run_mearurements_a_101<int201_t, int101_t>(min_size, max_size);

	cin.get();
	return 0;



	// run_mearurements_c();


	return 0;
}





// Amortizado a 100 ejecuciones:
// mult_a                     ;8388608;16834170.5874999985098838806152;330429.589597245503682643175125;16788002

// Sin Amortizacion:
// mult_a                     ;8388608;13431195.25;440874.761947301914915442466736;13509500

// Sin Mediciones internas al algormitmo y amortizado a 100 ejecuciones:
// mult_a                     ;8388608;13747670.5099999997764825820923;287356.488154414109885692596436;13684576

// Sin Mediciones internas al algormitmo y amortizado a 100 ejecuciones - Con WarmUp:
// mult_a                     ;8388608;13527951.2624999992549419403076;190674.424968340608756989240646;13589779



// --------------------------------------------
// Medir:
//		Tiempo de ejecucion
//		Consumo de memoria
//		Consumo de bateria
//		Consumo energético / Costo
//		

//		Transladar el tiempo de ejecución al consumo eléctrico
//		Medir/estimar (para un data center) cuanto es el consumo energético a medida que incrementa el tiempo de ejecución.
//			Comparar el costo energético con el costo de programación (sueldo de programadores de perfil NO-Performance contra Perfil-Performance).
//			

// --------------------------------------------

