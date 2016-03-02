/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include "IController.h"
#include "JoystickHandler.h"

namespace Engine
{
  namespace Input
  {
    class JoystickController : public IController, public JoystickHandler
    {
    public:
      JoystickController(IControlScheme * parent);
      virtual ~JoystickController();

    protected:
      virtual void handleButton(const SDL_JoyButtonEvent &e);
      virtual void handleMotion(const SDL_JoyAxisEvent &e);
    };
  }
}

