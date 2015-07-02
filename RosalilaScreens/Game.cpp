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

#include "Game.h"
#include "Rosalila/RosalilaGraphics/RosalilaGraphics.h"

Game::Game()
{
    screen=NULL;

    //Input receiver initialization
    receiver = new Receiver();

    //Graphics initialization
    rosalila_graphics = new RosalilaGraphics();
    rosalila_graphics->video(rosalila_graphics);
}

Game::~Game()
{
    //dtor
}

void Game::dispose()
{
    if (screen != NULL) screen->hide();
}

void Game::pause()
{
    if (screen != NULL) screen->pause();
}

void Game::resume()
{
    if (screen != NULL) screen->resume();
}

void Game::render()
{
    if (screen != NULL) screen->render(rosalila_graphics);
    receiver->updateInputs();
    rosalila_graphics->updateScreen();
    if(receiver->isKeyDown(SDLK_ESCAPE))
        exit(0);
}

void Game::setScreen(Screen *screen)
{
    if (this->screen != NULL) this->screen->hide();
        this->screen = screen;
        if (this->screen != NULL) {
            this->screen->show();
    }
}

Screen* Game::getScreen()
{
    return screen;
}
