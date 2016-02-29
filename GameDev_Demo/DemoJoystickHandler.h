/**
* @file
* @author Dan Nixon
*/

#ifndef _DEMOJOYSTICKHANDLER_H_
#define _DEMOJOYSTICKHANDLER_H_

#include <JoystickHandler.h>

#include <iostream>

/**
 * @class DemoJoystickHandler
 * @brief Demonstraton of a joystick event handler.
 * @author Dan Nixon
 */
class DemoJoystickHandler : public Engine::Input::JoystickHandler
{
public:
  DemoJoystickHandler()
  {
  }

  virtual ~DemoJoystickHandler()
  {
  }

  /**
   * @copydoc JoystickHandler::handleButton
   */
  void handleButton(const SDL_JoyButtonEvent &e)
  {
    std::cout << "Button: " << (int)e.button << std::endl
              << "State: "
              << ((e.state == SDL_PRESSED) ? "pressed" : "released")
              << std::endl;
  }

  /**
   * @copydoc JoystickHandler::handleMotion
   */
  void handleMotion(const SDL_JoyAxisEvent &e)
  {
    std::cout << "Axis: " << (int)e.axis << std::endl
              << "Value: " << e.value << std::endl;
  }
};

#endif