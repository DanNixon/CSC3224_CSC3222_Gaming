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
  class KeyboardController : public IController, public KeyboardHandler
  {
  public:
    KeyboardController(IControlScheme *parent);
    virtual ~KeyboardController();

    void setMapping(SDL_Keycode key, size_t state);

  private:
    virtual void handleKey(const SDL_KeyboardEvent &e);

    std::map<SDL_Keycode, size_t> m_mappings;
  };
}
}
