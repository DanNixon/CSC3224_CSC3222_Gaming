/**
 * @file
 * @author Dan Nixon
 */

#ifndef _GAMEDEV_DEMO_KMSIMULATORCONTROLS_H_
#define _GAMEDEV_DEMO_KMSIMULATORCONTROLS_H_

#include <Engine_Input/IControlScheme.h>

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
  class KMSimulatorControls : public Engine::Input::IControlScheme
  {
  public:
    /**
     * @brief Create a new keyboard and mouse control scheme.
     * @param game Target game
     */
    KMSimulatorControls(Engine::Common::Game *game)
        : m_game(game)
        , m_keyboard(new Engine::Input::KeyboardController(this))
        , m_mouse(new Engine::Input::MouseController(this, game->windowX(), game->windowY()))
    {
      m_keyboard->setMapping(SDLK_w, S_INCTHROT);
      m_keyboard->setMapping(SDLK_s, S_DECTHROT);
      m_keyboard->setMapping(SDLK_a, S_YAWCCW);
      m_keyboard->setMapping(SDLK_d, S_YAWCW);

      m_keyboard->setMapping(SDLK_f, S_FPV, true);
      m_keyboard->setMapping(SDLK_ESCAPE, S_OPENMENU, true);

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
      }
    }

  private:
    Engine::Common::Game *m_game;                  //!< Game instance this scheme is attached to
    Engine::Input::KeyboardController *m_keyboard; //!< Keyboard used in scheme
    Engine::Input::MouseController *m_mouse;       //!< Mouse used in scheme
  };
}
}

#endif