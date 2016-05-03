# Tao.Algorithm
#
# Copyright Fernando Pelliccioni 2016
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

enable_testing()

add_custom_target(benchmarks ALL
    COMMAND ${CMAKE_CTEST_COMMAND} -C Release --output-on-failure -R "test.+"
    COMMENT "Build and run all the benchmarks."
    DEPENDS ${UNIT_TEST_TARGETS}
)

function(tao_algorithm_add_test name)
    message("name1: " ${name})

    add_executable(test.${name} EXCLUDE_FROM_ALL ${name}.cpp)

    # add_test(NAME test.${name} COMMAND test.${name})
    add_dependencies(benchmarks test.${name})

    message("name2: " ${name})

    # add_custom_command(
    #   OUTPUT out.${name}
    #   COMMAND test.${name}
    #   COMMENT "..."
    #   VERBATIM
    # )    

    add_custom_command(
        TARGET benchmarks
        COMMENT "Run tests"
        POST_BUILD COMMAND test.${name}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}

    message("name3: " ${name})


    set(UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} ${name} PARENT_SCOPE)

    message("UNIT_TEST_TARGETS: " ${UNIT_TEST_TARGETS})
)

endfunction()

file(GLOB_RECURSE TAO_ALGORITHM_TEST_SOURCES
     RELATIVE ${CMAKE_CURRENT_LIST_DIR}
     "*.cpp")

foreach(file IN LISTS TAO_ALGORITHM_TEST_SOURCES)
    string(REGEX REPLACE "\\.cpp$" "" name ${file})
    string(REGEX REPLACE "/" "." name ${name})
    tao_algorithm_add_test(${name})
endforeach()
