/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#pragma once

#include "IController.h"
#include "JoystickHandler.h"

namespace Engine
{
namespace Input
{
  /**
   * @class JoystickController
   * @brief Represents a joystick control device.
   * @author Dan Nixon
   */
  class JoystickController : public IController, public JoystickHandler
  {
  public:
    JoystickController(IControlScheme *parent);
    virtual ~JoystickController();

    void setButtonMapping(Uint8 button, size_t state);
    void setAxisMapping(Uint8 axis, size_t state);

  private:
    virtual void handleButton(const SDL_JoyButtonEvent &e);
    virtual void handleMotion(const SDL_JoyAxisEvent &e);

    std::map<Uint8, size_t> m_buttonMappings;
    std::map<Uint8, size_t> m_axisMappings;
  };
}
}
