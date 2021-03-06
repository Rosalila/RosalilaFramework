#include "RosalilaGraphics/Notifications/Notification.h"

Notification::Notification(Image* image, int x, int y, int target_y, int duration)
{
    this->frame = 0;
    this->image = image;
    this->x = x;
    this->y = y;
    this->target_y = target_y;
    this->duration = duration;
    this->initial_y = y;
    this->velocity = 3;
}

void Notification::update()
{
    if(y<=target_y)
        frame++;

    if(frame<duration)
        y-= (int)velocity;
    else
        y+= (int)velocity;

    if(y<target_y)
        y=target_y;
}

bool Notification::isFinished()
{
    return y>initial_y && frame>=duration;
}
