/**
* @file
* @author Dan Nixon
*/

#include "MouseHandler.h"

#include <SDL.h>

namespace Engine
{
namespace Input
{
  MouseHandler::MouseHandler()
    : IEventHandler()
  {
  }

  MouseHandler::~MouseHandler()
  {
  }

  void MouseHandler::handleEvent(const SDL_Event &e)
  {
    // Fire if enabled and is not a repeat
    if (m_enabled && e.key.repeat == 0)
    {
      switch (e.type)
      {
      case SDL_MOUSEMOTION:
        // TODO
        break;
      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
        // TODO
        break;
      }
    }
  }
}
}