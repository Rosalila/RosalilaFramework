Rosalila Engine
===============
rosalilastudio.com
github.com/rosalila/engine


Build instructions using Code::Blocks:

1. Install the dependencies
---------------------------
* apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev freeglut3-dev
* yum install SDL-devel SDL_mixer-devel SDL_image-devel SDL_ttf-devel freeglut-devel 

2. Link the libraries
---------------------
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


3. Celebrate
------------
Well done, Robert Paulson.
