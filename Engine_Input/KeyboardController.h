/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include "IController.h"
#include "KeyboardHandler.h"

namespace Engine
{
  namespace Input
  {
    class KeyboardController : public IController, public KeyboardHandler
    {
    public:
      KeyboardController();
      virtual ~KeyboardController();

    private:
      virtual void handleKey(const SDL_KeyboardEvent &e);
    };
  }
}

