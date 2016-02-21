#pragma once

#include "KeyboardHandler.h"

#include <iostream>

namespace Engine
{
namespace Input
{
  class DemoKeyboardHandler :public KeyboardHandler
  {
  public:
    DemoKeyboardHandler()
    {
    }

    virtual ~DemoKeyboardHandler()
    {
    }

    void handleKey(uint8_t state, SDL_Keycode key, uint16_t moidifiers)
    {
      std::cout << "State: " << ((state == SDL_PRESSED) ? "pressed" : "released") << std::endl
                << "Key: " << key << std::endl;
    }
};
}
}