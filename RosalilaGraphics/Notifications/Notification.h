#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "../Image.h"

class Notification
{
public:
    Image* image;
    int x;
    int y;
    int target_y;
    int frame;
    int duration;
    int initial_y;
    double velocity;
    Notification(Image* image, int x, int y, int target_y, int duration);
    void update();
    bool isFinished();
};

#endif
