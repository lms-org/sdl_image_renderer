# sdl_image_renderer
Render images into a window created with SDL2. The images will be copied on
top of each other with alpha blending. Rendering is performed in the given
order, the last image will be on top.

## Data channels
- All images provided by config `channels`

## Config
- **title** - Window title, defaults to module name
- **channels** - List of image channels to render
- **key.down.\<keycode\>.command** - Messaging command to trigger when someone
  presses a key
- **key.up.\<keycode\>.content** - Messaging content to trigger when someone
  releases a key
- **key.down.\<keycode\>.repeat** - Set to false, if repeated keys should be
  ignored, otherwise they will be accepted. Defaults to true.

```xml
<module>
    <name>sdl_image_renderer</name>
    <config>
        <title>My Window</title>
        <channels>IMAGE2,IMAGE3,IMAGE</channels>
        <key.down.79>
            <command>nav</command>
            <content>right</content>
        </key.down.79>
        <key.down.80>
            <command>nav</command>
            <content>left</content>
        </key.down.80>
        <key.down.81>
            <command>nav</command>
            <content>down</content>
        </key.down.81>
        <key.down.82>
            <command>nav</command>
            <content>up</content>
        </key.down.82>
        <key.down.44>
            <repeat>false</repeat>
            <command>nav</command>
            <content>space</content>
        </key.down.44>
    </config>
</module>
```

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
