#include "Button.h"

Button::Button(int key,std::string map)
{
    this->joystick_num=-1;
    this->joystick_button=-1;
    this->key=key;
    this->map=map;
    uses_joystick=false;
}

Button::Button(int joystick_button,int joystick_num,std::string map)
{
    this->key=-1;
    this->joystick_num=joystick_num;
    this->joystick_button=joystick_button;
    this->map=map;
    uses_joystick=true;
}

bool Button::isPressed()
{
    if(uses_joystick)
    {
        if(rosalila()->receiver->isJoyPressed(joystick_button,joystick_num))
            return true;
    }else
    {
        if (rosalila()->receiver->isKeyPressed(key))
            return true;
    }
    return false;
}

bool Button::isDown()
{
    if(uses_joystick)
    {
        if(rosalila()->receiver->isJoyDown(joystick_button,joystick_num))
            return true;
    }else
    {
        if (rosalila()->receiver->isKeyDown(key))
            return true;
    }
    return false;
}


std::string Button::getRosalilaInputs()
{
    if(uses_joystick)
    {
        if(joystick_button>=0)
            return rosalila()->utility->toString(joystick_button);
        if(joystick_button==-8)
            return std::string("up");
        if(joystick_button==-2)
            return std::string("down");
        if(joystick_button==-4)
            return std::string("left");
        if(joystick_button==-6)
            return std::string("right");
        return std::string("d");
    }else
    {
        return std::string(keyToString());
    }
}

std::string Button::keyToString()
{
    if(key==SDLK_q)
        return "Q";
    if(key==SDLK_w)
        return "W";
    if(key==SDLK_e)
        return "E";
    if(key==SDLK_r)
        return "R";
    if(key==SDLK_t)
        return "T";
    if(key==SDLK_y)
        return "Y";
    if(key==SDLK_u)
        return "U";
    if(key==SDLK_i)
        return "I";
    if(key==SDLK_o)
        return "O";
    if(key==SDLK_p)
        return "P";
    if(key==SDLK_a)
        return "A";
    if(key==SDLK_s)
        return "S";
    if(key==SDLK_d)
        return "D";
    if(key==SDLK_f)
        return "F";
    if(key==SDLK_g)
        return "G";
    if(key==SDLK_h)
        return "H";
    if(key==SDLK_j)
        return "J";
    if(key==SDLK_k)
        return "K";
    if(key==SDLK_l)
        return "L";
    if(key==SDLK_z)
        return "Z";
    if(key==SDLK_x)
        return "X";
    if(key==SDLK_c)
        return "C";
    if(key==SDLK_v)
        return "V";
    if(key==SDLK_b)
        return "B";
    if(key==SDLK_n)
        return "N";
    if(key==SDLK_m)
        return "M";
    return "error!";
}
