#include "sdl_image_renderer.h"

Window::Window(std::string const& title, int w, int h) {
    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h,
                                SDL_WINDOW_RESIZABLE);

    if(m_window == nullptr) {
        throw std::runtime_error("SDL_CreateWindow returned NULL");
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, 0);

    if(m_renderer == nullptr) {
        throw std::runtime_error("SDL_CreateRenderer returned NULL");
    }
}

Window::~Window() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}

void Window::clear() {
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
}

void Window::setLogicalSize(int w, int h) {
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(m_renderer, w, h);
}

bool SdlImageRenderer::initialize() {
    m_image = readChannel<lms::imaging::Image>("IMAGE");
    m_window.reset(new Window("My Window", 640, 480));

    return true;
}

bool SdlImageRenderer::deinitialize() {
    m_window.release();
    return true;
}

bool SdlImageRenderer::cycle() {
    if(m_image->format() != lms::imaging::Format::BGRA) {
        logger.error() << "Image has unexpected format " << m_image->format();
        return false;
    }

    if(m_image->width() == 0 || m_image->height() == 0) {
        logger.error() << "Image has zero dimension (" << m_image->width() << "," << m_image->height() << ")";
        return false;
    }

    m_window->clear();

    return true;
}
