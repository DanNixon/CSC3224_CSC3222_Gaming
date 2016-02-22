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
    : Game("Snooker", std::make_pair(640, 480))
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
  m_sp = new ShaderProgram();
  m_sp->addShader(new VertexShader("vert.glsl"));
  m_sp->addShader(new FragmentShader("frag.glsl"));
  m_sp->link();

  m_table = new RenderableObject(Mesh::GenerateRect2D(Vector2(3569.0f, 1778.0f)), m_sp);
  m_table->setModelMatrix(Matrix4::Translation(Vector3(0.0, 0.0, -3600.0)));

  m_s = new Scene(
    m_table, Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -10)),
    Matrix4::Perspective(1, 100000, 1.33f, 45.0f));

  glEnable(GL_DEPTH_TEST);
}

/**
 * @copydoc Game::gameLoop
 */
void SnookerSimulation::gameLoop(unsigned long dtUs)
{
  m_s->update();
  m_s->render();
}

/**
 * @copydoc Game::gameShutdown
 */
void SnookerSimulation::gameShutdown()
{
}
