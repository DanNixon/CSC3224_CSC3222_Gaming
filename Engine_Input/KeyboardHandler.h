#pragma once

#include <IEventHandler.h>

namespace Engine
{
namespace Input
{
  class KeyboardHandler : public Engine::Common::IEventHandler
  {
  public:
    KeyboardHandler();
    virtual ~KeyboardHandler();

  protected:
    virtual void handleEvent(const SDL_Event &e);

    virtual void handleKey(uint8_t state, SDL_Keycode key, uint16_t moidifiers) = 0;
  };
}
}