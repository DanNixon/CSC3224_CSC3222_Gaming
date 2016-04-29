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
  class EdgeSelectionPane;

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

  public:
    PathFinder();
    ~PathFinder();

    ViewMode_bitset viewMode() const
    {
      return m_viewMode;
    }

    void setViewMode(ViewMode_bitset mode = ViewMode_bitset());

    inline void setStartNode(NodeMap::iterator start)
    {
      m_startNode = start;
      setViewMode(m_viewMode);
    }

    inline void setEndNode(NodeMap::iterator end)
    {
      m_endNode = end;
      setViewMode(m_viewMode);
    }

    void runPathFinding();

  protected:
    int gameStartup();
    void gameLoop(Uint8 id, float dtMilliSec);
    void gameShutdown();

  private:
    friend class OptionsMenu;

    Uint8 m_graphicsLoop; //!< Graphics update loop ID
    Uint8 m_controlLoop;  //!< Control update loop ID

    TTF_Font *m_fontMedium;         //!< UI font
    Engine::Common::Scene *m_scene; //!< Scene containing path representation
    Controls *m_controls;           //!< Control scheme
    OptionsMenu *m_menu;            //!< Option menu

    NodeSelectionPane *m_nodeSelection;
    EdgeSelectionPane *m_edgeSelection;

    NodeMap m_nodes;
    EdgeMap m_edges;

    NodeMap::iterator m_startNode;
    NodeMap::iterator m_endNode;

    Simulation::PathFinding::AStar *m_finder;

    ViewMode_bitset m_viewMode;
  };
}
}

#endif
