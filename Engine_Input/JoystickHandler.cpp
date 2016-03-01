/**
 * @file
 * @author Dan Nixon
 */

#include "JoystickHandler.h"

namespace Engine
{
namespace Input
{
  /**
   * @brief Gets the number of joysticks detected on the system.
   * @return NUmber of connected joysticks
   */
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

  /**
   * @brief Opens a given joystick device.
   * @param deviceIndex Index of device to open
   * @return True if device was successfully opened
   */
  bool JoystickHandler::open(int deviceIndex)
  {
    m_joystick = SDL_JoystickOpen(deviceIndex);
    SDL_JoystickEventState(SDL_ENABLE);
    return (m_joystick != NULL);
  }

  /**
   * @brief CLoses the joystick device.
   */
  void JoystickHandler::close()
  {
    SDL_JoystickClose(m_joystick);
    m_joystick = NULL;
  }

  /**
   * @brief Gets the state of a button
   * @param button Button index
   * @return True if button is pressed
   */
  bool JoystickHandler::button(int button) const
  {
    if (m_joystick == NULL)
      return false;

    return (SDL_JoystickGetButton(m_joystick, button) == 1);
  }

  /**
   * @brief Gets the value of an axis.
   * @param axis Axis index
   * @return Axis position
   */
  Sint32 JoystickHandler::axis(int axis) const
  {
    if (m_joystick == NULL)
      return 0;

    return SDL_JoystickGetAxis(m_joystick, axis);
  }

  /**
   * @copydoc IEventHandler::handleEvent
   */
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
