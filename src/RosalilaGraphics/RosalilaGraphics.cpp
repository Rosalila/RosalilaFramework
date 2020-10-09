#include "RosalilaGraphics/RosalilaGraphics.h"

RosalilaGraphics::RosalilaGraphics()
{

}

void RosalilaGraphics::initImageFont()
{
    rosalila()->utility->writeLogLine("Setting up image font");
    this->image_font = NULL;
    Node* root_node = rosalila()->parser->getNodes(CONFIG_FILE_PATH);
    Node* image_font_node = root_node->getNodeByName("image_font");
    if(image_font_node)
    {
        if(image_font_node->hasAttribute("path"))
        {
            std::cout<<"Image font path: "<<image_font_node->attributes["path"]<<endl;
            this->image_font = this->getImage(assets_directory + image_font_node->attributes["path"]);
        }
    }

    if(!this->image_font)
    {
        rosalila()->utility->writeLogLine("Warning: Could not load image font");
        return;
    }

    GLubyte* pixels = new GLubyte[this->image_font->width*this->image_font->height*4];
    glBindTexture(GL_TEXTURE_2D, this->image_font->texture);
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    //Set the cell dimensions
    int cellW = this->image_font->width / 16;
    int cellH = this->image_font->height / 16;

    //New line variables
    int top = cellH;
    int baseA = cellH;

    int currentChar = 0;

    //Go through the cell rows
    for( int rows = 0; rows < 16; ++rows )
    {
        //Go through the cell columns
        for( int cols = 0; cols < 16; ++cols )
        {
            //Set the character offset
            image_font_character_rectangles[ currentChar ].x = cellW * cols;
            image_font_character_rectangles[ currentChar ].y = cellH * rows;

            //Set the dimensions of the character
            image_font_character_rectangles[ currentChar ].w = cellW;
            image_font_character_rectangles[ currentChar ].h = cellH;

            //Find Left Side
            //Go through pixel columns
            for( int pCol = 0; pCol < cellW; ++pCol )
            {
                //Go through pixel rows
                for( int pRow = 0; pRow < cellH; ++pRow )
                {
                    //Get the pixel offsets
                    int pX = ( cellW * cols ) + pCol;
                    int pY = ( cellH * rows ) + pRow;

                    size_t row = pRow * 256;
                    size_t col = pCol * 4;

                    //If a non colorkey pixel is found
                    if( pixels[row + col + 0] )
                    {
                        //Set the x offset
                        image_font_character_rectangles[ currentChar ].x = pX;

                        //Break the loops
                        pCol = cellW;
                        pRow = cellH;
                    }
                }
            }

            //Find Right Side
            //Go through pixel columns
            for( int pColW = cellW - 1; pColW >= 0; --pColW )
            {
                //Go through pixel rows
                for( int pRowW = 0; pRowW < cellH; ++pRowW )
                {
                    //Get the pixel offsets
                    int pX = ( cellW * cols ) + pColW;
                    int pY = ( cellH * rows ) + pRowW;

                    //If a non colorkey pixel is found
                    if( pixels[pX+pY+3] )
                    {
                        //Set the width
                        image_font_character_rectangles[ currentChar ].w = ( pX - image_font_character_rectangles[ currentChar ].x ) + 1;

                        //Break the loops
                        pColW = -1;
                        pRowW = cellH;
                    }
                }
            }

            //Find Top
            //Go through pixel rows
            for( int pRow = 0; pRow < cellH; ++pRow )
            {
                //Go through pixel columns
                for( int pCol = 0; pCol < cellW; ++pCol )
                {
                    //Get the pixel offsets
                    int pX = ( cellW * cols ) + pCol;
                    int pY = ( cellH * rows ) + pRow;

                    //If a non colorkey pixel is found
                    if( pixels[pX+pY+3] )
                    {
                        //If new top is found
                        if( pRow < top )
                        {
                            top = pRow;
                        }

                        //Break the loops
                        pCol = cellW;
                        pRow = cellH;
                    }
                }
            }

            //Find Bottom of A
            if( currentChar == 'A' )
            {
                //Go through pixel rows
                for( int pRow = cellH - 1; pRow >= 0; --pRow )
                {
                    //Go through pixel columns
                    for( int pCol = 0; pCol < cellW; ++pCol )
                    {
                        //Get the pixel offsets
                        int pX = ( cellW * cols ) + pCol;
                        int pY = ( cellH * rows ) + pRow;

                        //If a non colorkey pixel is found
                        if( pixels[pX+pY+3] )
                        {
                            //Bottom of a is found
                            baseA = pRow;

                            //Break the loops
                            pCol = cellW;
                            pRow = -1;
                        }
                    }
                }
            }

            //Go to the next character
            ++currentChar;
        }
    }

    //Calculate space
    this->image_font_space = cellW / 2;

    //Calculate new line
    this->image_font_new_line_space = baseA - top;

    //Lop off excess top pixels
    for( int i = 0; i < 256; ++i )
    {
        image_font_character_rectangles[ i ].y += top;
        image_font_character_rectangles[ i ].h -= top;
    }
}

void RosalilaGraphics::drawText( int x, int y, std::string text )
{
    if( this->image_font )
    {
		int curX = x, curY = y;
        for( int i = 0; i < (int)text.length(); ++i )
        {
            if( text[ i ] == ' ' )
            {
                curX += this->image_font_space;
            }
            else if( text[ i ] == '\n' )
            {
                curY += this->image_font_new_line_space;
                curX = x;
            }
            else
            {
                int ascii = (unsigned char)text[ i ];
                this->image_font->color_filter.red=255;
                this->image_font->color_filter.green=255;
                this->image_font->color_filter.blue=255;
                this->image_font->color_filter.alpha=255;
                this->drawCroppedImage (this->image_font, curX, curY, image_font_character_rectangles[ ascii ].x, image_font_character_rectangles[ ascii ].y, image_font_character_rectangles[ ascii ].w, image_font_character_rectangles[ ascii ].h);
                curX += image_font_character_rectangles[ ascii ].w + 1;
            }
        }
    }
}

void RosalilaGraphics::init()
{
    rosalila()->utility->writeLogLine("Initializing graphics");
    screen_shake_effect.init();
    grayscale_effect.init();
    transparency_effect.init();
    point_explosion_effect =  new PointExplosionEffect();

    rosalila()->utility->writeLogLine("Parsing config");
    //XML Initializations
    Node* root_node = rosalila()->parser->getNodes(CONFIG_FILE_PATH);

    Node* resolution_node = root_node->getNodeByName("resolution");
    screen_width=atoi(resolution_node->attributes["x"].c_str());
    screen_height=atoi(resolution_node->attributes["y"].c_str());

    Node* screen_size_node = root_node->getNodeByName("screen_size");
    int screen_resized_width=atoi(screen_size_node->attributes["x"].c_str());
    int screen_resized_height=atoi(screen_size_node->attributes["y"].c_str());

    Node* fullscreen_node = root_node->getNodeByName("fullscreen");
    fullscreen=fullscreen_node->attributes["enabled"]=="yes";

    //Internal initializations
    joystick_1 = NULL;
    joystick_2 = NULL;

    screen_bpp = 32;

    rosalila()->utility->writeLogLine("Initializing SDL");
    //Initialize all SDL subsystems
    if( SDL_Init(/*SDL_INIT_VIDEO |*/ SDL_INIT_JOYSTICK) < 0 )
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

    rosalila()->utility->writeLogLine("Setting up font");
    int font_size=10;
    int font_red=0;
    int font_green=0;
    int font_blue=0;
    this->font = NULL;
    Node* font_node = root_node->getNodeByName("font");
    if(font_node)
    {
        if(font_node->hasAttribute("size"))
        {
            font_size=atoi(font_node->attributes["size"].c_str());
        }
        if(font_node->hasAttribute("red"))
        {
            font_red=atoi(font_node->attributes["red"].c_str());
        }
        if(font_node->hasAttribute("green"))
        {
            font_green=atoi(font_node->attributes["green"].c_str());
        }
        if(font_node->hasAttribute("blue"))
        {
            font_blue=atoi(font_node->attributes["blue"].c_str());
        }
        if(font_node->hasAttribute("path"))
        {
            std::cout<<"TTF path"<<font_node->attributes["path"]<<endl;
            this->font = TTF_OpenFont( font_node->attributes["path"].c_str(), font_size );
        }
    }

    textColor.r = font_red;
    textColor.g = font_green;
    textColor.b = font_blue;
    
    if(font==NULL)
    {
        rosalila()->utility->writeLogLine("Error: Could not init font.");
    }else
    {
        rosalila()->utility->writeLogLine("Font initialized.");
    }

    rosalila()->utility->writeLogLine("OpenGL stuff");
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); // *new*

    rosalila()->utility->writeLogLine("Windowed or fullscreen setup stuff");
    window = SDL_CreateWindow( "Rosalila Framework", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               screen_resized_width, screen_resized_height,
                               SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    if(!window)
    {
        //rosalila()->utility->writeLogLine("Could not init window");
    }

    if(fullscreen)
        SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);

    rosalila()->utility->writeLogLine("More GL stuff");
    SDL_GL_CreateContext(window);
    GLenum error = GL_NO_ERROR;
    error = glGetError();
    if( error != GL_NO_ERROR ) {
         exit(12);
    }

    #ifndef OSX
        //glewInit();
    #endif

    rosalila()->utility->writeLogLine("GL flags setup");
    printf("OpenGL version supported by this platform (%s): \n",
    glGetString(GL_VERSION));
    //Set the openGL state?
    //glEnable( GL_TEXTURE_2D );
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    rosalila()->utility->writeLogLine("GL flags setupA");
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    glViewport( 0, 0, screen_resized_width, screen_resized_height );

    rosalila()->utility->writeLogLine("GL flags setupB");
    glClear( GL_COLOR_BUFFER_BIT );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    rosalila()->utility->writeLogLine("GL flags setupC");
    glOrtho(0.0f, screen_width, screen_height, 0.0f, -1.0f, 1.0f);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    rosalila()->utility->writeLogLine("GL flags setupD");
    //Fps cap
    frames_per_seccond = 60;
    frame = 0;
    last_tick=SDL_GetTicks();

    rosalila()->utility->writeLogLine("Setting up inputs");
    //Init joystickss
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

    rosalila()->utility->writeLogLine("Notifications");
    notification_background = NULL;
    notification_background_x = 0;
    notification_background_y = 0;

    if(root_node->hasAttribute("notifications"))
    {
        Node* notifications_node = root_node->getNodeByName("notifications");
        if(notifications_node->hasAttribute("background_path"))
        {
            notification_background = getImage(notifications_node->attributes["background_path"]);
            notification_background_x = screen_width/2 - notification_background->getWidth()/2;
            notification_background_y = screen_height - notification_background->getHeight();
        }
    }

    #ifndef OSX
        //glewInit();
    #endif

    SDL_SetWindowPosition(window, 0, 0);

    initImageFont();

    rosalila()->utility->writeLogLine("Graphics initialization finished");
}

RosalilaGraphics::~RosalilaGraphics()
{
    //Quit SDL
    SDL_Quit();
}


Image* RosalilaGraphics::getImage(std::string filename)
{
    if(!rosalila()->utility->fileExists(filename))
    {
        rosalila()->utility->writeLogLine("Warning: "+ filename+ " does not exist. Image could not be loaded.");        
        return NULL;
    }
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

void RosalilaGraphics::drawImage (Image* texture, int x, int y)
{
    double grey_scale = (texture->color_filter.red+texture->color_filter.green+texture->color_filter.blue)/3;

    double red_difference = texture->color_filter.red-grey_scale;
    double green_difference = texture->color_filter.green-grey_scale;
    double blue_difference = texture->color_filter.blue-grey_scale;

    texture->color_filter.red = (int)(grey_scale + red_difference * grayscale_effect.current_percentage);
	texture->color_filter.green = (int)(grey_scale + green_difference * grayscale_effect.current_percentage);
    texture->color_filter.blue = (int)(grey_scale + blue_difference * grayscale_effect.current_percentage);

    texture->color_filter.alpha = (int)(texture->color_filter.alpha * transparency_effect.current_percentage);

    glEnable( GL_TEXTURE_2D );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0.0f, screen_width, screen_height, 0.0f, -1.0f, 1.0f);
    glMatrixMode( GL_MODELVIEW );

    glDisable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glDisable (GL_DEPTH_TEST);

    //Screen shake
    x += screen_shake_effect.current_x;
    y += screen_shake_effect.current_y;

    GLfloat x1 = 0.f + x;
    GLfloat y1 = 0.f + y;
    GLfloat x2 = 0.f + x + (float)texture->width * texture->scale;
    GLfloat y2 = 0.f + y + (float)texture->height * texture->scale;

    //Flip
    if(texture->horizontal_flip)
    {
        GLfloat temp=x1;
        x1=x2;
        x2=temp;
    }

    //OpenGL draw
    //Save the current matrix.
    glPushMatrix();
    //Change the current matrix.
    float translate_x = (x2-x1) / 2 + x;
    float translate_y = (y2-y1) /2 + y;
    glTranslatef(translate_x,translate_y, 1.0);
    glRotatef(-texture->rotation, 0, 0, 1.0);

    glColor4ub(texture->color_filter.red, texture->color_filter.green, texture->color_filter.blue,texture->color_filter.alpha);
    glEnable(GL_BLEND);
    //glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE); // additive
    // GL_ONE_MINUS_SRC_COLOR - funky
    // GL_SRC_ALPHA - wuut
    // GL_ONE_MINUS_SRC_ALPHA - standard
    // GL_ONE - additive
    // glBlendFunc(GL_ZERO, GL_SRC_ALPHA);
    //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE);
    //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFuncSeparate(GL_SRC_COLOR, GL_ONE, GL_ZERO, GL_ONE_MINUS_SRC_COLOR);
    
    /*
    if(texture->blend_effect)
        glBlendFuncSeparate(GL_ONE, GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    else
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    */
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

void RosalilaGraphics::drawCroppedImage (Image* texture, int x, int y, int crop_x, int crop_y, int crop_width, int crop_height)
{
    double grey_scale = (texture->color_filter.red+texture->color_filter.green+texture->color_filter.blue)/3;

    double red_difference = texture->color_filter.red-grey_scale;
    double green_difference = texture->color_filter.green-grey_scale;
    double blue_difference = texture->color_filter.blue-grey_scale;

    texture->color_filter.red = (int)(grey_scale + red_difference * grayscale_effect.current_percentage);
    texture->color_filter.green = (int)(grey_scale + green_difference * grayscale_effect.current_percentage);
    texture->color_filter.blue = (int)(grey_scale + blue_difference * grayscale_effect.current_percentage);

    texture->color_filter.alpha = (int)(texture->color_filter.alpha * transparency_effect.current_percentage);

    glEnable( GL_TEXTURE_2D );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0.0f, screen_width, screen_height, 0.0f, -1.0f, 1.0f);
    glMatrixMode( GL_MODELVIEW );

    glDisable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glDisable (GL_DEPTH_TEST);

    //Screen shake
    x += screen_shake_effect.current_x;
    y += screen_shake_effect.current_y;

    
    double x_crop_percent = double(crop_x) / texture->width;
    double width_crop_percenent = double(crop_width) / texture->width;
    double y_crop_percent = double(crop_y) / texture->height;
    double height_crop_percent = double(crop_height) / texture->height;

    GLfloat x1 = 0.f + x;
    GLfloat y1 = 0.f + y;
    GLfloat x2 = 0.f + x + (float)texture->width * texture->scale;
    GLfloat y2 = 0.f + y + (float)texture->height * texture->scale;

    x1 *= (GLfloat)width_crop_percenent;
    x2 *= (GLfloat)width_crop_percenent;
    y1 *= (GLfloat)height_crop_percent;
    y2 *= (GLfloat)height_crop_percent;

    //Flip
    if(texture->horizontal_flip)
    {
        GLfloat temp=x1;
        x1=x2;
        x2=temp;
    }

    //OpenGL draw
    //Save the current matrix.
    glPushMatrix();
    //Change the current matrix.
    float translate_x = (x2-x1) / 2 + x;
    float translate_y = (y2-y1) /2 + y;
    glTranslatef(translate_x,translate_y, 1.0);
    glRotatef(-texture->rotation, 0, 0, 1.0);

    glColor4ub(texture->color_filter.red, texture->color_filter.green, texture->color_filter.blue,texture->color_filter.alpha);
    glEnable(GL_BLEND);
    //glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE); // additive
    // GL_ONE_MINUS_SRC_COLOR - funky
    // GL_SRC_ALPHA - wuut
    // GL_ONE_MINUS_SRC_ALPHA - standard
    // GL_ONE - additive
    // glBlendFunc(GL_ZERO, GL_SRC_ALPHA);
    //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE);
    //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFuncSeparate(GL_SRC_COLOR, GL_ONE, GL_ZERO, GL_ONE_MINUS_SRC_COLOR);
    
    /*
    if(texture->blend_effect)
        glBlendFuncSeparate(GL_ONE, GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    else
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    */
    glBindTexture( GL_TEXTURE_2D, texture->getTexture() );


    glBegin( GL_QUADS);
        //Bottom-left vertex (corner)
        glTexCoord2f((GLfloat)x_crop_percent, (GLfloat)y_crop_percent);
        glVertex3d(x1, y1, 0.0f);

        //Bottom-right vertex (corner)
        glTexCoord2f((GLfloat)(width_crop_percenent + x_crop_percent), (GLfloat)y_crop_percent);
        glVertex3d(x2, y1, 0.f);

        //Top-right vertex (corner)
        glTexCoord2f((GLfloat)(width_crop_percenent + x_crop_percent), (GLfloat)(height_crop_percent + y_crop_percent));
        glVertex3d(x2, y2, 0.f);

        //Top-left vertex (corner)
        glTexCoord2f((GLfloat)x_crop_percent, (GLfloat)(height_crop_percent + y_crop_percent));
        glVertex3d(x1, y2, 0.f);
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
             Color color_effects)
{
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


void RosalilaGraphics::drawRectangle(int x,int y,int width,int height,float rotation,int red,int green,int blue,int alpha)
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0.0f, screen_width, screen_height, 0.0f, -1.0f, 1.0f);
    glMatrixMode( GL_MODELVIEW );

    glDisable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glDisable (GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_TEXTURE_2D);
    GLubyte r=red;
    GLubyte g=green;
    GLubyte b=blue;
    GLubyte a=alpha;
    glColor4ub(r,g,b,a);

    //OpenGL draw
    //Save the current matrix.
    glPushMatrix();
    //Change the current matrix.
	GLfloat translate_x = (GLfloat)x;
	GLfloat translate_y = (GLfloat)y;
    glTranslatef(translate_x,translate_y, 1.0);
    glRotatef(-rotation, 0, 0, 1.0);
    x -= (int)translate_x;
    y -= (int)translate_y;

//    glRecti(x, y, width+x, height+y);



    glBegin(GL_QUADS);   //We want to draw a quad, i.e. shape with four sides
      glColor4ub(red,green,blue,alpha);
      glVertex2f(0, 0);
      glVertex2f(0, (GLfloat)height);
      glVertex2f((GLfloat)width, (GLfloat)height);
      glVertex2f((GLfloat)width, 0);
    glEnd();

    glFlush();

    //Reset the current matrix to the one that was saved.
    glPopMatrix();
}

void RosalilaGraphics::drawRectangles(vector<DrawableRectangle*>rectangles)
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

        rectangles[i]->color.red = (int)(grey_scale + red_difference * grayscale_effect.current_percentage);
        rectangles[i]->color.green = (int)(grey_scale + green_difference * grayscale_effect.current_percentage);
        rectangles[i]->color.blue = (int)(grey_scale + blue_difference * grayscale_effect.current_percentage);

        rectangles[i]->color.alpha = (int)(rectangles[i]->color.alpha * transparency_effect.current_percentage);

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

        p1 = rosalila()->utility->realRotateAroundPoint(p1,center, (float)rectangles[i]->angle);
        p2 = rosalila()->utility->realRotateAroundPoint(p2,center, (float)rectangles[i]->angle);
        p3 = rosalila()->utility->realRotateAroundPoint(p3,center, (float)rectangles[i]->angle);
        p4 = rosalila()->utility->realRotateAroundPoint(p4,center, (float)rectangles[i]->angle);

        glColor4ub(rectangles[i]->color.red,rectangles[i]->color.green,rectangles[i]->color.blue,rectangles[i]->color.alpha);

        glVertex2f((GLfloat)p1.x, (GLfloat)p1.y);
        glVertex2f((GLfloat)p2.x, (GLfloat)p2.y);
        glVertex2f((GLfloat)p3.x, (GLfloat)p3.y);
        glVertex2f((GLfloat)p4.x, (GLfloat)p4.y);
    }

    glEnd();
    glFlush();
    glPopMatrix();
}

void RosalilaGraphics::drawPoints(list<DrawablePoint*>points)
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

        glColor4ub((*i)->color.red,(*i)->color.green,(*i)->color.blue,(*i)->color.alpha);
        glVertex3f((GLfloat)x, (GLfloat)y, 0.0f);
    }

    glEnd( );
    glFlush();
    glPopMatrix();
}

void RosalilaGraphics::drawTriangles(vector<DrawableTriangle*>triangles)
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

        triangles[i]->color.red = (int)(grey_scale + red_difference * grayscale_effect.current_percentage);
        triangles[i]->color.green = (int)(grey_scale + green_difference * grayscale_effect.current_percentage);
        triangles[i]->color.blue = (int)(grey_scale + blue_difference * grayscale_effect.current_percentage);

        triangles[i]->color.alpha = (int)(triangles[i]->color.alpha * transparency_effect.current_percentage);

        triangles[i]->x += screen_shake_effect.current_x;
        triangles[i]->y += screen_shake_effect.current_y;

        triangles[i]->p1.x += triangles[i]->x;
        triangles[i]->p1.y += triangles[i]->y;
        triangles[i]->p2.x += triangles[i]->x;
        triangles[i]->p2.y += triangles[i]->y;
        triangles[i]->p3.x += triangles[i]->x;
        triangles[i]->p3.y += triangles[i]->y;

        Point center(triangles[i]->x,triangles[i]->y);//This should not be the center

        triangles[i]->p1 = rosalila()->utility->realRotateAroundPoint(triangles[i]->p1,center, (GLfloat)triangles[i]->angle);
        triangles[i]->p2 = rosalila()->utility->realRotateAroundPoint(triangles[i]->p2,center, (GLfloat)triangles[i]->angle);
        triangles[i]->p3 = rosalila()->utility->realRotateAroundPoint(triangles[i]->p3,center, (GLfloat)triangles[i]->angle);

        glColor4ub(triangles[i]->color.red,triangles[i]->color.green,triangles[i]->color.blue,triangles[i]->color.alpha);

        glVertex2f((GLfloat)triangles[i]->p1.x, (GLfloat)triangles[i]->p1.y);
        glVertex2f((GLfloat)triangles[i]->p2.x, (GLfloat)triangles[i]->p2.y);
        glVertex2f((GLfloat)triangles[i]->p3.x, (GLfloat)triangles[i]->p3.y);
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
    frameCap();

    grayscale_effect.update();
    transparency_effect.update();
    screen_shake_effect.update();
    point_explosion_effect->update();

    drawPoints(point_explosion_effect->current_points);

    notification_handler.update();
    if(notification_handler.notifications.size()>0)
    {
        Notification* current_notification = *notification_handler.notifications.begin();

        if(notification_background)
        rosalila()->graphics->drawImage(notification_background, 
                                          current_notification->x,
                                          current_notification->y);

        rosalila()->graphics->drawImage(current_notification->image, 
                                          current_notification->x,
                                          current_notification->y);
    }

    SDL_GL_SwapWindow(window);
    //clearScreen(Color(255,255,255,255));
    clearScreen(Color(0,0,0,0));
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
