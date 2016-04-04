/**
* @file
* @author Dan Nixon
*/

#include "MouseHandler.h"

#include <SDL/SDL.h>

namespace Engine
{
namespace Input
{
  /**
   * @brief Normalises a set of coordinates from a mouse motion event to the
   *        screen width and height.
   * @param e Event containing coordinates
   * @param width Width of window
   * @param height Height of window
   * @return Normalised coordinates
   *
   * Normalisation is such that the centre of the screen is (0, 0) and each
   * axis has range [-1, 1].
   */
  std::pair<float, float> MouseHandler::GetCentreNormalisedPos(const SDL_MouseMotionEvent &e, int width, int height)
  {
    float x = ((float)(2 * e.x) / (float)width) - 1.0f;
    float y = -((float)(2 * e.y) / (float)height) + 1.0f;
    return std::make_pair(x, y);
  }

  /**
   * @brief Normalises a set of coordinates from a mouse motion event to the
   *        screen width and height.
   * @param e Event containing coordinates
   * @param width Width of window
   * @param height Height of window
   * @return Normalised coordinates
   *
   * Normalisation is such that the top left corner of the screen is (0, 0) and each
   * axis has range [0, 1].
   */
  std::pair<float, float> MouseHandler::GetCornerNormalisedPos(const SDL_MouseMotionEvent &e, int width, int height)
  {
    float x = ((float)e.x / (float)width);
    float y = ((float)e.y / (float)height);
    return std::make_pair(x, y);
  }

  MouseHandler::MouseHandler()
      : IEventHandler()
  {
  }

  MouseHandler::~MouseHandler()
  {
  }

  /**
   * @copydoc IEventHandler::handleEvent
   */
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
