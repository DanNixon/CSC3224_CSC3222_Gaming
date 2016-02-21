/**
* @file
* @author Dan Nixon
*/

#pragma once

#include <IEventHandler.h>

#include <SDL.h>

namespace Engine
{
namespace Input
{
  class JoystickHandler : public Engine::Common::IEventHandler
  {
  public:
    JoystickHandler();
    virtual ~JoystickHandler();

  protected:
    virtual void handleEvent(const SDL_Event &e);

    virtual void handleButton(const SDL_JoyButtonEvent &e) = 0;
    virtual void handleMotion(const SDL_JoyAxisEvent &e) = 0;
  };
}
}