#include "Rosalila.h"

int main()
{
  rosalila()->init("../assets/config.json");

  Image* image = rosalila()->graphics->getTexture("../assets/image.png");
  Image* image2 = rosalila()->graphics->getTexture("../assets/x.png");

  while(true)
  {
    rosalila()->graphics->draw2DImage
    (   image,
        image->getWidth(),image->getHeight(),
        0,0,
        1.0,
        0.0,
        false,
        false,
        Color(255, 255, 255,255));
    
    rosalila()->graphics->draw2DImage
    (   image2,
        image2->getWidth(),image2->getHeight(),
        100,100,
        1.0,
        0.0,
        false,
        false,
        Color(255, 255, 255,255));

    rosalila()->update();
  }
  return 0;
}