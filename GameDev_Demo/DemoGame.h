/**
 * @file
 * @author Dan Nixon
 */

#ifndef _DEMOGAME_H_
#define _DEMOGAME_H_

#include <Game.h>

#include <RenderableObject.h>
#include <Scene.h>
#include <ShaderProgram.h>

#include "DemoJoystickHandler.h"
#include "DemoKeyboardHandler.h"
#include "DemoMouseHandler.h"

/**
 * @class DemoGame
 * @brief Game demonstrating features of the game engine.
 * @author Dan Nixon
 */
class DemoGame : public Engine::Common::Game
{
public:
  DemoGame();
  virtual ~DemoGame();

protected:
  void gameStartup();
  void gameLoop(Uint8 id, float dtMilliSec);
  void gameShutdown();

private:
  Uint8 m_graphicsLoop;
  Uint8 m_physicsLoop;
  Uint8 m_profileLoop;

  Engine::Graphics::ShaderProgram *m_sp;
  Engine::Common::Scene *m_s;

  Engine::Graphics::RenderableObject *m_cube;
  Engine::Graphics::RenderableObject *m_child;

  DemoKeyboardHandler m_keyboard;
  DemoMouseHandler m_mouse;
  DemoJoystickHandler m_joystick;
};

#endif