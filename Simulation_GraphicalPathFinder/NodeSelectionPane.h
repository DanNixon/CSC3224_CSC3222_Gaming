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
  class NodeSelectionPane : public SelectionPane
  {
  public:
    NodeSelectionPane(Engine::Common::Game *game, TTF_Font *font, float textSize, PathFinder::NodeMap::iterator begin,
                      PathFinder::NodeMap::iterator end);
    virtual ~NodeSelectionPane();

    inline PathFinder::NodeMap::iterator selectedNode()
    {
      return m_selectedNodeIt;
    }

    void selectNode(PathFinder::NodeMap::iterator it);

  protected:
    virtual void handleMenuOptionSelection(Engine::UIMenu::MenuItem *item);

  private:
    PathFinder::NodeMap::iterator m_nodesBegin;
    PathFinder::NodeMap::iterator m_nodesEnd;

    PathFinder::NodeMap::iterator m_selectedNodeIt;
  };
}
}

#endif
