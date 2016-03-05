/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATIONSNOOKER_SNOOKERSIMULATION_H_
#define _SIMULATIONSNOOKER_SNOOKERSIMULATION_H_

#include <Game.h>

#include <SDL_ttf.h>

#include <KeyboardHandler.h>
#include <Scene.h>
#include <ShaderProgram.h>
#include <TextPane.h>

#include <Entity.h>
#include <PhysicsUpdate.h>

#include "Ball.h"
#include "Table.h"

/**
 * @class SnookerSimulation
 * @brief Game application for the snooker simulation.
 * @author Dan Nixon
 */
class SnookerSimulation : public Engine::Common::Game,
                          public Engine::Input::KeyboardHandler
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

  void handleKey(const SDL_KeyboardEvent &e);

private:
  Uint8 m_graphicsLoop;
  Uint8 m_physicsLoop;
  Uint8 m_profileLoop;

  Engine::Common::Scene *m_scene;
  Engine::Common::Scene *m_ui;

  Table *m_table;
  Ball *m_balls[NUM_BALLS];

  Simulation::Physics::Entity::EntityPtrList m_entities;
  Simulation::Physics::PhysicsUpdate m_physics;

  TTF_Font *m_fontLarge;
  TTF_Font *m_fontMedium;
  Engine::Graphics::ShaderProgram * m_uiShader;
  Engine::Graphics::TextPane *m_profileGraphics;
  Engine::Graphics::TextPane *m_profilePhysics;
};

#endif