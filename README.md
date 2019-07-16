Rosalila Engine
===============

[![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](https://github.com/Rosalila/RosalilaEngine/blob/master/LICENSE)
[![Travis](https://img.shields.io/travis/Rosalila/RosalilaEngine.svg?logo=travis)](https://travis-ci.org/Rosalila/RosalilaEngine)

1. **Simple**: You only need to understand a few functions to create your game.
2. **Modern**: Use the prebuilt third party API’s support to catch up with the thrends. Read more
3. **Libre**: Free as in freedom, available even for commercial projects. Read more

## Features

| Feature | Supported |
|----------|------------ |
| Windows / Linux / MacOS | ✔ |
| Flexible OpenGL wrapper | ✔ |
| Siplified sound and music API | ✔ |
| PC, XInput, PS4 and Steam input supported | ✔ |
| Built in JSON parsing | ✔ |
| Steamworks | ✔ |
| Collision detection, math, seeded randoms, logs etc... | ✔ |
| Libre, MIT licensed | ✔ |

## Usage


### Draw images

```c++
Image* image = rosalila()->graphics->getTexture("image.png");

[...]

rosalila()->graphics->draw2DImage
(   image,
    image->getWidth(),image->getHeight(),
    x,y,
    scale,
    rotation,
    flip_horizontally,
    blend_effect,
    color_effects);
```

### Recieve inputs

```c++
if(rosalila()->receiver->isDown(player_1, "up"))
{
    // Up was pressed!
}

if(rosalila()->receiver->isPressed(player_1, "a"))
{
    // a was pressed
}
```

### Read json

```c++
Node* example_root_node = rosalila()->parser->getNodes("example.json");

std::string a = example_root_node->attributes["a"];
Node* tag = example_root_node->getNodeByName("Tag");
std::string subtag = tag->attributes["Subtag"];
vector<Node*> array = example_root_node->getNodesByName("Array");
for(auto array_element : array)
{
  cout << array_element->attributes["value"] << endl;
}
```

## Build

```
# Dependencies
sudo apt-get install g++ cmake libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev libsdl2-net-dev libglew-dev

# Compile
mkdir build
cd build
cmake ..
```
