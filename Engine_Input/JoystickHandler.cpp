/**
* @file
* @author Dan Nixon
*/

#include "JoystickHandler.h"

namespace Engine
{
namespace Input
{
  JoystickHandler::JoystickHandler()
    : IEventHandler()
  {
  }

  JoystickHandler::~JoystickHandler()
  {
  }

  void JoystickHandler::handleEvent(const SDL_Event &e)
  {
    // Fire if enabled and is not a repeat
    if (m_enabled && e.key.repeat == 0)
    {
      switch (e.type)
      {
      case SDL_JOYAXISMOTION:
        // TODO
        break;
      case SDL_JOYBUTTONDOWN:
      case SDL_JOYBUTTONUP:
        // TODO
        break;
      }
    }
  }
}
}