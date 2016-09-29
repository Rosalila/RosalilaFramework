#include "PointExplosionEffect.h"

PointExplosion::PointExplosion(Point point, Color color, int size, double angle, double velocity, int duration)
{
    this->point = point;
    this->color = color;
    this->size = size;
    this->angle = angle;
    this->velocity = velocity;
    this->duration = duration;
    this->frame = 0;
}

void PointExplosion::update()
{
    this->point.x += cos (this->angle * PI / 180) * this->velocity;
    this->point.y -= sin (this->angle * PI / 180) * this->velocity;
    frame++;
    color.alpha-=10;
}

void PointExplosionEffect::explode(int x, int y, Color color)
{
    for(int i=0;i<25;i++)
    {
        current_points.push_back(new PointExplosion(Point(x,y),
                                                    color,
                                                    5,
                                                    rosalila()->utility->getNonSeededRandomNumber()%360,
                                                    2*rosalila()->utility->getNonSeededRandomNumber()%10,
                                                    15));
    }
}

void PointExplosionEffect::update()
{
    for(list<DrawablePoint*>::iterator i=current_points.begin();
        i!=current_points.end();
        i++)
    {
        PointExplosion* explosion_point = (PointExplosion*)(*i);

        explosion_point->update();

        if(explosion_point->frame>=explosion_point->duration)
        {
            delete explosion_point;
            current_points.erase(i);
            --i;
        }
    }
}
