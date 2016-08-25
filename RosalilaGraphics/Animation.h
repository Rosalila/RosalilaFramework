#ifdef LINUX
#include <SDL2/SDL_image.h>
#endif

#ifdef OSX
#include <SDL2_image/SDL_image.h>
#endif

#include <SDL2/SDL_opengl.h>
#include <stdio.h>

#include "RosalilaGraphics.h"
#include "../RosalilaSound/RosalilaSound.h"
#include "../RosalilaInputs/RosalilaInputs.h"

class Animation
{
    std::vector <Image*> images;
    int x,y;
    int animation_velocity;
    int animation_iteration;
    int current_frame;
public:
    Animation(){}
    Animation(int x,int y,int animation_velocity);
    void addImage(Image*image);
    void render();
};
