from conans import ConanFile, CMake

    
class TaoCppAlgorithm(ConanFile):
    name = "algorithm"
    # version = "0.1"
    # version = get_version(0, 1)
    license = "http://www.boost.org/users/license.html"
    url = "https://github.com/tao-cpp/algorithm"
    description = "C++ general purpose algorithms library"

    settings = "os", "compiler", "arch", "build_type"

    # exports_sources = "include/*", "CMakeLists.txt", "example.cpp"
    exports_sources = "CMakeLists.txt", "include/*", "test/*", "benchmark/*", "src/*"
    # exports_sources = "include/*"
    no_copy_source = True


    # settings = None
    # generators = "cmake"

    


    # def build(self):
    #      #empty too, nothing to build in header only
    #     pass

    # exports_sources = "src/*", "CMakeLists.txt", "cmake/*", "bitprim-node-cintConfig.cmake.in", "include/*", "test/*", "console/*"
    # package_files = "build/lbitprim-node-cint.so"
    # build_policy = "missing"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        # cmake.install()
        cmake.test()

    def package(self):
        self.copy("*.h", dst="include", src="include")
        self.copy("*.hpp", dst="include", src="include")
        self.copy("*.ipp", dst="include", src="include")

    def package_id(self):
        self.info.header_only()

    # def deploy(self):
    #     self.copy("*.hpp")
    #     # self.copy_deps("*.dll") # copy from dependencies



