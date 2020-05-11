# Tao.Algorithm
#
# Copyright (c) 2016-2020 Fernando Pelliccioni.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

project(Tao.Algorithm CXX)

# cmake_minimum_required(VERSION 2.8)
cmake_minimum_required(VERSION 3.0)
# list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# add_compile_options(-std=c++14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


##############################################################################
# Setup custom functions to ease the creation of targets
##############################################################################
#   taocpp_algorithm_target_name_for(<output variable> <source file> [ext])
#
# Return the target name associated to a source file. If the path of the
# source file relative from the root of Algorithm is `path/to/source/file.ext`,
# the target name associated to it will be `path.to.source.file`.
#
# The extension of the file should be specified as a last argument. If no
# extension is specified, the `.cpp` extension is assumed.
function(taocpp_algorithm_target_name_for out file)
    if (NOT ARGV2)
    	# message("IF ARGV2: " "${ARGV2}")
        set(_extension ".cpp")
    else()
    	# message("ELSE ARGV2: " "${ARGV2}")
        set(_extension "${ARGV2}")
    endif()

    # file(RELATIVE_PATH _relative ${Boost.Hana_SOURCE_DIR} ${file})
    file(RELATIVE_PATH _relative ${CMAKE_CURRENT_SOURCE_DIR} ${file})
    message("_relative: " ${_relative})

    string(REPLACE "${_extension}" "" _name ${_relative})
    message("_name: " ${_name})
    string(REGEX REPLACE "/" "." _name ${_name})
    message("_name: " ${_name})
    set(${out} "${_name}" PARENT_SCOPE)

    message("out: " ${out})
endfunction()



include_directories(include)

add_subdirectory(benchmark)
add_subdirectory(test)
