#ifndef SDL_IMAGE_RENDERER_H
#define SDL_IMAGE_RENDERER_H

#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include <lms/imaging/image.h>
#include <lms/module.h>

class Window {
public:
    Window(std::string const& title, int w, int h);
    ~Window();

    Window(Window&) =delete;


    void clear();
    void setLogicalSize(int w, int h);
    void render();

    SDL_Renderer* getRenderer();
private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
};

struct Layer {
    lms::ReadDataChannel<lms::imaging::Image> image;
    SDL_Texture* texture;
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
    std::vector<Layer> m_layers;
    lms::WriteDataChannel<lms::imaging::Image> m_output;
    bool m_hasOutput;

    void triggerKey(const std::string &type, SDL_Scancode code, bool repeat);
};

#endif // SDL_IMAGE_RENDERER_H
