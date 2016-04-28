/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#ifndef _SIMULATION_GRAPHICALPATHFINDER_PATHFINDER_H_
#define _SIMULATION_GRAPHICALPATHFINDER_PATHFINDER_H_

#include <Engine_Common/Game.h>

#include <map>
#include <vector>

#include <Engine_Common/Scene.h>
#include <Engine_Graphics/RenderableObject.h>
#include <Engine_Graphics/ShaderProgram.h>

#include <Simulation_PathFinding/AStar.h>
#include <Simulation_PathFinding/Edge.h>
#include <Simulation_PathFinding/Node.h>

#include "Controls.h"
#include "OptionsMenu.h"
#include "ViewMode.h"

namespace Simulation
{
namespace GraphicalPathFinder
{
  class NodeSelectionPane;

  /**
   * @class PathFinder
   * @brief Game application for a graphical path finder.
   * @author Dan Nixon
   */
  class PathFinder : public Engine::Common::Game
  {
  public:
    typedef std::map<Simulation::PathFinding::Node *, Engine::Graphics::RenderableObject *> NodeMap;
    typedef std::map<Simulation::PathFinding::Edge *, Engine::Graphics::RenderableObject *> EdgeMap;

    bool IsOnList(const std::vector<Simulation::PathFinding::QueueableNode *> &list,
                  Simulation::PathFinding::Node *node);
    bool IsOnList(const std::vector<Simulation::PathFinding::Node *> &list, Simulation::PathFinding::Node *node);

  public:
    PathFinder();
    ~PathFinder();

    ViewMode_bitset viewMode() const
    {
      return m_viewMode;
    }

    void setViewMode(ViewMode_bitset mode = ViewMode_bitset());

  protected:
    int gameStartup();
    void gameLoop(Uint8 id, float dtMilliSec);
    void gameShutdown();

  private:
    Uint8 m_graphicsLoop; //!< Graphics update loop ID
    Uint8 m_controlLoop;  //!< Control update loop ID

    TTF_Font *m_fontMedium;
    Engine::Graphics::ShaderProgram *m_colShader; //!< Shader based on fragment colour
    Engine::Common::Scene *m_scene;               //!< Scene containing path representation
    Controls *m_controls;                         //!< Control scheme
    OptionsMenu *m_menu;                          //!< Option menu
    NodeSelectionPane *m_nodeSelection;

    NodeMap m_nodes;
    EdgeMap m_edges;
    NodeMap::iterator m_pickedNode;
    EdgeMap::iterator m_pickedEdge;

    Simulation::PathFinding::AStar *m_finder;

    ViewMode_bitset m_viewMode;
  };
}
}

#endif
