#ifndef SONIDO_H
#define SONIDO_H

#include "../system.h"

#include <string>
#include <vector>

#include <iostream>
using namespace std;

//SDL
#include "SDL2/SDL.h"

#ifdef LINUX
#include <SDL2/SDL_mixer.h>
#endif

#ifdef WINDOWS
#include <SDL2/SDL_mixer.h>
#endif

#ifdef OSX
#include <SDL2_mixer/SDL_mixer.h>
#endif

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
