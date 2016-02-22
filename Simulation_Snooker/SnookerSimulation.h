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
 * @class SnookerSimulation
 * @brief Game application for the snooker simulation.
 * @author Dan Nixon
 */
class SnookerSimulation : public Engine::Common::Game
{
public:
  SnookerSimulation();
  ~SnookerSimulation();

protected:
  void gameStartup();
  void gameLoop(unsigned long dtUs);
  void gameShutdown();

private:
  Engine::Graphics::ShaderProgram *m_sp;
  Engine::Graphics::RenderableObject *m_table;
  Engine::Common::Scene *m_s;
};
