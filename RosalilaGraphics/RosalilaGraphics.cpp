#include "RosalilaGraphics.h"

RosalilaGraphics::RosalilaGraphics()
{

}

void RosalilaGraphics::init()
{
    screen_shake_effect.init();
    grayscale_effect.init();
    transparency_effect.init();
    point_explosion_effect =  new PointExplosionEffect();

    //XML Initializations
    Node* root_node = rosalila()->parser->getNodes(assets_directory+"config.xml");

    Node* resolution_node = root_node->getNodeByName("Resolution");
    screen_width=atoi(resolution_node->attributes["x"].c_str());
    screen_height=atoi(resolution_node->attributes["y"].c_str());

    Node* screen_size_node = root_node->getNodeByName("ScreenSize");
    int screen_resized_width=atoi(screen_size_node->attributes["x"].c_str());
    int screen_resized_height=atoi(screen_size_node->attributes["y"].c_str());

    Node* fullscreen_node = root_node->getNodeByName("Fullscreen");
    fullscreen=fullscreen_node->attributes["enabled"]=="yes";

    Node* font_node = root_node->getNodeByName("Font");

    int font_size=10;
    if(font_node->hasAttribute("size"))
    {
        font_size=atoi(font_node->attributes["size"].c_str());
    }
    int font_red=0;
    if(font_node->hasAttribute("red"))
    {
        font_red=atoi(font_node->attributes["red"].c_str());
    }
    int font_green=0;
    if(font_node->hasAttribute("green"))
    {
        font_green=atoi(font_node->attributes["green"].c_str());
    }
    int font_blue=0;
    if(font_node->hasAttribute("blue"))
    {
        font_blue=atoi(font_node->attributes["blue"].c_str());
    }
    //Internal initializations
    joystick_1 = NULL;
    joystick_2 = NULL;

    screen_bpp = 32;
    camera_x=camera_y=0;

    //Initialize all SDL subsystems
    if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0 )
    {
        //rosalila()->utility->writeLogLine(SDL_GetError());
        return;
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        //rosalila()->utility->writeLogLine(SDL_GetError());
        return;
    }

    font = NULL;
    textColor.r = font_red;
    textColor.g = font_green;
    textColor.b = font_blue;

    string font_path=assets_directory+"misc/font.ttf";
    font = TTF_OpenFont( font_path.c_str(), font_size );

    if(font==NULL)
    {
        //rosalila()->utility->writeLogLine("Could not init font. Place it on /misc/font.ttf .");
    }

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); // *new*

    window = SDL_CreateWindow( "Rosalila Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               screen_resized_width, screen_resized_height,
                               SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    if(!window)
    {
        //rosalila()->utility->writeLogLine("Could not init window");
    }

    if(fullscreen)
        SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);

    //Set the openGL state?
    glEnable( GL_TEXTURE_2D );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    glViewport( 0, 0, screen_resized_width, screen_resized_height );

    glClear( GL_COLOR_BUFFER_BIT );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glOrtho(0.0f, screen_width, screen_height, 0.0f, -1.0f, 1.0f);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Fps cap
    frames_per_seccond = 60;
    frame = 0;
    last_tick=SDL_GetTicks();

    //Init joysticks
    if( SDL_NumJoysticks() == 1 )
    {
//        rosalila()->utility->writeLogLine("1 joystick was found.");
        joystick_1 = SDL_JoystickOpen( 0 );
//        if(joystick_1 != NULL)
//            rosalila()->utility->writeLogLine("Joystick for player 1 initialized succesfully.");
//        else
//            rosalila()->utility->writeLogLine("Error initializing joystick for player 1.");
    }
    if( SDL_NumJoysticks() == 2 )
    {
//        rosalila()->utility->writeLogLine("2 joysticks were found.");
        joystick_1 = SDL_JoystickOpen( 0 );
//        if(joystick_1 != NULL)
//            rosalila()->utility->writeLogLine("Joystick for player 1 initialized succesfully.");
//        else
//            rosalila()->utility->writeLogLine("Error initializing joystick for player 1.");
        joystick_2 = SDL_JoystickOpen( 1 );
//        if(joystick_2 != NULL)
//            rosalila()->utility->writeLogLine("Joystick for player 2 initialized succesfully.");
//        else
//            rosalila()->utility->writeLogLine("Error initializing joystick for player 2.");
    }



    //If everything initialized fine
//    rosalila()->utility->writeLogLine("Success! SDL initialized.");

     SDL_GL_CreateContext(window);
    GLenum error = GL_NO_ERROR;
    error = glGetError();
    if( error != GL_NO_ERROR ) {
         exit(12);
    }

    notification_background = getTexture(assets_directory+"misc/messages/notification_background.png");
    notification_background_x = screen_width/2 - notification_background->getWidth()/2;
    notification_background_y = screen_height - notification_background->getHeight();
}

RosalilaGraphics::~RosalilaGraphics()
{
    //Quit SDL
    SDL_Quit();
}


Image* RosalilaGraphics::getTexture(std::string filename)
{
    SDL_Surface *surface;
    GLenum texture_format;
    GLint  nOfColors;
    GLuint texture;

    if ( (surface = IMG_Load(filename.c_str())) ) {

            // get the number of channels in the SDL surface
            nOfColors = surface->format->BytesPerPixel;
            if (nOfColors == 4)     // contains an alpha channel
            {
                    if (surface->format->Rmask == 0x000000ff)
                            texture_format = GL_RGBA;
                    //else
                            //texture_format = GL_BGRA;
            } else if (nOfColors == 3)     // no alpha channel
            {
                    if (surface->format->Rmask == 0x000000ff)
                            texture_format = GL_RGB;
                    //else
                            //texture_format = GL_BGR;
            } else {
                rosalila()->utility->writeLogLine("Warning: "+ filename+ " is not truecolor. This will probably break.");
                    // this error should not go unhandled
            }

        // Have OpenGL generate a texture object handle for us
        glGenTextures( 1, &texture );

        // Bind the texture object
        glBindTexture( GL_TEXTURE_2D, texture );

        // Set the texture's stretching properties
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

//for(int x=0;x<surface->w;x++)
//for(int y=0;y<surface->h;y++)
//((unsigned int*)surface->pixels)[y*(surface->pitch/sizeof(unsigned int)) + x]+=1;
        // Edit the texture object's image data using the information SDL_Surface gives us
#ifdef OSX
        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
                          GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels );
#else
        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
                          texture_format, GL_UNSIGNED_BYTE, surface->pixels );
#endif
    }
    else {
        std::string sdl_error=SDL_GetError();
        rosalila()->utility->writeLogLine("SDL could not load "+filename+": "+sdl_error);
        SDL_Quit();
        return NULL;
    }


    Image*image=new Image();
    image->setTexture(texture);
    image->setWidth(surface->w);
    image->setHeight(surface->h);

    // Free the SDL_Surface only if it was successfully created
    if ( surface ) {
        SDL_FreeSurface( surface );
    }

    rosalila()->utility->writeLogLine(filename+" loaded");

    return image;
}

void RosalilaGraphics::draw2DImage	(
             Image* texture,
             int size_x,int size_y,
             int position_x,int position_y,
             float scale,
             float rotation,
             bool flipHorizontally,
             int depth_effect_x,
             int depth_effect_y,
             Color color_effects,
             int shadow_x,int shadow_y,
             bool camera_align,
             FlatShadow flat_shadow)
{
    double grey_scale = (color_effects.red+color_effects.green+color_effects.blue)/3;

    double red_difference = color_effects.red-grey_scale;
    double green_difference = color_effects.green-grey_scale;
    double blue_difference = color_effects.blue-grey_scale;

    color_effects.red = grey_scale + red_difference * grayscale_effect.current_percentage;
    color_effects.green = grey_scale + green_difference * grayscale_effect.current_percentage;
    color_effects.blue = grey_scale + blue_difference * grayscale_effect.current_percentage;

    color_effects.alpha = (double)color_effects.alpha * transparency_effect.current_percentage;

    glEnable( GL_TEXTURE_2D );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0.0f, screen_width, screen_height, 0.0f, -1.0f, 1.0f);
    glMatrixMode( GL_MODELVIEW );

    glDisable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glDisable (GL_DEPTH_TEST);

    //Camera and depth effect
    if(depth_effect_x>0)
    {
        position_x-=camera_x/depth_effect_x;
    }else if(depth_effect_x<0)
    {
        position_x-=camera_x*-depth_effect_x;
    }else if(camera_align)
    {
        position_x-=camera_x;
    }

    if(depth_effect_y>0)
    {
        position_y+=camera_y/depth_effect_y;
    }else if(depth_effect_y<0)
    {
        position_y+=camera_y*-depth_effect_y;
    }else if(camera_align)
    {
        position_y+=camera_y;
    }

    //Screen shake
    position_x += screen_shake_effect.current_x;
    position_y += screen_shake_effect.current_y;

    GLfloat x1=0.f+position_x;
    GLfloat y1=0.f+position_y;
    GLfloat x2=0.f+position_x+(float)size_x*scale;
    GLfloat y2=0.f+position_y+(float)size_y*scale;

    //Flip
    if(flipHorizontally)
    {
        GLfloat temp=x1;
        x1=x2;
        x2=temp;
    }

    //OpenGL draw
    //Save the current matrix.
    glPushMatrix();
    //Change the current matrix.
    float translate_x=(x2-x1)/2+position_x;
    float translate_y=(y2-y1)/2+position_y;
    glTranslatef(translate_x,translate_y, 1.0);
    glRotatef(-rotation, 0, 0, 1.0);

    glColor4ub(color_effects.red, color_effects.green, color_effects.blue,color_effects.alpha);
    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    if((flat_shadow.shadow_x!=0 || flat_shadow.shadow_y!=0) && flat_shadow.points_left.size()>0)
    {
        glBindTexture( GL_TEXTURE_2D, flat_shadow.image->getTexture() );

    glColor4ub(color_effects.red, color_effects.green, color_effects.blue,color_effects.alpha);
    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

        glColor4ub(100,100,100,100);

        if(x1>=flat_shadow.shadow_x)// Right shadow
        {
            float gifiti1=(x2-flat_shadow.shadow_x)*flat_shadow.shadow_lenght;
            float gifiti2=(y1-flat_shadow.shadow_y)*flat_shadow.shadow_lenght;
            float gifiti1b=(x1-flat_shadow.shadow_x)*flat_shadow.shadow_lenght;
            float gifiti2b=(y2-flat_shadow.shadow_y)*flat_shadow.shadow_lenght;
            glBegin( GL_POLYGON );
                //Top-left vertex (corner)
                //glColor4ub(100,100,100,255);
                glColor4ub(255,255,255,flat_shadow.alpha_init);
                glTexCoord2i( 0, 0 );
                glVertex3f( x2-translate_x+flat_shadow.points_right[1]->x,
                           y1-translate_y+flat_shadow.points_right[1]->y,
                           0.0f );

                //Bottom-right vertex (corner)
                glColor4ub(255,255,255,flat_shadow.alpha_end);
                //glColor4ub(0,0,0,255);
                glTexCoord2i( 1, 0 );
                glVertex3f( x2-translate_x+gifiti1, y1-translate_y+gifiti2, 0.f );


                //Down-right vertex (corner)
                //glColor4ub(0,0,0,255);
                glColor4ub(255,255,255,flat_shadow.alpha_end);
                glTexCoord2i( 1, 1 );
                glVertex3f( x1-translate_x+gifiti1b, y2-translate_y+gifiti2b, 0.f );



                //Top-left vertex (corner)
                //glColor4ub(100,100,100,255);
                glColor4ub(255,255,255,flat_shadow.alpha_init);
                glTexCoord2i( 0, 1 );
                glVertex3f( x1-translate_x+flat_shadow.points_right[0]->x,
                            y2-translate_y+flat_shadow.points_right[0]->y,
                            0.f );


                for(int i=0;i<(int)flat_shadow.inbetween_points_right.size();i++)
                glVertex3f( x1-translate_x+flat_shadow.points_right[0]->x+flat_shadow.inbetween_points_right[i]->x,
                            y2-translate_y+flat_shadow.points_right[0]->y+flat_shadow.inbetween_points_right[i]->y,
                            0.f );

            glEnd();
        }else if(x2<=flat_shadow.shadow_x)// Left shadow
        {
            float gifiti1=(flat_shadow.shadow_x-x1)*flat_shadow.shadow_lenght;
            float gifiti2=(flat_shadow.shadow_y-y1)*flat_shadow.shadow_lenght;
            float gifiti1b=(flat_shadow.shadow_x-x2)*flat_shadow.shadow_lenght;
            float gifiti2b=(flat_shadow.shadow_y-y2)*flat_shadow.shadow_lenght;
            glBegin( GL_POLYGON );
                //Bottom-left vertex (corner)
                //glColor4ub(0,0,0,255);
                glColor4ub(255,255,255,flat_shadow.alpha_end);
                glTexCoord2i( 0, 0 );
                glVertex3f( x1-translate_x-gifiti1, y1-translate_y-gifiti2, 0.0f );

                //Bottom-right vertex (corner)
                //glColor4ub(100,100,100,255);
                glColor4ub(255,255,255,flat_shadow.alpha_init);
                glTexCoord2i( 1, 0 );
                glVertex3f( x1-translate_x+flat_shadow.points_left[0]->x,
                           y1-translate_y+flat_shadow.points_left[0]->y,
                           0.f );

                for(int i=0;i<(int)flat_shadow.inbetween_points_left.size();i++)
                glVertex3f( x1-translate_x+flat_shadow.points_left[0]->x+flat_shadow.inbetween_points_left[i]->x,
                           y1-translate_y+flat_shadow.points_left[0]->y+flat_shadow.inbetween_points_left[i]->y,
                           0.f );

                //Top-right vertex (corner)
                //glColor4ub(100,100,100,255);
                glColor4ub(255,255,255,flat_shadow.alpha_init);
                glTexCoord2i( 1, 1 );
                glVertex3f( x2-translate_x+flat_shadow.points_left[1]->x,
                           y2-translate_y+flat_shadow.points_left[1]->y,
                           0.f );

                //Top-left vertex (corner)
                //glColor4ub(0,0,0,255);
                glColor4ub(255,255,255,flat_shadow.alpha_end);
                glTexCoord2i( 0, 1 );
                glVertex3f( x2-translate_x-gifiti1b, y2-translate_y-gifiti2b, 0.f );

            glEnd();
        }else// Top shadow
        {
            float gifiti1=(flat_shadow.shadow_x-x1)*flat_shadow.shadow_lenght;
            float gifiti2=(flat_shadow.shadow_y-y1)*flat_shadow.shadow_lenght;

            float gifiti1x=(x2-flat_shadow.shadow_x)*flat_shadow.shadow_lenght;
            float gifiti2x=(y1-flat_shadow.shadow_y)*flat_shadow.shadow_lenght;

            glBegin( GL_QUADS );
                //Bottom-left vertex (corner)
                //glColor4ub(0,0,0,255);
                glColor4ub(255,255,255,flat_shadow.alpha_end);
                glTexCoord2i( 0, 0 );
                glVertex3f( x1-translate_x-gifiti1, y1-translate_y-gifiti2, 0.0f );

                //Bottom-right vertex (corner)
                //glColor4ub(100,100,100,255);
                glColor4ub(255,255,255,flat_shadow.alpha_init);
                glTexCoord2i( 1, 0 );
                glVertex3f( x1-translate_x+flat_shadow.points_top[0]->x,
                           y1-translate_y+flat_shadow.points_top[0]->y,
                           0.f );


                //Top-right vertex (corner)
                //glColor4ub(100,100,100,255);
                glColor4ub(255,255,255,flat_shadow.alpha_init);
                glTexCoord2i( 1, 1 );
                glVertex3f( x2-translate_x+flat_shadow.points_top[1]->x,
                           y1-translate_y+flat_shadow.points_top[1]->y,
                           0.f );

                //Top-left vertex (corner)
                glColor4ub(255,255,255,flat_shadow.alpha_end);
                glTexCoord2i( 0, 1 );
                glVertex3f( x2-translate_x+gifiti1x, y1-translate_y+gifiti2x, 0.f );

            glEnd();
        }
        glColor4ub(color_effects.red, color_effects.green, color_effects.blue,color_effects.alpha);
    }

    glBindTexture( GL_TEXTURE_2D, texture->getTexture() );


    glBegin( GL_QUADS);
        //Bottom-left vertex (corner)
        glTexCoord2i( 0, 0 );
        glVertex3f( x1-translate_x, y1-translate_y, 0.0f );

        //Bottom-right vertex (corner)
        glTexCoord2i( 1, 0 );
        glVertex3f( x2-translate_x, y1-translate_y, 0.f );

        //Top-right vertex (corner)
        glTexCoord2i( 1, 1 );
        glVertex3f( x2-translate_x, y2-translate_y, 0.f );

        //Top-left vertex (corner)
        glTexCoord2i( 0, 1 );
        glVertex3f( x1-translate_x, y2-translate_y, 0.f );

    glEnd();

    //Reset the current matrix to the one that was saved.
    glPopMatrix();
}

void RosalilaGraphics::draw2DImageBatch(
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
             FlatShadow flat_shadow)
{

    //Camera and depth effect

    glEnable( GL_TEXTURE_2D );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0.0f, screen_width, screen_height, 0.0f, -1.0f, 1.0f);
    glMatrixMode( GL_MODELVIEW );

    glDisable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glDisable (GL_DEPTH_TEST);

    glColor4ub(color_effects.red, color_effects.green, color_effects.blue,color_effects.alpha);
    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glBindTexture( GL_TEXTURE_2D, texture->getTexture() );



    glPushMatrix();
    glTranslatef(1.0,1.0, 1.0);

    glBegin( GL_QUADS);
    for(int i=0;i<(int)position_x.size();i++)
    {

        if(depth_effect_x>0)
        {
            position_x[i]-=camera_x/depth_effect_x;
        }else if(depth_effect_x<0)
        {
            position_x[i]-=camera_x*-depth_effect_x;
        }else if(camera_align)
        {
            position_x[i]-=camera_x;
        }

        if(depth_effect_y>0)
        {
            position_y[i]+=camera_y/depth_effect_y;
        }else if(depth_effect_y<0)
        {
            position_y[i]+=camera_y*-depth_effect_y;
        }else if(camera_align)
        {
            position_y[i]+=camera_y;
        }

        //Screen shake
        position_x[i] += screen_shake_effect.current_x;
        position_y[i] += screen_shake_effect.current_y;

        GLfloat x1=0.f+position_x[i];
        GLfloat y1=0.f+position_y[i];
        GLfloat x2=0.f+position_x[i]+(float)size_x*scale;
        GLfloat y2=0.f+position_y[i]+(float)size_y*scale;

        //Flip
        if(flipHorizontally)
        {
            GLfloat temp=x1;
            x1=x2;
            x2=temp;
        }

        //OpenGL draw
        //Save the current matrix.

        //Change the current matrix.
        //glTranslatef(translate_x,translate_y, 1.0);

        //glRotatef(-rotation[i], 0, 0, 1.0);


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



    }
    glEnd();
    glPopMatrix();

    //Reset the current matrix to the one that was saved.
//    glPopMatrix();
}


void RosalilaGraphics::drawRectangle(int x,int y,int width,int height,float rotation,int red,int green,int blue,int alpha,bool camera_align)
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0.0f, screen_width, screen_height, 0.0f, -1.0f, 1.0f);
    glMatrixMode( GL_MODELVIEW );

    glDisable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glDisable (GL_DEPTH_TEST);

    glDisable(GL_TEXTURE_2D);
    GLubyte r=red;
    GLubyte g=green;
    GLubyte b=blue;
    GLubyte a=alpha;
    glColor4ub(r,g,b,a);

    if(camera_align)
    {
        y+=camera_y;
        x-=camera_x;
    }

    //OpenGL draw
    //Save the current matrix.
    glPushMatrix();
    //Change the current matrix.
    float translate_x=x;
    float translate_y=y;
    glTranslatef(translate_x,translate_y, 1.0);
    glRotatef(-rotation, 0, 0, 1.0);
    x-=translate_x;
    y-=translate_y;

//    glRecti(x, y, width+x, height+y);



    glBegin(GL_QUADS);   //We want to draw a quad, i.e. shape with four sides
      glColor4ub(red,green,blue,alpha);
      glVertex2f(0, 0);
      glVertex2f(0, height);
      glVertex2f(width, height);
      glVertex2f(width, 0);
    glEnd();

    glFlush();

    //Reset the current matrix to the one that was saved.
    glPopMatrix();
}

void RosalilaGraphics::drawRectangles(vector<DrawableRectangle*>rectangles, int depth_effect_x, int depth_effect_y,bool camera_align)
{
    glLoadIdentity();
    glMatrixMode( GL_MODELVIEW );

    glPushMatrix();

    glDisable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glDisable (GL_DEPTH_TEST);

    glDisable(GL_TEXTURE_2D);

    glTranslatef(0,0, 1.0);

    glBegin(GL_QUADS);

    for(int i=0;i<(int)rectangles.size();i++)
    {
        double grey_scale = (rectangles[i]->color.red+rectangles[i]->color.green+rectangles[i]->color.blue)/3;

        double red_difference = rectangles[i]->color.red-grey_scale;
        double green_difference = rectangles[i]->color.green-grey_scale;
        double blue_difference = rectangles[i]->color.blue-grey_scale;

        rectangles[i]->color.red = grey_scale + red_difference * grayscale_effect.current_percentage;
        rectangles[i]->color.green = grey_scale + green_difference * grayscale_effect.current_percentage;
        rectangles[i]->color.blue = grey_scale + blue_difference * grayscale_effect.current_percentage;

        rectangles[i]->color.alpha = (double)rectangles[i]->color.alpha * transparency_effect.current_percentage;

        //Camera and depth effect
        if(depth_effect_x>0)
        {
            rectangles[i]->x-=camera_x/depth_effect_x;
        }else if(depth_effect_x<0)
        {
            rectangles[i]->x-=camera_x*-depth_effect_x;
        }else if(camera_align)
        {
            rectangles[i]->x-=camera_x;
        }

        if(depth_effect_y>0)
        {
            rectangles[i]->y+=camera_y/depth_effect_y;
        }else if(depth_effect_y<0)
        {
            rectangles[i]->y+=camera_y*-depth_effect_y;
        }else if(camera_align)
        {
            rectangles[i]->y+=camera_y;
        }

        rectangles[i]->x += screen_shake_effect.current_x;
        rectangles[i]->y += screen_shake_effect.current_y;

        Point p1(rectangles[i]->x,
                 rectangles[i]->y);
        Point p2(rectangles[i]->x,
                  rectangles[i]->y+rectangles[i]->height);
        Point p3(rectangles[i]->x+rectangles[i]->width,
                  rectangles[i]->y+rectangles[i]->height);
        Point p4(rectangles[i]->x+rectangles[i]->width,
                  rectangles[i]->y);

        Point center(rectangles[i]->x+rectangles[i]->width/2,
                     rectangles[i]->y+rectangles[i]->height/2);

        p1 = rosalila()->utility->realRotateAroundPoint(p1,center,rectangles[i]->angle);
        p2 = rosalila()->utility->realRotateAroundPoint(p2,center,rectangles[i]->angle);
        p3 = rosalila()->utility->realRotateAroundPoint(p3,center,rectangles[i]->angle);
        p4 = rosalila()->utility->realRotateAroundPoint(p4,center,rectangles[i]->angle);

        glColor4ub(rectangles[i]->color.red,rectangles[i]->color.green,rectangles[i]->color.blue,rectangles[i]->color.alpha);

        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p2.y);
        glVertex2f(p3.x, p3.y);
        glVertex2f(p4.x, p4.y);
    }

    glEnd();
    glFlush();
    glPopMatrix();
}

void RosalilaGraphics::drawPoints(list<DrawablePoint*>points, int depth_effect_x, int depth_effect_y,bool camera_align)
{
    glLoadIdentity();
    glMatrixMode( GL_MODELVIEW );

    glPushMatrix();

    glDisable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glDisable (GL_DEPTH_TEST);

    glDisable(GL_TEXTURE_2D);

    glTranslatef(0,0, 1.0);


    glPointSize(5);
    glBegin(GL_POINTS);


    for(list<DrawablePoint*>::iterator i=points.begin();
        i!=points.end();
        i++)
    {
        int x = (*i)->point.x;
        int y = (*i)->point.y;

        //Camera and depth effect
        if(depth_effect_x>0)
        {
            x-=camera_x/depth_effect_x;
        }else if(depth_effect_x<0)
        {
            x-=camera_x*-depth_effect_x;
        }else if(camera_align)
        {
            x-=camera_x;
        }

        if(depth_effect_y>0)
        {
            y+=camera_y/depth_effect_y;
        }else if(depth_effect_y<0)
        {
            y+=camera_y*-depth_effect_y;
        }else if(camera_align)
        {
            y+=camera_y;
        }

        glColor4ub((*i)->color.red,(*i)->color.green,(*i)->color.blue,(*i)->color.alpha);
        glVertex3f(x, y, 0.0f);
    }

    glEnd( );
    glFlush();
    glPopMatrix();
}

void RosalilaGraphics::drawTriangles(vector<DrawableTriangle*>triangles, int depth_effect_x, int depth_effect_y,bool camera_align)
{
    glLoadIdentity();
    glMatrixMode( GL_MODELVIEW );

    glPushMatrix();

    glDisable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glDisable (GL_DEPTH_TEST);

    glDisable(GL_TEXTURE_2D);

    glTranslatef(0,0, 1.0);

    glBegin(GL_TRIANGLES);

    for(int i=0;i<(int)triangles.size();i++)
    {
        double grey_scale = (triangles[i]->color.red+triangles[i]->color.green+triangles[i]->color.blue)/3;

        double red_difference = triangles[i]->color.red-grey_scale;
        double green_difference = triangles[i]->color.green-grey_scale;
        double blue_difference = triangles[i]->color.blue-grey_scale;

        triangles[i]->color.red = grey_scale + red_difference * grayscale_effect.current_percentage;
        triangles[i]->color.green = grey_scale + green_difference * grayscale_effect.current_percentage;
        triangles[i]->color.blue = grey_scale + blue_difference * grayscale_effect.current_percentage;

        triangles[i]->color.alpha = (double)triangles[i]->color.alpha * transparency_effect.current_percentage;

        //Camera and depth effect
        if(depth_effect_x>0)
        {
            triangles[i]->x-=camera_x/depth_effect_x;
        }else if(depth_effect_x<0)
        {
            triangles[i]->x-=camera_x*-depth_effect_x;
        }else if(camera_align)
        {
            triangles[i]->x-=camera_x;
        }

        if(depth_effect_y>0)
        {
            triangles[i]->y+=camera_y/depth_effect_y;
        }else if(depth_effect_y<0)
        {
            triangles[i]->y+=camera_y*-depth_effect_y;
        }else if(camera_align)
        {
            triangles[i]->y+=camera_y;
        }

        triangles[i]->x += screen_shake_effect.current_x;
        triangles[i]->y += screen_shake_effect.current_y;

        triangles[i]->p1.x += triangles[i]->x;
        triangles[i]->p1.y += triangles[i]->y;
        triangles[i]->p2.x += triangles[i]->x;
        triangles[i]->p2.y += triangles[i]->y;
        triangles[i]->p3.x += triangles[i]->x;
        triangles[i]->p3.y += triangles[i]->y;

        Point center(triangles[i]->x,triangles[i]->y);//This should not be the center

        triangles[i]->p1 = rosalila()->utility->realRotateAroundPoint(triangles[i]->p1,center,triangles[i]->angle);
        triangles[i]->p2 = rosalila()->utility->realRotateAroundPoint(triangles[i]->p2,center,triangles[i]->angle);
        triangles[i]->p3 = rosalila()->utility->realRotateAroundPoint(triangles[i]->p3,center,triangles[i]->angle);

        glColor4ub(triangles[i]->color.red,triangles[i]->color.green,triangles[i]->color.blue,triangles[i]->color.alpha);

        glVertex2f(triangles[i]->p1.x, triangles[i]->p1.y);
        glVertex2f(triangles[i]->p2.x, triangles[i]->p2.y);
        glVertex2f(triangles[i]->p3.x, triangles[i]->p3.y);
    }

    glEnd();
    glFlush();
    glPopMatrix();
}

void RosalilaGraphics::frameCap()
{
    frame++;

    //If a second has passed since the caption was last updated

    //If we want to cap the frame rate
    int ticks_difference = SDL_GetTicks() - last_tick;
    if(ticks_difference < 1000 / frames_per_seccond)
    {
        //Sleep the remaining frame time
        SDL_Delay( ( 1000 / frames_per_seccond ) - ticks_difference );
    }

    last_tick = SDL_GetTicks();
}
void RosalilaGraphics::drawText(std::string text,int position_x,int position_y, bool center_x, bool center_y)
{
  position_x += screen_shake_effect.current_x;
  position_y += screen_shake_effect.current_y;

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
  if(center_x)
  {
      x1+=0.f+screen_width/2-message->w/2;
  }
  GLfloat y1=0.f+position_y;
  if(center_y)
  {
      y1+=0.f+screen_height/2-message->h/2;
  }
  GLfloat x2=0.f+x1+message->w;
  GLfloat y2=0.f+y1+message->h;
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

void RosalilaGraphics::drawText(TTF_Font* font, std::string text, int position_x, int position_y, bool center_x, bool center_y)
{
  position_x += screen_shake_effect.current_x;
  position_y += screen_shake_effect.current_y;

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
  if(center_x)
  {
      x1+=0.f+screen_width/2-message->w/2;
  }
  GLfloat y1=0.f+position_y;
  if(center_y)
  {
      y1+=0.f+screen_height/2-message->h/2;
  }
  GLfloat x2=0.f+x1+message->w;
  GLfloat y2=0.f+y1+message->h;
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

void RosalilaGraphics::updateScreen()
{
    std::string error= ">>>";
    error+=SDL_GetError();
    if(error!=">>>")
        rosalila()->utility->writeLogLine(error);
    frameCap();

    grayscale_effect.update();
    transparency_effect.update();
    screen_shake_effect.update();
    point_explosion_effect->update();

    drawPoints(point_explosion_effect->current_points, 0, 0, true);

    notification_handler.update();
    if(notification_handler.notifications.size()>0)
    {
        Notification* current_notification = *notification_handler.notifications.begin();

        rosalila()->graphics->draw2DImage
        (   notification_background,
            notification_background->getWidth(),notification_background->getHeight(),
            current_notification->x,current_notification->y,
            1.0,
            0.0,
            false,
            0,0,
            Color(255,255,255,255),
            0,0,
            false,
            FlatShadow());


        rosalila()->graphics->draw2DImage
        (   current_notification->image,
            current_notification->image->getWidth(),current_notification->image->getHeight(),
            current_notification->x,current_notification->y,
            1.0,
            0.0,
            false,
            0,0,
            Color(255,255,255,255),
            0,0,
            false,
            FlatShadow());
    }

    SDL_GL_SwapWindow(window);
}


void RosalilaGraphics::screenshot(int x, int y, int w, int h, string filename)
{
    unsigned char * pixels = new unsigned char[w*h*4]; // 4 bytes for RGBA
    glReadPixels(x,y,w, h, GL_BGRA, GL_UNSIGNED_BYTE, pixels);

    SDL_Surface * surf = SDL_CreateRGBSurfaceFrom(pixels, w, h, 8*4, w*4, 0,0,0,0);
    SDL_SaveBMP(surf, filename.c_str());

    SDL_FreeSurface(surf);
    delete [] pixels;
}

void RosalilaGraphics::clearScreen(Color color)
{
    float red = ((float)color.red)/255.0f;
    float green = ((float)color.green)/255.0f;
    float blue = ((float)color.blue)/255.0f;
    glClearColor( red, green, blue, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT );
}
