/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include "IController.h"
#include "MouseHandler.h"

namespace Engine
{
  namespace Input
  {
    class MouseController : public IController, public MouseHandler
    {
    public:
      MouseController(IControlScheme * parent);
      virtual ~MouseController();

    protected:
      virtual void handleButton(const SDL_MouseButtonEvent &e);
      virtual void handleMotion(const SDL_MouseMotionEvent &e);
    };
  }
}

