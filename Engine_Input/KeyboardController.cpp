/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "KeyboardController.h"

namespace Engine
{
namespace Input
{
  /**
   * @copydoc IController::IController
   */
  KeyboardController::KeyboardController(IControlScheme *parent)
      : IController(parent)
  {
  }

  KeyboardController::~KeyboardController()
  {
  }

  /**
   * @brief Sets the state mapping for a given key.
   * @param key Key code
   * @param state State ID
   * @param flip If the key should toggle the state
   */
  void KeyboardController::setMapping(SDL_Keycode key, size_t state, bool flip)
  {
    m_mappings[key] = std::make_pair(state, flip);
  }

  /**
   * @copydoc KeyboardHandler::handleKey
   */
  void KeyboardController::handleKey(const SDL_KeyboardEvent &e)
  {
    auto it = m_mappings.find(e.keysym.sym);
    if (it != m_mappings.end())
    {
      bool down = e.type == SDL_KEYDOWN;

      if (!it->second.second)
        m_controlScheme->setState(it->second.first, down);
      else if (down)
        m_controlScheme->flipState(it->second.first);
    }
  }
}
}
