#include "Hitbox.h"

Hitbox::Hitbox(int x,int y,int width,int height,float angle)
{
    this->x=x;
    this->y=y;
    this->width=width;
    this->height=height;
    this->angle=angle;
    setLines();
}

Hitbox::Hitbox()
{
    this->x=0;
    this->y=0;
    this->width=0;
    this->height=0;
    this->angle=0;
    setLines();
}

int Hitbox::getX()
{
    return x;
}

int Hitbox::getY()
{
    return y;
}

int Hitbox::getWidth()
{
    return width;
}

int Hitbox::getHeight()
{
    return height;
}

float Hitbox::getAngle()
{
    return angle;
}

void Hitbox::setX(int x)
{
    this->x=x;
    setLines();
}
void Hitbox::setY(int y)
{
    this->y=y;
    setLines();
}
void Hitbox::setWidth(int width)
{
    this->width=width;
    setLines();
}
void Hitbox::setHeight(int height)
{
    this->height=height;
    setLines();
}
void Hitbox::setAngle(float angle)
{
    this->angle=angle;
    setLines();
}

void Hitbox::setValues(int x,int y, int width, int height,float angle)
{
    this->x=x;
    this->y=y;
    this->width=width;
    this->height=height;
    this->angle=angle;
    setLines();
}

bool Hitbox::collides(Hitbox hitbox_param)
{
    return hitboxLinesCollision(this->line1,this->line2,this->line3,this->line4,
                                hitbox_param.line1,hitbox_param.line2,hitbox_param.line3,hitbox_param.line4);
}

bool Hitbox::collides(Hitbox hitbox_param,int hitbox_x,int hitbox_y,int hitbox_angle)
{
    hitbox_param.setX(hitbox_param.getX()+hitbox_x);
    hitbox_param.setY(hitbox_param.getY()+hitbox_y);
    hitbox_param.setAngle(hitbox_param.getAngle()+hitbox_angle);

    return hitboxLinesCollision(this->line1,this->line2,this->line3,this->line4,
                                hitbox_param.line1,hitbox_param.line2,hitbox_param.line3,hitbox_param.line4);
}

Hitbox Hitbox::getPlacedHitbox(double x, double y)
{
    Hitbox hitbox = *this;
    Point rotated=rotateAroundPoint(Point(hitbox.getX(),hitbox.getY()),
                                    Point(x,y),
                                    0);
    hitbox.setX(rotated.x);
    hitbox.setY(rotated.y);
    hitbox.setAngle(0);
    hitbox.setLines();
    return hitbox;
}

Hitbox Hitbox::getPlacedHitbox(double x, double y,float a)
{
    Hitbox hitbox = *this;
    Point rotated=rotateAroundPoint(Point(hitbox.getX(),hitbox.getY()),
                                    Point(x,y),
                                    a+hitbox.getAngle());
    hitbox.setX(rotated.x);
    hitbox.setY(rotated.y);
    hitbox.setAngle(a+hitbox.getAngle());
    hitbox.setLines();
    return hitbox;
}

void Hitbox::setLines()
{
    Point point1(x,
              y);

    Point point2(x + cos (angle*PI/180) * width
             ,y - sin (angle*PI/180) * width);

    Point point3(x + cos (angle*PI/180) * width + sin (angle*PI/180) * height,
              y - sin (angle*PI/180) * width + cos (angle*PI/180) * height);

    Point point4(x + sin (angle*PI/180) * height,
              y + cos (angle*PI/180) * height);


    line1.set(point1,point2);
    line2.set(point2,point3);
    line3.set(point3,point4);
    line4.set(point4,point1);
}
