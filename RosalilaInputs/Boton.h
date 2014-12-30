#ifndef BOTON_H
#define BOTON_H

#include "../RosalilaInputs/Receiver.h"

class Boton
{
private:


    bool usando_joystick;
    int num_joystick;
    Receiver* receiver;
public:
int joystick;
std::string mapeo;
int teclado;
    Boton(Receiver* receiver,int teclado,std::string mapeo);
    Boton(Receiver* receiver,int joystick,int num_joystick,std::string mapeo);
    bool estaPresionado();
    std::string getMapeo();
    std::string getRosalilaInputs();
    int getNumJoystick();
    bool usaJoystick();
    std::string keyToString();
};

#endif
