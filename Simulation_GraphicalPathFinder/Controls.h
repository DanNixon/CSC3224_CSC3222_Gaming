/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#ifndef _SIMULATION_GRAPHICALPATHFINDER_CONTROLS_H_
#define _SIMULATION_GRAPHICALPATHFINDER_CONTROLS_H_

#include <Engine_Input/IControlScheme.h>

#include <Engine_Common/Game.h>
#include <Engine_Input/KeyboardController.h>
#include <Engine_Input/MouseController.h>

namespace Simulation
{
namespace GraphicalPathFinder
{
  /**
   * @brief Enumeration of control states for the snooker simulation.
   */
  enum ControlTypes
  {
    A_MOUSE_X,
    A_MOUSE_Y,
  };

  /**
   * @class Controls
   * @brief Control scheme for snooker simulation.
   * @author Dan Nixon
   */
  class Controls : public Engine::Input::IControlScheme
  {
  public:
    /**
     * @copydoc IControlScheme:IControlScheme
     */
    Controls(Engine::Common::Game *game)
        : Engine::Input::IControlScheme(game)
        , m_keyboard(new Engine::Input::KeyboardController(this))
        , m_mouse(new Engine::Input::MouseController(this, game->windowX(), game->windowY()))
    {
      m_mouse->setXMapping(A_MOUSE_X);
      m_mouse->setYMapping(A_MOUSE_Y);

      addController(m_keyboard);
      addController(m_mouse);

      game->addEventHandler(m_keyboard);
      game->addEventHandler(m_mouse);
    }

    virtual ~Controls()
    {
      m_game->removeEventHandler(m_keyboard);
      m_game->removeEventHandler(m_mouse);
    }

  private:
    Engine::Input::KeyboardController *m_keyboard; //!< Keyboard used in scheme
    Engine::Input::MouseController *m_mouse;       //!< Mouse used in scheme
  };
}
}

#endif
