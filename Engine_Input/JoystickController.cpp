/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "JoystickController.h"

namespace Engine
{
namespace Input
{
  /**
   * @copydoc IController::IController
   */
  JoystickController::JoystickController(IControlScheme *parent)
      : IController(parent)
  {
  }

  JoystickController::~JoystickController()
  {
  }

  /**
   * @brief Sets the state mapping for a given buton.
   * @param button Button ID
   * @param state State ID
   */
  void JoystickController::setButtonMapping(Uint8 button, size_t state)
  {
    m_buttonMappings[button] = state;
  }

  /**
   * @brief Sets the analog state mapping for a given axis.
   * @param axis Axis ID
   * @param state Analog state ID
   */
  void JoystickController::setAxisMapping(Uint8 axis, size_t state)
  {
    m_axisMappings[axis] = state;
  }

  /**
   * @copydoc JoystickHandler::handleButton
   */
  void JoystickController::handleButton(const SDL_JoyButtonEvent &e)
  {
    auto it = m_buttonMappings.find(e.button);
    if (it != m_buttonMappings.end())
      m_controlScheme->setState(it->second, e.type == SDL_JOYBUTTONDOWN);
  }

  /**
   * @copydoc JoystickHandler::handleMotion
   */
  void JoystickController::handleMotion(const SDL_JoyAxisEvent &e)
  {
    auto it = m_axisMappings.find(e.axis);
    if (it != m_axisMappings.end())
    {
      float value = (float)e.value / 32767.0f;
      m_controlScheme->setAnalog(it->second, value);
    }
  }
}
}
