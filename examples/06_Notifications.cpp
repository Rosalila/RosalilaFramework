#include "Rosalila.h"

int main()
{
  rosalila()->init("../assets/config.json");

  Image* loading_image = rosalila()->graphics->getImage("../assets/loading.png");
  Image* sucess_image = rosalila()->graphics->getImage("../assets/sucess.png");


  
  int frame = 0;
  while(true)
  {

if(frame==30)
  rosalila()->graphics->notification_handler.notifications.push_back(
    new Notification(loading_image,
                        rosalila()->graphics->screen_width / 2 - loading_image->getWidth() / 2,
                        rosalila()->graphics->screen_height,
                        rosalila()->graphics->screen_height - loading_image->getHeight(),
                        99999));

    if(frame == 120)
    {
      rosalila()->graphics->notification_handler.interruptCurrentNotification();

      rosalila()->graphics->notification_handler.notifications.push_back(
        new Notification(sucess_image,
                            rosalila()->graphics->screen_width / 2 - sucess_image->getWidth() / 2,
                            rosalila()->graphics->screen_height,
                            rosalila()->graphics->screen_height - sucess_image->getHeight(),
                            60));
    }

    frame++;
    rosalila()->update();
  }
  return 0;
}