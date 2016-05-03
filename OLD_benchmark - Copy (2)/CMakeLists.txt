# Tao.Algorithm
#
# Copyright Fernando Pelliccioni 2016
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

enable_testing()

add_custom_target(benchmarks ALL
    COMMAND ${CMAKE_CTEST_COMMAND} -C Debug --output-on-failure -R "test.+"
    COMMENT "Build and run all the benchmarks.")

function(tao_algorithm_add_test name)
    add_executable(test.${name} EXCLUDE_FROM_ALL ${name}.cpp)
    add_test(NAME test.${name} COMMAND test.${name})
    add_dependencies(benchmarks test.${name})
endfunction()

file(GLOB_RECURSE TAO_ALGORITHM_TEST_SOURCES
     RELATIVE ${CMAKE_CURRENT_LIST_DIR}
     "*.cpp")

foreach(file IN LISTS TAO_ALGORITHM_TEST_SOURCES)
    string(REGEX REPLACE "\\.cpp$" "" name ${file})
    string(REGEX REPLACE "/" "." name ${name})
    tao_algorithm_add_test(${name})
endforeach()
