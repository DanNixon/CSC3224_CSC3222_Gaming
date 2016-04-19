/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _GAMEDEV_DEMO_KMSIMULATORCONTROLS_H_
#define _GAMEDEV_DEMO_KMSIMULATORCONTROLS_H_

#include "SimulatorControls.h"

#include <Engine_Common/Game.h>

#include <Engine_Input/KeyboardController.h>
#include <Engine_Input/MouseController.h>

#include "controls.h"

namespace GameDev
{
namespace Demo
{
  /**
   * @class KMSimulatorControls
   * @brief Control scheme for flight simulation using a keyboard and mouse.
   * @author Dan Nixon
   */
  class KMSimulatorControls : public SimulatorControls
  {
  public:
    /**
     * @copydoc IControlScheme:IControlScheme
     */
    KMSimulatorControls(Engine::Common::Game *game)
        : SimulatorControls(game)
        , m_mouse(new Engine::Input::MouseController(this, game->windowX(), game->windowY()))
    {
      m_keyboard->setMapping(SDLK_w, S_INCTHROT);
      m_keyboard->setMapping(SDLK_s, S_DECTHROT);
      m_keyboard->setMapping(SDLK_a, S_YAWCCW);
      m_keyboard->setMapping(SDLK_d, S_YAWCW);
      m_keyboard->setMapping(SDLK_1, S_ENGINEOFF);
      m_keyboard->setMapping(SDLK_2, S_ENGINE1);
      m_keyboard->setMapping(SDLK_3, S_ENGINE2);

      m_mouse->setXMapping(A_ROLL);
      m_mouse->setYMapping(A_PITCH);
      m_mouse->setButtonMapping(SDL_BUTTON_LEFT, S_FPV);

      addController(m_mouse);
      game->addEventHandler(m_mouse);
    }

    virtual ~KMSimulatorControls()
    {
      m_game->removeEventHandler(m_mouse);
    }

    /**
     * @copydoc IControlScheme::setState
     */
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

      case S_ENGINEOFF:
        if (active)
          setAnalog(A_ENGINE, 0.0f);
        break;
      case S_ENGINE1:
        if (active)
          setAnalog(A_ENGINE, 0.75f);
        break;
      case S_ENGINE2:
        if (active)
          setAnalog(A_ENGINE, 1.0f);
        break;
      }
    }

  protected:
    Engine::Input::MouseController *m_mouse; //!< Mouse input
  };
}
}

#endif
