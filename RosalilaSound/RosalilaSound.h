#ifndef SONIDO_H
#define SONIDO_H

#include <string>
#include <vector>

#include <iostream>
using namespace std;

//SDL
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"

#include "../RosalilaUtility/RosalilaUtility.h"
#include <map>

class Sound
{
    std::map<std::string,Mix_Chunk*> sounds;
    Mix_Music *music;
public:
    Sound();
    void drop();
    void addSound(std::string variable,std::string value);
    bool soundExists(std::string variable);
    void playSound(std::string variable);
    void playMusic(std::string variable);
    void stopMusic();
};

#endif
