/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include <Game.h>

#include <Scene.h>
#include <ShaderProgram.h>

#include "Table.h"
#include "Ball.h"

/**
 * @class SnookerSimulation
 * @brief Game application for the snooker simulation.
 * @author Dan Nixon
 */
class SnookerSimulation : public Engine::Common::Game
{
public:
  static const int NUM_BALLS = 22;

  SnookerSimulation();
  ~SnookerSimulation();

protected:
  void gameStartup();
  void gameLoop(Uint8 id, Uint32 deltaT);
  void gameShutdown();

private:
  Uint8 m_graphicsLoop;
  Uint8 m_physicsLoop;

  Engine::Common::Scene *m_scene;

  Table *m_table;
  Ball *m_balls[NUM_BALLS];
};