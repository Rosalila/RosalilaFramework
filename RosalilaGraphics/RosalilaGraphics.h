#ifndef GRAFICO_H
#define GRAFICO_H

#include <iostream>
#include <list>

#include "../system.h"

#ifdef LINUX
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#ifdef WINDOWS
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#ifdef OSX
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#endif


#include "../TinyXml/tinyxml.h"

#include <SDL2/SDL_opengl.h>
#include <stdio.h>

#include "../RosalilaGraphics/Image.h"
#include "../RosalilaGraphics/Timer.h"
#include "../RosalilaGraphics/Explosion.h"
#include "../RosalilaGraphics/Cube.h"
#include "../RosalilaGraphics/Object3D.h"
#include "../RosalilaUtility/RosalilaUtility.h"

#include <iostream>
#include <fstream>
using namespace std;

class Color
{
public:
    int red;
    int green;
    int blue;
    int alpha;

    Color()
    {
        this->red=0;
        this->green=0;
        this->blue=0;
        this->alpha=255;
    }

    Color(int red,int green,int blue,int alpha)
    {
        this->red=red;
        this->green=green;
        this->blue=blue;
        this->alpha=alpha;
    }

    int getRed()
    {
        return red;
    }

    int getGreen()
    {
        return green;
    }

    int getBlue()
    {
        return blue;
    }

    int getAlpha()
    {
        return alpha;
    }
};

class RosalilaGraphics
{
    public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Color textColor;
    int screen_width;
    int screen_height;
    bool fullscreen;
    int screen_bpp;
    int camera_x,camera_y;
    SDL_Joystick *joystick_1;
    SDL_Joystick *joystick_2;

    //Set fps
    int frames_per_seccond;
    int frame;
    int current_fps;
    Timer *fps;
    Timer *update;

    //3D
    list<Explosion*> explosions;
    Cube cube;

    RosalilaGraphics();
    ~RosalilaGraphics();
    Image* getTexture(std::string filename);
    void draw2DImage(
	             Image* texture,
				 int size_x,int size_y,
				 int position_x,int position_y,
				 float scale,
				 float rotation,
				 bool flipHorizontally,
				 int depth_effect_x,
				 int depth_effect_y,
				 Color color_effects,
				 int shadow_x, int shadow_y,
				 bool camera_align);
    void drawText(std::string text,int position_x,int position_y);
    void drawRectangle(int x,int y,int width,int height,float rotation,int red,int green,int blue,int alpha,bool camera_align);
    void draw3D();
    void draw3DCube(int x,int y,float size,Color color);
    void explode(float pos_x,float pos_y);
    void addExplosion(int x,int y);
    void drawObject();
    void updateScreen();
    void frameCap();
    int getFrameCap();
    void resetScreen();
    void video(RosalilaGraphics*painter);
};
#endif
