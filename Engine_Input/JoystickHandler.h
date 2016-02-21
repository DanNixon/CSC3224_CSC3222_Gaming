/**
* @file
* @author Dan Nixon
*/

#pragma once

#include <IEventHandler.h>

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
  };
}
}