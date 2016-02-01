set(SOURCES
    "src/sdl_image_renderer.cpp"
    "src/interface.cpp"
)

set(HEADERS
    "include/sdl_image_renderer.h"
)

include_directories(
        include
        /usr/local/include
)
add_library(sdl_image_renderer MODULE ${SOURCES} ${HEADERS})
target_link_libraries(sdl_image_renderer PRIVATE lmscore imaging sdl_service SDL2)
