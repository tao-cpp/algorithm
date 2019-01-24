// Copyright Fernando Pelliccioni 2016-2019
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

// #include "measurements.hpp"
// using namespace std;

#include <cstddef>
#include <vector>



#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <iomanip>

#include "timer.hpp"
#include "type_description.hpp"
// #include "algorithm.h"
// #include "merge_inplace.h"
// #include "merge.h"
// #include "sort_ph.h"
// #include "sort_akraft.h"
// #include "sort_bert.h"
// #include "sort_rjernst.h"

#include <tao/algorithm/iota.hpp>
#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/iterator.hpp>
#include <tao/algorithm/type_attributes.hpp>

#include <tao/algorithm/sorting/pdqsort.h>

template <typename I>
void print_range(I f, I l) {
	while (f != l) {
		std::cout << *f << " ";
		++f;
	}
	std::cout << '\n';
}

template <ForwardIterator I> 
    requires(Writable<I>)
inline
void iota_void(I f, I l) {
    tao::algorithm::iota(f, l);
}

template <BidirectionalIterator I>
using gen_ptr = void (*)(I, I);

template <TotallyOrdered T>
using sort_ptr = void (*)(T*, T*);

template <BidirectionalIterator I>
inline
// const char* function_name(void (*gen)(I, I)) {
const char* function_name(gen_ptr<I> gen) {	
	void (*generator[])(I, I) = {
		iota_void<I>,
		tao::algorithm::hill<I>,
		tao::algorithm::valley<I>,
		tao::algorithm::reverse_iota<I>, 
		tao::algorithm::random_iota<I>
	};
	
	const char* names[] = {
		"iota",
		"hill",
		"valley",
		"reverse_iota",
		"random_iota"
	};
	size_t number_of_generators = sizeof(generator)/sizeof(generator[0]);
	size_t index = std::find(generator, generator + number_of_generators, gen) - generator;
	if (index >= number_of_generators) return "unknown data generation ";
	return names[index];
}

template <TotallyOrdered T>
// double time_sort(T* f, T* l, void (*sort)(T*, T*), T* buffer, size_t count) {
double time_sort(T* f, T* l, sort_ptr<T> sort, T* buffer, size_t count) {
	timer t;
	t.start();
	size_t i = count;
	while (i--) {
		std::copy(buffer, buffer + std::distance(f, l), f);
		sort(f, l);
		// if (!std::is_sorted(f, l)) {
		// 	std::cerr << "*** SORT FAILED! ***\n";
		// 	return 0;
		// }
	}
	return t.stop();
} 

template <TotallyOrdered T, Generator G>
void test_sort(size_t min_size, size_t max_size, G gen) {

	time_t now = time(0);

	std::cout << "Sorting " << type_description(T(0)) 
  			  << " from " << min_size << " up to " << max_size 
			  << " elements" << " generated with " << function_name(gen) 
			  <<" at: " << asctime(localtime(&now));

  
	void (*f_pointers[])(T*, T*) = {
		std::sort<T*>
		, std::stable_sort<T*>
		, pdqsort<T*>
		// ,sort_inplace_with_buffer<T*>
		// ,sort_1_64th<T*>
		// ,sort_ph<T*>
		// ,sort_akraft<T*>
		// ,sort_bert<T*>
		// ,sort_rjernst<T*>
	};

	size_t number_of_sorts = sizeof(f_pointers) / sizeof(f_pointers[0]);

	int colwidth = 10;

	std::cout << std::right 
	          << std::setw(12) << " size" 
			  << std::setw(colwidth) << "sort" 
			  << std::setw(colwidth) << "stable" 
			  << std::setw(colwidth) << "pdqsort" 
			  
			//   << std::setw(colwidth) << "merge" 
			//   << std::setw(colwidth) << "1_64th" 
			//   << std::setw(colwidth) << "ph"
			//   << std::setw(colwidth) << "akraft"
			//   << std::setw(colwidth) << "bert"
			//   << std::setw(colwidth) << "rjernst"
			  << '\n';

	for (size_t array_size(min_size); array_size <= max_size; array_size *= 2) {    
		size_t const n = max_size / array_size;
		std::vector<T> vec(array_size);
		gen(&*vec.begin(), (&*vec.begin()) + vec.size());
		std::vector<T> tmp(vec.begin(), vec.end());
		std::cout << std::setw(12) << array_size;    
		for (size_t i(0); i < number_of_sorts; ++i) {
			size_t bound = max_size;
			double time = time_sort(&*tmp.begin(), (&*tmp.begin()) + tmp.size(), f_pointers[i], &*vec.begin(), n);
			time /= double(array_size * n);
			std::cout << std::setw(colwidth) << std::fixed << std::setprecision(0) << time;
		}
		std::cout << '\n';
	}
}

//-------------------------------------------------------
constexpr size_t min_size(8);
constexpr size_t max_size(2 * 1024 * 1024);

int main() {
	test_sort<double>(min_size, max_size, tao::algorithm::random_iota<double*>); 
}
