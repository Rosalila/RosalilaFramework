#ifndef SCREEN_SHAKE_EFFECT_H
#define SCREEN_SHAKE_EFFECT_H

#include <stdlib.h>

class ScreenShakeEffect
{
public:
    int magnitude;
    int time;
    int original_x;
    int original_y;
    int current_x;
    int current_y;

    void init();
    void set(int magnitude, int time, int original_x, int original_y);
    void update();
};

#endif
