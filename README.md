**Tao.Algorithm**
==================

C++11/14/17 Algorithm Library

## Introduction ##

**Tao.Algorithm** is a **C++11/14/17** library of algorithms collection.
See the documentation at http://tao-cpp.github.io/algorithm/.

## Requirements ##

The library requires a standard conformant implementation of **C++11**; a few
additional features are only available under **C++14**. Some effort was done
to support incomplete language or standard library implementations &mdash;see
[Config](http://tao-cpp.github.io/algorithm/config.html "Config - Tao.Algorithm")
&mdash;. There are no external dependencies.

The library is continuously tested with the following configurations:
[![Build Status](https://travis-ci.org/tao-cpp/algorithm.svg?branch=master)](https://travis-ci.org/tao-cpp/algorithm)
[![Build Status](https://ci.appveyor.com/api/projects/status/github/tao-cpp/algorithm?branch=master&svg=true)](https://ci.appveyor.com/project/K-ballo/algorithm)

 - _Clang_ 3.5, 3.6
 - _GCC_ 4.9, 5
 - _Apple LLVM_ 7.0
 - _MSVC_ 2013, 2015

_[Note:_ Older versions of _Clang_ (3.0+) and _GCC_ (4.6+) are no longer tested,
but should still work; please report any issues if you are using them. Older
versions of _MSVC_ are not supported._]_

## Future Work ##

The following is an incomplete list of pending functionality to be implemented:

 - Explicit control over the type of the discriminator, introduced via a
   `basic_algorithm` class template.

 - Layout optimization. Requires even more flavors of special storage.

---

> Copyright _Fernando Pelliccioni_, 2016
> 
> Distributed under the Boost Software License, Version 1.0. (See accompanying
> file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
