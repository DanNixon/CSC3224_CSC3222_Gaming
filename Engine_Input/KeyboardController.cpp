/**
 * @file
 * @author Dan Nixon
 */

#include "KeyboardController.h"

namespace Engine
{
  namespace Input
  {
    KeyboardController::KeyboardController(IControlScheme * parent)
      : IController(parent)
    {
    }

    KeyboardController::~KeyboardController()
    {
    }

    void KeyboardController::setMapping(SDL_Keycode key, size_t s)
    {
      m_mappings[key] = s;
    }

    void KeyboardController::handleKey(const SDL_KeyboardEvent &e)
    {
      auto it = m_mappings.find(e.keysym.sym);
      if (it != m_mappings.end())
        m_controlScheme->setState(it->second, e.type == SDL_KEYDOWN);
    }
  }
}
