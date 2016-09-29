from conans import ConanFile, CMake

class SdlImageRendererConan(ConanFile):
    name = "lms_sdl_image_renderer"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    exports = "include/*","src/*","CMakeLists.txt","configs/*","README.md"
    requires = "lms_imaging/1.0@lms/stable","lms/2.0@lms/stable","SDL2_image/2.0.1@lasote/stable","lms_sdl_service/1.0@lms/stable"
    generators = "cmake"

    def build(self):
        cmake = CMake(self.settings)
        self.run('cmake %s %s' % (self.conanfile_directory, cmake.command_line))
        self.run("cmake --build . %s" % cmake.build_config)

    def package(self):
        self.copy("*.h", dst="include",src="include")
