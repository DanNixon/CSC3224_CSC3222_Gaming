/**
* @file
* @author Dan Nixon
*/

#include "KeyboardHandler.h"

#include "SDL/SDL.h"

using namespace Engine::Common;

namespace Engine
{
namespace Input
{
  /**
   * @brief Tests to see if a given key is pressed.
   * @param key Key to test
   * @return True if key is pressed
   */
  bool KeyboardHandler::KeyPressed(SDL_Keycode key)
  {
    const Uint8 *state = SDL_GetKeyboardState(nullptr);
    return state[SDL_GetScancodeFromKey(key)] == 1;
  }

  KeyboardHandler::KeyboardHandler()
      : IEventHandler()
  {
  }

  KeyboardHandler::~KeyboardHandler()
  {
  }

  /**
   * @copydoc IEventHandler::handleEvent
   */
  void KeyboardHandler::handleEvent(const SDL_Event &e)
  {
    // Fire if enabled, is a keyboard event and is not a repeat event
    if (m_enabled && (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) && e.key.repeat == 0)
      handleKey(e.key);
  }
}
}
