#include "KeyboardHandler.h"

using namespace Engine::Common;

namespace Engine
{
namespace Input
{
  KeyboardHandler::KeyboardHandler()
  {
  }

  KeyboardHandler::~KeyboardHandler()
  {
  }

  void KeyboardHandler::handleEvent(const SDL_Event &e)
  {
    // Fire if enabled, is a keyboard event and is not a repeat event
    if (m_enabled && (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) && e.key.repeat == 0)
      handleKey(e.key.state, e.key.keysym.sym, e.key.keysym.mod);
  }
}
}