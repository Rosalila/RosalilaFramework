#ifndef DRAWABLE_RECTANGLE_H
#define DRAWABLE_RECTANGLE_H

#include "../Color.h"

class DrawableRectangle
{
public:
    int x;
    int y;
    int width;
    int height;
    int angle;
    Color color;
    DrawableRectangle(int x, int y, int width, int height, int angle, Color color);
};

#endif
