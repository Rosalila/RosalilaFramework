#ifndef DRAWABLE_TRIANGLE_H
#define DRAWABLE_TRIANGLE_H

#include "../../RosalilaUtility/Point.h"
#include "../Color.h"

class DrawableTriangle
{
public:
    int x;
    int y;
    Point p1;
    Point p2;
    Point p3;
    int angle;
    Color color;
    DrawableTriangle(int x, int y,Point p1, Point p2, Point p3, int angle, Color color);
};

#endif
