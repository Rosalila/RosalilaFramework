#ifndef TRANSPARENCY_EFFECT_H
#define TRANSPARENCY_EFFECT_H

class TransparencyEffect
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
