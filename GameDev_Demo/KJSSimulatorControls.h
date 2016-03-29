/**
 * @file
 * @author Dan Nixon
 */

#ifndef _GAMEDEV_DEMO_KJSSIMULATORCONTROLS_H_
#define _GAMEDEV_DEMO_KJSSIMULATORCONTROLS_H_

#include <Engine_Input/IControlScheme.h>

#include <Engine_Common/Game.h>

#include <Engine_Input/JoystickController.h>
#include <Engine_Input/KeyboardController.h>

#include "controls.h"

namespace GameDev
{
namespace Demo
{
  /**
   * @class KJSSimulatorControls
   * @brief Control scheme for flight simulation using a keyboard and joystick.
   * @author Dan Nixon
   */
  class KJSSimulatorControls : public Engine::Input::IControlScheme
  {
  public:
    /**
     * @brief Create a new keyboard and joystick control scheme.
     * @param game Target game
     */
    KJSSimulatorControls(Engine::Common::Game *game)
        : m_game(game)
        , m_keyboard(new Engine::Input::KeyboardController(this))
        , m_joystick(new Engine::Input::JoystickController(this))
    {
      m_keyboard->setMapping(SDLK_f, S_FPV, true);
      m_keyboard->setMapping(SDLK_ESCAPE, S_OPENMENU, true);

      m_joystick->setAxisMapping(1, A_PITCH);
      m_joystick->setAxisMapping(0, A_ROLL);
      m_joystick->setAxisMapping(2, A_THROT);
      m_joystick->setAxisMapping(3, A_YAW);
      m_joystick->setButtonMapping(0, S_FPV);

      addController(m_keyboard);
      addController(m_joystick);

      m_game->addEventHandler(m_keyboard);
      m_game->addEventHandler(m_joystick);
    }

    virtual ~KJSSimulatorControls()
    {
      m_game->removeEventHandler(m_keyboard);
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

  private:
    Engine::Common::Game *m_game;
    Engine::Input::KeyboardController *m_keyboard;
    Engine::Input::JoystickController *m_joystick;
  };
}
}

#endif