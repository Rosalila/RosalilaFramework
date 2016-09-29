#ifndef DRAWABLE_POINT_H
#define DRAWABLE_POINT_H

#include "../../RosalilaUtility/Point.h"
#include "../Color.h"

class DrawablePoint
{
public:
    Point point;
    Color color;
    int size;
    DrawablePoint(){}
    DrawablePoint(Point point, Color color, int size)
    {
        this->point = point;
        this->color = color;
        this->size = size;
    }
};

#endif
