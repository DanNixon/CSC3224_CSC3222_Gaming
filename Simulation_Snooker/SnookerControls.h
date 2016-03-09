/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SNOOKERCONTROLS_H_
#define _SNOOKERCONTROLS_H_

#include <IControlScheme.h>

#include <Game.h>

#include <KeyboardController.h>
#include <MouseController.h>

enum Controls
{
  A_MOUSE_X,
  A_MOUSE_Y,
  S_CUEBALL_UP,
  S_CUEBALL_DOWN,
  S_CUEBALL_LEFT,
  S_CUEBALL_RIGHT,
  S_TAKE_SHOT,
  S_TEST
};

/**
 * @class SnooerControls
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
      , m_mouse(new Engine::Input::MouseController(this, game->windowX(),
                                                   game->windowY()))
  {
    m_keyboard->setMapping(SDLK_w, S_CUEBALL_UP);
    m_keyboard->setMapping(SDLK_s, S_CUEBALL_DOWN);
    m_keyboard->setMapping(SDLK_a, S_CUEBALL_LEFT);
    m_keyboard->setMapping(SDLK_d, S_CUEBALL_RIGHT);
    m_keyboard->setMapping(SDLK_SPACE, S_TEST);

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

    delete m_keyboard;
    delete m_mouse;
  }

private:
  Engine::Common::Game *m_game; //!< Game instance this scheme is attached to
  Engine::Input::KeyboardController *m_keyboard; //!< Keyboard used in scheme
  Engine::Input::MouseController *m_mouse;       //!< Mouse used in scheme
};

#endif
