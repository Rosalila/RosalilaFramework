#ifndef BUTTON_H
#define BUTTON_H

#include "../RosalilaInputs/Receiver.h"

class Button
{
private:


    bool usando_joystick;
    int num_joystick;
    Receiver* receiver;
public:
int joystick;
std::string mapeo;
int teclado;
    Button(Receiver* receiver,int teclado,std::string mapeo);
    Button(Receiver* receiver,int joystick,int num_joystick,std::string mapeo);
    bool isPressed();
    bool isDown();
    std::string getMapeo();
    std::string getRosalilaInputs();
    int getNumJoystick();
    bool usaJoystick();
    std::string keyToString();
};

#endif
