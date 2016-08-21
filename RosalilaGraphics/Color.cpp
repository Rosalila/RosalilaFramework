#include "Color.h"

Color::Color()
{
    this->red=0;
    this->green=0;
    this->blue=0;
    this->alpha=255;
}

Color::Color(int red,int green,int blue,int alpha)
{
    this->red=red;
    this->green=green;
    this->blue=blue;
    this->alpha=alpha;
}
