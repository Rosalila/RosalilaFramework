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

### Draw an image

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

### Draw a rectangle

```c++
rosalila()->graphics->drawRectangle(x, y,
                                    width, height,
                                    rotation, red, green, blue, alpha);
```

### Play music and sounds

```c++
rosalila()->sound->playMusic("../assets/music.ogg", music_loops);
rosalila()->sound->addSound("my_sound", "../assets/sound.ogg");

[...]

rosalila()->sound->playSound("my_sound", sound_channel, sound_loops, panning);
```

### Check if an input is down or was pressed

```c++
if(rosalila()->receiver->isDown(player_1, "up"))
{
    // Up was pressed!
}

if(rosalila()->receiver->isPressed(player_1, "a"))
{
    // a was pressed!
}
```

### Unlock an achievement

```c++
rosalila()->api_integrator->unlockAchievement("My achievement");
```

### Get a stat

```c++
int counter = rosalila()->api_integrator->getStat("My counter");
```

### Set a stat

```c++
rosalila()->api_integrator->setStat("My counter",counter + 1);
```

### Submit a leaderboard entry

```c++
TODO
```

### Retrieve leaderboard data

```c++
TODO
```

### Check if player's API is running

```c++
TODO
```

### Trigger a notification

```c++
TODO
```

### Get a random number

```c++
rosalila()->utility->getRandomNumber()
```

### Greyscale effect??

```c++
rosalila()->graphics->grayscale_effect.set(1, 0.003);
```

### Fade music???

```c++
rosalila()->sound->fadeMusicVolume(128, 2);
```

### Set transparency effect???

```c++
rosalila()->graphics->transparency_effect.set(1, 0.03);
```

### Get screen size???

```c++
int width = rosalila()->graphics->screen_width;
int height = rosalila()->graphics->screen_height;
```

### Get a non seeded random number

```c++
int rosalila()->utility->getNonSeededRandomNumber();
```

### Set a random seed???

```c++
rosalila()->utility->setRandomSeed(time(NULL));
```

### Write a log line

```c++
rosalila()->utility->writeLogLine("My log text.");
```

### Read json

```c++
Node* example_root_node = rosalila()->parser->getNodes("example.json");

Node* tag = example_root_node->getNodeByName("Tag");
cout << tag->attributes["a"] << endl;

for(auto array_element : example_root_node->getNodesByName("Array"))
{
  cout << array_element->attributes["value"] << endl;
}
```

## Getting started

Link the Rosalila libraries and include it.

```c++
#include "Rosalila.h"

int main()
{
  rosalila()->init("config.json");
  
  // Initialize stuff here
  
  while(true)
  {
    // Draw, play sounds, check inputs here

    rosalila()->update();
  }

  return 0;
}
```

Also, setup a `font.ttf`, `notification_background.png` and a `config.json` file.

config.json:

```json
{
  "Resolution": 
  {
    "x": "1280",
    "y": "720"
  },
  "ScreenSize": 
  {
    "x": "1280",
    "y": "720"
  },
  "Fullscreen": 
  {
    "enabled": "no"
  },
  "Font": 
  {
    "path": "font.ttf",
    "red": "255",
    "green": "255",
    "blue": "255",
    "size": "30"
  },
  "Notifications": 
  {
    "background_path": "notification_background.png"
  },
  "Inputs": 
  {
    "Player": 
    {
      "number": "0",
      "Type": 
      [
        {
          "name": "keyboard",
          "button": 
          [
            {
              "name": "up",
              "key": "up"
            },            
            {
              "name": "down",
              "key": "down"
            },            
            {
              "name": "left",
              "key": "left"
            },            
            {
              "name": "right",
              "key": "right"
            },            
            {
              "name": "a",
              "key": "z"
            },            
            {
              "name": "b",
              "key": "x"
            }
          ]
        },        
        {
          "name": "gamepad",
          "button": 
          [            
            {
              "name": "up",
              "key": "up"
            },            
            {
              "name": "down",
              "key": "down"
            },            
            {
              "name": "left",
              "key": "left"
            },            
            {
              "name": "right",
              "key": "right"
            },            
            {
              "name": "a",
              "key": "1"
            },            
            {
              "name": "b",
              "key": "2"
            }
          ]
        }
      ]
    }
  }
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
