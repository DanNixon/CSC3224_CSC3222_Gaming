/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_INPUT_MOUSEHANDLER_H_
#define _ENGINE_INPUT_MOUSEHANDLER_H_

#include <Engine_Common/IEventHandler.h>

namespace Engine
{
namespace Input
{
  /**
   * @class MouseHandler
   * @brief Abstract class for handling mouse input.
   * @author Dan Nixon
   */
  class MouseHandler : public Engine::Common::IEventHandler
  {
  public:
    std::pair<float, float> GetCentreNormalisedPos(const SDL_MouseMotionEvent &e, int width, int height);
    std::pair<float, float> GetCornerNormalisedPos(const SDL_MouseMotionEvent &e, int width, int height);

    MouseHandler();
    virtual ~MouseHandler();

  protected:
    virtual void handleEvent(const SDL_Event &e);

    /**
     * @brief Handle a button being pressed or released.
     * @param e Event
     */
    virtual void handleButton(const SDL_MouseButtonEvent &e) = 0;

    /**
     * @brief Handle the mouse being moved.
     * @param e Event
     */
    virtual void handleMotion(const SDL_MouseMotionEvent &e) = 0;
  };
}
}

#endif