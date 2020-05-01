#include "Rosalila.h"

int main()
{
  rosalila()->init("../assets/config.json");

  Image* image = rosalila()->graphics->getImage("../assets/rosalila.png");

  //rosalila()->graphics->transparency_effect.set(0.0 /*Target greyscale percentage*/,
  //                                         0.001 /*Delta change speed*/);

  int frame = 0;
  while(true)
  {
    image->color_filter.red = (frame * 2) % 512;
    image->color_filter.green = (frame * 4) % 512;
    rosalila()->graphics->drawImage(image, 0, 0);

    frame++;
    rosalila()->update();
  }
  return 0;
}