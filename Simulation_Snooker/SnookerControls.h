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
    S_PROFILE_DISPLAY,
    S_TAKE_SHOT
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
     * @brief Create a new keyboard and mouse control scheme.
     * @param game Target game
     */
    SnookerControls(Engine::Common::Game *game)
        : m_game(game)
        , m_keyboard(new Engine::Input::KeyboardController(this))
        , m_mouse(new Engine::Input::MouseController(this, game->windowX(), game->windowY()))
    {
      m_keyboard->setMapping(SDLK_f, S_PROFILE_DISPLAY, true);

      m_mouse->setXMapping(A_MOUSE_X);
      m_mouse->setYMapping(A_MOUSE_Y);
      m_mouse->setButtonMapping(SDL_BUTTON_LEFT, S_TAKE_SHOT);

      addController(m_keyboard);
      addController(m_mouse);

      m_game->addEventHandler(m_keyboard);
      m_game->addEventHandler(m_mouse);
    }

    virtual ~SnookerControls()
    {
      m_game->removeEventHandler(m_keyboard);
      m_game->removeEventHandler(m_mouse);
    }

  private:
    Engine::Common::Game *m_game;                  //!< Game instance this scheme is attached to
    Engine::Input::KeyboardController *m_keyboard; //!< Keyboard used in scheme
    Engine::Input::MouseController *m_mouse;       //!< Mouse used in scheme
  };
}
}

#endif