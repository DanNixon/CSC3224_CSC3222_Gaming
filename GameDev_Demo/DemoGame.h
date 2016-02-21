/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include <Game.h>

#include <Scene.h>
#include <RenderableObject.h>
#include <ShaderProgram.h>
#include "DemoKeyboardHandler.h"
#include "DemoMouseHandler.h"
#include "DemoJoystickHandler.h"

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
  void gameLoop(unsigned long dtUs);
  void gameShutdown();

private:
  Engine::Graphics::ShaderProgram *m_sp;
  Engine::Graphics::RenderableObject *m_cube;
  Engine::Graphics::RenderableObject *m_child;
  Engine::Common::Scene *m_s;
  DemoKeyboardHandler m_keyboard;
  DemoMouseHandler m_mouse;
  DemoJoystickHandler m_joystick;
};
