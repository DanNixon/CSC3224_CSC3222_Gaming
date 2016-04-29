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
#include <Engine_Graphics/TextPane.h>

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
    /**
     * @typedef NodeMap
     * @brief Container for path finding Node and a graphical representation of
     *        it.
     */
    typedef std::vector<std::pair<Simulation::PathFinding::Node *, Engine::Graphics::RenderableObject *>> NodeMap;

    /**
     * @typedef EdgeMap
     * @brief Container for path finding Edge and a graphical representation of
     *        it.
     */
    typedef std::vector<std::pair<Simulation::PathFinding::Edge *, Engine::Graphics::RenderableObject *>> EdgeMap;

  public:
    PathFinder();
    ~PathFinder();

    /**
     * @brief Gets the current view mode.
     * @return View mode
     */
    ViewMode_bitset viewMode() const
    {
      return m_viewMode;
    }

    void setViewMode(ViewMode_bitset mode = ViewMode_bitset());

    /**
     * @brief Sets the start node.
     * @param start Iterator to node
     */
    inline void setStartNode(NodeMap::iterator start)
    {
      m_startNode = start;
      setViewMode(m_viewMode);
    }

    /**
     * @brief Sets the end node.
     * @param end Iterator to node
     */
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
    friend class Controls;

    Uint8 m_graphicsLoop; //!< Graphics update loop ID
    Uint8 m_controlLoop;  //!< Control update loop ID

    TTF_Font *m_fontMedium;         //!< UI font
    Engine::Common::Scene *m_scene; //!< Scene containing path representation
    Controls *m_controls;           //!< Control scheme
    OptionsMenu *m_menu;            //!< Option menu

    NodeSelectionPane *m_nodeSelection; //!< Node seelction widget
    EdgeSelectionPane *m_edgeSelection; //!< Edge selection widget

    Engine::Graphics::TextPane *m_rotationModeText; //!< Text indicating rotation mode

    NodeMap m_nodes; //!< Path finding nodes and graphical representations
    EdgeMap m_edges; //!< Path finding edges and graphical representations

    NodeMap::iterator m_startNode; //!< Iterator to start node
    NodeMap::iterator m_endNode;   //!< Iterator to end node

    Simulation::PathFinding::AStar *m_finder; //!< Path finder

    ViewMode_bitset m_viewMode; //!< View mode
    bool m_graphRotationFree;   //!< Graph rotation mode
  };
}
}

#endif
