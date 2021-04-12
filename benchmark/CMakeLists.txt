# Tao.Algorithm
#
# Copyright (c) 2016-2021 Fernando Pelliccioni.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.


##############################################################################
# Required packages, gems and caveats
##############################################################################

# find_package( PythonInterp 2.7 REQUIRED )
find_package(PythonInterp 2.7 REQUIRED)
# if(NOT ${PYTHONINTERP_FOUND})
#     message(WARNING "Python >= 2.7 was not found; the benchmarks will be unavailable.")
#     return()
# endif()

# find_package(Ruby 2.1)
# if(NOT ${RUBY_FOUND})
#     message(WARNING "Ruby >= 2.1 was not found; the benchmarks will be unavailable.")
#     return()
# endif()

# # Check for the 'ruby-progressbar' and 'tilt' gems
# execute_process(COMMAND ${RUBY_EXECUTABLE} -r ruby-progressbar -r tilt -e ""
#                 RESULT_VARIABLE __TAOCPP_ALGORITHM_MISSING_GEMS
#                 OUTPUT_QUIET ERROR_QUIET)
# if(${__TAOCPP_ALGORITHM_MISSING_GEMS})
#     message(WARNING
#         "The 'ruby-progressbar' and/or 'tilt' gems were not found; "
#         "the benchmarks will be unavailable."
#         "Use `gem install ruby-progressbar tilt` to install the missing gems.")
#     return()
# endif()


##############################################################################

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(benchmarks COMMENT "Generate all the benchmarks.")

# add_custom_target(travis_compiler_slug USES_TERMINAL
#     COMMAND ${CMAKE_COMMAND} -E echo "travis_compiler_slug: $<LOWER_CASE:${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}>")
# add_custom_target(travis_config_slug USES_TERMINAL
#     COMMAND ${CMAKE_COMMAND} -E echo "travis_config_slug: $<LOWER_CASE:$<CONFIG>>")


file(GLOB_RECURSE TAO_ALGORITHM_BENCHMARKS
     RELATIVE ${CMAKE_CURRENT_LIST_DIR}
     *.cpp)


# message(${TAO_ALGORITHM_BENCHMARKS})

# add_executable(bench_median_of_3X
#     ../src/benchmark/instrumented.cpp
#     inst_median_of_3.cpp
# )

# add_executable(bench_median_of_5
#     ../src/benchmark/instrumented.cpp
#     inst_median_of_5.cpp
# )

# add_executable(bench_median_of_7
#     ../src/benchmark/instrumented.cpp
#     inst_median_of_7.cpp
# )


# add_dependencies(benchmarks bench_median_of_3X)
# add_dependencies(benchmarks bench_median_of_5)
# add_dependencies(benchmarks bench_median_of_7)

foreach(file IN LISTS TAO_ALGORITHM_BENCHMARKS)
    string(REGEX REPLACE "\\.cpp$" "" name ${file})
    string(REGEX REPLACE "/" "." name ${name})

    # message(${name})

    # add_executable(bench.${name} EXCLUDE_FROM_ALL ${name}.cpp)
    add_executable(bench.${name} ${name}.cpp ../src/benchmark/instrumented.cpp)
    # add_test(NAME bench.${name} COMMAND bench.${name})
    add_dependencies(benchmarks bench.${name})



    # boost_hana_target_name_for(target ${benchmark} ".erb.json")
    # get_filename_component(directory "${benchmark}" DIRECTORY)
    # file(GLOB cpp_files ${directory}/*.erb.cpp)
    # configure_file("${benchmark}" "${CMAKE_CURRENT_BINARY_DIR}/${target}.erb.json" @ONLY)

    # file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${target}.measure.cpp "")
    # add_executable(${target}.measure EXCLUDE_FROM_ALL ${CMAKE_CURRENT_BINARY_DIR}/${target}.measure.cpp)
    # set_target_properties(${target}.measure PROPERTIES RULE_LAUNCH_COMPILE "${CMAKE_CURRENT_BINARY_DIR}/measure.rb")
    # set_property(TARGET ${target}.measure APPEND PROPERTY INCLUDE_DIRECTORIES "${directory}")
    # add_custom_target(${target}.measure.run COMMAND ${target}.measure)

    # add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${target}.json"
    #     COMMAND ${RUBY_EXECUTABLE} -r tilt -r ${CMAKE_CURRENT_BINARY_DIR}/measure.rb
    #         -e "MEASURE_FILE = '${CMAKE_CURRENT_BINARY_DIR}/${target}.measure.cpp'"
    #         -e "MEASURE_TARGET = '${target}.measure'"
    #         -e "json = Tilt::ERBTemplate.new('${CMAKE_CURRENT_BINARY_DIR}/${target}.erb.json').render"
    #         -e "File.open('${CMAKE_CURRENT_BINARY_DIR}/${target}.json', 'w') { |f| f.write(json) } "
    #     WORKING_DIRECTORY ${directory}
    #     DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${target}.erb.json ${cpp_files}
    #     VERBATIM USES_TERMINAL
    #     COMMENT "Generating dataset for ${target}"
    # )

    # add_custom_target(${target} DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${target}.json")
    # add_dependencies(benchmarks ${target})
endforeach()












# enable_testing()

# add_custom_target(benchmarks ALL
#     COMMAND ${CMAKE_CTEST_COMMAND} -C Release --output-on-failure -R "bench.+"
#     COMMENT "Build and run all the benchmarks."
#     # DEPENDS ${UNIT_TEST_TARGETS}
# )

# function(tao_algorithm_add_test name)
#     message("name1: " ${name})

#     add_executable(bench.${name} EXCLUDE_FROM_ALL ${name}.cpp)
#     # add_test(NAME bench.${name} COMMAND bench.${name})
#     add_dependencies(benchmarks bench.${name})
#     message("name2: " ${name})

#     # add_custom_command(
#     #   OUTPUT out.${name}
#     #   COMMAND bench.${name}
#     #   COMMENT "..."
#     #   VERBATIM
#     # )

#     # add_custom_command(
#     #     TARGET benchmarks
#     #     COMMENT "Run tests"
#     #     POST_BUILD COMMAND bench.${name}
#     #     WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#     # )

#     # message("name3: " ${name})


#     # set(UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} ${name} PARENT_SCOPE)

#     # message("UNIT_TEST_TARGETS: " ${UNIT_TEST_TARGETS})

# endfunction()

# file(GLOB_RECURSE TAO_ALGORITHM_TEST_SOURCES
#      RELATIVE ${CMAKE_CURRENT_LIST_DIR}
#      "*.cpp")

# foreach(file IN LISTS TAO_ALGORITHM_TEST_SOURCES)
#     string(REGEX REPLACE "\\.cpp$" "" name ${file})
#     string(REGEX REPLACE "/" "." name ${name})
#     tao_algorithm_add_test(${name})
# endforeach()
