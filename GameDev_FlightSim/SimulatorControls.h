/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#ifndef _GAMEDEV_FLIGHTSIM_SIMULATORCONTROLS_H_
#define _GAMEDEV_FLIGHTSIM_SIMULATORCONTROLS_H_

#include <Engine_Input/IControlScheme.h>

#include <Engine_Common/Game.h>

#include <Engine_Input/JoystickController.h>
#include <Engine_Input/KeyboardController.h>

#include "controls.h"

namespace GameDev
{
namespace FlightSim
{
  /**
   * @class SimulatorControls
   * @brief Control scheme for flight simulation.
   * @author Dan Nixon
   */
  class SimulatorControls : public Engine::Input::IControlScheme
  {
  public:
    /**
     * @copydoc IControlScheme:IControlScheme
     */
    SimulatorControls(Engine::Common::Game *game)
        : Engine::Input::IControlScheme(game)
        , m_keyboard(new Engine::Input::KeyboardController(this))
    {
      m_keyboard->setMapping(SDLK_f, S_FPV, true);
      m_keyboard->setMapping(SDLK_ESCAPE, S_OPENMENU, true);

      addController(m_keyboard);
      game->addEventHandler(m_keyboard);
    }

    virtual ~SimulatorControls()
    {
      m_game->removeEventHandler(m_keyboard);
    }

  protected:
    Engine::Input::KeyboardController *m_keyboard; //!< Keyboard input
  };
}
}

#endif
