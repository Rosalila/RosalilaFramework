#include "Line.h"

Line::Line()
{
}

Line::Line(Point p1,Point p2)
{
    this->p1=p1;
    this->p2=p2;
}

void Line::set(Point p1,Point p2)
{
    this->p1=p1;
    this->p2=p2;
}
