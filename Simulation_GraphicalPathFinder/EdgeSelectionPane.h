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
  /**
   * @class EdgeSelectionPane
   * @brief Used to select and adjust edges in the graph.
   * @author Dan Nixon
   */
  class EdgeSelectionPane : public SelectionPane
  {
  public:
    static const float DELTA_WEIGHT;

  public:
    EdgeSelectionPane(Engine::Common::Game *game, TTF_Font *font, float textSize, PathFinder::EdgeMap::iterator begin,
                      PathFinder::EdgeMap::iterator end);
    virtual ~EdgeSelectionPane();

    /**
     * @brief Gets the selected edge.
     * @return Iterator to selected edge
     */
    inline PathFinder::EdgeMap::iterator selectedEdge()
    {
      return m_selectedEdgeIt;
    }

    void selectEdge(PathFinder::EdgeMap::iterator it);

    void updateDisplay();

  protected:
    virtual void handleMenuOptionSelection(Engine::UIMenu::MenuItem *item);

  private:
    Engine::UIMenu::MenuItem *m_traversableButton; //!< Traversable toggle button
    Engine::Graphics::TextPane *m_weightText;      //!< Weight label
    Engine::Graphics::TextPane *m_connectionText;  //!< Connection label
    Engine::Graphics::TextPane *m_costText;        //!< COst label

    PathFinder::EdgeMap::iterator m_edgesBegin; //!< Iterator to start of edges
    PathFinder::EdgeMap::iterator m_edgesEnd;   //!< Iterator to end of edges

    PathFinder::EdgeMap::iterator m_selectedEdgeIt; //!< Selected edge
  };
}
}

#endif
