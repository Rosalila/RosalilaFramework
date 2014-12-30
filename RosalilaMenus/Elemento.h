#ifndef ELEMENTO_H
#define ELEMENTO_H

#include "../RosalilaGraphics/RosalilaGraphics.h"

class Elemento
{
protected:
    RosalilaGraphics*painter;
public:
    int x;
    int y;
    int displacement_x;
    int displacement_y;
    int stop_displacement_x_at;
    int stop_displacement_y_at;
    int current_displacement_x;
    int current_displacement_y;
    int width;
    int height;
    Elemento();
    Elemento(RosalilaGraphics*painter,int x, int y,int displacement_x,int displacement_y,int stop_displacement_x_at,int stop_displacement_y_at,int current_displacement_x,int current_displacement_y, int width, int height);
    virtual void dibujar()=0;
    virtual std::string getTipo()=0;
};
#endif
