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
#include <Engine_Graphics/SphericalMesh.h>
#include <Engine_Logging/Logger.h>
#include <Engine_Maths/Quaternion.h>

#include <Simulation_PathFinding/GraphLoader.h>

#include "EdgeSelectionPane.h"
#include "NodeSelectionPane.h"

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
  bool PathFinder::IsOnList(const std::vector<QueueableNode *> &list, Node *node)
  {
    return std::find_if(list.begin(), list.end(), [node](QueueableNode *n) { return n->node == node; }) != list.end();
  }

  bool PathFinder::IsOnList(const std::vector<Node *> &list, Node *node)
  {
    return std::find(list.begin(), list.end(), node) != list.end();
  }

  PathFinder::PathFinder()
      : Game("Graphical Path Finder", std::make_pair(1024, 768))
  {
  }

  PathFinder::~PathFinder()
  {
  }

  void PathFinder::setViewMode(ViewMode_bitset mode)
  {
    m_viewMode = mode;

    const bool showWeights(m_viewMode.test(ViewMode::WEIGHTS));
    const bool showOpenList(m_viewMode.test(ViewMode::OPEN_LIST));
    const bool showClosedList(m_viewMode.test(ViewMode::CLOSED_LIST));
    const bool showPath(m_viewMode.test(ViewMode::PATH));

    // Process nodes
    for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it)
    {
      Node *node = it->first;
      Colour nodeColour = ColourLookup::Instance().get("node_default");

      if (showOpenList && IsOnList(m_finder->openList(), node))
        nodeColour = ColourLookup::Instance().get("node_open_list");

      if (showClosedList && IsOnList(m_finder->closedList(), node))
        nodeColour = ColourLookup::Instance().get("node_closed_list");

      if (showPath && IsOnList(m_finder->path(), node))
        nodeColour = ColourLookup::Instance().get("node_path");

      it->second->mesh()->setStaticColour(nodeColour);
    }

    // Process edges
    for (auto it = m_edges.begin(); it != m_edges.end(); ++it)
    {
      Edge *edge = it->first;
      Colour edgeColour = ColourLookup::Instance().get("edge_default");

      if (showWeights)
      {
        // TODO
      }

      if (showPath && IsOnList(m_finder->path(), edge->nodeA()) && IsOnList(m_finder->path(), edge->nodeB()))
        edgeColour = ColourLookup::Instance().get("edge_path");

      it->second->mesh()->setStaticColour(edgeColour);
    }
  }

  /**
   * @copydoc Game::gameStartup
   */
  int PathFinder::gameStartup()
  {
    // Load fonts
    m_fontMedium = TTF_OpenFont("../resources/open-sans/OpenSans-Regular.ttf", 20);

    // Set colours
    ColourLookup::Instance().add("node_default", Colour(1.0f, 1.0f, 1.0f, 1.0f));
    ColourLookup::Instance().add("node_open_list", Colour(0.0f, 1.0f, 0.0f, 1.0f));
    ColourLookup::Instance().add("node_closed_list", Colour(1.0f, 0.0f, 0.0f, 1.0f));
    ColourLookup::Instance().add("node_path", Colour(0.0f, 0.0f, 1.0f, 1.0f));

    ColourLookup::Instance().add("edge_default", Colour(1.0f, 1.0f, 1.0f, 1.0f));
    ColourLookup::Instance().add("edge_open_list", Colour(0.0f, 1.0f, 0.0f, 1.0f));
    ColourLookup::Instance().add("edge_closed_list", Colour(1.0f, 0.0f, 0.0f, 1.0f));
    ColourLookup::Instance().add("edge_path", Colour(0.0f, 0.0f, 1.0f, 1.0f));

    // Controls
    m_controls = new Controls(this);

    // Shaders
    m_colShader = new ShaderProgram();
    m_colShader->addShader(new VertexShader("../resources/shader/vert_simple.glsl"));
    m_colShader->addShader(new FragmentShader("../resources/shader/frag_col.glsl"));
    m_colShader->link();
    ShaderProgramLookup::Instance().add("col_shader", m_colShader);

    ShaderProgram *menuShader = new ShaderProgram();
    menuShader = new ShaderProgram();
    menuShader->addShader(new VertexShader("../resources/shader/vert_simple.glsl"));
    menuShader->addShader(new FragmentShader("../resources/shader/frag_tex.glsl"));
    menuShader->link();
    ShaderProgramLookup::Instance().add("menu_shader", menuShader);

    // Scene
    Matrix4 view = Matrix4::BuildViewMatrix(Vector3(0, 0, -15), Vector3(0, 0, 0));
    Matrix4 proj = Matrix4::Perspective(1, 100, 1.33f, 45.0f);
    m_scene = new Scene(new SceneObject("root"), view, proj);

    // Menu
    m_menu = new OptionsMenu(this, m_fontMedium, 0.05f);
    m_menu->setMargin(Vector2(0.005f, 0.005f));
    m_menu->layout();
    m_menu->show();
    addEventHandler(m_menu);

    // Node selection menu
    nodeSelection = new NodeSelectionPane(this, m_fontMedium, 0.05f);
    nodeSelection->setPosition(Vector3(-0.75f, -0.95f));
    nodeSelection->layout();
    addEventHandler(nodeSelection);
    nodeSelection->hide();

    // Edge selection menu
    edgeSelection = new EdgeSelectionPane(this, m_fontMedium, 0.05f);
    edgeSelection->setPosition(Vector3(-0.75f, -0.95f));
    edgeSelection->layout();
    addEventHandler(edgeSelection);
    edgeSelection->hide();

    // Load graph
    const std::string graphDataFile("../resources/buckminsterfullerene.dat");
    // const std::string graphDataFile("../resources/test_graph.dat");

    std::vector<Node *> nodes;
    std::vector<Edge *> edges;
    if (!GraphLoader::LoadGraph(nodes, edges, graphDataFile))
    {
      g_log.critical("Could not load graph data file");
      return 1;
    }

    // Create graphical nodes
    for (auto it = nodes.begin(); it != nodes.end(); ++it)
    {
      SphericalMesh *mesh = new SphericalMesh(0.1f);
      RenderableObject *obj = new RenderableObject((*it)->id(), mesh, m_colShader);
      obj->setModelMatrix(Matrix4::Translation((*it)->position()));
      m_scene->root()->addChild(obj);

      m_nodes[*it] = obj;
    }

    m_pickedNode = m_nodes.begin();

    // Create graphical edges
    for (auto it = edges.begin(); it != edges.end(); ++it)
    {
      LineMesh *mesh = new LineMesh((*it)->nodeA()->position(), (*it)->nodeB()->position());
      RenderableObject *obj = new RenderableObject((*it)->id(), mesh, m_colShader);
      m_scene->root()->addChild(obj);

      m_edges[*it] = obj;
    }

    m_pickedEdge = m_edges.begin();

    // Create path finder
    m_finder = new AStar(nodes);

    // Default view
    setViewMode();

    // Timed loops
    m_graphicsLoop = addTimedLoop(16.66f, "graphics");
    m_controlLoop = addTimedLoop(25.0f, "control");

    // GL settings
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

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
      m_menu->update(dtMilliSec, Subsystem::GRAPHICS);
      nodeSelection->update(dtMilliSec, Subsystem::GRAPHICS);
      edgeSelection->update(dtMilliSec, Subsystem::GRAPHICS);

      swapBuffers();
    }
    // Handle controls
    else if (id == m_controlLoop)
    {
      // Handle node selection
      bool prevNode = m_controls->state(S_PREV_NODE);
      bool nextNode = m_controls->state(S_NEXT_NODE);

      if (prevNode || nextNode)
      {
        // TODO
      }

      // Update graph rotation
      float yaw = m_controls->analog(A_MOUSE_X) * 180.0f;
      float pitch = m_controls->analog(A_MOUSE_Y) * 180.0f;
      Quaternion rotQuat(yaw, pitch, 0.0f);
      m_scene->root()->setModelMatrix(rotQuat.rotationMatrix());
    }
  }

  /**
   * @copydoc Game::gameShutdown
   */
  void PathFinder::gameShutdown()
  {
    // Delete graph
    for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it)
      delete it->first;
    for (auto it = m_edges.begin(); it != m_edges.end(); ++it)
      delete it->first;

    // Delete fonts
    TTF_CloseFont(m_fontMedium);
  }
}
}