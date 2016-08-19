#include "RosalilaSound.h"

Sound::Sound()
{
    music=NULL;

    writeLogLine("Initializing SLD sound engine.");
    int channels=10;
    if( Mix_OpenAudio( 44100, AUDIO_S16SYS/*MIX_DEFAULT_FORMAT*/, 2, 4096 ) == -1 )
    {
        writeLogLine("Failed initializing sound engine. :(");
        return;
    }
    Mix_AllocateChannels(100);
    writeLogLine("Success!");
    current_music="";
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
    //if(sounds.find(variable)==sounds.end())
        sounds[variable]=Mix_LoadWAV(value.c_str());
}

int Sound::playSound(std::string variable, int channel, int loops)
{
    if(!soundExists(variable))
    {
        writeLogLine("Error: "+variable+" sound does not exists.");
        return -1;
    }

    if(sounds[variable]!=NULL)
    {
        //Mix_HaltChannel(channel);
        return Mix_PlayChannel( channel, sounds[variable], loops);
        //Mix_PlayChannel( -1, sounds[variable], 0 );
    }
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

string Sound::getCurrentMusic()
{
    return current_music;
}
