from conans import ConanFile, CMake

    
class TaoCppAlgorithm(ConanFile):
    name = "algorithm"
    # license = "http://www.boost.org/users/license.html"
    url = "https://github.com/tao-cpp/algorithm"
    description = "C++ general purpose algorithms library"

    settings = "os", "compiler", "arch", "build_type"

    exports_sources = "CMakeLists.txt", "include/*", "test/*", "benchmark/*", "src/*"
    no_copy_source = True
    # build_policy = "missing"

    options = {
        "tests": [True, False],
    }

    default_options = {
        "tests": False,
    }    

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
        self.info.options.tests = "ANY"

    # def deploy(self):
    #     self.copy("*.hpp")
    #     # self.copy_deps("*.dll") # copy from dependencies



