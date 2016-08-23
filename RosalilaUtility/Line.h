#ifndef LINE_H
#define LINE_H

#include "Point.h"

class Line
{
public:
    Point p1;
    Point p2;

    Line();
    Line(Point p1,Point p2);
    void set(Point p1,Point p2);
};

#endif
