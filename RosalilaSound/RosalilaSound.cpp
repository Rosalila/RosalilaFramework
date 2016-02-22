#include "RosalilaSound.h"

Sound::Sound()
{
    music=NULL;

    writeLogLine("Initializing SLD sound engine.");
    int channels=10;
    if( Mix_OpenAudio( 88200, AUDIO_S16SYS/*MIX_DEFAULT_FORMAT*/, 2, 2048 ) == -1 )
    {
        writeLogLine("Failed initializing sound engine. :(");
        return;
    }
    Mix_AllocateChannels(30);
    writeLogLine("Success!");
}

void Sound::drop()
{
    //TODO for each chunk
    //Mix_FreeChunk( chunk );
    Mix_FreeMusic(music);
    Mix_CloseAudio();
}
void Sound::addSound(std::string variable,std::string value)
{
    if(sounds.find(variable)==sounds.end())
        sounds[variable]=Mix_LoadWAV(value.c_str());
}
void Sound::playSound(std::string variable)
{
    if(!soundExists(variable))
    {
        writeLogLine("Error: "+variable+" sound does not exists.");
    }

    if(sounds[variable]!=NULL)
    {
        Mix_PlayChannel( 1, sounds[variable], 0 );
    }
}

void Sound::playSound(std::string variable, int channel)
{
    if(!soundExists(variable))
    {
        writeLogLine("Error: "+variable+" sound does not exists.");
    }

    if(sounds[variable]!=NULL)
    {
        Mix_PlayChannel( channel, sounds[variable], 0 );
    }
}

void Sound::playMusic(std::string path)
{
    stopMusic();
    writeLogLine("Playing music: "+path);
    music = Mix_LoadMUS(path.c_str());
    Mix_PlayMusic(music,-1);
}

void Sound::playMusic(std::string path,int loops)
{
    stopMusic();
    writeLogLine("Playing music: "+path);
    music = Mix_LoadMUS(path.c_str());
    Mix_PlayMusic(music,loops);
}

void Sound::stopMusic()
{
    if(music!=NULL)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(music);
        music=NULL;
    }
}

bool Sound::soundExists(std::string variable)
{
    map<std::string,Mix_Chunk*>::iterator it = sounds.find(variable);
    return it!=sounds.end();
    return false;
}
