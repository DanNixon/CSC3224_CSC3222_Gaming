/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include <Game.h>

#include <Scene.h>
#include <RenderableObject.h>
#include <ShaderProgram.h>

/**
 * @class DemoGame
 * @brief Game demonstrating features of the game engine.
 * @author Dan Nixon
 */
class DemoGame : public Game
{
public:
  DemoGame();
  virtual ~DemoGame();

protected:
  void gameStartup();
  void gameLoop(unsigned long dtUs);
  void gameShutdown();

private:
  ShaderProgram *m_sp;
  RenderableObject *m_cube;
  RenderableObject *m_child;
  Scene *m_s;
};
