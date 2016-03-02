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
   * @brief Checks if the joystick has been opened.
   * @return True if the joystick is ready to use
   */
  bool JoystickHandler::isOpen() const
  {
    return (m_joystick != NULL);
  }

  /**
   * @brief Gets the number of buttons on the open joystick.
   * @return Number of buttons
   *
   * May also return 0 if there is no open joystick.
   */
  int JoystickHandler::numButtons() const
  {
    if (m_joystick == NULL)
      return 0;

    return SDL_JoystickNumButtons(m_joystick);
  }

  /**
   * @brief Gets the number of axes on the open joystick.
   * @return Number of axes
   *
   * May also return 0 if there is no open joystick.
   */
  int JoystickHandler::numAxes() const
  {
    if (m_joystick == NULL)
      return 0;

    return SDL_JoystickNumAxes(m_joystick);
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
    // Fire if enabled and joystick is open
    if (m_enabled && (m_joystick != NULL))
    {
      SDL_JoystickID jsID = SDL_JoystickInstanceID(m_joystick);

      switch (e.type)
      {
      case SDL_JOYAXISMOTION:
        if (e.jaxis.which == jsID)
          handleMotion(e.jaxis);
        break;
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
