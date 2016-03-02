/**
 * @file
 * @author Dan Nixon
 */

#include "JoystickController.h"

namespace Engine
{
  namespace Input
  {
    JoystickController::JoystickController(IControlScheme * parent)
      : IController(parent)
    {
    }

    JoystickController::~JoystickController()
    {
    }

    void JoystickController::handleButton(const SDL_JoyButtonEvent &e)
    {
      // TODO
    }

    void JoystickController::handleMotion(const SDL_JoyAxisEvent &e)
    {
      // TODO
    }
  }
}
