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
  std::pair<float, float> MouseHandler::GetNormalisedPos(const SDL_MouseMotionEvent &e, int width, int height)
  {
    float x = ((float) (2 * e.x) / (float) width) - 1.0f;
    float y = -((float) (2 * e.y) / (float) height) + 1.0f;
    return std::make_pair(x, y);
  }

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
        handleMotion(e.motion);
        break;
      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
        handleButton(e.button);
        break;
      }
    }
  }
}
}