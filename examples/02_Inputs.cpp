#include "Rosalila.h"

int main()
{
  rosalila()->init("../assets/config.json");

  Image* image = rosalila()->graphics->getImage("../assets/image.png");

  int x = 0;
  int y = 0;
  int player_1 = 0;

  while(true)
  {
    rosalila()->graphics->draw2DImage(image, x, y);
    
    if(rosalila()->receiver->isDown(player_1, "left"))
      x--;
    if(rosalila()->receiver->isDown(player_1, "right"))
      x++;
    if(rosalila()->receiver->isDown(player_1, "up"))
      y--;
    if(rosalila()->receiver->isDown(player_1, "down"))
      y++;
    
    if(rosalila()->receiver->isPressed(player_1, "a"))
      image->horizontal_flip = !image->horizontal_flip;

    rosalila()->update();
  }
  return 0;
}