/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#ifndef _GAMEDEV_FLIGHTSIM_KJSSIMULATORCONTROLS_H_
#define _GAMEDEV_FLIGHTSIM_KJSSIMULATORCONTROLS_H_

#include "SimulatorControls.h"

#include <Engine_Common/Game.h>

#include <Engine_Input/JoystickController.h>
#include <Engine_Input/KeyboardController.h>
#include <Engine_IO/KVNode.h>

#include "controls.h"

namespace GameDev
{
namespace FlightSim
{
  /**
   * @class KJSSimulatorControls
   * @brief Control scheme for flight simulation using a keyboard and joystick.
   * @author Dan Nixon
   */
  class KJSSimulatorControls : public SimulatorControls
  {
  public:
    /**
     * @copydoc IControlScheme:IControlScheme
     */
    KJSSimulatorControls(Engine::Common::Game *game, Engine::IO::KVNode & config)
        : SimulatorControls(game)
        , m_joystick(new Engine::Input::JoystickController(this))
    {
      m_joystick->setAxisMapping((Uint8)config.keyUnsignedLong("axis_pitch"), A_PITCH);
      m_joystick->setAxisMapping((Uint8)config.keyUnsignedLong("axis_roll"), A_ROLL);
      m_joystick->setAxisMapping((Uint8)config.keyUnsignedLong("axis_collective"), A_THROT);
      m_joystick->setAxisMapping((Uint8)config.keyUnsignedLong("axis_yaw"), A_YAW);
      m_joystick->setAxisMapping((Uint8)config.keyUnsignedLong("axis_throttle"), A_ENGINE);

      addController(m_joystick);
      game->addEventHandler(m_joystick);
    }

    virtual ~KJSSimulatorControls()
    {
      m_game->removeEventHandler(m_joystick);
    }

    /**
     * @brief Gets a pointer to the joystick handler.
     * @return Joystick handler
     */
    Engine::Input::JoystickHandler *joystick()
    {
      return m_joystick;
    }

  protected:
    Engine::Input::JoystickController *m_joystick; //!< Joystick input
  };
}
}

#endif
