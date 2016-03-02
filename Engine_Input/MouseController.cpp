/**
 * @file
 * @author Dan Nixon
 */

#include "MouseController.h"

namespace Engine
{
  namespace Input
  {
    MouseController::MouseController(IControlScheme * parent)
      : IController(parent)
    {
    }

    MouseController::~MouseController()
    {
    }

    void MouseController::handleButton(const SDL_MouseButtonEvent &e)
    {
      // TODO
    }

    void MouseController::handleMotion(const SDL_MouseMotionEvent &e)
    {
      // TODO
    }
  }
}
