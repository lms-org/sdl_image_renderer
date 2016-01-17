#ifndef SDL_IMAGE_RENDERER_H
#define SDL_IMAGE_RENDERER_H

#include <SDL2/SDL.h>
#include <memory>
#include <lms/imaging/image.h>
#include <lms/module.h>

class Window {
public:
    Window(std::string const& title, int w, int h);
    ~Window();

    Window(Window&) =delete;


    void clear();
    void setLogicalSize(int w, int h);
private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
};

/**
 * @brief LMS module sdl_image_renderer
 **/
class SdlImageRenderer : public lms::Module {
public:
    bool initialize() override;
    bool deinitialize() override;
    bool cycle() override;
private:
    std::unique_ptr<Window> m_window;
    lms::ReadDataChannel<lms::imaging::Image> m_image;
};

#endif // SDL_IMAGE_RENDERER_H
