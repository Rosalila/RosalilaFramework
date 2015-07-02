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

#ifndef GAME_H
#define GAME_H
#include "Screen.h"
#include "Rosalila/RosalilaGraphics/RosalilaGraphics.h"
#include "Rosalila/RosalilaInputs/Receiver.h"

class Game
{
    public:
        Game();
        Screen *screen;
        RosalilaGraphics* rosalila_graphics;
        Receiver* receiver;

        virtual ~Game();

        virtual void create()=0;

        void dispose();
        void pause();
        void resume();
        void render();

        void setScreen(Screen *screen);
        Screen* getScreen();
    protected:
    private:
};

#endif // GAME_H
