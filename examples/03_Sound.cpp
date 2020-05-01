#include "Rosalila.h"

int main()
{
  rosalila()->init("../assets/config.json");
  Image* image = rosalila()->graphics->getImage("../assets/image.png");

  bool music_is_playing = true;
  int player_1 = 0;
  int panning = rosalila()->graphics->screen_width / 2;
  int music_loops = 0; // infinite
  int sound_loops = 0;
  int sound_channel = -1; // pick any channel
  rosalila()->sound->playMusic("../assets/music.ogg", music_loops);
  rosalila()->sound->addSound("my_sound", "../assets/sound.ogg");
  
  while(true)
  {
    // Toggle music
    if(rosalila()->receiver->isPressed(player_1, "a"))
    {
      if(music_is_playing)
      {
        rosalila()->sound->stopMusic();
      }else
      {
        rosalila()->sound->playMusic("../assets/music.ogg", 0);
      }
      music_is_playing = !music_is_playing;
    }

    // Play sound
    if(rosalila()->receiver->isPressed(player_1, "b"))
    {
      rosalila()->sound->playSound("my_sound", sound_channel, sound_loops, panning);
    }

    // Manage volume
    if(rosalila()->receiver->isDown(player_1, "up"))
      rosalila()->sound->setMusicVolume(rosalila()->sound->getMusicVolume() + 1);
    if(rosalila()->receiver->isDown(player_1, "down"))
      rosalila()->sound->setMusicVolume(rosalila()->sound->getMusicVolume() - 1);

    // Manage panning
    if(rosalila()->receiver->isDown(player_1, "left"))
      panning--;
    if(rosalila()->receiver->isDown(player_1, "right"))
      panning++;
    
    // Graphic stuff
    string volume_text = "Volume: ";
    volume_text += rosalila()->utility->toString(rosalila()->sound->getMusicVolume());
    string panning_text = "Panning: ";
    panning_text += rosalila()->utility->toString(panning);
    rosalila()->graphics->drawRectangle(0,0,rosalila()->graphics->screen_width,rosalila()->graphics->screen_height,0,0,0,0,255);
    rosalila()->graphics->drawText(volume_text, 0, 0, true, true);
    rosalila()->graphics->drawText(panning_text, 0, 100, true, true);
    rosalila()->graphics->drawRectangle(panning, 500, 10, 20, 0, 255, 255, 255, 255);
    rosalila()->update();
  }
  return 0;
}