/**
 * @file
 * @author Dan Nixon
 */

#include "JoystickController.h"

namespace Engine
{
  namespace Input
  {
    JoystickController::JoystickController(IControlScheme * parent)
      : IController(parent)
    {
    }

    JoystickController::~JoystickController()
    {
    }

    void JoystickController::poll()
    {
      if (!isOpen())
        return;

      for (int i = 0; i < numButtons(); i++)
      {
        auto it = m_buttonMappings.find(i);
        if (it != m_buttonMappings.end())
          m_controlScheme->setState(it->second, button(i));
      }
    }

    void JoystickController::setButtonMapping(Uint8 button, size_t state)
    {
      m_buttonMappings[button] = state;
    }

    void JoystickController::setAxisMapping(Uint8 axis, size_t state)
    {
      m_axisMappings[axis] = state;
    }

    void JoystickController::handleButton(const SDL_JoyButtonEvent &e)
    {
      (void)e;
    }

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
