from conans import ConanFile, CMake
    
class TaoCppAlgorithm(ConanFile):
    name = "algorithm"
    license = "MIT"
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

    def configure(self):
        # self.output.info("****** configure ******* self.options.tests: %s" % (self.options.tests,))

        # If header only, the compiler, etc, does not affect the package!
        if not self.options.tests:
            # self.output.info("****** CLEARING THE SETTINGS *******")
            self.settings.clear()

    def build(self):
        if self.options.tests:
            # self.output.info("****** build ******* self.options.tests: %s" % (self.options.tests,))
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



