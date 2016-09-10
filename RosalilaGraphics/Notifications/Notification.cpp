#include "Notification.h"

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

    int current_velocity;

    if(y==target_y)
        current_velocity = 0;

    if(frame<duration)
        current_velocity = -velocity;
    else
        current_velocity = velocity;

    y+=current_velocity;

    if(y<target_y && current_velocity<0)
        y=target_y;
}

bool Notification::isFinished()
{
    return y>initial_y && frame>=duration;
}
