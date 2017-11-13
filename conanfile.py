from conans import ConanFile, CMake
# import os

class TaoCppAlgorithm(ConanFile):
    name = "algorithm"
    version = "0.1"
    license = "http://www.boost.org/users/license.html"
    url = "https://github.com/tao-cpp/algorithm"
    description = "C++ general purpose algorithms library"

    settings = None

    def build(self):
         #empty too, nothing to build in header only

    generators = "cmake"
    # exports_sources = "src/*", "CMakeLists.txt", "cmake/*", "bitprim-node-cintConfig.cmake.in", "include/*", "test/*", "console/*"
    # package_files = "build/lbitprim-node-cint.so"
    # build_policy = "missing"


    # def imports(self):
    #     self.copy("*.h", "./deps/include/bitprim", "include/bitprim")
    #     self.copy("*.hpp", dst="./deps/include/bitprim", src="include/bitprim")
    #     self.copy("*.lib", dst="./deps/lib", src="lib")
    #     self.copy("*.a", dst="./deps/lib", src="lib")
    #     self.copy("*.dylib", dst="./deps/lib", src="lib")
    #     self.copy("*.so", dst="./deps/lib", src="lib")
    #     self.copy("*.dll", dst="./deps/lib", src="lib")

