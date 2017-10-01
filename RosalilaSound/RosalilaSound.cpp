#include "RosalilaSound.h"

void RosalilaSound::init()
{
    music=NULL;
    if( Mix_OpenAudio( 44100, AUDIO_S16SYS/*MIX_DEFAULT_FORMAT*/, 2, 512 ) == -1 )
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
    if(sounds.find(variable)==sounds.end())
    {
        sounds[variable]=Mix_LoadWAV(value.c_str());
        if(sounds[variable])
        {
            rosalila()->utility->writeLogLine("Sound " + value + " loaded");
        }else
        {
            rosalila()->utility->writeLogLine("Could not load sound " + value);
        }
    }
}

int RosalilaSound::playSound(std::string variable, int channel, int loops, int panning, bool uses_camera)
{
    if(!soundExists(variable))
    {
        rosalila()->utility->writeLogLine("Error: "+variable+" sound does not exists.");
        return -1;
    }

    if(sounds[variable]!=NULL)
    {
        int return_channel = Mix_PlayChannel( channel, sounds[variable], loops);
        if(panning != 0)
        {
            if(uses_camera)
                panning -= rosalila()->graphics->camera_x;
            if(panning>rosalila()->graphics->screen_width)
                panning = rosalila()->graphics->screen_width;
            if(panning<0)
                panning=0;
            int left = panning*254/rosalila()->graphics->screen_width;
            Mix_SetPanning(return_channel, 254 - left, left);
        }

        return return_channel;
    }

    return -1;
}

void RosalilaSound::playMusic(std::string path,int loops)
{
    stopMusic();
    rosalila()->utility->writeLogLine("Playing music: "+path);
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

int RosalilaSound::getMusicVolume()
{
  return Mix_VolumeMusic(-1);
}

void RosalilaSound::setMusicVolume(int volume)
{
  Mix_VolumeMusic(volume);
}

void RosalilaSound::fadeMusicVolume(int volume, int velocity)
{
  this->target_fade_volume = volume;
  this->target_fade_velocity = velocity;
}

void RosalilaSound::update()
{
  int new_volume;
  if(rosalila()->sound->getMusicVolume() < target_fade_volume)
  {
    new_volume = this->getMusicVolume() + target_fade_velocity;
    if(new_volume > 128)
      new_volume = 128;
  }else
  {
    new_volume = this->getMusicVolume() - target_fade_velocity;
    if(new_volume < 0)
      new_volume = 0;
  }
  this->setMusicVolume(new_volume);
}
