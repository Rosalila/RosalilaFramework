#include "RosalilaInputs/RosalilaInputs.h"

void RosalilaReceiver::init()
{
  for (int i = 0; i < 322; i++)
    is_key_pressed[i] = false;

  for (int i = 0; i < max_joystick_inputs; i++)
    is_joy1_pressed[i] = false;

  for (int i = 0; i < max_joystick_inputs; i++)
    is_joy2_pressed[i] = false;

  hat_up_pressed_player_1 = false;
  hat_down_pressed_player_1 = false;
  hat_left_pressed_player_1 = false;
  hat_right_pressed_player_1 = false;

  stick_up_pressed_player_1 = false;
  stick_down_pressed_player_1 = false;
  stick_left_pressed_player_1 = false;
  stick_right_pressed_player_1 = false;

  joy_up_pressed_player_2 = false;
  joy_down_pressed_player_2 = false;
  joy_left_pressed_player_2 = false;
  joy_right_pressed_player_2 = false;

  button_up_flag = true;

  Node *root_node = rosalila()->parser->getNodes(CONFIG_FILE_PATH);
  Node *inputs_node = root_node->getNodeByName("inputs");
  for (auto player : inputs_node->getNodesByName("player"))
  {
    for (auto type : player->getNodesByName("type"))
    {
      vector<Node *> button_nodes = player->getNodesByName("button");
      for(auto button : type->getNodesByName("button"))
      {
        this->inputs[atoi(player->attributes["number"].c_str())]
          [type->attributes["name"]]
          [button->attributes["name"]] = 
          button->attributes["key"];
      }
    }
  }
}

bool RosalilaReceiver::isKeyPressed(int keycode)
{
  if (is_key_pressed[keycode])
  {
    is_key_pressed[keycode] = false;
    return true;
  }
  return false;
}

bool RosalilaReceiver::isKeyDown(int keycode)
{
  if (keycode >= 332)
  {
    return false;
  }
  if (is_key_pressed[keycode])
  {
    return true;
  }
  return false;
}

bool RosalilaReceiver::isJoyDown(int gamepad_number, int joyCode)
{
  if (gamepad_number == 0)
  {
    if (joyCode == -1)
      return (hat_down_pressed_player_1 && hat_left_pressed_player_1) || (stick_down_pressed_player_1 && stick_left_pressed_player_1);
    if (joyCode == -3)
      return (hat_down_pressed_player_1 && hat_right_pressed_player_1) || (stick_down_pressed_player_1 && stick_right_pressed_player_1);
    if (joyCode == -7)
      return (hat_up_pressed_player_1 && hat_left_pressed_player_1) || (stick_up_pressed_player_1 && stick_left_pressed_player_1);
    if (joyCode == -9)
      return (hat_up_pressed_player_1 && hat_right_pressed_player_1) || (stick_up_pressed_player_1 && stick_right_pressed_player_1);
    if (joyCode == -2)
      return hat_down_pressed_player_1 || stick_down_pressed_player_1;
    if (joyCode == -4)
      return hat_left_pressed_player_1 || stick_left_pressed_player_1;
    if (joyCode == -6)
      return hat_right_pressed_player_1 || stick_right_pressed_player_1;
    if (joyCode == -8)
      return hat_up_pressed_player_1 || stick_up_pressed_player_1;
    if (is_joy1_pressed[joyCode])
    {
      return true;
    }
    return false;
  }
  if (gamepad_number == 1)
  {
    if (joyCode == -1)
      return joy_down_pressed_player_2 && joy_left_pressed_player_2;
    if (joyCode == -3)
      return joy_down_pressed_player_2 && joy_right_pressed_player_2;
    if (joyCode == -7)
      return joy_up_pressed_player_2 && joy_left_pressed_player_2;
    if (joyCode == -9)
      return joy_up_pressed_player_2 && joy_right_pressed_player_2;
    if (joyCode == -2)
      return joy_down_pressed_player_2;
    if (joyCode == -4)
      return joy_left_pressed_player_2;
    if (joyCode == -6)
      return joy_right_pressed_player_2;
    if (joyCode == -8)
      return joy_up_pressed_player_2;
    if (is_joy2_pressed[joyCode])
    {
      return true;
    }
    return false;
  }
  return false;
}

bool RosalilaReceiver::isJoyPressed(int gamepad_number, int joyCode)
{
  if (gamepad_number == 0)
  {
    if (joyCode == -1)
    {
      if ((hat_down_pressed_player_1 && hat_left_pressed_player_1) || (stick_down_pressed_player_1 && stick_left_pressed_player_1))
      {
        hat_down_pressed_player_1 = false;
        hat_left_pressed_player_1 = false;
        stick_down_pressed_player_1 = false;
        stick_left_pressed_player_1 = false;
        return true;
      }
    }
    if (joyCode == -3 && ((hat_down_pressed_player_1 && hat_right_pressed_player_1) || (stick_down_pressed_player_1 && stick_right_pressed_player_1)))
    {
      hat_down_pressed_player_1 = false;
      hat_right_pressed_player_1 = false;
      stick_down_pressed_player_1 = false;
      stick_right_pressed_player_1 = false;
      return true;
    }
    if (joyCode == -7 && ((hat_up_pressed_player_1 && hat_up_pressed_player_1) || (stick_left_pressed_player_1 && stick_left_pressed_player_1)))
    {
      hat_up_pressed_player_1 = false;
      hat_left_pressed_player_1 = false;
      stick_up_pressed_player_1 = false;
      stick_left_pressed_player_1 = false;
      return true;
    }
    if (joyCode == -9 && ((hat_up_pressed_player_1 && hat_right_pressed_player_1) || (stick_up_pressed_player_1 && stick_right_pressed_player_1)))
    {
      hat_up_pressed_player_1 = false;
      hat_right_pressed_player_1 = false;
      stick_up_pressed_player_1 = false;
      stick_right_pressed_player_1 = false;
      return true;
    }
    if (joyCode == -2 && (hat_down_pressed_player_1 || stick_down_pressed_player_1))
    {
      hat_down_pressed_player_1 = false;
      stick_down_pressed_player_1 = false;
      return true;
    }
    if (joyCode == -4 && (hat_left_pressed_player_1 || stick_left_pressed_player_1))
    {
      hat_left_pressed_player_1 = false;
      stick_left_pressed_player_1 = false;
      return true;
    }
    if (joyCode == -6 && (hat_right_pressed_player_1 || stick_right_pressed_player_1))
    {
      hat_right_pressed_player_1 = false;
      stick_right_pressed_player_1 = false;
      return true;
    }
    if (joyCode == -8 && (hat_up_pressed_player_1 || stick_up_pressed_player_1))
    {
      hat_up_pressed_player_1 = false;
      stick_up_pressed_player_1 = false;
      return true;
    }
    if (is_joy1_pressed[joyCode])
    {
      is_joy1_pressed[joyCode] = false;
      return true;
    }
    return false;
  }
  if (gamepad_number == 1)
  {
    if (joyCode == -1)
    {
      if (joy_down_pressed_player_2 && joy_left_pressed_player_2)
      {
        joy_down_pressed_player_2 = false;
        joy_left_pressed_player_2 = false;
        return true;
      }
    }
    if (joyCode == -3 && joy_down_pressed_player_2 && joy_right_pressed_player_2)
    {
      joy_down_pressed_player_2 = false;
      joy_right_pressed_player_2 = false;
      return true;
    }
    if (joyCode == -7 && joy_up_pressed_player_2 && joy_left_pressed_player_2)
    {
      joy_up_pressed_player_2 = false;
      joy_left_pressed_player_2 = false;
      return true;
    }
    if (joyCode == -9 && joy_up_pressed_player_2 && joy_right_pressed_player_2)
    {
      joy_up_pressed_player_2 = false;
      joy_right_pressed_player_2 = false;
      return true;
    }
    if (joyCode == -2 && joy_down_pressed_player_2)
    {
      joy_down_pressed_player_2 = false;
      return true;
    }
    if (joyCode == -4 && joy_left_pressed_player_2)
    {
      joy_left_pressed_player_2 = false;
      return true;
    }
    if (joyCode == -6 && joy_right_pressed_player_2)
    {
      joy_right_pressed_player_2 = false;
      return true;
    }
    if (joyCode == -8 && joy_up_pressed_player_2)
    {
      joy_up_pressed_player_2 = false;
      return true;
    }
    if (is_joy2_pressed[joyCode])
    {
      is_joy2_pressed[joyCode] = false;
      return true;
    }
    return false;
  }
  return false;
}

void RosalilaReceiver::updateInputs()
{
  //While there's events to handle
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    //If the user has Xed out the window
    if (event.type == SDL_QUIT)
    {
      exit(0);
    }
    if (event.type == SDL_KEYDOWN)
    {
      if (event.key.keysym.sym == SDLK_UP)
        is_key_pressed[SDL_SCANCODE_UP] = true;
      else if (event.key.keysym.sym == SDLK_DOWN)
        is_key_pressed[SDL_SCANCODE_DOWN] = true;
      else if (event.key.keysym.sym == SDLK_LEFT)
        is_key_pressed[SDL_SCANCODE_LEFT] = true;
      else if (event.key.keysym.sym == SDLK_RIGHT)
        is_key_pressed[SDL_SCANCODE_RIGHT] = true;
      else if (event.key.keysym.sym < 322)
        is_key_pressed[event.key.keysym.sym] = true;
      else
        rosalila()->utility->writeLogLine("Key pressed but not supported:" + rosalila()->utility->toString(event.key.keysym.sym));
    }
    if (event.type == SDL_KEYUP)
    {
      if (event.key.keysym.sym == SDLK_UP)
        is_key_pressed[SDL_SCANCODE_UP] = false;
      else if (event.key.keysym.sym == SDLK_DOWN)
        is_key_pressed[SDL_SCANCODE_DOWN] = false;
      else if (event.key.keysym.sym == SDLK_LEFT)
        is_key_pressed[SDL_SCANCODE_LEFT] = false;
      else if (event.key.keysym.sym == SDLK_RIGHT)
        is_key_pressed[SDL_SCANCODE_RIGHT] = false;
      else if (event.key.keysym.sym < 322)
        is_key_pressed[event.key.keysym.sym] = false;
      else
        rosalila()->utility->writeLogLine("Key pressed but not supported:" + rosalila()->utility->toString(event.key.keysym.sym));
    }
    if (event.type == SDL_JOYBUTTONDOWN)
    {
      for (int i = 0; i < max_joystick_inputs; i++)
      {
        if (event.jbutton.button == i && event.jbutton.which == 0)
        {
          is_joy1_pressed[i] = true;
        }
      }
      for (int i = 0; i < max_joystick_inputs; i++)
      {
        if (event.jbutton.button == i && event.jbutton.which == 1)
        {
          is_joy2_pressed[i] = true;
        }
      }
    }
    if (event.type == SDL_JOYBUTTONUP)
    {
      for (int i = 0; i < max_joystick_inputs; i++)
      {
        if (event.jbutton.button == i && event.jbutton.which == 0)
        {
          is_joy1_pressed[i] = false;
        }
      }
      for (int i = 0; i < max_joystick_inputs; i++)
      {
        if (event.jbutton.button == i && event.jbutton.which == 1)
        {
          is_joy2_pressed[i] = false;
        }
      }
    }

    if (event.type == SDL_JOYHATMOTION)
    {
      //If joystick 0 has moved
      if (event.jhat.which == 0)
      {
        hat_left_pressed_player_1 = false;
        hat_right_pressed_player_1 = false;
        hat_up_pressed_player_1 = false;
        hat_down_pressed_player_1 = false;
        switch (event.jhat.value)
        {
        case 8: //Left
          hat_left_pressed_player_1 = true;
          break;
        case 2: //Right
          hat_right_pressed_player_1 = true;
          break;
        case 1: //Up
          hat_up_pressed_player_1 = true;
          break;
        case 4: //Down
          hat_down_pressed_player_1 = true;
          break;
        case 9: //Left up
          hat_left_pressed_player_1 = true;
          hat_up_pressed_player_1 = true;
          break;
        case 3: //Right up
          hat_right_pressed_player_1 = true;
          hat_up_pressed_player_1 = true;
          break;
        case 12: //left down
          hat_left_pressed_player_1 = true;
          hat_down_pressed_player_1 = true;
          break;
        case 6: //Right down
          hat_right_pressed_player_1 = true;
          hat_down_pressed_player_1 = true;
          break;
        }
      }
      if (event.jhat.which == 1)
      {
        joy_left_pressed_player_2 = false;
        joy_right_pressed_player_2 = false;
        joy_up_pressed_player_2 = false;
        joy_down_pressed_player_2 = false;
        switch (event.jhat.value)
        {
        case 8: //Left
          joy_left_pressed_player_2 = true;
          break;
        case 2: //Right
          joy_right_pressed_player_2 = true;
          break;
        case 1: //Up
          joy_up_pressed_player_2 = true;
          break;
        case 4: //Down
          joy_down_pressed_player_2 = true;
          break;
        case 9: //Left up
          joy_left_pressed_player_2 = true;
          joy_up_pressed_player_2 = true;
          break;
        case 3: //Right up
          joy_right_pressed_player_2 = true;
          joy_up_pressed_player_2 = true;
          break;
        case 12: //left down
          joy_left_pressed_player_2 = true;
          joy_down_pressed_player_2 = true;
          break;
        case 6: //Right down
          joy_right_pressed_player_2 = true;
          joy_down_pressed_player_2 = true;
          break;
        }
      }
    }

    if (event.type == SDL_JOYAXISMOTION)
    {
      //If joystick 0 has moved
      if (event.jaxis.which == 0)
      {
        if (event.jaxis.axis == 0)
        {
          if ((event.jaxis.value > -8000) && (event.jaxis.value < 8000))
          {
            stick_left_pressed_player_1 = false;
            stick_right_pressed_player_1 = false;
          }
          else
          {
            if (event.jaxis.value < 0)
            {
              stick_left_pressed_player_1 = true;
              stick_right_pressed_player_1 = false;
            }
            else
            {
              stick_right_pressed_player_1 = true;
              stick_left_pressed_player_1 = false;
            }
          }
        }
        //If the Y axis changed
        else if (event.jaxis.axis == 1)
        {
          if ((event.jaxis.value > -8000) && (event.jaxis.value < 8000))
          {
            stick_up_pressed_player_1 = false;
            stick_down_pressed_player_1 = false;
          }
          else
          {
            if (event.jaxis.value < 0)
            {
              stick_up_pressed_player_1 = true;
              stick_down_pressed_player_1 = false;
            }
            else
            {
              stick_down_pressed_player_1 = true;
              stick_up_pressed_player_1 = false;
            }
          }
        }
      }

      if (event.jaxis.which == 1)
      {
        if (event.jaxis.axis == 0)
        {
          if ((event.jaxis.value > -8000) && (event.jaxis.value < 8000))
          {
            joy_left_pressed_player_2 = false;
            joy_right_pressed_player_2 = false;
          }
          else
          {
            if (event.jaxis.value < 0)
            {
              joy_left_pressed_player_2 = true;
              joy_right_pressed_player_2 = false;
            }
            else
            {
              joy_left_pressed_player_2 = false;
              joy_right_pressed_player_2 = true;
            }
          }
        }
        //If the Y axis changed
        else if (event.jaxis.axis == 1)
        {
          if ((event.jaxis.value > -8000) && (event.jaxis.value < 8000))
          {
            joy_up_pressed_player_2 = false;
            joy_down_pressed_player_2 = false;
          }
          else
          {
            if (event.jaxis.value < 0)
            {
              joy_up_pressed_player_2 = true;
              joy_down_pressed_player_2 = false;
            }
            else
            {
              joy_up_pressed_player_2 = false;
              joy_down_pressed_player_2 = true;
            }
          }
        }
      }
    }
  }
}

void RosalilaReceiver::unpressAllInputs()
{
  for (int i = 0; i < 255; i++)
    is_key_pressed[i] = false;
  for (int i = 0; i < max_joystick_inputs; i++)
    is_joy1_pressed[i] = false;
  for (int i = 0; i < max_joystick_inputs; i++)
    is_joy2_pressed[i] = false;
}

bool RosalilaReceiver::isPressed(int player, std::string name)
{
  if(this->inputs.find(player) != inputs.end())
  {
    for(auto type : this->inputs[player])
    {
      if(type.second.find(name) != type.second.end())
      {
        std::string button = type.second[name];
        if(type.first == "keyboard")
        {
          if(button == "up" && this->isKeyPressed(SDL_SCANCODE_UP))
            return true;
          if(button == "down" && this->isKeyPressed(SDL_SCANCODE_DOWN))
            return true;
          if(button == "left" && this->isKeyPressed(SDL_SCANCODE_LEFT))
            return true;
          if(button == "right" && this->isKeyPressed(SDL_SCANCODE_RIGHT))
            return true;
          if(isKeyPressed(button[0]))
            return true;
        }
        if(type.first == "gamepad")
        {
          if(button == "up" && this->isJoyPressed(player, -8))
            return true;
          if(button == "down" && this->isJoyPressed(player, -2))
            return true;
          if(button == "left" && this->isJoyPressed(player, -4))
            return true;
          if(button == "right" && this->isJoyPressed(player, -6))
            return true;
          if(isJoyPressed(player, atoi(button.c_str())))
            return true;
        }
      }
    }
  }
  return false;
}

bool RosalilaReceiver::isDown(int player, std::string name)
{
  if(this->inputs.find(player) != inputs.end())
  {
    for(auto type : this->inputs[player])
    {
      if(type.second.find(name) != type.second.end())
      {
        std::string button = type.second[name];
        if(type.first == "keyboard")
        {
          if(button == "up" && this->isKeyDown(SDL_SCANCODE_UP))
            return true;
          if(button == "down" && this->isKeyDown(SDL_SCANCODE_DOWN))
            return true;
          if(button == "left" && this->isKeyDown(SDL_SCANCODE_LEFT))
            return true;
          if(button == "right" && this->isKeyDown(SDL_SCANCODE_RIGHT))
            return true;
          if(button.size() == 1 && isKeyDown(button[0]))
            return true;
        }
        if(type.first == "gamepad")
        {
          if(button == "up" && this->isJoyDown(player, -8))
            return true;
          if(button == "down" && this->isJoyDown(player, -2))
            return true;
          if(button == "left" && this->isJoyDown(player, -4))
            return true;
          if(button == "right" && this->isJoyDown(player, -6))
            return true;
          if(button.size() == 1 && isJoyDown(player, atoi(button.c_str())))
            return true;
        }
      }
    }
  }
  return false;
}
