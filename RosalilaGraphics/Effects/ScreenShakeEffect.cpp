#include "ScreenShakeEffect.h"

void ScreenShakeEffect::init()
{
    this->magnitude = 0;
    this->time = 0;
    this->original_x = 0;
    this->original_y = 0;
    this->current_x = 0;
    this->current_y = 0;
}

void ScreenShakeEffect::set(int magnitude, int time, int original_x, int original_y)
{
    this->magnitude = magnitude;
    this->time = time;
    this->original_x = original_x;
    this->original_y = original_y;
}

void ScreenShakeEffect::update()
{

}
