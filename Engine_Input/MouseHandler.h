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
  class MouseHandler : public Engine::Common::IEventHandler
  {
  public:
    MouseHandler();
    virtual ~MouseHandler();

  protected:
    virtual void handleEvent(const SDL_Event &e);
  };
}
}