# sdl_image_renderer
Render images into a window created with SDL2. The images will be copied on
top of each other with alpha blending. Rendering is performed in the given
order, the last image will be on top.

## Data channels
- All images provided by config `channels`

## Config
- **title** - Window title, defaults to module name
- **channels** - List of image channels to render

## Dependencies
- sdl_service
- imaging
- SDL2

### Ubuntu
```
sudo apt-get install libsdl2-2.0-0 libsdl2-dev
```

### OS X (Homebrew)
```
brew install sdl2
```
