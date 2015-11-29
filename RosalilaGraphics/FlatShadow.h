#ifndef FLATSHADOW_H
#define FLATSHADOW_H

#include <vector>
#include "../RosalilaUtility/RosalilaUtility.h"
#include "../RosalilaGraphics/Image.h"

class Point;
class RosalilaGraphics;

class FlatShadow
{
    public:
        Image* image;
        float shadow_lenght=1;
        float alpha_init=128;
        float alpha_end=0;
        float shadow_x;
        float shadow_y;
        vector<Point*>points;
        FlatShadow(Image* image, float shadow_lenght,float alpha_init,float alpha_end,float shadow_x,float shadow_y,vector<Point*>points);
        FlatShadow();
        virtual ~FlatShadow();
    protected:
    private:
};

#endif // FLATSHADOW_H
