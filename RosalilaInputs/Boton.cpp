#include "Boton.h"

Boton::Boton(Receiver* receiver,int teclado,std::string mapeo)
{
    this->teclado=teclado;
    this->mapeo=mapeo;
    usando_joystick=false;
    this->receiver=receiver;
    //this->joystick=999;
}

Boton::Boton(Receiver* receiver,int joystick,int num_joystick,std::string mapeo)
{
    this->num_joystick=num_joystick;
    this->joystick=joystick;
    this->mapeo=mapeo;
    usando_joystick=true;
    this->receiver=receiver;
}

bool Boton::estaPresionado()
{
    if(usando_joystick)
    {
        if(receiver->isJoyDown(joystick,num_joystick))
            return true;
    }else
    {
        if (receiver->isKeyDown(teclado))
            return true;
    }
    return false;
}

std::string Boton::getMapeo()
{
    return mapeo;
}

std::string convertInt(int number)
{
    if (number == 0)
        return "0";
    std::string temp="";
    std::string returnvalue="";
    while (number>0)
    {
        temp+=number%10+48;
        number/=10;
    }
    for (int i=0;i<(int)temp.length();i++)
        returnvalue+=temp[temp.length()-i-1];
    return returnvalue;
}

std::string Boton::getRosalilaInputs()
{
    if(usando_joystick)
    {
        if(joystick>=0)
            return convertInt(joystick);
        if(joystick==-8)
            return std::string("up");
        if(joystick==-2)
            return std::string("down");
        if(joystick==-4)
            return std::string("left");
        if(joystick==-6)
            return std::string("right");
        return std::string("d");
    }else
    {
        return std::string(keyToString());
    }
}

std::string Boton::keyToString()
{
    if(teclado==SDLK_q)
        return "Q";
    if(teclado==SDLK_w)
        return "W";
    if(teclado==SDLK_e)
        return "E";
    if(teclado==SDLK_r)
        return "R";
    if(teclado==SDLK_t)
        return "T";
    if(teclado==SDLK_y)
        return "Y";
    if(teclado==SDLK_u)
        return "U";
    if(teclado==SDLK_i)
        return "I";
    if(teclado==SDLK_o)
        return "O";
    if(teclado==SDLK_p)
        return "P";
    if(teclado==SDLK_a)
        return "A";
    if(teclado==SDLK_s)
        return "S";
    if(teclado==SDLK_d)
        return "D";
    if(teclado==SDLK_f)
        return "F";
    if(teclado==SDLK_g)
        return "G";
    if(teclado==SDLK_h)
        return "H";
    if(teclado==SDLK_j)
        return "J";
    if(teclado==SDLK_k)
        return "K";
    if(teclado==SDLK_l)
        return "L";
    if(teclado==SDLK_z)
        return "Z";
    if(teclado==SDLK_x)
        return "X";
    if(teclado==SDLK_c)
        return "C";
    if(teclado==SDLK_v)
        return "V";
    if(teclado==SDLK_b)
        return "B";
    if(teclado==SDLK_n)
        return "N";
    if(teclado==SDLK_m)
        return "M";
    return "error!";
}

bool Boton::usaJoystick()
{
    return usando_joystick;
}

int Boton::getNumJoystick()
{
    return num_joystick;
}
