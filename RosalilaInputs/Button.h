#ifndef BUTTON_H
#define BUTTON_H

#include "../Rosalila.h"
#include "../RosalilaInputs/RosalilaInputs.h"

class Button
{
public:
    bool uses_joystick;
    int joystick_num;

    int joystick_button;
    int key;
    std::string map;

    Button(int teclado,std::string mapeo);
    Button(int joystick,int num_joystick,std::string mapeo);
    bool isPressed();
    bool isDown();
    std::string getRosalilaInputs();
    std::string keyToString();
};

#endif
