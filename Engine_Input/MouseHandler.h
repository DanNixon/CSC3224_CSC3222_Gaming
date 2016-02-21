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
    std::pair<float, float> GetNormalisedPos(const SDL_MouseMotionEvent &e, int width, int height);

    MouseHandler();
    virtual ~MouseHandler();

  protected:
    virtual void handleEvent(const SDL_Event &e);

    virtual void handleButton(const SDL_MouseButtonEvent &e) = 0;
    virtual void handleMotion(const SDL_MouseMotionEvent &e) = 0;
  };
}
}