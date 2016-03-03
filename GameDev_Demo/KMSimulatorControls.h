/**
 * @file
 * @author Dan Nixon
 */

#ifndef _KMSIMULATORCONTROLS_H_
#define _KMSIMULATORCONTROLS_H_

#include <IControlScheme.h>

#include <Game.h>

#include <KeyboardController.h>
#include <MouseController.h>

#include "controls.h"

/**
 * @class KMSimulatorControls
 * @brief Control scheme for flight simulation using a keyboard and mouse.
 * @author Dan Nixon
 */
class KMSimulatorControls : public Engine::Input::IControlScheme
{
public:
  KMSimulatorControls(Engine::Common::Game *game)
      : m_game(game)
      , m_keyboard(new Engine::Input::KeyboardController(this))
      , m_mouse(new Engine::Input::MouseController(this, game->windowX(),
                                                   game->windowY()))
  {
    m_keyboard->setMapping(SDLK_w, S_INCTHROT);
    m_keyboard->setMapping(SDLK_s, S_DECTHROT);
    m_keyboard->setMapping(SDLK_a, S_YAWCCW);
    m_keyboard->setMapping(SDLK_d, S_YAWCW);
    m_keyboard->setMapping(SDLK_f, S_FPV, true);
    m_keyboard->setMapping(SDLK_p, S_PAUSE, true);
    m_keyboard->setMapping(SDLK_r, S_RESET);

    m_mouse->setXMapping(A_ROLL);
    m_mouse->setYMapping(A_PITCH);
    m_mouse->setButtonMapping(SDL_BUTTON_LEFT, S_FPV);

    addController(m_keyboard);
    addController(m_mouse);

    m_game->addEventHandler(m_keyboard);
    m_game->addEventHandler(m_mouse);
  }

  virtual ~KMSimulatorControls()
  {
    m_game->removeEventHandler(m_keyboard);
    m_game->removeEventHandler(m_mouse);

    delete m_keyboard;
    delete m_mouse;
  }

  virtual void setState(size_t state, bool active)
  {
    IControlScheme::setState(state, active);

    switch (state)
    {
    case S_INCTHROT:
      if (active)
        setAnalog(A_THROT, analog(A_THROT) + 0.1f);
      break;
    case S_DECTHROT:
      if (active)
        setAnalog(A_THROT, analog(A_THROT) - 0.1f);
      break;
    case S_YAWCCW:
      setAnalog(A_YAW, active ? -0.5f : 0.0f);
      break;
    case S_YAWCW:
      setAnalog(A_YAW, active ? 0.5f : 0.0f);
      break;
    }
  }

private:
  Engine::Common::Game *m_game; //!< Game instance this scheme is attached to
  Engine::Input::KeyboardController *m_keyboard; //!< Keyboard used in scheme
  Engine::Input::MouseController *m_mouse; //!< Mouse used in scheme
};

#endif
