/**
* @file
* @author Dan Nixon
*/

#ifndef _ENGINE_INPUT_KEYBOARDHANDLER_H_
#define _ENGINE_INPUT_KEYBOARDHANDLER_H_

#include <IEventHandler.h>

namespace Engine
{
namespace Input
{
  /**
   * @class KeyboardHandler
   * @brief Abstract class for handling keyboard input.
   * @author Dan Nixon
   */
  class KeyboardHandler : public Engine::Common::IEventHandler
  {
  public:
    static bool KeyPressed(SDL_Keycode key);

    KeyboardHandler();
    virtual ~KeyboardHandler();

  protected:
    virtual void handleEvent(const SDL_Event &e);

    /**
     * @brief Handles a key being pressed or released.
     * @param e Event
     */
    virtual void handleKey(const SDL_KeyboardEvent &e) = 0;
  };
}
}

#endif