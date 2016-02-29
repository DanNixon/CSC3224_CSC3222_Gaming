/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATIONSNOOKER_SNOOKERSIMULATION_H_
#define _SIMULATIONSNOOKER_SNOOKERSIMULATION_H_

#include <Game.h>

#include <Scene.h>
#include <ShaderProgram.h>

#include <Entity.h>

#include "Ball.h"
#include "Table.h"

/**
 * @class SnookerSimulation
 * @brief Game application for the snooker simulation.
 * @author Dan Nixon
 */
class SnookerSimulation : public Engine::Common::Game
{
public:
  /**
   * @brief Number of snooker balls.
   */
  static const int NUM_BALLS = 22;

  SnookerSimulation();
  ~SnookerSimulation();

protected:
  void gameStartup();
  void gameLoop(Uint8 id, float dtMilliSec);
  void gameShutdown();

private:
  Uint8 m_graphicsLoop;
  Uint8 m_physicsLoop;
  Uint8 m_profileLoop;

  Engine::Common::Scene *m_scene;

  Table *m_table;
  Ball *m_balls[NUM_BALLS];

  Simulation::Physics::Entity::EntityPtrList m_entities;
};

#endif