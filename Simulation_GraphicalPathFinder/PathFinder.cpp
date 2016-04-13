/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#include "PathFinder.h"

#include <sstream>

#include <Engine_Common/SceneObject.h>
#include <Engine_Graphics/LineMesh.h>
#include <Engine_Graphics/RenderableObject.h>
#include <Engine_Graphics/Shaders.h>
#include <Engine_Logging/Logger.h>
#include <Simulation_PathFinding/GraphLoader.h>

using namespace Engine::Common;
using namespace Engine::Graphics;
using namespace Engine::Maths;
using namespace Simulation::PathFinding;

namespace
{
Engine::Logging::Logger g_log(__FILE__);
}

namespace Simulation
{
namespace GraphicalPathFinder
{
  PathFinder::PathFinder()
      : Game("Graphical Path Finder", std::make_pair(1024, 768))
  {
  }

  PathFinder::~PathFinder()
  {
  }

  /**
   * @copydoc Game::gameStartup
   */
  int PathFinder::gameStartup()
  {
    // Shaders
    m_colShader = new ShaderProgram();
    m_colShader->addShader(new VertexShader("../resources/shader/vert_simple.glsl"));
    m_colShader->addShader(new FragmentShader("../resources/shader/frag_col.glsl"));
    m_colShader->link();

    // Scene
    Matrix4 view = Matrix4::BuildViewMatrix(Vector3(0, 0, -50), Vector3(0, 0, 0));
    Matrix4 proj = Matrix4::Perspective(1, 100, 1.33f, 45.0f);
    m_scene = new Scene(new SceneObject("root"), view, proj);

    // Load graph
    if (!GraphLoader::LoadGraph(m_nodes, m_edges, "../resources/buckminsterfullerene.dat"))
    {
      g_log.critical("Could not load graph data file");
      return 1;
    }

    // Add graphical nodes
    for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it)
    {
      // TODO
    }

    // Add graphical edges
    for (auto it = m_edges.begin(); it != m_edges.end(); ++it)
    {
      LineMesh *mesh = new LineMesh((*it)->nodeA()->position(), (*it)->nodeB()->position());
      RenderableObject *obj = new RenderableObject((*it)->id(), mesh, m_colShader);
      m_scene->root()->addChild(obj);
    }

    // Timed loops
    m_graphicsLoop = addTimedLoop(16.66f, "graphics");

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    return 0;
  }

  /**
   * @copydoc Game::gameLoop
   */
  void PathFinder::gameLoop(Uint8 id, float dtMilliSec)
  {
    // Handle graphics
    if (id == m_graphicsLoop)
    {
      m_scene->update(dtMilliSec, Subsystem::GRAPHICS);
      swapBuffers();
    }
  }

  /**
   * @copydoc Game::gameShutdown
   */
  void PathFinder::gameShutdown()
  {
    for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it)
      delete *it;
    for (auto it = m_edges.begin(); it != m_edges.end(); ++it)
      delete *it;
  }
}
}