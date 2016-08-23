#include "RosalilaSound.h"

void RosalilaSound::init()
{
    music=NULL;
    if( Mix_OpenAudio( 44100, AUDIO_S16SYS/*MIX_DEFAULT_FORMAT*/, 2, 4096 ) == -1 )
    {
        return;
    }
    Mix_AllocateChannels(100);
    current_music="";
}

void RosalilaSound::drop()
{
    //TODO for each chunk
    //Mix_FreeChunk( chunk );
    Mix_FreeMusic(music);
    Mix_CloseAudio();
}
void RosalilaSound::addSound(std::string variable,std::string value)
{
    //if(sounds.find(variable)==sounds.end())
        sounds[variable]=Mix_LoadWAV(value.c_str());
}

int RosalilaSound::playSound(std::string variable, int channel, int loops)
{
    if(!soundExists(variable))
    {
        Rosalila()->Utility->writeLogLine("Error: "+variable+" sound does not exists.");
        return -1;
    }

    if(sounds[variable]!=NULL)
    {
        return Mix_PlayChannel( channel, sounds[variable], loops);
    }

    return -1;
}

void RosalilaSound::playMusic(std::string path,int loops)
{
    stopMusic();
    Rosalila()->Utility->writeLogLine("Playing music: "+path);
    music = Mix_LoadMUS(path.c_str());
    Mix_PlayMusic(music,loops);
    current_music=path;
}

void RosalilaSound::stopMusic()
{
    if(music!=NULL)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(music);
        music=NULL;
    }
}

bool RosalilaSound::soundExists(std::string variable)
{
    map<std::string,Mix_Chunk*>::iterator it = sounds.find(variable);
    return it!=sounds.end();
    return false;
}
