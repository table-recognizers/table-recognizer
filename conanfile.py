import os
from conan import ConanFile
from conan.tools.cmake import cmake_layout
from conan.tools.cmake import CMake

class FuckingShit(ConanFile):
    generators = "CMakeDeps", "CMakeToolchain"
    settings = "os", "compiler", "build_type", "arch"

    def requirements(self):
        self.requires("opencv/4.9.0")
        self.requires("cpp-httplib/0.15.3")

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
