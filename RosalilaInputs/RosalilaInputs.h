#ifndef MYEVENTRECEIVER_H
#define MYEVENTRECEIVER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stdarg.h>
using namespace std;

#include "SDL2/SDL.h"
#include "../RosalilaUtility/RosalilaUtility.h"
#include "Button.h"

class Button;

const int max_joystick_inputs=50;

class RosalilaReceiver
{
public:
    bool button_up_flag;
    map<string,Button*> controls;

    int joystick;

    bool is_key_pressed[322];
    bool is_joy1_pressed[max_joystick_inputs];
    bool is_joy2_pressed[max_joystick_inputs];
    bool hat_up_pressed_player_1;
    bool hat_down_pressed_player_1;
    bool hat_left_pressed_player_1;
    bool hat_right_pressed_player_1;
    bool stick_up_pressed_player_1;
    bool stick_down_pressed_player_1;
    bool stick_left_pressed_player_1;
    bool stick_right_pressed_player_1;
    bool joy_up_pressed_player_2;
    bool joy_down_pressed_player_2;
    bool joy_left_pressed_player_2;
    bool joy_right_pressed_player_2;

    void init();
    bool isKeyDown(int keycode);
    bool isKeyPressed(int keycode);
    bool isJoyDown(int joyCode,int joystick);
    bool isJoyPressed(int joyCode,int joystick);
    void updateInputs();
    void unpressAllInputs();

    bool isPressed(string action_name);
    bool isDown(string action_name);
};

#endif // MYEVENTRECEIVER_H>
