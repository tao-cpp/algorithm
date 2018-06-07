// Copyright Fernando Pelliccioni 2016-2018
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)



// mkdir build
// cd build
// cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-std=c++14" ..
// make tests
// make benchmarks


#include <tao/algorithm/shift.hpp>

#include "measurements.hpp"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <tuple>

#include <vector>
#include <list>
#include <forward_list>

using namespace std;



template <Container C, Integral N>
void measure_and_print_shift_right(C const& copy, N n) {
	using tao::algorithm::shift_right;

	C data;

	auto t = measure_nullary<1000>(
		[&]() {data = copy;},
		[&]() {return shift_right(begin(data), end(data), n);});

	cout << '\t' << '\t'
        << n << ";" 
        << get<0>(t) << ";" 
        << get<1>(t) << ";" 
        << get<2>(t) << endl;	
}


// template <Container C>
// void measure_and_print_shift_right(C const& copy) {
// 	using tao::algorithm::shift_right;

// 	auto cat = iterator_category_str<IteratorType<C>>();
// 	C data;

// 	auto size = std::distance(begin(copy), end(copy));

// 	for (size_t i{0}; i < size; ++i) {
// 		auto t = measure_nullary<1000>(
// 			[&]() {data = copy;},
// 			[&]() {return shift_right(begin(data), end(data), i);});

// 		cout << "shift_right     ;" << cat << ";" 
// 		 					        << i << ";" 
// 		                            << data.size() << ";" 
// 		                            << get<0>(t) << ";" 
// 		                            << get<1>(t) << ";" 
// 		                            << get<2>(t) << endl;	
// 	}
// }


template <Container C>
void measure_and_print_shift_right(C const& copy) {
	auto size = std::distance(begin(copy), end(copy));

	measure_and_print_shift_right(copy, 0);
	measure_and_print_shift_right(copy, 1);
	measure_and_print_shift_right(copy, size / 4);
	measure_and_print_shift_right(copy, size / 2);
	measure_and_print_shift_right(copy, size * 3 / 4);
	measure_and_print_shift_right(copy, size);
}


template <Container C>
void print(C const& c) {
	for (auto const& x : c) {
		cout << x << ", ";
	}
	cout << '\n';
}


/*
Categorías (ortogonales) a medir:
	
	- Algoritmo (sort, rotate, shift, binary_search)
	- Tipo de Contenedor (IteratorCategory: forward, bidirectional, random_access,...)
	- Tamaño del elemento (value_type: int32_t, int64_t)
	- Tamaño del contenedor
	- COSAS A MEDIR ESPECÍFICAS DEL ALGORITMO (ej: en shift_right hay un n).
*/






template <Integral N, template <typename T, typename A = std::allocator<T>> class Cont, Procedure P>
void run_mearurements_generic(std::string const& algo_name, size_t min_size, size_t max_size, P p) {

	using random_eng_t = random_int_generator<N>;
	random_eng_t eng;

	// auto cat = iterator_category_str(data_random_access);
	auto cat = iterator_category_str<IteratorType<Cont<N>>>();
	auto type_name = builtin_type_name<N>();


	cout << algo_name << ";" 
		 << cat << ";" 
		 << type_name << ";"
		 << endl;	


	size_t array_size = min_size;
	while (array_size <= max_size) {
		
		auto cont = random_container_creator<Cont>(array_size, eng);

		cout << '\t'
			 << "data size: " << array_size << ";" 
			 << endl;	


		p(cont);

		array_size *= 2;
	}
}



template <template <typename T, typename A = std::allocator<T>> class Cont, Procedure P>
void run_mearurements_all_value_types(std::string const& algo_name, size_t min_size, size_t max_size, P p) {
	run_mearurements_generic< int8_t,  Cont>(algo_name, min_size, max_size, p);
	run_mearurements_generic<uint8_t,  Cont>(algo_name, min_size, max_size, p);
	run_mearurements_generic< int16_t, Cont>(algo_name, min_size, max_size, p);
	run_mearurements_generic<uint16_t, Cont>(algo_name, min_size, max_size, p);
	run_mearurements_generic< int32_t, Cont>(algo_name, min_size, max_size, p);
	run_mearurements_generic<uint32_t, Cont>(algo_name, min_size, max_size, p);
	run_mearurements_generic< int64_t, Cont>(algo_name, min_size, max_size, p);
	run_mearurements_generic<uint64_t, Cont>(algo_name, min_size, max_size, p);
}

template <Procedure P>
void run_mearurements_all_containers(std::string const& algo_name, size_t min_size, size_t max_size, P p) {
	run_mearurements_all_value_types<std::vector>(algo_name, min_size, max_size, p);
	run_mearurements_all_value_types<std::list>(algo_name, min_size, max_size, p);
	run_mearurements_all_value_types<std::forward_list>(algo_name, min_size, max_size, p);
}



void run_mearurements(size_t min_size, size_t max_size) {

	// run_mearurements<int32_t, std::vector>("shift_right", min_size, max_size, [](auto const& c){
	// 	measure_and_print_shift_right(c);
	// });


	// run_mearurements_all_value_types<std::vector>("shift_right", min_size, max_size, [](auto const& c){
	// 	measure_and_print_shift_right(c);
	// });

	run_mearurements_all_containers("shift_right", min_size, max_size, [](auto const& c){
		measure_and_print_shift_right(c);
	});

}



// // template <typename IntMax, typename IntMin>
// void run_mearurements_a_32(size_t min_size, size_t max_size) {
// 	using random_eng_t = random_int_generator<int32_t>;
// 	random_eng_t eng;

// 	size_t array_size = min_size;
// 	while (array_size <= max_size) {
		
// 		auto data_random_access = random_container_creator<std::vector>(array_size, eng);


// 		// auto cat = iterator_category_str<IteratorType<C>>();
// 		auto cat = iterator_category_str(data_random_access);

// 		cout << "shift_right;" << cat << ";" 
//                             << "int32_t" << ";"
//                             << array_size << ";" 
//                             << endl;	


// 		measure_and_print_shift_right(data_random_access);



// 		// auto data1 = random_container_creator<std::list>(array_size, eng);
// 		// auto data1 = random_container_creator<std::forward_list>(array_size, eng);



// 		// auto data_bidirectional = container_move<std::list>(data_random_access);
// 		// auto data_forward = container_move<std::forward_list>(data_random_access);




// 		// cout << array_size << endl;
// 		// cout << data1.size() << endl;
// 		// cout << data1[0] << endl;
// 		// cout << "-------------------------" << endl;

// 		array_size *= 2;
// 	}
// }



int main() {
    std::cout << std::setprecision(std::numeric_limits<long double>::digits10 + 1);


	
	constexpr size_t min_size = 8;
	// constexpr size_t max_size = 32;
	// constexpr size_t max_size = 1024;
	constexpr size_t max_size = 16 * 1024 * 1024;

	run_mearurements(min_size, max_size);

    return 0;
}
