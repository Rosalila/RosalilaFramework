Rosalila Engine
===============

Rosalila engine is a free as in freedom game engine written in C++.

#Core values

This engine is being developed with the following values ordered by importance:

1. **Simplicity**: Easy to learn, easy to code
2. **Adaptability**: Adaptable to different platforms, libraries, APIs etc...
3. **Performance**: Hardware accelerated graphics and not much overhead overall

#Features

* **Graphics**: SDL + OpenGL wrapper for 2d graphics
* **Sound**: SDL sound wraper for sound effects and music
* **Input**: SDL + Steam Controller API wraper for keyboard and gamepads
* **Parser**: TinyXML wraper for XML parsing
* **Rosalila** API: Steam API wraper for achievements, stats, leaderboards and user generated content

#Dependencies

##Instalation

> apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev
> yum install SDL-devel SDL_mixer-devel SDL_image-devel SDL_ttf-devel

##Linkage

In Code::Blocks: "Linker settings" -> "Other linker options"
Add the following:

Linux:

-lGL
-lSDL2
-lSDL2_image
-lSDL2_ttf
-lSDL2_mixer

Windows:

-lOpenGL32
-lfreeglut
-lmingw32 -lSDL2main -lSDL2
-lSDL2_image
-lSDL2_mixer
-lSDL2_ttf
