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
  m_texShader = new ShaderProgram();
  m_texShader->addShader(new VertexShader("vert.glsl"));
  m_texShader->addShader(new FragmentShader("frag_tex.glsl"));
  m_texShader->link();

  m_colShader = new ShaderProgram();
  m_colShader->addShader(new VertexShader("vert.glsl"));
  m_colShader->addShader(new FragmentShader("frag_col.glsl"));
  m_colShader->link();

  m_tableTex = new Texture("tabletopTex");
  m_tableTex->load("table.bmp");

  m_table = new RenderableObject(
      Mesh::GenerateRect2D(Vector2(3569.0f, 1778.0f)), m_texShader, m_tableTex);
  m_table->setModelMatrix(Matrix4::Translation(Vector3(0.0, 0.0, -3600.0)));

  m_child = new RenderableObject(Mesh::GenerateRect2D(Vector2(200.0f, 100.0f)),
                                 m_colShader);
  m_child->setModelMatrix(Matrix4::Translation(Vector3(0.0f, 1000.0f, 0.0f)));
  m_table->addChild(*m_child);

  Matrix4 view = Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -10));
  Matrix4 proj = Matrix4::Perspective(1, 100000, 1.33f, 45.0f);

  m_scene = new Scene(m_table, view, proj);

  glEnable(GL_DEPTH_TEST);

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
