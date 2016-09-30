#ifndef POINT_EXPLOSION_EFFECT
#define POINT_EXPLOSION_EFFECT

#include <list>
#include <cmath>
#include <stdlib.h>
#include "../Drawables/DrawablePoint.cpp"
#include "../../Rosalila.h"

#define PI 3.14159265

using namespace std;

class PointExplosion : public DrawablePoint
{
public:
    double angle;
    double velocity;
    int duration;
    int frame;
    PointExplosion(Point point, Color color, int size, double angle, double velocity, int duration);
    void update();
};

class PointExplosionEffect
{
public:
    list<DrawablePoint*> current_points;
    void explode(int x, int y, Color color, int intensity);
    void update();
};

#endif
