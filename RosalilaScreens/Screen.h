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

#ifndef SCREEN_H
#define SCREEN_H
#include "Rosalila/RosalilaGraphics/RosalilaGraphics.h"

class Screen
{
    public:
        Screen();

        virtual void show ()=0;
        virtual void render (RosalilaGraphics*)=0;
//        void resize (int width, int height);
        virtual void pause ()=0;
        virtual void resume ()=0;
        virtual void hide ()=0;
        virtual void dispose ()=0;

        virtual ~Screen();
    protected:
    private:
};

#endif // SCREEN_H
