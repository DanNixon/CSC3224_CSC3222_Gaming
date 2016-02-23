/**
 * @file
 * @author Dan Nixon
 */

#include "SnookerSimulation.h"

#include <Shaders.h>

using namespace Engine::Common;
using namespace Engine::Graphics;
using namespace Engine::Maths;

SnookerSimulation::SnookerSimulation()
    : Game("Snooker", std::make_pair(1024, 768))
{
}

SnookerSimulation::~SnookerSimulation()
{
}

/**
 * @copydoc Game::gameStartup
 */
void SnookerSimulation::gameStartup()
{
  // Table
  m_table = new Table();
  m_table->setModelMatrix(Matrix4::Translation(Vector3(0.0, 0.0, -3600.0)));

  // Balls
  m_balls[0] = new Ball(Vector2(900.0f, 0.0f), -1); // Cue
  m_balls[1] = new Ball(Vector2(600.0f, 200.0f), 2); // Yellow
  m_balls[2] = new Ball(Vector2(600.0f, -200.0f), 3); // Green
  m_balls[3] = new Ball(Vector2(600.0f, 0.0f), 4); // Brown
  m_balls[4] = new Ball(Vector2(0.0f, 0.0f), 5); // Blue
  m_balls[5] = new Ball(Vector2(-600.0f, 0.0f), 6); // Pink
  m_balls[6] = new Ball(Vector2(-900.0f, 0.0f), 7); // Black

  for (size_t i = 0; i < NUM_BALLS; i++)
  {
    if (m_balls[i] != NULL)
      m_table->addChild(*(m_balls[i]));
  }

  // Scene
  Matrix4 view = Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -10));
  Matrix4 proj = Matrix4::Perspective(1, 100000, 1.33f, 45.0f);
  m_scene = new Scene(m_table, view, proj);

  glEnable(GL_DEPTH_TEST);

  // Times loops
  m_graphicsLoop = addTimedLoop(16, "graphics");
  m_physicsLoop = addTimedLoop(8, "physics");
}

/**
 * @copydoc Game::gameLoop
 */
void SnookerSimulation::gameLoop(Uint8 id, Uint32 deltaT)
{
  if (id == m_graphicsLoop)
  {
    m_scene->update();
    m_scene->render();
    swapBuffers();
  }
  else if (id == m_physicsLoop)
  {
    // TODO
  }
}

/**
 * @copydoc Game::gameShutdown
 */
void SnookerSimulation::gameShutdown()
{
}
