/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include "IController.h"
#include "KeyboardHandler.h"

namespace Engine
{
namespace Input
{
  /**
   * @class KeyboardController
   * @brief Represents a keyboard control device.
   * @author Dan Nixon
   */
  class KeyboardController : public IController, public KeyboardHandler
  {
  public:
    KeyboardController(IControlScheme *parent);
    virtual ~KeyboardController();

    void setMapping(SDL_Keycode key, size_t state, bool flip = false);

  private:
    virtual void handleKey(const SDL_KeyboardEvent &e);

    std::map<SDL_Keycode, std::pair<size_t, bool>> m_mappings;
  };
}
}
