#ifndef GRAFICO_H
#define GRAFICO_H

#include <iostream>
#include <list>

#include "../Rosalila.h"

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

#include <SDL2/SDL_opengl.h>
#include <stdio.h>

#include "../RosalilaGraphics/Color.h"
#include "../RosalilaGraphics/FlatShadow.h"
#include "../RosalilaGraphics/Image.h"
#include "../RosalilaGraphics/Timer.h"
#include "../RosalilaUtility/RosalilaUtility.h"

#include <iostream>
#include <fstream>
using namespace std;

class FlatShadow;

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
    int last_tick;

    //Screen Shake
    int shake_magnitude;
    int shake_time;
    int shake_original_x;
    int shake_original_y;
    int current_screen_shake_x;
    int current_screen_shake_y;

    //Grayscale effect
    double current_grayscale_percentage;
    double target_grayscale_percentage;
    double grayscale_change_speed;

    ~RosalilaGraphics();
    void init();
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
				 bool camera_align,
				 FlatShadow flat_shadow);
    void draw2DImageBatch(
	             Image* texture,
				 int size_x,int size_y,
				 vector<int> position_x,vector<int>position_y,
				 float scale,
				 vector<float>rotation,
				 bool flipHorizontally,
				 int depth_effect_x,
				 int depth_effect_y,
				 Color color_effects,
				 int shadow_x, int shadow_y,
				 bool camera_align,
				 FlatShadow flat_shadow);
    void shakeScreen(int shake_magnitude, int shake_time);
    void setGrayscale(double target_grayscale_percentage, double grayscale_change_speed);
    void updateGrayscale();
    void drawText(std::string text,int position_x,int position_y);
    void drawRectangle(int x,int y,int width,int height,float rotation,int red,int green,int blue,int alpha,bool camera_align);
    void updateScreen();
    void frameCap();
    void screenshot(int x, int y, int w, int h, string filename);
};
#endif
