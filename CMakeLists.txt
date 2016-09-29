cmake_minimum_required(VERSION 2.8.12)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(SOURCES
    "src/sdl_image_renderer.cpp"
    "src/interface.cpp"
)

set(HEADERS
    "include/sdl_image_renderer.h"
)
#set compiler flags
if((${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang") OR (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU"))
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wreturn-type -Wpedantic ")
endif()

include_directories(include)
add_library(sdl_image_renderer MODULE ${SOURCES} ${HEADERS})
target_link_libraries(sdl_image_renderer PRIVATE lmscore ${CONAN_LIBS})
