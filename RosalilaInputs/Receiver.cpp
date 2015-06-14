#include "RosalilaInputs.h"

Receiver::Receiver()
{
    for(int i = 0; i < 322; i++)   // init them all to false
    {
        KEYS[i] = false;
    }

    for(int i = 0; i < max_joystick_inputs; i++)   // init them all to false
    {
        JOYKEYS_player1[i] = false;
    }
    for(int i = 0; i < max_joystick_inputs; i++)   // init them all to false
    {
        JOYKEYS_player2[i] = false;
    }

    joy_up_pressed_player_1=false;
    joy_down_pressed_player_1=false;
    joy_left_pressed_player_1=false;
    joy_right_pressed_player_1=false;
    joy_up_pressed_player_2=false;
    joy_down_pressed_player_2=false;
    joy_left_pressed_player_2=false;
    joy_right_pressed_player_2=false;


//    SDL_EnableKeyRepeat(0,0);
}

bool Receiver::isKeyPressed(int keycode)
{
    if(KEYS[keycode])
    {
        KEYS[keycode]=false;
        return true;
    }
    return false;
}

bool Receiver::isKeyDown(int keycode)
{
    if(keycode>=332)
    {
        cout<<keycode<<endl;cout.flush();
//        exit(keycode);
        return false;
    }
    if(KEYS[keycode])
    {
        //KEYS[keycode]=false;
        return true;
    }
    return false;
//  if (keystates[keycode])
//  {
//     return true;
//  }
//  else
//  {
//     return false;
//  }
}

bool Receiver::isOuyaDown(char key)
{
    //Unimplemented for PC
    return false;
}

bool Receiver::isOuyaPressed(char key)
{
    //Unimplemented for PC
    return false;
}

bool Receiver::isJoyDown(int joyCode,int joystick)
{
    if(joystick==0)
    {
        if(joyCode==-1)
            return joy_down_pressed_player_1 && joy_left_pressed_player_1;
        if(joyCode==-3)
            return joy_down_pressed_player_1 && joy_right_pressed_player_1;
        if(joyCode==-7)
            return joy_up_pressed_player_1 && joy_left_pressed_player_1;
        if(joyCode==-9)
            return joy_up_pressed_player_1 && joy_right_pressed_player_1;
        if(joyCode==-2)
            return joy_down_pressed_player_1;
        if(joyCode==-4)
            return joy_left_pressed_player_1;
        if(joyCode==-6)
            return joy_right_pressed_player_1;
        if(joyCode==-8)
            return joy_up_pressed_player_1;
        if(JOYKEYS_player1[joyCode])
        {
            return true;
        }
        return false;
    }
    if(joystick==1)
    {
        if(joyCode==-1)
            return joy_down_pressed_player_2 && joy_left_pressed_player_2;
        if(joyCode==-3)
            return joy_down_pressed_player_2 && joy_right_pressed_player_2;
        if(joyCode==-7)
            return joy_up_pressed_player_2 && joy_left_pressed_player_2;
        if(joyCode==-9)
            return joy_up_pressed_player_2 && joy_right_pressed_player_2;
        if(joyCode==-2)
            return joy_down_pressed_player_2;
        if(joyCode==-4)
            return joy_left_pressed_player_2;
        if(joyCode==-6)
            return joy_right_pressed_player_2;
        if(joyCode==-8)
            return joy_up_pressed_player_2;
        if(JOYKEYS_player2[joyCode])
        {
            return true;
        }
        return false;
    }
    return false;
}

bool Receiver::isJoyPressed(int joyCode,int joystick)
{
    if(joystick==0)
    {
        if(joyCode==-1)
        {
            if(joy_down_pressed_player_1 && joy_left_pressed_player_1)
            {
                joy_down_pressed_player_1 = false;
                joy_left_pressed_player_1 = false;
                return true;
            }
        }
        if(joyCode==-3 && joy_down_pressed_player_1 && joy_right_pressed_player_1)
        {
            joy_down_pressed_player_1 = false;
            joy_right_pressed_player_1 = false;
            return true;
        }
        if(joyCode==-7 && joy_up_pressed_player_1 && joy_left_pressed_player_1)
        {
            joy_up_pressed_player_1 = false;
            joy_left_pressed_player_1 = false;
            return true;
        }
        if(joyCode==-9 && joy_up_pressed_player_1 && joy_right_pressed_player_1)
        {
            joy_up_pressed_player_1 = false;
            joy_right_pressed_player_1 = false;
            return true;
        }
        if(joyCode==-2 && joy_down_pressed_player_1)
        {
            joy_down_pressed_player_1 = false;
            return true;
        }
        if(joyCode==-4 && joy_left_pressed_player_1)
        {
            joy_left_pressed_player_1 = false;
            return true;
        }
        if(joyCode==-6 && joy_right_pressed_player_1)
        {
            joy_right_pressed_player_1 = false;
            return true;
        }
        if(joyCode==-8 && joy_up_pressed_player_1)
        {
            joy_up_pressed_player_1 = false;
            return true;
        }
        if(JOYKEYS_player1[joyCode])
        {
            JOYKEYS_player1[joyCode] = false;
            return true;
        }
        return false;
    }
    if(joystick==1)
    {
        if(joyCode==-1)
        {
            if(joy_down_pressed_player_2 && joy_left_pressed_player_2)
            {
                joy_down_pressed_player_2 = false;
                joy_left_pressed_player_2 = false;
                return true;
            }
        }
        if(joyCode==-3 && joy_down_pressed_player_2 && joy_right_pressed_player_2)
        {
            joy_down_pressed_player_2 = false;
            joy_right_pressed_player_2 = false;
            return true;
        }
        if(joyCode==-7 && joy_up_pressed_player_2 && joy_left_pressed_player_2)
        {
            joy_up_pressed_player_2 = false;
            joy_left_pressed_player_2 = false;
            return true;
        }
        if(joyCode==-9 && joy_up_pressed_player_2 && joy_right_pressed_player_2)
        {
            joy_up_pressed_player_2 = false;
            joy_right_pressed_player_2 = false;
            return true;
        }
        if(joyCode==-2 && joy_down_pressed_player_2)
        {
            joy_down_pressed_player_1 = false;
            return true;
        }
        if(joyCode==-4 && joy_left_pressed_player_2)
        {
            joy_left_pressed_player_2 = false;
            return true;
        }
        if(joyCode==-6 && joy_right_pressed_player_2)
        {
            joy_right_pressed_player_2 = false;
            return true;
        }
        if(joyCode==-8 && joy_up_pressed_player_2)
        {
            joy_up_pressed_player_2 = false;
            return true;
        }
        if(JOYKEYS_player2[joyCode])
        {
            JOYKEYS_player2[joyCode] = false;
            return true;
        }
        return false;
    }
    return false;
}

void Receiver::updateInputs()
{
    //While there's events to handle
    SDL_Event event;
    while( SDL_PollEvent( &event ) )
    {
        //If the user has Xed out the window
        if( event.type == SDL_QUIT )
        {
            exit(0);
        }
        if( event.type == SDL_KEYDOWN )
        {
            if(event.key.keysym.sym==SDLK_UP)
                KEYS[SDL_SCANCODE_UP] = true;
            else if(event.key.keysym.sym==SDLK_DOWN)
                KEYS[SDL_SCANCODE_DOWN] = true;
            else if(event.key.keysym.sym==SDLK_LEFT)
                KEYS[SDL_SCANCODE_LEFT] = true;
            else if(event.key.keysym.sym==SDLK_RIGHT)
                KEYS[SDL_SCANCODE_RIGHT] = true;
            else if(event.key.keysym.sym<322)
                KEYS[event.key.keysym.sym] = true;
            else
                writeLogLine("Key pressed but not supported:"+toString(event.key.keysym.sym));
        }
        if( event.type == SDL_KEYUP )
        {
            if(event.key.keysym.sym==SDLK_UP)
                KEYS[SDL_SCANCODE_UP] = false;
            else if(event.key.keysym.sym==SDLK_DOWN)
                KEYS[SDL_SCANCODE_DOWN] = false;
            else if(event.key.keysym.sym==SDLK_LEFT)
                KEYS[SDL_SCANCODE_LEFT] = false;
            else if(event.key.keysym.sym==SDLK_RIGHT)
                KEYS[SDL_SCANCODE_RIGHT] = false;
            else if(event.key.keysym.sym<322)
                KEYS[event.key.keysym.sym] = false;
            else
                writeLogLine("Key pressed but not supported:"+toString(event.key.keysym.sym));
        }
        if( event.type == SDL_JOYBUTTONDOWN )
        {
            for(int i=0; i<max_joystick_inputs; i++)
            {
                if ( event.jbutton.button == i
                        && event.jbutton.which==0)
                {
                    JOYKEYS_player1[i]=true;
                }
            }
            for(int i=0; i<max_joystick_inputs; i++)
            {
                if ( event.jbutton.button == i
                        && event.jbutton.which==1)
                {
                    JOYKEYS_player2[i]=true;
                }
            }
        }
        if( event.type == SDL_JOYBUTTONUP )
        {
            for(int i=0; i<max_joystick_inputs; i++)
            {
                if ( event.jbutton.button == i
                        && event.jbutton.which==0)
                {
                    JOYKEYS_player1[i]=false;
                }
            }
            for(int i=0; i<max_joystick_inputs; i++)
            {
                if ( event.jbutton.button == i
                        && event.jbutton.which==1)
                {
                    JOYKEYS_player2[i]=false;
                }
            }
        }

        if( event.type == SDL_JOYHATMOTION)
        {
            //If joystick 0 has moved
            if( event.jhat.which == 0 )
            {
                joy_left_pressed_player_1=false;
                joy_right_pressed_player_1=false;
                joy_up_pressed_player_1=false;
                joy_down_pressed_player_1=false;
                switch(event.jhat.value)
                {
                case 8://Left
                    joy_left_pressed_player_1=true;
                    break;
                case 2://Right
                    joy_right_pressed_player_1=true;
                    break;
                case 1://Up
                    joy_up_pressed_player_1=true;
                    break;
                case 4://Down
                    joy_down_pressed_player_1=true;
                    break;
                case 9://Left up
                    joy_left_pressed_player_1=true;
                    joy_up_pressed_player_1=true;
                    break;
                case 3://Right up
                    joy_right_pressed_player_1=true;
                    joy_up_pressed_player_1=true;
                    break;
                case 12://left down
                    joy_left_pressed_player_1=true;
                    joy_down_pressed_player_1=true;
                    break;
                case 6://Right down
                    joy_right_pressed_player_1=true;
                    joy_down_pressed_player_1=true;
                    break;
                }

            }
            if( event.jhat.which == 1 )
            {
                joy_left_pressed_player_2=false;
                joy_right_pressed_player_2=false;
                joy_up_pressed_player_2=false;
                joy_down_pressed_player_2=false;
                switch(event.jhat.value)
                {
                case 8://Left
                    joy_left_pressed_player_2=true;
                    break;
                case 2://Right
                    joy_right_pressed_player_2=true;
                    break;
                case 1://Up
                    joy_up_pressed_player_2=true;
                    break;
                case 4://Down
                    joy_down_pressed_player_2=true;
                    break;
                case 9://Left up
                    joy_left_pressed_player_2=true;
                    joy_up_pressed_player_2=true;
                    break;
                case 3://Right up
                    joy_right_pressed_player_2=true;
                    joy_up_pressed_player_2=true;
                    break;
                case 12://left down
                    joy_left_pressed_player_2=true;
                    joy_down_pressed_player_2=true;
                    break;
                case 6://Right down
                    joy_right_pressed_player_2=true;
                    joy_down_pressed_player_2=true;
                    break;
                }
            }
        }

        if( event.type == SDL_JOYAXISMOTION )
        {
            //If joystick 0 has moved
            if( event.jaxis.which == 0 )
            {
                if( event.jaxis.axis == 0 )
                {
                    if( ( event.jaxis.value > -8000 ) && ( event.jaxis.value < 8000 ) )
                    {
                        joy_left_pressed_player_1=false;
                        joy_right_pressed_player_1=false;
                    }
                    else
                    {
                        if( event.jaxis.value < 0 )
                        {
                            joy_left_pressed_player_1=true;
                            joy_right_pressed_player_1=false;
                        }
                        else
                        {
                            joy_right_pressed_player_1=true;
                            joy_left_pressed_player_1=false;
                        }
                    }
                }
                //If the Y axis changed
                else if( event.jaxis.axis == 1 )
                {
                    if( ( event.jaxis.value > -8000 ) && ( event.jaxis.value < 8000 ) )
                    {
                        joy_up_pressed_player_1=false;
                        joy_down_pressed_player_1=false;
                    }
                    else
                    {
                        if( event.jaxis.value < 0 )
                        {
                            joy_up_pressed_player_1=true;
                            joy_down_pressed_player_1=false;
                        }
                        else
                        {
                            joy_down_pressed_player_1=true;
                            joy_up_pressed_player_1=false;
                        }
                    }
                }
            }

            if( event.jaxis.which == 1 )
            {
                if( event.jaxis.axis == 0 )
                {
                    if( ( event.jaxis.value > -8000 ) && ( event.jaxis.value < 8000 ) )
                    {
                        joy_left_pressed_player_2=false;
                        joy_right_pressed_player_2=false;
                    }
                    else
                    {
                        if( event.jaxis.value < 0 )
                        {
                            joy_left_pressed_player_2=true;
                            joy_right_pressed_player_2=false;
                        }
                        else
                        {
                            joy_left_pressed_player_2=false;
                            joy_right_pressed_player_2=true;
                        }
                    }
                }
                //If the Y axis changed
                else if( event.jaxis.axis == 1 )
                {
                    if( ( event.jaxis.value > -8000 ) && ( event.jaxis.value < 8000 ) )
                    {
                        joy_up_pressed_player_2=false;
                        joy_down_pressed_player_2=false;
                    }
                    else
                    {
                        if( event.jaxis.value < 0 )
                        {
                            joy_up_pressed_player_2=true;
                            joy_down_pressed_player_2=false;
                        }
                        else
                        {
                            joy_up_pressed_player_2=false;
                            joy_down_pressed_player_2=true;
                        }
                    }
                }
            }
        }

    }
    //SDL_GetKeyboardState( NULL );
}

void Receiver::unpressAllInputs()
{
    for(int i=0;i<255;i++)
        KEYS[i]=false;
    for(int i=0;i<max_joystick_inputs;i++)
        JOYKEYS_player1[i]=false;
    for(int i=0;i<max_joystick_inputs;i++)
        JOYKEYS_player2[i]=false;
}
