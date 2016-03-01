/**
 * @file
 * @author Dan Nixon
 */

#include "SnookerSimulation.h"

#include <Profiler.h>
#include <Shaders.h>

#include <PhysicsUpdate.h>

using namespace Engine::Common;
using namespace Engine::Graphics;
using namespace Engine::Maths;
using namespace Simulation::Physics;

SnookerSimulation::SnookerSimulation()
    : Game("Snooker Loopy", std::make_pair(1024, 768))
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
  m_entities.push_back(m_table->cushion(0));
  m_entities.push_back(m_table->cushion(1));
  m_entities.push_back(m_table->cushion(2));
  m_entities.push_back(m_table->cushion(3));

  // Balls
  m_balls[0] = new Ball(Vector2(-1100.0f, 0.0f), -1); // Cue ball
  // m_balls[1] = new Ball(Vector2(0.0f, 0.0f), 1); // Red
  // m_balls[2] = new Ball(Vector2(0.0f, 0.0f), 1); // Red
  // m_balls[3] = new Ball(Vector2(0.0f, 0.0f), 1); // Red
  // m_balls[4] = new Ball(Vector2(0.0f, 0.0f), 1); // Red
  // m_balls[5] = new Ball(Vector2(0.0f, 0.0f), 1); // Red
  // m_balls[6] = new Ball(Vector2(0.0f, 0.0f), 1); // Red
  // m_balls[7] = new Ball(Vector2(0.0f, 0.0f), 1); // Red
  // m_balls[8] = new Ball(Vector2(0.0f, 0.0f), 1); // Red
  // m_balls[9] = new Ball(Vector2(0.0f, 0.0f), 1); // Red
  // m_balls[10] = new Ball(Vector2(0.0f, 0.0f), 1); // Red
  // m_balls[11] = new Ball(Vector2(0.0f, 0.0f), 1); // Red
  // m_balls[12] = new Ball(Vector2(0.0f, 0.0f), 1); // Red
  // m_balls[13] = new Ball(Vector2(0.0f, 0.0f), 1); // Red
  // m_balls[14] = new Ball(Vector2(0.0f, 0.0f), 1); // Red
  // m_balls[15] = new Ball(Vector2(0.0f, 0.0f), 1); // Red
  m_balls[16] = new Ball(Vector2(-1047.75f, -291.1f), 2);  // Yellow
  m_balls[17] = new Ball(Vector2(-1047.75f, 291.1f), 3); // Green
  m_balls[18] = new Ball(Vector2(-1047.75f, 0.0f), 4);    // Brown
  m_balls[19] = new Ball(Vector2(0.0f, 0.0f), 5);      // Blue
  m_balls[20] = new Ball(Vector2(895.35f, 0.0f), 6);   // Pink
  m_balls[21] = new Ball(Vector2(1466.85f, 0.0f), 7);   // Black

  for (size_t i = 0; i < NUM_BALLS; i++)
  {
    if (m_balls[i] != NULL)
    {
      m_table->addChild(*(m_balls[i]));
      m_entities.push_back(m_balls[i]);
    }
  }

  // Sample physics
  m_balls[0]->setVelocity(Vector2(-3.0f, 0.0f));

  // Scene
  Matrix4 view = Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -10));
  Matrix4 proj = Matrix4::Perspective(1, 100000, 1.33f, 45.0f);
  m_scene = new Scene(m_table, view, proj);

  // Times loops
  m_graphicsLoop = addTimedLoop(16.66f, "graphics");
  m_physicsLoop = addTimedLoop(8.33f, "physics");
  m_profileLoop = addTimedLoop(1000.0f, "profile");

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  m_profiler = new Profiler(this);
}

/**
 * @copydoc Game::gameLoop
 */
void SnookerSimulation::gameLoop(Uint8 id, float dtMilliSec)
{
  // Handle graphics
  if (id == m_graphicsLoop)
  {
    m_scene->update();
    m_scene->render();
    swapBuffers();
  }
  // Handle physics
  else if (id == m_physicsLoop)
  {
    PhysicsUpdate::Update(m_entities, (float)dtMilliSec);

    for (Entity::EntityPtrListIter it = m_entities.begin();
         it != m_entities.end(); ++it)
    {
      Ball *b = dynamic_cast<Ball *>(*it);
      if (!b)
        continue;

      b->mesh()->setStaticColour(b->colour(1.0f - (0.5f * b->hasInterface())));
    }
  }
  // Output profiling data
  else if (id == m_profileLoop)
  {
    m_profiler->computeStats(dtMilliSec);
    std::cout << "Performance statistics:" << std::endl
              << *m_profiler << std::endl;
  }
}

/**
 * @copydoc Game::gameShutdown
 */
void SnookerSimulation::gameShutdown()
{
}
