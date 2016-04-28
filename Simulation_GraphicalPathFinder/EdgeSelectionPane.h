/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#ifndef _SIMULATION_GRAPHICALPATHFINDER_EDGESELECTIONPANE_H_
#define _SIMULATION_GRAPHICALPATHFINDER_EDGESELECTIONPANE_H_

#include "SelectionPane.h"

namespace Simulation
{
namespace GraphicalPathFinder
{
  class EdgeSelectionPane : public SelectionPane
  {
  public:
    static const float DELTA_WEIGHT;

  public:
    EdgeSelectionPane(Engine::Common::Game *game, TTF_Font *font, float textSize, PathFinder::EdgeMap::iterator begin,
                      PathFinder::EdgeMap::iterator end);
    virtual ~EdgeSelectionPane();

    inline PathFinder::EdgeMap::iterator selectedEdge()
    {
      return m_selectedEdgeIt;
    }

    void selectEdge(PathFinder::EdgeMap::iterator it);

    void updateDisplay();

  protected:
    virtual void handleMenuOptionSelection(Engine::UIMenu::MenuItem *item);

  private:
    Engine::UIMenu::MenuItem *m_traversableButton;
    Engine::Graphics::TextPane *m_weightText;
    Engine::Graphics::TextPane *m_connectionText;
    Engine::Graphics::TextPane *m_costText;

    PathFinder::EdgeMap::iterator m_edgesBegin;
    PathFinder::EdgeMap::iterator m_edgesEnd;

    PathFinder::EdgeMap::iterator m_selectedEdgeIt;
  };
}
}

#endif
