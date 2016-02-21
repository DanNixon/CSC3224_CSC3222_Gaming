/**
* @file
* @author Dan Nixon
*/

#pragma once

#include <MouseHandler.h>

#include <iostream>

/**
 * @class DemoMouseHandler
 * @brief Demonstraton of a mouse event handler.
 * @author Dan Nixon
 */
class DemoMouseHandler : public Engine::Input::MouseHandler
{
public:
  DemoMouseHandler()
  {
  }

  virtual ~DemoMouseHandler()
  {
  }

  /**
   * @copydoc MouseHandler::handleButton
   */
  void handleButton(const SDL_MouseButtonEvent &e)
  {
    std::cout << "State: " << ((e.state == SDL_PRESSED) ? "pressed" : "released") << std::endl
              << "Button: " << e.button << std::endl;
  }

  /**
   * @copydoc MouseHandler::handleButton
   */
  void handleMotion(const SDL_MouseMotionEvent &e)
  {
    auto relScrn = MouseHandler::GetNormalisedPos(e, 640, 480);
    std::cout << "Pos: (" << e.x << "," << e.y << ")" << std::endl
      << "Rel: (" << e.xrel << "," << e.yrel << ")" << std::endl
      << "RelScrn: (" << relScrn.first << "," << relScrn.second << ")" << std::endl;
  }
};
