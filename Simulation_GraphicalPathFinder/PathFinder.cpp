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
#include <Engine_Graphics/ShaderProgram.h>
#include <Engine_Graphics/Shaders.h>
#include <Engine_Graphics/SphericalMesh.h>
#include <Engine_Logging/Logger.h>
#include <Engine_Logging/LoggingService.h>
#include <Engine_Maths/Quaternion.h>

#include <Simulation_PathFInding/Utils.h>
#include <Simulation_PathFinding/GraphLoader.h>

#include "EdgeSelectionPane.h"
#include "NodeSelectionPane.h"

using namespace Engine::Common;
using namespace Engine::Graphics;
using namespace Engine::Maths;
using namespace Engine::Logging;
using namespace Simulation::PathFinding;

namespace
{
Logger g_log(__FILE__);
}

namespace Simulation
{
namespace GraphicalPathFinder
{
  /**
   * @brief Creates a new path finder.
   */
  PathFinder::PathFinder()
      : Game("Graphical Path Finder", std::make_pair(1024, 768))
  {
#ifdef _DEBUG
    LoggingService::Instance().setLevel(LogLevel::DEBUG);
#endif
  }

  PathFinder::~PathFinder()
  {
  }

  /**
   * @brief Sets the current view mode and updates colours of graph features.
   * @param mode View mode
   */
  void PathFinder::setViewMode(ViewMode_bitset mode)
  {
    m_viewMode = mode;

    const bool showWeights(m_viewMode.test(ViewMode::WEIGHTS));
    const bool showStaticCosts(m_viewMode.test(ViewMode::STATIC_COSTS));
    const bool showCosts(m_viewMode.test(ViewMode::COSTS));
    const bool showOpenList(m_viewMode.test(ViewMode::OPEN_LIST));
    const bool showClosedList(m_viewMode.test(ViewMode::CLOSED_LIST));
    const bool showPath(m_viewMode.test(ViewMode::PATH));

    // Process nodes
    for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it)
    {
      Node *node = it->first;
      Colour nodeColour = ColourLookup::Instance().get("node_default");

      const bool isStart(node == m_startNode->first);
      const bool isEnd(node == m_endNode->first);
      const bool isSelected(node == m_nodeSelection->selectedNode()->first);

      if (showOpenList && Utils::IsOnList(m_finder->openList(), node))
        nodeColour = ColourLookup::Instance().get("node_open_list");

      if (showClosedList && Utils::IsOnList(m_finder->closedList(), node))
        nodeColour = ColourLookup::Instance().get("node_closed_list");

      if (showPath && Utils::IsOnList(m_finder->path(), node))
        nodeColour = ColourLookup::Instance().get("node_path");

      if (isStart)
        nodeColour = ColourLookup::Instance().get("node_start");

      if (isEnd)
        nodeColour = ColourLookup::Instance().get("node_end");

      if (isSelected)
        nodeColour = ColourLookup::Instance().get("node_selected");

      it->second->mesh()->setStaticColour(nodeColour);

      // Check this node has traversable connections, set to invisible if all
      // edges are not traversable, unless it is the start, end or selected node
      bool visible = isStart || isEnd || isSelected;
      for (size_t i = 0; i < node->numConnections(); i++)
      {
        if (node->edge(i)->traversable())
          visible = true;
      }
      it->second->setActive(visible);
    }

    // Process edges
    std::pair<float, float> limits = std::make_pair(std::numeric_limits<float>::max(), 0.0f);
    if (showWeights || showStaticCosts || showCosts)
    {
      for (auto it = m_edges.begin(); it != m_edges.end(); ++it)
      {
        float v = 0.0f;
        if (showWeights)
          v = it->first->weight();
        else if (showStaticCosts)
          v = it->first->staticCost();
        else if (showCosts)
          v = it->first->cost();

        if (v < limits.first)
          limits.first = v;
        else if (v > limits.second)
          limits.second = v;
      }
    }

    for (auto it = m_edges.begin(); it != m_edges.end(); ++it)
    {
      Edge *edge = it->first;
      Colour edgeColour = ColourLookup::Instance().get("edge_default");

      const bool isSelected(edge == m_edgeSelection->selectedEdge()->first);

      if (showWeights || showStaticCosts || showCosts)
      {
        edgeColour = Colour(1.0f, 1.0f, 1.0f);

        float v = 0.0f;
        if (showWeights)
          v = it->first->weight();
        else if (showStaticCosts)
          v = it->first->staticCost();
        else if (showCosts)
          v = it->first->cost();

        if (v < 1.0f)
          edgeColour[1] -= v / limits.first;
        else
          edgeColour[0] -= v / limits.second;
      }

      if (showPath && Utils::IsOnPath(m_finder->path(), edge))
        edgeColour = ColourLookup::Instance().get("edge_path");

      if (isSelected)
        edgeColour = ColourLookup::Instance().get("node_selected");

      it->second->mesh()->setStaticColour(edgeColour);

      // Set this edge to invisible if it is not traversable, unless it is
      // selected
      it->second->setActive(edge->traversable() || isSelected);
    }

    // Update the menu options
    m_menu->updateViewMenu(m_viewMode);
  }

  /**
   * @brief Run path finding and show path on graph.
   */
  void PathFinder::runPathFinding()
  {
    m_finder->reset();
    m_finder->findPath(m_startNode->first, m_endNode->first);

    // Update view (set the path to visible by default after running path finding)
    m_viewMode.set(ViewMode::PATH);
    setViewMode(m_viewMode);
  }

  /**
   * @copydoc Game::gameStartup
   */
  int PathFinder::gameStartup()
  {
    // Load fonts
    m_fontMedium = TTF_OpenFont("../resources/open-sans/OpenSans-Regular.ttf", 20);

    // Set colours
    ColourLookup::Instance().add("node_start", Colour(0.0f, 1.0f, 0.0f, 1.0f)); // Green
    ColourLookup::Instance().add("node_end", Colour(1.0f, 0.0f, 0.0f, 1.0f));   // Red

    ColourLookup::Instance().add("node_selected", Colour(1.0f, 1.0f, 0.0f, 1.0f)); // Yellow
    ColourLookup::Instance().add("edge_selected", Colour(1.0f, 1.0f, 0.0f, 1.0f)); // Yellow

    ColourLookup::Instance().add("node_default", Colour(1.0f, 1.0f, 1.0f, 1.0f)); // White
    ColourLookup::Instance().add("edge_default", Colour(1.0f, 1.0f, 1.0f, 1.0f)); // White

    ColourLookup::Instance().add("node_open_list", Colour(1.0f, 0.2f, 0.5f, 1.0f));   // Pink
    ColourLookup::Instance().add("node_closed_list", Colour(1.0f, 0.5f, 0.0f, 1.0f)); // Orange
    ColourLookup::Instance().add("node_path", Colour(0.0f, 0.0f, 1.0f, 1.0f));        // Blue
    ColourLookup::Instance().add("edge_path", Colour(0.0f, 0.0f, 1.0f, 1.0f));        // Blue

    // Controls
    m_controls = new Controls(this);

    // Shaders
    ShaderProgram *colShader = new ShaderProgram();
    colShader->addShader(new VertexShader("../resources/shader/vert_simple.glsl"));
    colShader->addShader(new FragmentShader("../resources/shader/frag_col.glsl"));
    colShader->link();
    ShaderProgramLookup::Instance().add("col_shader", colShader);

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

    // Rotation mode indicator
    m_rotationModeText = new TextPane("rotation_mode", 0.08f, menuShader, m_fontMedium);
    m_rotationModeText->setTextColour(Colour(1.0f, 1.0f, 1.0f));
    m_rotationModeText->setAlignment(GetAlignment(Alignment::X_RIGHT, Alignment::Y_BOTTOM));
    m_rotationModeText->setModelMatrix(Matrix4::Translation(Vector3(1.9f, -1.9f)));
    m_rotationModeText->setText("Rotation: Fixed");
    m_menu->root()->addChild(m_rotationModeText);

    // Load graph
    const std::string graphDataFile("../resources/buckminsterfullerene.dat");

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
      RenderableObject *obj = new RenderableObject((*it)->id(), mesh, colShader);
      obj->setModelMatrix(Matrix4::Translation((*it)->position()));
      m_scene->root()->addChild(obj);

      m_nodes.push_back(std::make_pair(*it, obj));
    }

    m_startNode = m_nodes.begin();
    m_endNode = ++(m_nodes.begin());

    // Create graphical edges
    for (auto it = edges.begin(); it != edges.end(); ++it)
    {
      LineMesh *mesh = new LineMesh((*it)->nodeA()->position(), (*it)->nodeB()->position());
      RenderableObject *obj = new RenderableObject((*it)->id(), mesh, colShader);
      m_scene->root()->addChild(obj);

      m_edges.push_back(std::make_pair(*it, obj));
    }

    // Create path finder
    m_finder = new AStar(nodes);

    // Node selection menu
    m_nodeSelection = new NodeSelectionPane(this, m_fontMedium, 0.05f, m_nodes.begin(), m_nodes.end());
    m_nodeSelection->setPosition(Vector3(-0.75f, -0.95f));
    m_nodeSelection->layout();
    addEventHandler(m_nodeSelection);
    m_nodeSelection->hide();

    // Edge selection menu
    m_edgeSelection = new EdgeSelectionPane(this, m_fontMedium, 0.05f, m_edges.begin(), m_edges.end());
    m_edgeSelection->setPosition(Vector3(-0.75f, -0.95f));
    m_edgeSelection->layout();
    addEventHandler(m_edgeSelection);
    m_edgeSelection->hide();

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
      m_nodeSelection->update(dtMilliSec, Subsystem::GRAPHICS);
      m_edgeSelection->update(dtMilliSec, Subsystem::GRAPHICS);

      swapBuffers();
    }
    // Handle controls
    else if (id == m_controlLoop)
    {
      // Check rotation mode
      bool graphRotationMode = m_controls->state(S_MOVABLE_GRAPH);
      if (graphRotationMode != m_graphRotationFree)
      {
        m_graphRotationFree = graphRotationMode;
        m_rotationModeText->setText(m_graphRotationFree ? "Rotation: Free" : "Rotation: Fixed");
      }

      // Update graph rotation
      if (m_graphRotationFree)
      {
        float yaw = m_controls->analog(A_MOUSE_X) * 180.0f;
        float pitch = m_controls->analog(A_MOUSE_Y) * 180.0f;
        Quaternion rotQuat(yaw, pitch, 0.0f);
        m_scene->root()->setModelMatrix(rotQuat.rotationMatrix());
      }
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
