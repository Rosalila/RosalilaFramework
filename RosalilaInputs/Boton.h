#ifndef BUTTON_H
#define BUTTON_H

#include "../RosalilaInputs/Receiver.h"

class Button
{
public:
    Receiver* receiver;

    bool uses_joystick;
    int joystick_num;

    int joystick_button;
    int key;
    std::string map;

    Button(Receiver* receiver,int teclado,std::string mapeo);
    Button(Receiver* receiver,int joystick,int num_joystick,std::string mapeo);
    bool isPressed();
    bool isDown();
    std::string getRosalilaInputs();
    std::string keyToString();
};

#endif
