#include "RosalilaGraphics/RosalilaGraphics.h"

Image::Image()
{
    width=-1;
    height=-1;
    scale = 1.0;
    rotation = 0.0;
    horizontal_flip = false;
    blend_effect = false;
    color_filter.red = 255;
    color_filter.green = 255;
    color_filter.blue = 255;
    color_filter.alpha = 255;
}

int Image::getWidth()
{
    return width;
}
int Image::getHeight()
{
    return height;
}

GLuint Image::getTexture()
{
    return texture;
}

void Image::setTexture(GLuint texture)
{
    this->texture=texture;
}

void Image::setWidth(int width)
{
    this->width = width;
    this->original_width = width;
}
void Image::setHeight(int height)
{
    this->height = height;
    this->original_height = height;
}

Image::~Image()
{
    glDeleteTextures( 1, &texture );
}
