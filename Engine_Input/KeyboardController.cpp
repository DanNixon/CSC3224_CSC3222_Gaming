/**
 * @file
 * @author Dan Nixon
 */

#include "KeyboardController.h"

namespace Engine
{
namespace Input
{
  KeyboardController::KeyboardController(IControlScheme *parent)
      : IController(parent)
  {
  }

  KeyboardController::~KeyboardController()
  {
  }

  void KeyboardController::setMapping(SDL_Keycode key, size_t s, bool flip)
  {
    m_mappings[key] = std::make_pair(s, flip);
  }

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
