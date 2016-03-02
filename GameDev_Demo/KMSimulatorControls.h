#pragma once

#include <IControlScheme.h>

#include <Game.h>

#include <MouseController.h>
#include <KeyboardController.h>

#include "controls.h"

class KMSimulatorControls : public Engine::Input::IControlScheme
{
public:
  KMSimulatorControls(Engine::Common::Game * game) :
    m_keyboard(new Engine::Input::KeyboardController(this))
  {
    m_keyboard->setMapping(SDLK_w, S_INCTHROT);
    m_keyboard->setMapping(SDLK_s, S_DECTHROT);
    m_keyboard->setMapping(SDLK_a, S_YAWCCW);
    m_keyboard->setMapping(SDLK_d, S_YAWCW);
    m_keyboard->setMapping(SDLK_f, S_FPV);
    m_keyboard->setMapping(SDLK_p, S_PAUSE);
    m_keyboard->setMapping(SDLK_r, S_RESET);

    addController(m_keyboard);
    game->addEventHandler(m_keyboard);
  }

  virtual ~KMSimulatorControls()
  {
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
  Engine::Input::KeyboardController * m_keyboard;
};

