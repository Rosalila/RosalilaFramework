#include "FlatShadow.h"

FlatShadow::FlatShadow(Image* image, float shadow_lenght,float alpha_init,float alpha_end,float shadow_x,float shadow_y,vector<Point*>points)
{
    this->shadow_lenght=shadow_lenght;
    this->alpha_init=alpha_init;
    this->alpha_end=alpha_end;
    this->shadow_x=shadow_x;
    this->shadow_y=shadow_y;
    this->points=points;
    this->image = image;
}

FlatShadow::FlatShadow()
{
    this->shadow_lenght=0;
    this->alpha_init=0;
    this->alpha_end=0;
    this->shadow_x=0;
    this->shadow_y=0;
}

FlatShadow::~FlatShadow()
{
    //dtor
}
