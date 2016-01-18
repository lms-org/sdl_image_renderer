#include "sdl_image_renderer.h"
#include "sdl_service/sdl_service.h"

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

void Window::render() {
    SDL_RenderPresent(m_renderer);
}

SDL_Renderer* Window::getRenderer() {
    return m_renderer;
}

bool SdlImageRenderer::initialize() {
    if(! getService<sdl_service::SdlService>("sdl_service")) {
        logger.error() << "sdl_image_renderer requires sdl_service to be enabled";
        return false;
    }

    m_window.reset(new Window(config().get<std::string>("title", getName()), 640, 480));

    for(const std::string &channel : config().getArray<std::string>("channels")) {
        Layer layer;
        layer.image = readChannel<lms::imaging::Image>(channel);
        layer.texture = nullptr;
        m_layers.push_back(layer);
    }

    return true;
}

bool SdlImageRenderer::deinitialize() {
    m_window.release();
    return true;
}

bool SdlImageRenderer::cycle() {
    m_window->clear();

    for(Layer &layer : m_layers) {
        if(layer.image->format() != lms::imaging::Format::BGRA) {
            logger.error() << "Image has unexpected format " << layer.image->format();
            continue;
        }

        if(layer.image->width() == 0 || layer.image->height() == 0) {
            logger.error() << "Image has zero dimension (" << layer.image->width()
                           << "," << layer.image->height() << ")";
            continue;
        }

        if(layer.texture == nullptr) {
            layer.texture = SDL_CreateTexture(m_window->getRenderer(), SDL_PIXELFORMAT_ARGB8888,
                SDL_TEXTUREACCESS_STREAMING, layer.image->width(), layer.image->height());
            SDL_SetTextureBlendMode(layer.texture, SDL_BLENDMODE_BLEND);
        }

        // write image to GPU
        SDL_UpdateTexture(layer.texture, nullptr, layer.image->data(),
            layer.image->width() * sizeof(uint32_t));

        SDL_RenderCopy(m_window->getRenderer(), layer.texture, nullptr, nullptr);
    }
    m_window->render();

    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        // ignore
    }

    return true;
}
