/**
* @file
* @author Dan Nixon
*/

#pragma once

#include "SDL.h"

#include <IEventHandler.h>

namespace Engine
{
namespace Input
{
  class KeyboardHandler : public Engine::Common::IEventHandler
  {
  public:
    static bool KeyPressed(SDL_Keycode key);

    KeyboardHandler();
    virtual ~KeyboardHandler();

  protected:
    virtual void handleEvent(const SDL_Event &e);

    virtual void handleKey(const SDL_KeyboardEvent &e) = 0;
  };
}
}