/**
* @file
* @author Dan Nixon
*/

#pragma once

#include <JoystickHandler.h>

#include <iostream>

class DemoJoystickHandler : public Engine::Input::JoystickHandler
{
public:
  DemoJoystickHandler()
  {
  }

  virtual ~DemoJoystickHandler()
  {
  }

  void handleButton(const SDL_JoyButtonEvent &e)
  {
    std::cout << "Button: " << (int) e.button << std::endl
      << "State: " << ((e.state == SDL_PRESSED) ? "pressed" : "released") << std::endl;
  }

  void handleMotion(const SDL_JoyAxisEvent &e)
  {
    std::cout << "Axis: " << (int) e.axis << std::endl
      << "Value: " << e.value << std::endl;
  }
};
