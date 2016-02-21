/**
* @file
* @author Dan Nixon
*/

#include "JoystickHandler.h"

namespace Engine
{
namespace Input
{
  int JoystickHandler::NumJoysticks()
  {
    return SDL_NumJoysticks();
  }

  JoystickHandler::JoystickHandler()
    : IEventHandler()
    , m_joystick(NULL)
  {
  }

  JoystickHandler::~JoystickHandler()
  {
  }

  bool JoystickHandler::open(int deviceIndex)
  {
    m_joystick = SDL_JoystickOpen(deviceIndex);
    SDL_JoystickEventState(SDL_ENABLE);
    return (m_joystick != NULL);
  }

  void JoystickHandler::close()
  {
    SDL_JoystickClose(m_joystick);
    m_joystick = NULL;
  }

  bool JoystickHandler::button(int button) const
  {
    if (m_joystick == NULL)
      return false;

    return (SDL_JoystickGetButton(m_joystick, button) == 1);
  }

  Sint32 JoystickHandler::axis(int axis) const
  {
    if (m_joystick == NULL)
      return 0;

    return SDL_JoystickGetAxis(m_joystick, axis);
  }

  void JoystickHandler::handleEvent(const SDL_Event &e)
  {
    // Fire if enabled and is not a repeat
    if (m_enabled && e.key.repeat == 0 && (m_joystick != NULL))
    {
      SDL_JoystickID jsID = SDL_JoystickInstanceID(m_joystick);

      switch (e.type)
      {
      case SDL_JOYAXISMOTION:
        if (e.jaxis.which == jsID)
          handleMotion(e.jaxis);
        break;
      // Annoyingly only the key up events seem to be fired
      case SDL_JOYBUTTONDOWN:
      case SDL_JOYBUTTONUP:
        if (e.jbutton.which == jsID)
          handleButton(e.jbutton);
        break;
      }
    }
  }
}
}