/**
 * @file
 * @author Dan Nixon
 */

#ifndef _KJSSIMULATORCONTROLS_H_
#define _KJSSIMULATORCONTROLS_H_

#include <IControlScheme.h>

#include <Game.h>

#include <JoystickController.h>
#include <KeyboardController.h>

#include "controls.h"

class KJSSimulatorControls : public Engine::Input::IControlScheme
{
public:
  KJSSimulatorControls(Engine::Common::Game *game)
      : m_game(game)
      , m_keyboard(new Engine::Input::KeyboardController(this))
      , m_joystick(new Engine::Input::JoystickController(this))
  {
    m_keyboard->setMapping(SDLK_f, S_FPV);
    m_keyboard->setMapping(SDLK_p, S_PAUSE);
    m_keyboard->setMapping(SDLK_r, S_RESET);

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

    delete m_keyboard;
    delete m_joystick;
  }

  Engine::Input::JoystickHandler *joystick()
  {
    return m_joystick;
  }

private:
  Engine::Common::Game *m_game;
  Engine::Input::KeyboardController *m_keyboard;
  Engine::Input::JoystickController *m_joystick;
};

#endif