#ifdef LINUX
#include <SDL2/SDL_image.h>
#endif

#ifdef OSX
#include <SDL2_image/SDL_image.h>
#endif

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdio.h>

class Image
{
public:
    GLuint texture;
    int width;
    int height;

    Image();
    ~Image();
    int getWidth();
    int getHeight();
    GLuint getTexture();
    void setTexture(GLuint texture);
    void setWidth(int width);
    void setHeight(int height);
};
