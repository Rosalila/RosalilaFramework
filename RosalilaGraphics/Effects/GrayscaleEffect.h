#ifndef GRAYSCALE_EFFECT_H
#define GRAYSCALE_EFFECT_H

class GrayscaleEffect
{
public:
    double current_percentage;
    double target_percentage;
    double change_speed;

    void init();
    void set(double target_percentage, double change_speed);
    void update();
};

#endif
