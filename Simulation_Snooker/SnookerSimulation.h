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
  void gameLoop(Uint8 id, Uint32 deltaT);
  void gameShutdown();

private:
  Uint8 m_graphicsLoop;
  Uint8 m_physicsLoop;

  Engine::Graphics::ShaderProgram *m_texShader;
  Engine::Graphics::ShaderProgram *m_colShader;
  Engine::Graphics::Texture *m_tableTex;
  Engine::Common::Scene *m_scene;

  Engine::Graphics::RenderableObject *m_table;
  Engine::Graphics::RenderableObject *m_child;
};
