Rosalila Engine
===============

[![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](https://github.com/Rosalila/RosalilaEngine/blob/master/LICENSE)
[![Travis](https://img.shields.io/travis/Rosalila/RosalilaEngine.svg?logo=travis)](https://travis-ci.org/Rosalila/RosalilaEngine)

A modern game engine for programmers that like doing more than learning.

## Keywords

This engine is being developed with the following values ordered by importance:

1. **Simple**: You only need to understand a few functions to create your game.
2. **Modern**: Use the prebuilt third party API’s support to catch up with the thrends. Read more
3. **Libre**: Free as in freedom, available even for commercial projects. Read more

## Features

* **Graphics**: SDL2 + OpenGL wrapper for 2d graphics
* **Sound**: SDL2 sound wrapper for sound effects and music
* **Input**: SDL2 + Steam Controller API wrapper for keyboard and gamepads
* **Parser**: Json for modern C++ wrapper for JSON parsing
* **Rosalila API**: Steam API wrapper for achievements, stats, leaderboards and user generated content
* **Utility**: Useful stuff that games tend to need such as collision detection, math, seeded random, logs etc...

## Development

Check out our [wiki](https://github.com/Rosalila/RosalilaEngine/wiki).

## Build

### Dependencies

```
sudo apt-get install g++ cmake libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev libsdl2-net-dev libglew-dev
```

### Compile

```
mkdir build
cd build
cmake ..
```
