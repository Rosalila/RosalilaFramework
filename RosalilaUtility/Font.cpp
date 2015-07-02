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

#include "Font.h"

Font::Font(string path)
{
    font_path=assets_directory+"misc/"+path;
    font = TTF_OpenFont( font_path.c_str(), font_size );

    if(font==NULL)
    {
        writeLogLine("Could not init font. Place it on /misc/font.ttf .");
    }

    textColor.r = 255;
    textColor.g = 255;
    textColor.b = 255;
}

Font::~Font()
{
    //dtor
}

void Font::setSize(int size)
{
    font_size=size;
    font = TTF_OpenFont( font_path.c_str(), font_size );

    if(font==NULL)
    {
        writeLogLine("Could not init font. Place it on /misc/"+font_path);
    }
}

void Font::setColor(int r,int g,int b)
{
    textColor.r = r;
    textColor.g = g;
    textColor.b = b;
}

void Font::drawText(std::string text,int position_x,int position_y)
{
    if(text=="")
        text=" ";
    GLuint texture;

    SDL_Surface *message = NULL;
    message = TTF_RenderUTF8_Blended( font, text.c_str(), textColor );


    // Prepare the texture for the font
    GLenum textFormat;
    if(message->format->BytesPerPixel == 4)
    {
        // alpha
        if(message->format->Rmask == 0x000000ff)
            textFormat = GL_RGBA;
        else
            textFormat = GL_BGRA_EXT;
    }

    // Create the font's texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, message->format->BytesPerPixel, message->w, message->h, 0, textFormat, GL_UNSIGNED_BYTE, message->pixels);

    GLfloat x1=0.f+position_x;
    GLfloat y1=0.f+position_y;
    GLfloat x2=0.f+position_x+message->w;
    GLfloat y2=0.f+position_y+message->h;
    SDL_FreeSurface(message);


    //OpenGL draw
    glBindTexture( GL_TEXTURE_2D, texture );
    glColor3ub(255, 255, 255);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glBegin( GL_QUADS );

        //Bottom-left vertex (corner)
        glTexCoord2i( 0, 0 );
        glVertex3f( x1, y1, 0.0f );

        //Bottom-right vertex (corner)
        glTexCoord2i( 1, 0 );
        glVertex3f( x2, y1, 0.f );

        //Top-right vertex (corner)
        glTexCoord2i( 1, 1 );
        glVertex3f( x2, y2, 0.f );

        //Top-left vertex (corner)
        glTexCoord2i( 0, 1 );
        glVertex3f( x1, y2, 0.f );

    glEnd();
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glDeleteTextures( 1, &texture );
}
