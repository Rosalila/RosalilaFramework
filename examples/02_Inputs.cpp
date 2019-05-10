#include "Rosalila.h"

int main()
{
  rosalila()->init("../assets/config.json");

  Image* image = rosalila()->graphics->getTexture("../assets/image.png");

  int x = 0;
  int y = 0;
  int player_1 = 0;
  bool mirror_image = false;
  while(true)
  {
    rosalila()->graphics->draw2DImage
    (   image,
        image->getWidth(),image->getHeight(),
        x,y,
        1.0,
        0.0,
        mirror_image,
        Color(255, 255, 255,255));
    
    if(rosalila()->receiver->isDown(player_1, "left"))
      x--;
    if(rosalila()->receiver->isDown(player_1, "right"))
      x++;
    if(rosalila()->receiver->isDown(player_1, "up"))
      y--;
    if(rosalila()->receiver->isDown(player_1, "down"))
      y++;
    
    if(rosalila()->receiver->isPressed(player_1, "a"))
      mirror_image = !mirror_image;

    rosalila()->update();
  }
  return 0;
}