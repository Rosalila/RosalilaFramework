/**
* @author: Kevin J. Estevez (kenystev)
*
* GNU GENERAL PUBLIC LICENSE Version 2
* The licenses for most software are designed to take away your
* freedom to share and change it.  By contrast, the GNU General Public
* License is intended to guarantee your freedom to share and change free
* software--to make sure the software is free for all its users.  This
* General Public License applies to most of the Free Software
* Foundation's software and to any other program whose authors commit to
* using it.
*/

#ifndef FONT_H
#define FONT_H

#include <iostream>

#include "../RosalilaGraphics/RosalilaGraphics.h"

using namespace std;

class Font
{
    public:
        int font_size=10;
        TTF_Font* font;
        SDL_Color textColor;
        string font_path;
        Font(string);

        void drawText(std::string text,int position_x,int position_y);
        void setSize(int size);
        void setColor(int,int,int);

        virtual ~Font();
    protected:
    private:
};

#endif // FONT_H
