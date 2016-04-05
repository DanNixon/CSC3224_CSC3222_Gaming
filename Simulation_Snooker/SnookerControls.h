/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_SNOOKER_CONTROLS_H_
#define _SIMULATION_SNOOKER_CONTROLS_H_

#include <Engine_Input/IControlScheme.h>

#include <Engine_Common/Game.h>
#include <Engine_Input/KeyboardController.h>
#include <Engine_Input/MouseController.h>

#include "SnookerSimulation.h"

namespace Simulation
{
namespace Snooker
{
  /**
   * @brief Enumeration of control states for the snooker simulation.
   */
  enum Controls
  {
    A_MOUSE_X,
    A_MOUSE_Y,

    S_TAKE_SHOT,

    S_PROFILE_DISPLAY,
    S_PAUSE,
    S_RESET
  };

  /**
   * @class SnookerControls
   * @brief Control scheme for snooker simulation.
   * @author Dan Nixon
   */
  class SnookerControls : public Engine::Input::IControlScheme
  {
  public:
    /**
     * @copydoc IControlScheme:IControlScheme
     */
    SnookerControls(Engine::Common::Game *game)
        : Engine::Input::IControlScheme(game)
        , m_keyboard(new Engine::Input::KeyboardController(this))
        , m_mouse(new Engine::Input::MouseController(this, game->windowX(), game->windowY()))
    {
      m_keyboard->setMapping(SDLK_f, S_PROFILE_DISPLAY, true);
      m_keyboard->setMapping(SDLK_p, S_PAUSE, true);
      m_keyboard->setMapping(SDLK_r, S_RESET);

      m_mouse->setXMapping(A_MOUSE_X);
      m_mouse->setYMapping(A_MOUSE_Y);
      m_mouse->setButtonMapping(SDL_BUTTON_LEFT, S_TAKE_SHOT);

      addController(m_keyboard);
      addController(m_mouse);

      game->addEventHandler(m_keyboard);
      game->addEventHandler(m_mouse);
    }

    virtual ~SnookerControls()
    {
      m_game->removeEventHandler(m_keyboard);
      m_game->removeEventHandler(m_mouse);
    }

    virtual void setState(size_t state, bool active)
    {
      IControlScheme::setState(state, active);
      static_cast<SnookerSimulation *>(m_game)->m_menu->updateTextFromControls();
    }

  private:
    Engine::Input::KeyboardController *m_keyboard; //!< Keyboard used in scheme
    Engine::Input::MouseController *m_mouse;       //!< Mouse used in scheme
    OptionsMenu *m_menu;
  };
}
}

#endif