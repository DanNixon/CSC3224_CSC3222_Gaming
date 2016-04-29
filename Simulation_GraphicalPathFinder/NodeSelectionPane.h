/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#ifndef _SIMULATION_GRAPHICALPATHFINDER_NODESELECTIONPANE_H_
#define _SIMULATION_GRAPHICALPATHFINDER_NODESELECTIONPANE_H_

#include "SelectionPane.h"

namespace Simulation
{
namespace GraphicalPathFinder
{
  /**
   * @class NodeSelectionPane
   * @brief Used to select nodes in the graph.
   * @author Dan Nixon
   */
  class NodeSelectionPane : public SelectionPane
  {
  public:
    NodeSelectionPane(Engine::Common::Game *game, TTF_Font *font, float textSize, PathFinder::NodeMap::iterator begin,
                      PathFinder::NodeMap::iterator end);
    virtual ~NodeSelectionPane();

    /**
     * @brief Gets the selected node.
     * @return Iterator to selected node
     */
    inline PathFinder::NodeMap::iterator selectedNode()
    {
      return m_selectedNodeIt;
    }

    void selectNode(PathFinder::NodeMap::iterator it);

    void updateDisplay();

  protected:
    virtual void handleMenuOptionSelection(Engine::UIMenu::MenuItem *item);

  private:
    PathFinder::NodeMap::iterator m_nodesBegin; //!< Iterator to start of nodes
    PathFinder::NodeMap::iterator m_nodesEnd;   //!< Iterator to end of nodes

    PathFinder::NodeMap::iterator m_selectedNodeIt; //!< Selected node
  };
}
}

#endif
