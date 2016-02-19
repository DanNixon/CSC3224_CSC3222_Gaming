/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include <Game.h>

#include <Scene.h>
#include <RenderableObject.h>
#include <ShaderProgram.h>

class DemoGame : public Game
{
public:
  DemoGame();
  virtual ~DemoGame();

  void setup();
  void loop(unsigned long dtUs);
  void tearDown();

private:
  ShaderProgram *m_sp;
  RenderableObject *m_cube;
  RenderableObject *m_child;
  Scene *m_s;
};
