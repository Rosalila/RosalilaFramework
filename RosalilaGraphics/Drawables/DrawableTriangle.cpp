#include "DrawableTriangle.h"

DrawableTriangle::DrawableTriangle(int x, int y, Point p1, Point p2, Point p3, int angle, Color color)
{
    this->x = x;
    this->y = y;
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->angle = angle;
    this->color = color;
}
