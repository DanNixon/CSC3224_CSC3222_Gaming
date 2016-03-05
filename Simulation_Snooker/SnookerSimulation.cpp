/**
 * @file
 * @author Dan Nixon
 */

#include "SnookerSimulation.h"

#include <SDL_ttf.h>

#include <Profiler.h>
#include <Shaders.h>
#include <TextPane.h>

using namespace Engine::Common;
using namespace Engine::Graphics;
using namespace Engine::Maths;
using namespace Engine::Input;
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
  // Load font for text display
  m_font = TTF_OpenFont("../resources/open-sans/OpenSans-Regular.ttf", 45);

  // Table
  m_table = new Table(m_entities);
  m_table->setModelMatrix(Matrix4::Translation(Vector3(0.0, 0.0, -3600.0)));

  // Balls
  m_balls[0] = new Ball(Vector2(-1150.0f, 0.0f), -1);     // Cue ball
  m_balls[1] = new Ball(Vector2(957.85f, 0.0f), 1);       // Red
  m_balls[2] = new Ball(Vector2(1010.35f, 26.25f), 1);    // Red
  m_balls[3] = new Ball(Vector2(1010.35f, -26.25f), 1);   // Red
  m_balls[4] = new Ball(Vector2(1062.85f, 52.5f), 1);     // Red
  m_balls[5] = new Ball(Vector2(1062.85f, 0.0f), 1);      // Red
  m_balls[6] = new Ball(Vector2(1062.85f, -52.5f), 1);    // Red
  m_balls[7] = new Ball(Vector2(1115.35f, 78.75f), 1);    // Red
  m_balls[8] = new Ball(Vector2(1115.35f, 26.25f), 1);    // Red
  m_balls[9] = new Ball(Vector2(1115.35f, -26.25f), 1);   // Red
  m_balls[10] = new Ball(Vector2(1115.35f, -78.75f), 1);  // Red
  m_balls[11] = new Ball(Vector2(1167.85f, 105.0f), 1);   // Red
  m_balls[12] = new Ball(Vector2(1167.85f, 52.5f), 1);    // Red
  m_balls[13] = new Ball(Vector2(1167.85f, 0.0f), 1);     // Red
  m_balls[14] = new Ball(Vector2(1167.85f, -52.5f), 1);   // Red
  m_balls[15] = new Ball(Vector2(1167.85f, -105.0f), 1);  // Red
  m_balls[16] = new Ball(Vector2(-1047.75f, -291.1f), 2); // Yellow
  m_balls[17] = new Ball(Vector2(-1047.75f, 291.1f), 3);  // Green
  m_balls[18] = new Ball(Vector2(-1047.75f, 0.0f), 4);    // Brown
  m_balls[19] = new Ball(Vector2(0.0f, 0.0f), 5);         // Blue
  m_balls[20] = new Ball(Vector2(895.35f, 0.0f), 6);      // Pink
  m_balls[21] = new Ball(Vector2(1466.85f, 0.0f), 7);     // Black

  for (size_t i = 0; i < NUM_BALLS; i++)
  {
    if (m_balls[i] != NULL)
    {
      m_table->addChild(*(m_balls[i]));
      m_entities.push_back(m_balls[i]);
    }
  }

  // Scene
  Matrix4 view = Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -10));
  Matrix4 proj = Matrix4::Perspective(1, 100000, 1.33f, 45.0f);
  m_scene = new Scene(m_table, view, proj);

  // UI
  ShaderProgram *sp = new ShaderProgram();
  sp->addShader(new VertexShader("../resources/shader/vert_simple.glsl"));
  sp->addShader(new FragmentShader("../resources/shader/frag_tex.glsl"));
  sp->link();
  TextPane *p = new TextPane(0.8f, sp, m_font);
  p->setModelMatrix(Matrix4::Translation(Vector3(0.0f, 0.9f, 0.0f)));
  p->setText("Snooker Loopy!");

  Matrix4 orth = Matrix4::Orthographic(0.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f);
  m_ui = new Scene(p, view, orth);

  // Timed loops
  m_graphicsLoop = addTimedLoop(16.66f, "graphics");
  m_physicsLoop = addTimedLoop(8.33f, "physics");
  m_profileLoop = addTimedLoop(1000.0f, "profile");

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  // Handle keyboard presses myself
  addEventHandler(this);

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
    m_ui->update();
    m_ui->render();
    swapBuffers();
  }
  // Handle physics
  else if (id == m_physicsLoop)
  {
    m_physics.update(m_entities, dtMilliSec);

    // TODO
    auto inters = m_physics.interfaces();
    for (auto it = inters.begin(); it != inters.end(); ++it)
    {
      Entity *a = it->first.first;
      Entity *b = it->first.second;

      if (dynamic_cast<Pocket *>(a))
        std::cout << "Ball in pocket" << std::endl;
      else
        std::cout << it->first.first << " - " << it->first.second << " ["
                  << it->second << "]" << std::endl;
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

/**
 * @copydoc KeyboardHandler::handleKey
 */
void SnookerSimulation::handleKey(const SDL_KeyboardEvent &e)
{
  if (e.state == SDL_PRESSED)
  {
    Ball *cueBall = m_balls[0];
    Vector2 cueBallVel = cueBall->velocity();

    switch (e.keysym.sym)
    {
    case SDLK_w:
      cueBall->setVelocity(cueBallVel + Vector2(0.0f, 1.0f));
      break;
    case SDLK_a:
      cueBall->setVelocity(cueBallVel + Vector2(-1.0f, 0.0f));
      break;
    case SDLK_s:
      cueBall->setVelocity(cueBallVel + Vector2(0.0f, -1.0f));
      break;
    case SDLK_d:
      cueBall->setVelocity(cueBallVel + Vector2(1.0f, 0.0f));
      break;
    }
  }
}
